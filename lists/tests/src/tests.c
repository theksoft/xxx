#include "tests.h"
#include "tests_sll_s.h"
#include "tests_dll_s.h"

const test_suite_getter_t tsg_table[] = {
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
