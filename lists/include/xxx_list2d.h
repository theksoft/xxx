#ifndef _XXX_LIST2D_H_
#define _XXX_LIST2D_H_

#include "xxx_linked_list.h"
#include <stdlib.h>

typedef struct xxx_list2d_node_s {
  struct xxx_list2d_node_s* next;
  struct xxx_list2d_node_s* previous;
} xxx_list2d_node_t;

typedef struct xxx_list2d_s {
  xxx_list2d_node_t* head;
  xxx_list2d_node_t* tail;
  size_t count;
} xxx_list2d_t;

xxx_ll_result_t xxx_list2d_node_create(xxx_list2d_node_t* node);
xxx_ll_result_t xxx_list2d_node_destroy(xxx_list2d_node_t* node);

xxx_ll_result_t xxx_list2d_create(xxx_list2d_t* list);
xxx_ll_result_t xxx_list2d_destroy(xxx_list2d_t* list);
size_t xxx_list2d_count(const xxx_list2d_t *list);

xxx_ll_result_t xxx_list2d_push(xxx_list2d_t* list, xxx_list2d_node_t* node);
xxx_ll_result_t xxx_list2d_push_back(xxx_list2d_t* list, xxx_list2d_node_t* node);
xxx_ll_result_t xxx_list2d_add_ordered(xxx_list2d_t* list, xxx_list2d_node_t* node, xxx_ll_compare_t compare);
xxx_list2d_node_t* xxx_list2d_pop(xxx_list2d_t* list);
xxx_list2d_node_t* xxx_list2d_pop_back(xxx_list2d_t* list);
xxx_ll_result_t xxx_list2d_remove(xxx_list2d_t* list, xxx_list2d_node_t* node);

xxx_ll_result_t xxx_list2d_has(const xxx_list2d_t* list, const xxx_list2d_node_t* node);
xxx_ll_result_t xxx_list2d_foreach(xxx_list2d_t* restrict list, xxx_ll_handler_t handler, void* restrict data);
xxx_ll_result_t xxx_list2d_forsome(xxx_list2d_t* restrict list, xxx_ll_filter_t filter, xxx_ll_handler_t handler, void* restrict data);
xxx_list2d_node_t* xxx_list2d_find(xxx_list2d_t* restrict list, xxx_ll_match_t match, void* restrict data);

xxx_ll_result_t xxx_list2d_foreach_r(xxx_list2d_t* restrict list, xxx_ll_handler_t handler, void* restrict data);
xxx_ll_result_t xxx_list2d_forsome_r(xxx_list2d_t* restrict list, xxx_ll_filter_t filter, xxx_ll_handler_t handler, void* restrict data);
xxx_list2d_node_t* xxx_list2d_find_r(xxx_list2d_t* restrict list, xxx_ll_match_t match, void* restrict data);

#endif
