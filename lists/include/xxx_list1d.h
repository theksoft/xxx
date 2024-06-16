#ifndef _XXX_LIST1D_H_
#define _XXX_LIST1D_H_

#include "xxx_list.h"
#include <stdlib.h>

typedef struct xxx_list1d_node_s {
  struct xxx_list1d_node_s *next;
} xxx_list1d_node_t;

typedef struct xxx_list1d_s {
  xxx_list1d_node_t *head;
  size_t count;
} xxx_list1d_t;

xxx_list_result_t xxx_list1d_node_create(xxx_list1d_node_t* node);
xxx_list_result_t xxx_list1d_node_destroy(xxx_list1d_node_t* node);

xxx_list_result_t xxx_list1d_create(xxx_list1d_t* list);
xxx_list_result_t xxx_list1d_destroy(xxx_list1d_t* list);
size_t xxx_list1d_count(const xxx_list1d_t *list);

xxx_list_result_t xxx_list1d_push(xxx_list1d_t* list, xxx_list1d_node_t* node);
xxx_list_result_t xxx_list1d_push_back(xxx_list1d_t* list, xxx_list1d_node_t* node);
xxx_list_result_t xxx_list1d_add_ordered(xxx_list1d_t* list, xxx_list1d_node_t* node, xxx_list_compare_t compare);
xxx_list1d_node_t* xxx_list1d_pop(xxx_list1d_t* list);
xxx_list1d_node_t* xxx_list1d_pop_back(xxx_list1d_t* list);
xxx_list_result_t xxx_list1d_remove(xxx_list1d_t* list, xxx_list1d_node_t* node);

xxx_list_result_t xxx_list1d_has(const xxx_list1d_t* list, const xxx_list1d_node_t* node);
xxx_list_result_t xxx_list1d_foreach(xxx_list1d_t* restrict list, xxx_list_handler_t handler, void* restrict data);
xxx_list_result_t xxx_list1d_forsome(xxx_list1d_t* restrict list, xxx_list_filter_t filter, xxx_list_handler_t handler, void* restrict data);
xxx_list1d_node_t* xxx_list1d_find(xxx_list1d_t* restrict list, xxx_list_match_t match, void* restrict data);

#endif
