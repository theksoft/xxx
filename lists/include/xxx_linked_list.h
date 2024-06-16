#ifndef _XXX_LINKED_LIST_H_
#define _XXX_LINKED_LIST_H_

typedef enum {
  XXX_LL_SUCCESS,
  XXX_LL_ERROR,
  XXX_LL_STOPPED
} xxx_ll_result_t;

/* Check if the node match the provided data
 * @return
 * - != 0 : Node match the data
 * -  = 0 : Node does not match the data
*/
typedef int (*xxx_ll_match_t)(void* node, void* data);

/* Compare two nodes of same type : xxx_list1d_node_t or xx_list2d_node_t
 * @return
 * - -1 : left < right
 * -  0 : left = right
 * -  1 : left > right
 */
typedef int (*xxx_ll_compare_t)(void* left, void* right);

/* Handle a node processing during a list traversal
 * @return
 * - != 0 : list traversal can continue
 * -  = 0 : list traversal must be stopped
 */
typedef int (*xxx_ll_handler_t)(void* node, void* data);

/* Handle a node processing during a list traversal
 * @return
 * - != 0 : node process must be called for node and data
 * -  = 0 : node process must not be called for node and data
 */
typedef int (*xxx_ll_filter_t)(void* node, void* data);

#endif
