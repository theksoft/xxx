#ifndef _XXX_DLL_H_
#define _XXX_DLL_H_

/*
 * [unsafe] DOUBLY LINKED LIST
 * The unsafe version does not:
 * + check function parameters in non debug version
 * + check if a node to add is already present in the list
 * + check if a node to remove is actually present
 * Using it the wrong results with undefined behavior
 * including NULL pointer dereferencing if function argument is NULL.
 */

#include "xxx_linked_list.h"
#include <stdlib.h>

typedef struct xxx_dll_node_s {
  struct xxx_dll_node_s* next;
  struct xxx_dll_node_s* previous;
} xxx_dll_node_t;

typedef struct xxx_dll_s {
  xxx_dll_node_t* head;
  xxx_dll_node_t* tail;
  size_t count;
} xxx_dll_t;

xxx_ll_result_t xxx_dll_node_create(xxx_dll_node_t* node);
xxx_ll_result_t xxx_dll_node_destroy(xxx_dll_node_t* node);

xxx_ll_result_t xxx_dll_create(xxx_dll_t* list);
xxx_ll_result_t xxx_dll_destroy(xxx_dll_t* list);
size_t xxx_dll_count(const xxx_dll_t *list);

xxx_ll_result_t xxx_dll_push(xxx_dll_t* list, xxx_dll_node_t* node);
xxx_ll_result_t xxx_dll_push_back(xxx_dll_t* list, xxx_dll_node_t* node);
xxx_ll_result_t xxx_dll_add_ordered(xxx_dll_t* list, xxx_dll_node_t* node, xxx_ll_compare_t compare);
xxx_dll_node_t* xxx_dll_pop(xxx_dll_t* list);
xxx_dll_node_t* xxx_dll_pop_back(xxx_dll_t* list);
xxx_ll_result_t xxx_dll_remove(xxx_dll_t* list, xxx_dll_node_t* node);

xxx_ll_result_t xxx_dll_foreach(xxx_dll_t* restrict list, xxx_ll_handler_t handler, void* restrict data);
xxx_ll_result_t xxx_dll_forsome(xxx_dll_t* restrict list, xxx_ll_filter_t filter, xxx_ll_handler_t handler, void* restrict data);
xxx_dll_node_t* xxx_dll_find(xxx_dll_t* restrict list, xxx_ll_match_t match, void* restrict data);
xxx_dll_node_t* xxx_dll_has(const xxx_dll_t* list, const xxx_dll_node_t* node);

xxx_ll_result_t xxx_dll_foreach_r(xxx_dll_t* restrict list, xxx_ll_handler_t handler, void* restrict data);
xxx_ll_result_t xxx_dll_forsome_r(xxx_dll_t* restrict list, xxx_ll_filter_t filter, xxx_ll_handler_t handler, void* restrict data);
xxx_dll_node_t* xxx_dll_find_r(xxx_dll_t* restrict list, xxx_ll_match_t match, void* restrict data);

#endif
