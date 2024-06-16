#include "xxx_dll_s.h"

#include <stdlib.h>
#include <assert.h>

/*============================================================================*/

static int has(const xxx_dll_s_t* list, const xxx_dll_s_node_t* node);

/*============================================================================*/

xxx_ll_result_t xxx_dll_s_node_create(xxx_dll_s_node_t* node) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (node) {
    node->previous = node->next = NULL;
    rtn = XXX_LL_SUCCESS;
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_dll_s_node_destroy(xxx_dll_s_node_t* node) {
  return xxx_dll_s_node_create(node);
}

/*============================================================================*/

xxx_ll_result_t xxx_dll_s_create(xxx_dll_s_t* list) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list) {
    list->head = list->tail = NULL;
    list->count = 0;
    rtn = XXX_LL_SUCCESS;
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_dll_s_destroy(xxx_dll_s_t* list) {
  return xxx_dll_s_create(list);
}

/*----------------------------------------------------------------------------*/

size_t xxx_dll_s_count(const xxx_dll_s_t *list) {
  size_t rtn = 0;
  if (list) {
    rtn = list->count;
  }
  return rtn;
}

/*============================================================================*/

xxx_ll_result_t xxx_dll_s_push(xxx_dll_s_t* list, xxx_dll_s_node_t* node) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list && node) {
    rtn = XXX_LL_DUPLICATED;
    if (!has(list, node)) {
      node->previous = NULL;
      node->next = list->head;
      if (list->head) {
        list->head->previous = node;
      } else {
        assert(!list->tail);
        list->tail = node;
      }
      list->head = node;
      list->count ++;
      rtn = XXX_LL_SUCCESS;
    }
  }
  return rtn;
}

xxx_ll_result_t xxx_dll_s_push_back(xxx_dll_s_t* list, xxx_dll_s_node_t* node) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list && node) {
    rtn = XXX_LL_DUPLICATED;
    if (!has(list, node)) {
      node->next = NULL;
      node->previous = list->tail;
      if (list->tail) {
        list->tail->next = node;
      } else {
        assert(!list->head);
        list->head = node;
      }
      list->tail = node;
      list->count ++;
      rtn = XXX_LL_SUCCESS;
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_dll_s_add_ordered(xxx_dll_s_t* list, xxx_dll_s_node_t* node, xxx_ll_compare_t compare) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list && node && compare) {
    rtn = XXX_LL_DUPLICATED;
    int found = 0;
    xxx_dll_s_node_t* p;
    for (p = list->head; !found && p; p = p->next) {
      found = (p == node);
      /* insert before p */
      if (compare(node, p) < 0) break;
    }
    if (!found) {
      if (!p) {
        /* @tail and possibliy an empty list */
        node->next = NULL;
        node->previous = list->tail;
        if (list->tail) {
          list->tail->next = node;
          list->tail = node;
        } else {
          assert(!list->head);
          list->tail = list->head = node;
        }
      } else {
        /* p is not null and can be head */
        node->next = p;
        node->previous = p->previous;
        if (p->previous) {
          p->previous->next = node;
        } else {
          /* head! */
          assert(p == list->head);
          list->head = node;
        }
        p->previous = node;
      }
      list->count ++;
      rtn = XXX_LL_SUCCESS;
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_dll_s_node_t* xxx_dll_s_pop(xxx_dll_s_t* list) {
  xxx_dll_s_node_t* rtn = NULL;
  if (list) {
    rtn  = list->head;
    if (rtn) {
      list->head = rtn->next;
      if (list->tail == rtn) {
        assert(!list->head);
        list->tail = NULL;
      }
      list->count --;
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_dll_s_node_t* xxx_dll_s_pop_back(xxx_dll_s_t* list) {
  xxx_dll_s_node_t* rtn = NULL;
  if (list) {
    rtn = list->tail;
    if (rtn) {
      list->tail = rtn->previous;
      if (rtn->previous) {
        rtn->previous->next = NULL;
      } else {
        assert(rtn == list->head);
        list->head = NULL;
      }
      list->count --;
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_dll_s_remove(xxx_dll_s_t* list, xxx_dll_s_node_t* node) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list && node) {
    rtn = XXX_LL_NOT_FOUND;
    int found = 0;
    for (xxx_dll_s_node_t* p = list->head; !found && p; p = p->next) {
      found = (node == p);
    }
    if (found) {
      if (node->previous) {
        node->previous->next = node->next;
      } else {
        /* head! */
        assert(node == list->head);
        list->head = node->next;
      }
      if (node->next) {
        node->next->previous = node->previous;
      } else {
        /* tail! */
        assert(node == list->tail);
        list->tail = node->previous;
      }
      node->previous = node->next = NULL;
      list->count --;
      rtn = XXX_LL_SUCCESS;
    }
  }
  return rtn;
}

/*============================================================================*/

xxx_ll_result_t xxx_dll_s_has(const xxx_dll_s_t* list, const xxx_dll_s_node_t* node) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list && node) {
    rtn = has(list, node) ? XXX_LL_SUCCESS : XXX_LL_NOT_FOUND;
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_dll_s_foreach(xxx_dll_s_t* restrict list, xxx_ll_handler_t handler, void* restrict data) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list && handler) {
    rtn = XXX_LL_SUCCESS;
    int stop = 0;
    for (xxx_dll_s_node_t* p = list->head; !stop && p; p = p->next) {
      if ((stop = !handler(p, data))) {
        rtn = XXX_LL_STOPPED;
      }
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_dll_s_forsome(xxx_dll_s_t* restrict list, xxx_ll_filter_t filter, xxx_ll_handler_t handler, void* restrict data) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list && handler && filter) {
    rtn = XXX_LL_SUCCESS;
    int stop = 0;
    for (xxx_dll_s_node_t* p = list->head; !stop && p; p = p->next) {
      if (!filter(p, data)) continue;
      if ((stop = !handler(p, data))) {
        rtn = XXX_LL_STOPPED;
      }
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_dll_s_node_t* xxx_dll_s_find(xxx_dll_s_t* restrict list, xxx_ll_match_t match, void* restrict data) {
  xxx_dll_s_node_t* rtn = NULL;
  if (list && match) {
    for (xxx_dll_s_node_t* p = list->head; !rtn && p; p = p->next) {
      if (match(p, data)) {
        rtn = p;
      }
    }
  }
  return rtn;
}

/*============================================================================*/

xxx_ll_result_t xxx_dll_s_foreach_r(xxx_dll_s_t* restrict list, xxx_ll_handler_t handler, void* restrict data) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list && handler) {
    rtn = XXX_LL_SUCCESS;
    int stop = 0;
    for (xxx_dll_s_node_t* p = list->tail; !stop && p; p = p->previous) {
      if ((stop = !handler(p, data))) {
        rtn = XXX_LL_STOPPED;
      }
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_dll_s_forsome_r(xxx_dll_s_t* restrict list, xxx_ll_filter_t filter, xxx_ll_handler_t handler, void* restrict data) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list && handler && filter) {
    rtn = XXX_LL_SUCCESS;
    int stop = 0;
    for (xxx_dll_s_node_t* p = list->tail; !stop && p; p = p->previous) {
      if (!filter(p, data)) continue;
      if ((stop = !handler(p, data))) {
        rtn = XXX_LL_STOPPED;
      }
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_dll_s_node_t* xxx_dll_s_find_r(xxx_dll_s_t* restrict list, xxx_ll_match_t match, void* restrict data) {
  xxx_dll_s_node_t* rtn = NULL;
  if (list && match) {
    for (xxx_dll_s_node_t* p = list->tail; !rtn && p; p = p->previous) {
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

static int has(const xxx_dll_s_t* list, const xxx_dll_s_node_t* node) {
  assert(list && node);
  int found = 0;
  for (xxx_dll_s_node_t* p = list->head; !found && p; p = p->next) {
    found = (p == node);
  }
  return found;
}
