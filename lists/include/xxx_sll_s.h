#ifndef _XXX_SLL_S_H_
#define _XXX_SLL_S_H_

/*
 * [safe] SINGLY LINKED LIST
 * The safe version controls:
 * + the validity of every function parameters
 * + if a node to add is already present or not in the list
 * + if a node to remove is actually present or not in the list
 */

#include "xxx_linked_list.h"
#include <stdlib.h>

typedef struct xxx_sll_s_node_s {
  struct xxx_sll_s_node_s *next;
} xxx_sll_s_node_t;

typedef struct xxx_sll_s_s {
  xxx_sll_s_node_t *head;
  size_t count;
} xxx_sll_s_t;

xxx_ll_result_t xxx_sll_s_node_create(xxx_sll_s_node_t* node);
xxx_ll_result_t xxx_sll_s_node_destroy(xxx_sll_s_node_t* node);

xxx_ll_result_t xxx_sll_s_create(xxx_sll_s_t* list);
xxx_ll_result_t xxx_sll_s_destroy(xxx_sll_s_t* list);
size_t xxx_sll_s_count(const xxx_sll_s_t *list);

xxx_ll_result_t xxx_sll_s_push(xxx_sll_s_t* list, xxx_sll_s_node_t* node);
xxx_ll_result_t xxx_sll_s_push_back(xxx_sll_s_t* list, xxx_sll_s_node_t* node);
xxx_ll_result_t xxx_sll_s_add_ordered(xxx_sll_s_t* list, xxx_sll_s_node_t* node, xxx_ll_compare_t compare);
xxx_sll_s_node_t* xxx_sll_s_pop(xxx_sll_s_t* list);
xxx_sll_s_node_t* xxx_sll_s_pop_back(xxx_sll_s_t* list);
xxx_ll_result_t xxx_sll_s_remove(xxx_sll_s_t* list, xxx_sll_s_node_t* node);

xxx_ll_result_t xxx_sll_s_has(const xxx_sll_s_t* list, const xxx_sll_s_node_t* node);
xxx_ll_result_t xxx_sll_s_foreach(xxx_sll_s_t* restrict list, xxx_ll_handler_t handler, void* restrict data);
xxx_ll_result_t xxx_sll_s_forsome(xxx_sll_s_t* restrict list, xxx_ll_filter_t filter, xxx_ll_handler_t handler, void* restrict data);
xxx_sll_s_node_t* xxx_sll_s_find(xxx_sll_s_t* restrict list, xxx_ll_match_t match, void* restrict data);

#endif
