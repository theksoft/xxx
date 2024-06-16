#include "xxx_sll.h"

#include <stdlib.h>
#include <assert.h>

/*============================================================================*/

xxx_ll_result_t xxx_sll_node_create(xxx_sll_node_t* node) {
  assert(node);
  node->next = NULL;
  return XXX_LL_SUCCESS;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_sll_node_destroy(xxx_sll_node_t* node) {
  assert(node);
  return xxx_sll_node_create(node);
}

/*============================================================================*/

xxx_ll_result_t xxx_sll_create(xxx_sll_t* list) {
  assert(list);
  list->head = NULL;
  list->count = 0;
  return XXX_LL_SUCCESS;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_sll_destroy(xxx_sll_t* list) {
  assert(list);
  return xxx_sll_create(list);
}

/*----------------------------------------------------------------------------*/

size_t xxx_sll_count(const xxx_sll_t *list) {
  assert(list);
  return list->count;
}

/*============================================================================*/

xxx_ll_result_t xxx_sll_push(xxx_sll_t* list, xxx_sll_node_t* node) {
  assert(list);
  assert(node && !node->next);
  node->next = list->head;
  list->head = node;
  list->count ++;
  return XXX_LL_SUCCESS;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_sll_push_back(xxx_sll_t* list, xxx_sll_node_t* node) {
  assert(list);
  assert(node && !node->next);
  xxx_sll_node_t* p;
  for (p = list->head; p && p->next; p = p->next) {}
  node->next = NULL;
  if (p) {
    p->next = node;
  } else {
    assert(!list->head);
    list->head = node;
  }
  list->count ++;
  return XXX_LL_SUCCESS;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_sll_add_ordered(xxx_sll_t* list, xxx_sll_node_t* node, xxx_ll_compare_t compare) {
  assert(list);
  assert(node && !node->next);
  assert(compare);
  xxx_sll_node_t* p;
  xxx_sll_node_t* prev;
  for (prev = NULL, p = list->head; p; prev = p, p = p->next) {
    /* insert before p */
    if (compare(node, p) < 0) break;
  }
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
  return XXX_LL_SUCCESS;
}

/*----------------------------------------------------------------------------*/

xxx_sll_node_t* xxx_sll_pop(xxx_sll_t* list) {
  assert(list);
  xxx_sll_node_t* rtn = list->head;
  if (rtn) {
    list->head = rtn->next;
    rtn->next = NULL;
    list->count --;
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_sll_node_t* xxx_sll_pop_back(xxx_sll_t* list) {
  assert(list);
  xxx_sll_node_t* rtn = NULL;
  xxx_sll_node_t* p;
  xxx_sll_node_t* prev;
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
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_sll_remove(xxx_sll_t* list, xxx_sll_node_t* node) {
  assert(list && node);
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  int found = 0;
  xxx_sll_node_t* p;
  xxx_sll_node_t* prev;
  /* must find the node for getting the previous */
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
  return rtn;
}

/*============================================================================*/

xxx_ll_result_t xxx_sll_foreach(xxx_sll_t* restrict list, xxx_ll_handler_t handler, void* restrict data) {
  assert(list && handler);
  xxx_ll_result_t rtn = XXX_LL_SUCCESS;
  int stop = 0;
  for (xxx_sll_node_t* p = list->head; !stop && p; p = p->next) {
    if ((stop = !handler(p, data))) {
      rtn = XXX_LL_STOPPED;
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_sll_forsome(xxx_sll_t* restrict list, xxx_ll_filter_t filter, xxx_ll_handler_t handler, void* restrict data) {
  xxx_ll_result_t rtn = XXX_LL_SUCCESS;
  assert(list && handler && filter);
  int stop = 0;
  for (xxx_sll_node_t* p = list->head; !stop && p; p = p->next) {
    if (!filter(p, data)) continue;
    if ((stop = !handler(p, data))) {
      rtn = XXX_LL_STOPPED;
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_sll_node_t* xxx_sll_find(xxx_sll_t* restrict list, xxx_ll_match_t match, void* restrict data) {
  xxx_sll_node_t* rtn = NULL;
  assert(list && match);
  for (xxx_sll_node_t* p = list->head; !rtn && p; p = p->next) {
    if (match(p, data)) {
      rtn = p;
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_sll_node_t* xxx_sll_has(const xxx_sll_t* list, const xxx_sll_node_t* node) {
  assert(list && node);
  xxx_sll_node_t* rtn = NULL;
  for (xxx_sll_node_t* p = list->head; !rtn && p; p = p->next) {
    if (p == node) {
      rtn = p;
    }
  }
  return rtn;
}
