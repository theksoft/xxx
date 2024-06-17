#include "xxx_dll_s.h"

#include <stdlib.h>
#include <assert.h>

/*============================================================================*/

xxx_ll_result_t xxx_dll_s_node_create(xxx_dll_node_t* node) {
  return (node) ? xxx_dll_node_create(node) : XXX_LL_ERROR;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_dll_s_node_destroy(xxx_dll_node_t* node) {
  return xxx_dll_s_node_create(node);
}

/*============================================================================*/

xxx_ll_result_t xxx_dll_s_create(xxx_dll_t* list) {
  return (list) ? xxx_dll_create(list) : XXX_LL_ERROR;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_dll_s_destroy(xxx_dll_t* list) {
  return xxx_dll_s_create(list);
}

/*----------------------------------------------------------------------------*/

size_t xxx_dll_s_count(const xxx_dll_t *list) {
  return (list) ? xxx_dll_count(list) : 0;
}

/*============================================================================*/

xxx_ll_result_t xxx_dll_s_push(xxx_dll_t* list, xxx_dll_node_t* node) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list && node && !node->next && !node->previous) {
    if (list->tail != node && list->head != node) {
      rtn = xxx_dll_push(list, node);
    }
  }
  return rtn;
}

xxx_ll_result_t xxx_dll_s_push_back(xxx_dll_t* list, xxx_dll_node_t* node) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list && node && !node->next && !node->previous) {
    if (list->tail != node && list->head != node) {
      rtn = xxx_dll_push_back(list, node);
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_dll_s_add_ordered(xxx_dll_t* list, xxx_dll_node_t* node, xxx_ll_compare_t compare) {
  xxx_ll_result_t rtn = XXX_LL_ERROR;
  if (list && node && !node->next && !node->previous && compare) {
    if (list->tail != node && list->head != node) {
      rtn = xxx_dll_add_ordered(list, node, compare);
    }
  }
  return rtn;
}

/*----------------------------------------------------------------------------*/

xxx_dll_node_t* xxx_dll_s_pop(xxx_dll_t* list) {
  return (list) ? xxx_dll_pop(list) : NULL;
}

/*----------------------------------------------------------------------------*/

xxx_dll_node_t* xxx_dll_s_pop_back(xxx_dll_t* list) {
  return (list) ? xxx_dll_pop_back(list) : NULL;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_dll_s_remove(xxx_dll_t* list, xxx_dll_node_t* node) {
  return (list && node && xxx_dll_has(list, node)) ? xxx_dll_remove(list, node) : XXX_LL_ERROR;
}

/*============================================================================*/

xxx_ll_result_t xxx_dll_s_foreach(xxx_dll_t* restrict list, xxx_ll_handler_t handler, void* restrict data) {
  return (list && handler) ? xxx_dll_foreach(list, handler, data) : XXX_LL_ERROR;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_dll_s_forsome(xxx_dll_t* restrict list, xxx_ll_filter_t filter, xxx_ll_handler_t handler, void* restrict data) {
  return (list && handler && filter) ? xxx_dll_forsome(list, filter, handler, data) : XXX_LL_ERROR;
}

/*----------------------------------------------------------------------------*/

xxx_dll_node_t* xxx_dll_s_find(xxx_dll_t* restrict list, xxx_ll_match_t match, void* restrict data) {
  return (list && match) ? xxx_dll_find(list, match, data) : NULL;
}

/*----------------------------------------------------------------------------*/

xxx_dll_node_t* xxx_dll_s_has(const xxx_dll_t* list, const xxx_dll_node_t* node) {
  return (list && node) ? xxx_dll_has(list, node) : NULL;
}

/*============================================================================*/

xxx_ll_result_t xxx_dll_s_foreach_r(xxx_dll_t* restrict list, xxx_ll_handler_t handler, void* restrict data) {
  return (list && handler) ? xxx_dll_foreach_r(list, handler, data) : XXX_LL_ERROR;
}

/*----------------------------------------------------------------------------*/

xxx_ll_result_t xxx_dll_s_forsome_r(xxx_dll_t* restrict list, xxx_ll_filter_t filter, xxx_ll_handler_t handler, void* restrict data) {
  return (list && handler && filter) ? xxx_dll_forsome_r(list, filter, handler, data) : XXX_LL_ERROR;
}

/*----------------------------------------------------------------------------*/

xxx_dll_node_t* xxx_dll_s_find_r(xxx_dll_t* restrict list, xxx_ll_match_t match, void* restrict data) {
  return (list && match) ? xxx_dll_find_r(list, match, data) : NULL;
}
