#ifndef _XXX_DLL_S_H_
#define _XXX_DLL_S_H_

/*
 * [safe] DOUBLY LINKED LIST
 * The safe version controls:
 * + the validity of every function parameters
 * + if a node to add is already present or not in the list
 * + if a node to remove is actually present or not in the list
 */

#include "xxx_linked_list.h"
#include "xxx_dll.h"
#include <stdlib.h>

xxx_ll_result_t xxx_dll_s_node_create(xxx_dll_node_t* node);
xxx_ll_result_t xxx_dll_s_node_destroy(xxx_dll_node_t* node);

xxx_ll_result_t xxx_dll_s_create(xxx_dll_t* list);
xxx_ll_result_t xxx_dll_s_destroy(xxx_dll_t* list);
size_t xxx_dll_s_count(const xxx_dll_t *list);

xxx_ll_result_t xxx_dll_s_push(xxx_dll_t* list, xxx_dll_node_t* node);
xxx_ll_result_t xxx_dll_s_push_back(xxx_dll_t* list, xxx_dll_node_t* node);
xxx_ll_result_t xxx_dll_s_add_ordered(xxx_dll_t* list, xxx_dll_node_t* node, xxx_ll_compare_t compare);
xxx_dll_node_t* xxx_dll_s_pop(xxx_dll_t* list);
xxx_dll_node_t* xxx_dll_s_pop_back(xxx_dll_t* list);
xxx_ll_result_t xxx_dll_s_remove(xxx_dll_t* list, xxx_dll_node_t* node);

xxx_ll_result_t xxx_dll_s_foreach(xxx_dll_t* restrict list, xxx_ll_handler_t handler, void* restrict data);
xxx_ll_result_t xxx_dll_s_forsome(xxx_dll_t* restrict list, xxx_ll_filter_t filter, xxx_ll_handler_t handler, void* restrict data);
xxx_dll_node_t* xxx_dll_s_find(xxx_dll_t* restrict list, xxx_ll_match_t match, void* restrict data);
xxx_dll_node_t* xxx_dll_s_has(const xxx_dll_t* list, const xxx_dll_node_t* node);

xxx_ll_result_t xxx_dll_s_foreach_r(xxx_dll_t* restrict list, xxx_ll_handler_t handler, void* restrict data);
xxx_ll_result_t xxx_dll_s_forsome_r(xxx_dll_t* restrict list, xxx_ll_filter_t filter, xxx_ll_handler_t handler, void* restrict data);
xxx_dll_node_t* xxx_dll_s_find_r(xxx_dll_t* restrict list, xxx_ll_match_t match, void* restrict data);

#endif
