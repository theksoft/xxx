#include "xxx_sll_s.h"

#include <stdlib.h>
#include <assert.h>

/*============================================================================*/

static int has(const xxx_sll_s_t* list, const xxx_sll_s_node_t* node);

/*============================================================================*/

xxx_ll_result_t xxx_sll_s_node_create(xxx_sll_s_node_t* node) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (node) {
    node->next = NULL;
    rtn = XXX_LL_SUCCESS;
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_sll_s_node_destroy(xxx_sll_s_node_t* node) {
  return xxx_sll_s_node_create(node);
}

/*============================================================================*/

xxx_ll_result_t xxx_sll_s_create(xxx_sll_s_t* list) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list) {
    list->head = NULL;
    list->count = 0;
    rtn = XXX_LL_SUCCESS;
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_sll_s_destroy(xxx_sll_s_t* list) {
  return xxx_sll_s_create(list);
}

/*----------------------------------------------------------------------------*/

size_t xxx_sll_s_count(const xxx_sll_s_t *list) {
  size_t rtn = 0;
  if (list) {
    rtn = list->count;
  }
  return rtn;
}

/*============================================================================*/

xxx_ll_result_t xxx_sll_s_push(xxx_sll_s_t* list, xxx_sll_s_node_t* node) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list && node) {
    rtn = XXX_LL_DUPLICATED;
    if (!has(list, node)) {
      node->next = list->head;
      list->head = node;
      list->count ++;
      rtn = XXX_LL_SUCCESS;
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_sll_s_push_back(xxx_sll_s_t* list, xxx_sll_s_node_t* node) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list && node) {
    rtn = XXX_LL_DUPLICATED;
    int found = 0;
    xxx_sll_s_node_t* p;
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
      rtn = XXX_LL_SUCCESS;
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_sll_s_add_ordered(xxx_sll_s_t* list, xxx_sll_s_node_t* node, xxx_ll_compare_t compare) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list && node && compare) {
    rtn = XXX_LL_DUPLICATED;
    int found = 0;
    xxx_sll_s_node_t* p;
    xxx_sll_s_node_t* prev;
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
      rtn = XXX_LL_SUCCESS;
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_sll_s_node_t* xxx_sll_s_pop(xxx_sll_s_t* list) {
  xxx_sll_s_node_t* rtn = NULL;
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

xxx_sll_s_node_t* xxx_sll_s_pop_back(xxx_sll_s_t* list) {
  xxx_sll_s_node_t* rtn = NULL;
  if (list) {
    xxx_sll_s_node_t* p;
    xxx_sll_s_node_t* prev;
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

xxx_ll_result_t xxx_sll_s_remove(xxx_sll_s_t* list, xxx_sll_s_node_t* node) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list && node) {
    rtn = XXX_LL_NOT_FOUND;
    int found = 0;
    xxx_sll_s_node_t* p;
    xxx_sll_s_node_t* prev;
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
      rtn = XXX_LL_SUCCESS;
    }
  }
  return rtn;
}

/*============================================================================*/

xxx_ll_result_t xxx_sll_s_has(const xxx_sll_s_t* list, const xxx_sll_s_node_t* node) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list && node) {
    rtn = has(list, node) ? XXX_LL_SUCCESS : XXX_LL_NOT_FOUND;
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_sll_s_foreach(xxx_sll_s_t* restrict list, xxx_ll_handler_t handler, void* restrict data) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list && handler) {
    rtn = XXX_LL_SUCCESS;
    int stop = 0;
    for (xxx_sll_s_node_t* p = list->head; !stop && p; p = p->next) {
      if ((stop = !handler(p, data))) {
        rtn = XXX_LL_STOPPED;
      }
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_sll_s_forsome(xxx_sll_s_t* restrict list, xxx_ll_filter_t filter, xxx_ll_handler_t handler, void* restrict data) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list && handler && filter) {
    rtn = XXX_LL_SUCCESS;
    int stop = 0;
    for (xxx_sll_s_node_t* p = list->head; !stop && p; p = p->next) {
      if (!filter(p, data)) continue;
      if ((stop = !handler(p, data))) {
        rtn = XXX_LL_STOPPED;
      }
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_sll_s_node_t* xxx_sll_s_find(xxx_sll_s_t* restrict list, xxx_ll_match_t match, void* restrict data) {
  xxx_sll_s_node_t* rtn = NULL;
  if (list && match) {
    for (xxx_sll_s_node_t* p = list->head; !rtn && p; p = p->next) {
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

static int has(const xxx_sll_s_t* list, const xxx_sll_s_node_t* node) {
  assert(list && node);
  int found = 0;
  for (xxx_sll_s_node_t* p = list->head; !found && p; p = p->next) {
    found = (p == node);
  }
  return found;
}
