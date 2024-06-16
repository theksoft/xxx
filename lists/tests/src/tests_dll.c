#include "tests.h"
#include "tests_dll.h"
#include "xxx_dll.h"
#include <CUnit/CUnit.h>
#include <stdlib.h>
#include <assert.h>

static void create_nodes(xxx_dll_node_t* table, size_t count);
static void create_list(xxx_dll_t* list, xxx_dll_node_t* table, size_t count);
static void check_list(xxx_dll_t* list, xxx_dll_node_t* table, size_t count);

static int compare_dummy(void* left, void* right);
static int find_dummy(void* node, void* data);
static int process_dummy(void* node, void* data);
static int filter_dummy(void* node, void* data);

static struct {
  size_t cmp, find, prcss, fltr;
} ctrs;

static void reset_ctrs();

/*============================================================================*/

static void node_create_tests();
static void node_destroy_tests();

test_suite_t* get_dll_node_test() {
  static test_t tests[] = {
    { "Node create", node_create_tests },
    { "Node destroy", node_destroy_tests },
    { NULL, NULL }
  };

  static test_suite_t suite = {
    .title = "[unsafe] Doubly linked list node creation and destroy",
    .init = NULL,
    .cleanup = NULL,
    .tests = tests
  };

  return &suite;
}

static void node_create_tests() {
  xxx_dll_node_t node = { .next = (xxx_dll_node_t*)42, .previous = (xxx_dll_node_t*)42 };
  CU_ASSERT_EQUAL(xxx_dll_node_create(&node), XXX_LL_SUCCESS);
  CU_ASSERT_PTR_NULL(node.next);
  CU_ASSERT_PTR_NULL(node.previous);
}

static void node_destroy_tests() {
  xxx_dll_node_t node = { .next = (xxx_dll_node_t*)42, .previous = (xxx_dll_node_t*)42 };
  CU_ASSERT_EQUAL(xxx_dll_node_destroy(&node), XXX_LL_SUCCESS);
  CU_ASSERT_PTR_NULL(node.next);
  CU_ASSERT_PTR_NULL(node.previous);
}

/*============================================================================*/

static void list_create_tests();
static void list_destroy_tests();
static void list_count_tests();

test_suite_t* get_dll_list_base_test() {
  static test_t tests[] = {
    { "List create", list_create_tests },
    { "List destroy", list_destroy_tests },
    { "List count", list_count_tests },
    { NULL, NULL }
  };

  static test_suite_t suite = {
    .title = "[unsafe] Doubly linked list (DLL) creation and destroy",
    .init = NULL,
    .cleanup = NULL,
    .tests = tests
  };

  return &suite;
}

static void list_create_tests() {
  xxx_dll_t list = { .head = (xxx_dll_node_t*)42, .tail = (xxx_dll_node_t*)42, .count = 42 };
  CU_ASSERT_EQUAL(xxx_dll_create(&list), XXX_LL_SUCCESS);
  CU_ASSERT_PTR_NULL(list.head);
  CU_ASSERT_PTR_NULL(list.tail);
  CU_ASSERT(!list.count);
}

static void list_destroy_tests() {
  xxx_dll_t list = { .head = (xxx_dll_node_t*)42, .tail = (xxx_dll_node_t*)42, .count = 42 };
  CU_ASSERT_EQUAL(xxx_dll_destroy(&list), XXX_LL_SUCCESS);
  CU_ASSERT_PTR_NULL(list.head);
  CU_ASSERT_PTR_NULL(list.tail);
  CU_ASSERT(!list.count);
}

static void list_count_tests() {
  xxx_dll_t l;
  xxx_dll_node_t n[4];

  CU_ASSERT_EQUAL(xxx_dll_create(&l), XXX_LL_SUCCESS);
  CU_ASSERT_EQUAL(xxx_dll_count(&l), 0);

  create_list(&l, n, 1);
  CU_ASSERT_EQUAL(xxx_dll_count(&l), 1);
  check_list(&l, n, 1);
  create_list(&l, n, 2);
  CU_ASSERT_EQUAL(xxx_dll_count(&l), 2);
  check_list(&l, n, 2);
  create_list(&l, n, 3);
  CU_ASSERT_EQUAL(xxx_dll_count(&l), 3);
  check_list(&l, n, 3);
  create_list(&l, n, 4);
  CU_ASSERT_EQUAL(xxx_dll_count(&l), 4);
  check_list(&l, n, 4);
}

/*============================================================================*/

static void list_push_tests();
static void list_push_back_tests();
static void list_add_ordered_tests();
static void list_pop_tests();
static void list_pop_back_tests();
static void list_remove_tests();

test_suite_t* get_dll_list_manage_test() {
  static test_t tests[] = {
    { "List push tests", list_push_tests },
    { "List push back tests", list_push_back_tests },
    { "List add ordered tests", list_add_ordered_tests },
    { "List pop tests", list_pop_tests },
    { "List pop back tests", list_pop_back_tests },
    { "List remove test", list_remove_tests },
    { NULL, NULL }
  };

  static test_suite_t suite = {
    .title = "[unsafe] Doubly linked list (DLL) management",
    .init = NULL,
    .cleanup = NULL,
    .tests = tests
  };

  return &suite;
}

static void list_push_tests() {
  xxx_dll_t l;
  xxx_dll_node_t n[4];
  CU_ASSERT_EQUAL(xxx_dll_create(&l), XXX_LL_SUCCESS);
  create_nodes(n, 4);
  CU_ASSERT_EQUAL(xxx_dll_push(&l, &n[3]), XXX_LL_SUCCESS);
  check_list(&l, &n[3], 1);
  CU_ASSERT_EQUAL(xxx_dll_push(&l, &n[2]), XXX_LL_SUCCESS);
  check_list(&l, &n[2], 2);
  CU_ASSERT_EQUAL(xxx_dll_push(&l, &n[1]), XXX_LL_SUCCESS);
  check_list(&l, &n[1], 3);
  CU_ASSERT_EQUAL(xxx_dll_push(&l, &n[0]), XXX_LL_SUCCESS);
  check_list(&l, &n[0], 4);
}

static void list_push_back_tests() {
  xxx_dll_t l;
  xxx_dll_node_t n[4];
  CU_ASSERT_EQUAL(xxx_dll_create(&l), XXX_LL_SUCCESS);
  create_nodes(n, 4);

  CU_ASSERT_EQUAL(xxx_dll_push_back(&l, &n[0]), XXX_LL_SUCCESS);
  check_list(&l, &n[0], 1);
  CU_ASSERT_EQUAL(xxx_dll_push_back(&l, &n[1]), XXX_LL_SUCCESS);
  check_list(&l, &n[0], 2);
  CU_ASSERT_EQUAL(xxx_dll_push_back(&l, &n[2]), XXX_LL_SUCCESS);
  check_list(&l, &n[0], 3);
  CU_ASSERT_EQUAL(xxx_dll_push_back(&l, &n[3]), XXX_LL_SUCCESS);
  check_list(&l, &n[0], 4);
}

static void list_add_ordered_tests() {
  xxx_dll_t l;
  xxx_dll_node_t n[4];
  CU_ASSERT_EQUAL(xxx_dll_create(&l), XXX_LL_SUCCESS);
  create_nodes(n, 4);

  CU_ASSERT_EQUAL(xxx_dll_add_ordered(&l, &n[2], compare_dummy), XXX_LL_SUCCESS);
  check_list(&l, &n[2], 1);
  CU_ASSERT_EQUAL(xxx_dll_add_ordered(&l, &n[1], compare_dummy), XXX_LL_SUCCESS);
  check_list(&l, &n[1], 2);
  CU_ASSERT_EQUAL(xxx_dll_add_ordered(&l, &n[3], compare_dummy), XXX_LL_SUCCESS);
  check_list(&l, &n[1], 3);
  CU_ASSERT_EQUAL(xxx_dll_add_ordered(&l, &n[0], compare_dummy), XXX_LL_SUCCESS);
  check_list(&l, &n[0], 4);

  CU_ASSERT_EQUAL(xxx_dll_create(&l), XXX_LL_SUCCESS);
  create_nodes(n, 4);
  CU_ASSERT_EQUAL(xxx_dll_add_ordered(&l, &n[0], compare_dummy), XXX_LL_SUCCESS);
  CU_ASSERT_EQUAL(xxx_dll_add_ordered(&l, &n[3], compare_dummy), XXX_LL_SUCCESS);
  CU_ASSERT_EQUAL(xxx_dll_add_ordered(&l, &n[2], compare_dummy), XXX_LL_SUCCESS);
  CU_ASSERT_EQUAL(xxx_dll_add_ordered(&l, &n[1], compare_dummy), XXX_LL_SUCCESS);
  check_list(&l, n, 4);
}

static void list_pop_tests() {
  xxx_dll_t l;
  xxx_dll_node_t n[4];
  CU_ASSERT_EQUAL(xxx_dll_create(&l), XXX_LL_SUCCESS);

  CU_ASSERT_PTR_NULL(xxx_dll_pop(&l));
  create_list(&l, n, 4);
  CU_ASSERT_PTR_EQUAL(xxx_dll_pop(&l), &n[0]);
  CU_ASSERT_PTR_EQUAL(xxx_dll_pop(&l), &n[1]);
  CU_ASSERT_PTR_EQUAL(xxx_dll_pop(&l), &n[2]);
  CU_ASSERT_PTR_EQUAL(xxx_dll_pop(&l), &n[3]);
  CU_ASSERT_PTR_NULL(xxx_dll_pop(&l));
  CU_ASSERT_PTR_NULL(l.head);
  CU_ASSERT(!l.count);
}

static void list_pop_back_tests() {
  xxx_dll_t l;
  xxx_dll_node_t n[4];
  CU_ASSERT_EQUAL(xxx_dll_create(&l), XXX_LL_SUCCESS);

  CU_ASSERT_PTR_NULL(xxx_dll_pop_back(&l));
  create_list(&l, n, 4);
  CU_ASSERT_PTR_EQUAL(xxx_dll_pop_back(&l), &n[3]);
  CU_ASSERT_PTR_EQUAL(xxx_dll_pop_back(&l), &n[2]);
  CU_ASSERT_PTR_EQUAL(xxx_dll_pop_back(&l), &n[1]);
  CU_ASSERT_PTR_EQUAL(xxx_dll_pop_back(&l), &n[0]);
  CU_ASSERT_PTR_NULL(xxx_dll_pop_back(&l));
  CU_ASSERT_PTR_NULL(l.head);
  CU_ASSERT(!l.count);
}

static void list_remove_tests() {
  xxx_dll_t l;
  xxx_dll_node_t n[4], node;
  CU_ASSERT_EQUAL(xxx_dll_create(&l), XXX_LL_SUCCESS);
  CU_ASSERT_EQUAL(xxx_dll_node_create(&node), XXX_LL_SUCCESS);

  create_list(&l, n, 4);
  CU_ASSERT_EQUAL(xxx_dll_remove(&l, &n[2]), XXX_LL_SUCCESS);
  CU_ASSERT_PTR_NULL(n[2].next);
  CU_ASSERT_PTR_NULL(n[2].previous);
  CU_ASSERT_EQUAL(l.count, 3);
  CU_ASSERT_PTR_EQUAL(l.head, &n[0]);
  CU_ASSERT_PTR_EQUAL(n[0].next, &n[1]);
  CU_ASSERT_PTR_EQUAL(n[1].next, &n[3]);
  CU_ASSERT_PTR_NULL(n[3].next);
  CU_ASSERT_PTR_NULL(n[0].previous);
  CU_ASSERT_PTR_EQUAL(n[1].previous, &n[0]);
  CU_ASSERT_PTR_EQUAL(n[3].previous, &n[1]);
  CU_ASSERT_EQUAL(xxx_dll_remove(&l, &n[3]), XXX_LL_SUCCESS);
  CU_ASSERT_PTR_NULL(n[3].next);
  CU_ASSERT_PTR_NULL(n[3].previous);
  CU_ASSERT_EQUAL(l.count, 2);
  check_list(&l, n, 2);
  CU_ASSERT_EQUAL(xxx_dll_remove(&l, &n[0]), XXX_LL_SUCCESS);
  CU_ASSERT_PTR_NULL(n[0].next);
  CU_ASSERT_PTR_NULL(n[0].previous);
  CU_ASSERT_EQUAL(l.count, 1);
  check_list(&l, &n[1], 1);
  CU_ASSERT_EQUAL(xxx_dll_remove(&l, &n[1]), XXX_LL_SUCCESS);
  CU_ASSERT_PTR_NULL(n[1].next);
  CU_ASSERT_PTR_NULL(n[1].previous);
  CU_ASSERT(!l.count);
  CU_ASSERT_PTR_NULL(l.head);
  CU_ASSERT_PTR_NULL(l.tail);
}

/*============================================================================*/

static void list_foreach_tests();
static void list_forsome_tests();
static void list_find_tests();
static void list_has_tests();

test_suite_t* get_dll_list_traverse_test() {
  static test_t tests[] = {
    { "List foreach tests", list_foreach_tests },
    { "List forsome tests", list_forsome_tests },
    { "List find tests", list_find_tests },
    { "List has", list_has_tests },
    { NULL, NULL }
  };

  static test_suite_t suite = {
    .title = "[unsafe] Doubly linked list (DLL) traversal",
    .init = NULL,
    .cleanup = NULL,
    .tests = tests
  };

  return &suite;
}

static void list_foreach_tests() {
  xxx_dll_t l;
  xxx_dll_node_t n[4];
  CU_ASSERT_EQUAL(xxx_dll_create(&l), XXX_LL_SUCCESS);

  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_foreach(&l, process_dummy, NULL), XXX_LL_SUCCESS);
  CU_ASSERT_EQUAL(ctrs.prcss, 0);

  create_list(&l, n, 4);
  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_foreach(&l, process_dummy, NULL), XXX_LL_SUCCESS);
  CU_ASSERT_EQUAL(ctrs.prcss, 4);
  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_foreach(&l, process_dummy, &n[3]), XXX_LL_STOPPED);
  CU_ASSERT_EQUAL(ctrs.prcss, 4);
  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_foreach(&l, process_dummy, &n[2]), XXX_LL_STOPPED);
  CU_ASSERT_EQUAL(ctrs.prcss, 3);
  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_foreach(&l, process_dummy, &n[1]), XXX_LL_STOPPED);
  CU_ASSERT_EQUAL(ctrs.prcss, 2);
  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_foreach(&l, process_dummy, &n[0]), XXX_LL_STOPPED);
  CU_ASSERT_EQUAL(ctrs.prcss, 1);

  check_list(&l, n, 4);
}

static void list_forsome_tests() {
  xxx_dll_t l;
  xxx_dll_node_t n[4];
  CU_ASSERT_EQUAL(xxx_dll_create(&l), XXX_LL_SUCCESS);

  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_forsome(&l, filter_dummy, process_dummy, NULL), XXX_LL_SUCCESS);
  CU_ASSERT_EQUAL(ctrs.fltr, 0);
  CU_ASSERT_EQUAL(ctrs.prcss, 0);

  create_list(&l, n, 4);
  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_forsome(&l, filter_dummy, process_dummy, NULL), XXX_LL_SUCCESS);
  CU_ASSERT_EQUAL(ctrs.fltr, 4);
  CU_ASSERT_EQUAL(ctrs.prcss, 4);
  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_forsome(&l, filter_dummy, process_dummy, &n[3]), XXX_LL_SUCCESS);
  CU_ASSERT_EQUAL(ctrs.fltr, 4);
  CU_ASSERT_EQUAL(ctrs.prcss, 3);
  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_forsome(&l, filter_dummy, process_dummy, &n[2]), XXX_LL_SUCCESS);
  CU_ASSERT_EQUAL(ctrs.fltr, 4);
  CU_ASSERT_EQUAL(ctrs.prcss, 3);
  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_forsome(&l, filter_dummy, process_dummy, &n[1]), XXX_LL_SUCCESS);
  CU_ASSERT_EQUAL(ctrs.fltr, 4);
  CU_ASSERT_EQUAL(ctrs.prcss, 3);
  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_forsome(&l, filter_dummy, process_dummy, &n[0]), XXX_LL_SUCCESS);
  CU_ASSERT_EQUAL(ctrs.fltr, 4);
  CU_ASSERT_EQUAL(ctrs.prcss, 3);

  check_list(&l, n, 4);
}

static void list_find_tests() {
  xxx_dll_t l;
  xxx_dll_node_t n[4];
  CU_ASSERT_EQUAL(xxx_dll_create(&l), XXX_LL_SUCCESS);

  reset_ctrs();
  CU_ASSERT_PTR_NULL(xxx_dll_find(&l, find_dummy, NULL));
  CU_ASSERT_EQUAL(ctrs.find, 0);
  reset_ctrs();
  CU_ASSERT_PTR_NULL(xxx_dll_find(&l, find_dummy, &n[0]));
  CU_ASSERT_EQUAL(ctrs.find, 0);

  create_list(&l, n, 4);
  reset_ctrs();
  CU_ASSERT_PTR_NULL(xxx_dll_find(&l, find_dummy, NULL));
  CU_ASSERT_EQUAL(ctrs.find, 4);
  reset_ctrs();
  CU_ASSERT_PTR_EQUAL(xxx_dll_find(&l, find_dummy, &n[0]), &n[0]);
  CU_ASSERT_EQUAL(ctrs.find, 1);
  reset_ctrs();
  CU_ASSERT_PTR_EQUAL(xxx_dll_find(&l, find_dummy, &n[1]), &n[1]);
  CU_ASSERT_EQUAL(ctrs.find, 2);
  reset_ctrs();
  CU_ASSERT_PTR_EQUAL(xxx_dll_find(&l, find_dummy, &n[2]), &n[2]);
  CU_ASSERT_EQUAL(ctrs.find, 3);
  reset_ctrs();
  CU_ASSERT_PTR_EQUAL(xxx_dll_find(&l, find_dummy, &n[3]), &n[3]);
  CU_ASSERT_EQUAL(ctrs.find, 4);

  check_list(&l, n, 4);
}

static void list_has_tests() {

  xxx_dll_t l;
  xxx_dll_node_t n[4], node = { .next = NULL, .previous = NULL };
  create_list(&l, n, 4);

  CU_ASSERT_PTR_EQUAL(xxx_dll_has(&l, &n[0]), &n[0]);
  CU_ASSERT_PTR_EQUAL(xxx_dll_has(&l, &n[1]), &n[1]);
  CU_ASSERT_PTR_EQUAL(xxx_dll_has(&l, &n[2]), &n[2]);
  CU_ASSERT_PTR_EQUAL(xxx_dll_has(&l, &n[3]), &n[3]);
  CU_ASSERT_PTR_NULL(xxx_dll_has(&l, &node));
  check_list(&l, n, 4);
  l.head = NULL;
  l.tail = NULL;
  l.count = 0;
  CU_ASSERT_PTR_NULL(xxx_dll_has(&l, &n[0]));
  CU_ASSERT_PTR_NULL(xxx_dll_has(&l, &n[1]));
  CU_ASSERT_PTR_NULL(xxx_dll_has(&l, &n[2]));
  CU_ASSERT_PTR_NULL(xxx_dll_has(&l, &n[3]));
  CU_ASSERT_PTR_NULL(l.head);
  CU_ASSERT_PTR_NULL(l.tail);
  CU_ASSERT(!l.count);
}

/*============================================================================*/

static void list_foreach_r_tests();
static void list_forsome_r_tests();
static void list_find_r_tests();

test_suite_t* get_dll_list_traverse_r_test() {
  static test_t tests[] = {
    { "List foreach reverse tests", list_foreach_r_tests },
    { "List forsome reverse tests", list_forsome_r_tests },
    { "List find reverse tests", list_find_r_tests },
    { NULL, NULL }
  };

  static test_suite_t suite = {
    .title = "[unsafe] Doubly linked list (DLL) reverse traversal",
    .init = NULL,
    .cleanup = NULL,
    .tests = tests
  };

  return &suite;
}

static void list_foreach_r_tests() {
  xxx_dll_t l;
  xxx_dll_node_t n[4];
  CU_ASSERT_EQUAL(xxx_dll_create(&l), XXX_LL_SUCCESS);

  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_foreach_r(&l, process_dummy, NULL), XXX_LL_SUCCESS);
  CU_ASSERT_EQUAL(ctrs.prcss, 0);

  create_list(&l, n, 4);
  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_foreach_r(&l, process_dummy, NULL), XXX_LL_SUCCESS);
  CU_ASSERT_EQUAL(ctrs.prcss, 4);
  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_foreach_r(&l, process_dummy, &n[0]), XXX_LL_STOPPED);
  CU_ASSERT_EQUAL(ctrs.prcss, 4);
  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_foreach_r(&l, process_dummy, &n[1]), XXX_LL_STOPPED);
  CU_ASSERT_EQUAL(ctrs.prcss, 3);
  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_foreach_r(&l, process_dummy, &n[2]), XXX_LL_STOPPED);
  CU_ASSERT_EQUAL(ctrs.prcss, 2);
  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_foreach_r(&l, process_dummy, &n[3]), XXX_LL_STOPPED);
  CU_ASSERT_EQUAL(ctrs.prcss, 1);

  check_list(&l, n, 4);
}

static void list_forsome_r_tests() {
  xxx_dll_t l;
  xxx_dll_node_t n[4];
  CU_ASSERT_EQUAL(xxx_dll_create(&l), XXX_LL_SUCCESS);

  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_forsome_r(&l, filter_dummy, process_dummy, NULL), XXX_LL_SUCCESS);
  CU_ASSERT_EQUAL(ctrs.fltr, 0);
  CU_ASSERT_EQUAL(ctrs.prcss, 0);

  create_list(&l, n, 4);
  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_forsome_r(&l, filter_dummy, process_dummy, NULL), XXX_LL_SUCCESS);
  CU_ASSERT_EQUAL(ctrs.fltr, 4);
  CU_ASSERT_EQUAL(ctrs.prcss, 4);
  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_forsome_r(&l, filter_dummy, process_dummy, &n[3]), XXX_LL_SUCCESS);
  CU_ASSERT_EQUAL(ctrs.fltr, 4);
  CU_ASSERT_EQUAL(ctrs.prcss, 3);
  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_forsome_r(&l, filter_dummy, process_dummy, &n[2]), XXX_LL_SUCCESS);
  CU_ASSERT_EQUAL(ctrs.fltr, 4);
  CU_ASSERT_EQUAL(ctrs.prcss, 3);
  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_forsome_r(&l, filter_dummy, process_dummy, &n[1]), XXX_LL_SUCCESS);
  CU_ASSERT_EQUAL(ctrs.fltr, 4);
  CU_ASSERT_EQUAL(ctrs.prcss, 3);
  reset_ctrs();
  CU_ASSERT_EQUAL(xxx_dll_forsome_r(&l, filter_dummy, process_dummy, &n[0]), XXX_LL_SUCCESS);
  CU_ASSERT_EQUAL(ctrs.fltr, 4);
  CU_ASSERT_EQUAL(ctrs.prcss, 3);

  check_list(&l, n, 4);
}

static void list_find_r_tests() {
  xxx_dll_t l;
  xxx_dll_node_t n[4];
  CU_ASSERT_EQUAL(xxx_dll_create(&l), XXX_LL_SUCCESS);

  reset_ctrs();
  CU_ASSERT_PTR_NULL(xxx_dll_find_r(&l, find_dummy, NULL));
  CU_ASSERT_EQUAL(ctrs.find, 0);
  reset_ctrs();
  CU_ASSERT_PTR_NULL(xxx_dll_find_r(&l, find_dummy, &n[0]));
  CU_ASSERT_EQUAL(ctrs.find, 0);

  create_list(&l, n, 4);
  reset_ctrs();
  CU_ASSERT_PTR_NULL(xxx_dll_find_r(&l, find_dummy, NULL));
  CU_ASSERT_EQUAL(ctrs.find, 4);
  reset_ctrs();
  CU_ASSERT_PTR_EQUAL(xxx_dll_find_r(&l, find_dummy, &n[0]), &n[0]);
  CU_ASSERT_EQUAL(ctrs.find, 4);
  reset_ctrs();
  CU_ASSERT_PTR_EQUAL(xxx_dll_find_r(&l, find_dummy, &n[1]), &n[1]);
  CU_ASSERT_EQUAL(ctrs.find, 3);
  reset_ctrs();
  CU_ASSERT_PTR_EQUAL(xxx_dll_find_r(&l, find_dummy, &n[2]), &n[2]);
  CU_ASSERT_EQUAL(ctrs.find, 2);
  reset_ctrs();
  CU_ASSERT_PTR_EQUAL(xxx_dll_find_r(&l, find_dummy, &n[3]), &n[3]);
  CU_ASSERT_EQUAL(ctrs.find, 1);

  check_list(&l, n, 4);
}

/*============================================================================*/

static void create_nodes(xxx_dll_node_t* table, size_t count) {
  assert(table && count);
  for (size_t i = 0; i < count; i++) {
    CU_ASSERT_EQUAL(xxx_dll_node_create(&table[i]), XXX_LL_SUCCESS);
  }
}

static void create_list(xxx_dll_t* list, xxx_dll_node_t* table, size_t count) {
  assert(list && table);
  list->head = list->tail = NULL;
  for (size_t i = 0; i < count; i++) {
    xxx_dll_node_t *p = &table[i];
    p->previous = (i) ? p - 1 : NULL;
    if (i < count - 1)
      p->next = p + 1;
    else {
      list->head = &table[0];
      list->tail = &table[count-1];
      list->count = count;
      p->next = NULL;
    }
  }
}

static void check_list(xxx_dll_t* list, xxx_dll_node_t* table, size_t count) {
  assert(list && table && count);
  CU_ASSERT_EQUAL(xxx_dll_count(list), count);
  CU_ASSERT_PTR_EQUAL(list->head, &table[0]);
  CU_ASSERT_PTR_EQUAL(list->tail, &table[count-1]);
  for (size_t i = 0; i < count - 1; i++) {
    CU_ASSERT_PTR_EQUAL(table[i].next, (i != count-1) ? &table[i+1] : NULL);
    CU_ASSERT_PTR_EQUAL(table[i].previous, (i) ? &table[i-1] : NULL);
  }
}

static int compare_dummy(void* left, void* right) {
  /* compare by @ */
  assert(left && right);
  ctrs.cmp ++;
  int rtn = 0;
  if (left < right) {
    return -1;
  } else if (left < right) {
    return 1;
  }
  return rtn;
}

static int find_dummy(void* node, void* data) {
  assert(node);
  ctrs.find ++;
  return (node == data);
}

static int process_dummy(void* node, void* data) {
  assert(node);
  ctrs.prcss ++;
  return (node != data);
}

static int filter_dummy(void* node, void* data) {
  assert(node);
  ctrs.fltr ++;
  return (node != data);
}

static void reset_ctrs() {
  ctrs.cmp = ctrs.find = ctrs.fltr = ctrs.prcss = 0;
}
