#include "xxx_sll_s.h"

#include <stdlib.h>
#include <assert.h>

/*============================================================================*/

xxx_ll_result_t xxx_sll_s_node_create(xxx_sll_node_t* node) {
  return (node) ? xxx_sll_node_create(node) : XXX_LL_ERROR;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_sll_s_node_destroy(xxx_sll_node_t* node) {
  return xxx_sll_s_node_create(node);
}

/*============================================================================*/

xxx_ll_result_t xxx_sll_s_create(xxx_sll_t* list) {
  return (list) ? xxx_sll_create(list) : XXX_LL_ERROR;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_sll_s_destroy(xxx_sll_t* list) {
  return xxx_sll_s_create(list);
}

/*----------------------------------------------------------------------------*/

size_t xxx_sll_s_count(const xxx_sll_t *list) {
  return (list) ? xxx_sll_count(list) : 0;
}

/*============================================================================*/

xxx_ll_result_t xxx_sll_s_push(xxx_sll_t* list, xxx_sll_node_t* node) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list && node && !node->next) {
    if (!xxx_sll_has(list, node)) {
      rtn = xxx_sll_push(list, node);
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

/* Reimplementd in order to avoid to mutalize the search traversal            */
xxx_ll_result_t xxx_sll_s_push_back(xxx_sll_t* list, xxx_sll_node_t* node) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list && node && !node->next) {
    xxx_sll_node_t* p;
    for (p = list->head; p && p->next; p = p->next) {}
    if (p != node) {
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

/* Reimplementd in order to mutalize the search traversal.
 * It is assumed elements are ordered and that passed the node to insert rank
 * the latter cannot be found.
 */
xxx_ll_result_t xxx_sll_s_add_ordered(xxx_sll_t* list, xxx_sll_node_t* node, xxx_ll_compare_t compare) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list && node && !node->next && compare) {
    int found = 0;
    xxx_sll_node_t* p;
    xxx_sll_node_t* prev;
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

xxx_sll_node_t* xxx_sll_s_pop(xxx_sll_t* list) {
  return (list) ? xxx_sll_pop(list) : NULL;
}

/*----------------------------------------------------------------------------*/

xxx_sll_node_t* xxx_sll_s_pop_back(xxx_sll_t* list) {
  return (list) ? xxx_sll_pop_back(list) : NULL;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_sll_s_remove(xxx_sll_t* list, xxx_sll_node_t* node) {
  return (list && node) ? xxx_sll_remove(list, node) : XXX_LL_ERROR;
}

/*============================================================================*/

xxx_ll_result_t xxx_sll_s_foreach(xxx_sll_t* restrict list, xxx_ll_handler_t handler, void* restrict data) {
  return (list && handler) ? xxx_sll_foreach(list, handler, data) : XXX_LL_ERROR;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_sll_s_forsome(xxx_sll_t* restrict list, xxx_ll_filter_t filter, xxx_ll_handler_t handler, void* restrict data) {
  return (list && handler && filter) ? xxx_sll_forsome(list, filter, handler, data) : XXX_LL_ERROR;
}

/*----------------------------------------------------------------------------*/

xxx_sll_node_t* xxx_sll_s_find(xxx_sll_t* restrict list, xxx_ll_match_t match, void* restrict data) {
  return (list && match) ? xxx_sll_find(list, match, data) : NULL;
}

/*----------------------------------------------------------------------------*/

xxx_sll_node_t* xxx_sll_s_has(const xxx_sll_t* list, const xxx_sll_node_t* node) {
  return (list && node) ? xxx_sll_has(list, node) : NULL;
}
