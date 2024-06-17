#include "xxx_dll.h"

#include <stdlib.h>
#include <assert.h>

/*============================================================================*/

xxx_ll_result_t xxx_dll_node_create(xxx_dll_node_t* node) {
  assert(node);
  node->previous = node->next = NULL;
  return XXX_LL_SUCCESS;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_dll_node_destroy(xxx_dll_node_t* node) {
  assert(node);
  return xxx_dll_node_create(node);
}

/*============================================================================*/

xxx_ll_result_t xxx_dll_create(xxx_dll_t* list) {
  assert(list);
  list->head = list->tail = NULL;
  list->count = 0;
  return XXX_LL_SUCCESS;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_dll_destroy(xxx_dll_t* list) {
  assert(list);
  return xxx_dll_create(list);
}

/*----------------------------------------------------------------------------*/

size_t xxx_dll_count(const xxx_dll_t *list) {
  assert(list);
  return list->count;
}

/*============================================================================*/

xxx_ll_result_t xxx_dll_push(xxx_dll_t* list, xxx_dll_node_t* node) {
  assert(list);
  assert(node && !node->next && !node->previous);
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
  return XXX_LL_SUCCESS;
}

xxx_ll_result_t xxx_dll_push_back(xxx_dll_t* list, xxx_dll_node_t* node) {
  assert(list);
  assert(node && !node->next && !node->previous);
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
  return XXX_LL_SUCCESS;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_dll_add_ordered(xxx_dll_t* list, xxx_dll_node_t* node, xxx_ll_compare_t compare) {
  assert(list);
  assert(node && !node->next && !node->previous);
  xxx_dll_node_t* p;
  for (p = list->head; p; p = p->next) {
    /* insert before p */
    if (compare(node, p) < 0) break;
  }
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
  return XXX_LL_SUCCESS;
}

/*----------------------------------------------------------------------------*/

xxx_dll_node_t* xxx_dll_pop(xxx_dll_t* list) {
  assert(list);
  xxx_dll_node_t* rtn = list->head;
  if (rtn) {
    list->head = rtn->next;
    if (list->tail == rtn) {
      assert(!list->head);
      list->tail = NULL;
    }
    rtn->previous = rtn->next = NULL;
    list->count --;
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_dll_node_t* xxx_dll_pop_back(xxx_dll_t* list) {
  assert(list);
  xxx_dll_node_t* rtn = list->tail;
  if (rtn) {
    list->tail = rtn->previous;
    if (rtn->previous) {
      rtn->previous->next = NULL;
    } else {
      assert(rtn == list->head);
      list->head = NULL;
    }
    rtn->previous = rtn->next = NULL;
    list->count --;
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_dll_remove(xxx_dll_t* list, xxx_dll_node_t* node) {
  assert(list && node);
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
  return XXX_LL_SUCCESS;
}

/*============================================================================*/

xxx_ll_result_t xxx_dll_foreach(xxx_dll_t* restrict list, xxx_ll_handler_t handler, void* restrict data) {
  assert(list && handler);
  xxx_ll_result_t rtn = XXX_LL_SUCCESS;
  int stop = 0;
  for (xxx_dll_node_t* p = list->head; !stop && p; p = p->next) {
    if ((stop = !handler(p, data))) {
      rtn = XXX_LL_STOPPED;
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_dll_forsome(xxx_dll_t* restrict list, xxx_ll_filter_t filter, xxx_ll_handler_t handler, void* restrict data) {
  assert(list && handler && filter);
  xxx_ll_result_t rtn = XXX_LL_SUCCESS;
  int stop = 0;
  for (xxx_dll_node_t* p = list->head; !stop && p; p = p->next) {
    if (!filter(p, data)) continue;
    if ((stop = !handler(p, data))) {
      rtn = XXX_LL_STOPPED;
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_dll_node_t* xxx_dll_find(xxx_dll_t* restrict list, xxx_ll_match_t match, void* restrict data) {
  assert(list && match);
  xxx_dll_node_t* rtn = NULL;
  for (xxx_dll_node_t* p = list->head; !rtn && p; p = p->next) {
    if (match(p, data)) {
      rtn = p;
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_dll_node_t* xxx_dll_has(const xxx_dll_t* list, const xxx_dll_node_t* node) {
  assert(list && node);
  xxx_dll_node_t* rtn = NULL;
  for (xxx_dll_node_t* p = list->head; !rtn && p; p = p->next) {
    if (p == node) {
      rtn = p;
    }
  }
  return rtn;
}

/*============================================================================*/

xxx_ll_result_t xxx_dll_foreach_r(xxx_dll_t* restrict list, xxx_ll_handler_t handler, void* restrict data) {
  assert(list && handler);
  xxx_ll_result_t rtn = XXX_LL_SUCCESS;
  int stop = 0;
  for (xxx_dll_node_t* p = list->tail; !stop && p; p = p->previous) {
    if ((stop = !handler(p, data))) {
      rtn = XXX_LL_STOPPED;
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_dll_forsome_r(xxx_dll_t* restrict list, xxx_ll_filter_t filter, xxx_ll_handler_t handler, void* restrict data) {
  assert(list && handler && filter);
  xxx_ll_result_t rtn = XXX_LL_SUCCESS;
  int stop = 0;
  for (xxx_dll_node_t* p = list->tail; !stop && p; p = p->previous) {
    if (!filter(p, data)) continue;
    if ((stop = !handler(p, data))) {
      rtn = XXX_LL_STOPPED;
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_dll_node_t* xxx_dll_find_r(xxx_dll_t* restrict list, xxx_ll_match_t match, void* restrict data) {
  assert(list && match);
  xxx_dll_node_t* rtn = NULL;
  for (xxx_dll_node_t* p = list->tail; !rtn && p; p = p->previous) {
    if (match(p, data)) {
      rtn = p;
    }
  }
  return rtn;
}
