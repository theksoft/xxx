#include "tests.h"
#include "tests1d.h"
#include "tests2d.h"

const test_suite_getter_t tsg_table[] = {
  get_list1d_node_test,
  get_list1d_list_base_test,
  get_list1d_list_manage_test,
  get_list1d_list_traverse_test,
  get_list2d_node_test,
  get_list2d_list_base_test,
  get_list2d_list_manage_test,
  get_list2d_list_traverse_test,
  get_list2d_list_traverse_r_test,
  TEST_SUITE_GETTER_END
};
