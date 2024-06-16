#include "xxx_list1d.h"

#include <stdlib.h>
#include <assert.h>

/*============================================================================*/

static int has(const xxx_list1d_t* list, const xxx_list1d_node_t* node);

/*============================================================================*/

xxx_list_result_t xxx_list1d_node_create(xxx_list1d_node_t* node) {
  xxx_list_result_t rtn = XXX_LIST_ERROR;
  if (node) {
    node->next = NULL;
    rtn = XXX_LIST_SUCCESS;
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_list_result_t xxx_list1d_node_destroy(xxx_list1d_node_t* node) {
  return xxx_list1d_node_create(node);
}

/*============================================================================*/

xxx_list_result_t xxx_list1d_create(xxx_list1d_t* list) {
  xxx_list_result_t rtn = XXX_LIST_ERROR;
  if (list) {
    list->head = NULL;
    list->count = 0;
    rtn = XXX_LIST_SUCCESS;
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_list_result_t xxx_list1d_destroy(xxx_list1d_t* list) {
  return xxx_list1d_create(list);
}

/*----------------------------------------------------------------------------*/

size_t xxx_list1d_count(const xxx_list1d_t *list) {
  size_t rtn = 0;
  if (list) {
    rtn = list->count;
  }
  return rtn;
}

/*============================================================================*/

xxx_list_result_t xxx_list1d_push(xxx_list1d_t* list, xxx_list1d_node_t* node) {
  xxx_list_result_t rtn = XXX_LIST_ERROR;
  if (list && node) {
    rtn = XXX_LIST_DUPLICATED;
    if (!has(list, node)) {
      node->next = list->head;
      list->head = node;
      list->count ++;
      rtn = XXX_LIST_SUCCESS;
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_list_result_t xxx_list1d_push_back(xxx_list1d_t* list, xxx_list1d_node_t* node) {
  xxx_list_result_t rtn = XXX_LIST_ERROR;
  if (list && node) {
    rtn = XXX_LIST_DUPLICATED;
    int found = 0;
    xxx_list1d_node_t* p;
    for (p = list->head; !found && p && p->next; p = p->next) {
      found = (node == p);
    }
    if (!found && p != node) {
      node->next = NULL;
      if (p) {
        p->next = node;
      } else {
        assert(!list->head);
        list->head = node;
      }
      list->count ++;
      rtn = XXX_LIST_SUCCESS;
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_list_result_t xxx_list1d_add_ordered(xxx_list1d_t* list, xxx_list1d_node_t* node, xxx_list_compare_t compare) {
  xxx_list_result_t rtn = XXX_LIST_ERROR;
  if (list && node && compare) {
    rtn = XXX_LIST_DUPLICATED;
    int found = 0;
    xxx_list1d_node_t* p;
    xxx_list1d_node_t* prev;
    for (prev = NULL, p = list->head; !found && p; prev = p, p = p->next) {
      found = (node == p);
      /* insert before p */
      if (compare(node, p) < 0) break;
    }
    if (!found) {
      if (!prev) {
        /* insert @head */
        assert( p == list->head);
        node->next = list->head;
        list->head = node;
      } else {
        /* prev is not null */
        node->next = p;
        prev->next = node;
      }
      list->count ++;
      rtn = XXX_LIST_SUCCESS;
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_list1d_node_t* xxx_list1d_pop(xxx_list1d_t* list) {
  xxx_list1d_node_t* rtn = NULL;
  if (list) {
    rtn  = list->head;
    if (rtn) {
      list->head = rtn->next;
      rtn->next = NULL;
      list->count --;
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_list1d_node_t* xxx_list1d_pop_back(xxx_list1d_t* list) {
  xxx_list1d_node_t* rtn = NULL;
  if (list) {
    xxx_list1d_node_t* p;
    xxx_list1d_node_t* prev;
    for (prev = NULL, p = list->head; p && p->next; prev = p, p = p->next) {}
    if ((rtn = p)) {
      if (prev) {
        prev->next = NULL;
      } else {
        assert(p == list->head);
        list->head = NULL;
      }
      list->count --;
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_list_result_t xxx_list1d_remove(xxx_list1d_t* list, xxx_list1d_node_t* node) {
  xxx_list_result_t rtn = XXX_LIST_ERROR;
  if (list && node) {
    rtn = XXX_LIST_NOT_FOUND;
    int found = 0;
    xxx_list1d_node_t* p;
    xxx_list1d_node_t* prev;
    for (prev = NULL, p = list->head; p; prev = p, p = p->next) {
      if ((found = (node == p))) break;
    }
    if (found) {
      if (prev) {
        prev->next = p->next;
      } else {
        /* head! */
        assert(node == list->head);
        list->head = node->next;
      }
      node->next = NULL;
      list->count --;
      rtn = XXX_LIST_SUCCESS;
    }
  }
  return rtn;
}

/*============================================================================*/

xxx_list_result_t xxx_list1d_has(const xxx_list1d_t* list, const xxx_list1d_node_t* node) {
  xxx_list_result_t rtn = XXX_LIST_ERROR;
  if (list && node) {
    rtn = has(list, node) ? XXX_LIST_SUCCESS : XXX_LIST_NOT_FOUND;
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_list_result_t xxx_list1d_foreach(xxx_list1d_t* restrict list, xxx_list_handler_t handler, void* restrict data) {
  xxx_list_result_t rtn = XXX_LIST_ERROR;
  if (list && handler) {
    rtn = XXX_LIST_SUCCESS;
    int stop = 0;
    for (xxx_list1d_node_t* p = list->head; !stop && p; p = p->next) {
      if ((stop = !handler(p, data))) {
        rtn = XXX_LIST_STOPPED;
      }
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_list_result_t xxx_list1d_forsome(xxx_list1d_t* restrict list, xxx_list_filter_t filter, xxx_list_handler_t handler, void* restrict data) {
  xxx_list_result_t rtn = XXX_LIST_ERROR;
  if (list && handler && filter) {
    rtn = XXX_LIST_SUCCESS;
    int stop = 0;
    for (xxx_list1d_node_t* p = list->head; !stop && p; p = p->next) {
      if (!filter(p, data)) continue;
      if ((stop = !handler(p, data))) {
        rtn = XXX_LIST_STOPPED;
      }
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_list1d_node_t* xxx_list1d_find(xxx_list1d_t* restrict list, xxx_list_match_t match, void* restrict data) {
  xxx_list1d_node_t* rtn = NULL;
  if (list && match) {
    for (xxx_list1d_node_t* p = list->head; !rtn && p; p = p->next) {
      if (match(p, data)) {
        rtn = p;
      }
    }
  }
  return rtn;
}

/*============================================================================*
 * INTERNALS                                                                  *
 *============================================================================*/

static int has(const xxx_list1d_t* list, const xxx_list1d_node_t* node) {
  assert(list && node);
  int found = 0;
  for (xxx_list1d_node_t* p = list->head; !found && p; p = p->next) {
    found = (p == node);
  }
  return found;
}
