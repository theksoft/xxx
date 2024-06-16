#ifndef _XXX_SLL_H_
#define _XXX_SLL_H_

/*
 * [unsafe] SINGLY LINKED LIST
 * The unsafe version does not:
 * + check function parameters in non debug version
 * + check if a node to add is already present in the list
 * + check if a node to remove is actually present
 * Using it the wrong results with undefined behavior
 * including NULL pointer dereferencing if function argument is NULL.
 */

#include "xxx_linked_list.h"
#include <stdlib.h>

typedef struct xxx_sll_node_s {
  struct xxx_sll_node_s *next;
} xxx_sll_node_t;

typedef struct xxx_sll_s {
  xxx_sll_node_t *head;
  size_t count;
} xxx_sll_t;

xxx_ll_result_t xxx_sll_node_create(xxx_sll_node_t* node);
xxx_ll_result_t xxx_sll_node_destroy(xxx_sll_node_t* node);

xxx_ll_result_t xxx_sll_create(xxx_sll_t* list);
xxx_ll_result_t xxx_sll_destroy(xxx_sll_t* list);
size_t xxx_sll_count(const xxx_sll_t *list);

xxx_ll_result_t xxx_sll_push(xxx_sll_t* list, xxx_sll_node_t* node);
xxx_ll_result_t xxx_sll_push_back(xxx_sll_t* list, xxx_sll_node_t* node);
xxx_ll_result_t xxx_sll_add_ordered(xxx_sll_t* list, xxx_sll_node_t* node, xxx_ll_compare_t compare);
xxx_sll_node_t* xxx_sll_pop(xxx_sll_t* list);
xxx_sll_node_t* xxx_sll_pop_back(xxx_sll_t* list);
xxx_ll_result_t xxx_sll_remove(xxx_sll_t* list, xxx_sll_node_t* node);

xxx_ll_result_t xxx_sll_foreach(xxx_sll_t* restrict list, xxx_ll_handler_t handler, void* restrict data);
xxx_ll_result_t xxx_sll_forsome(xxx_sll_t* restrict list, xxx_ll_filter_t filter, xxx_ll_handler_t handler, void* restrict data);
xxx_sll_node_t* xxx_sll_find(xxx_sll_t* restrict list, xxx_ll_match_t match, void* restrict data);
xxx_sll_node_t* xxx_sll_has(const xxx_sll_t* list, const xxx_sll_node_t* node);

#endif
