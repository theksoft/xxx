#include "tests.h"
#include "tests_sll.h"
#include "tests_dll.h"
#include "tests_sll_s.h"
#include "tests_dll_s.h"

const test_suite_getter_t tsg_table[] = {

  get_sll_node_test,
  get_sll_list_base_test,
  get_sll_list_manage_test,
  get_sll_list_traverse_test,

  get_dll_node_test,
  get_dll_list_base_test,
  get_dll_list_manage_test,
  get_dll_list_traverse_test,
  get_dll_list_traverse_r_test,

  get_sll_s_node_test,
  get_sll_s_list_base_test,
  get_sll_s_list_manage_test,
  get_sll_s_list_traverse_test,

  get_dll_s_node_test,
  get_dll_s_list_base_test,
  get_dll_s_list_manage_test,
  get_dll_s_list_traverse_test,
  get_dll_s_list_traverse_r_test,

  TEST_SUITE_GETTER_END
};
