#include <stdbool.h>
#include <stdlib.h>

#include "heap_min_ordered.h"

/**
 * Returns 1 if the tree-based heap is in min-heap order.
 * You may assume an empty tree is in min-heap order.
 * You may assume a single node is in min-heap order.
 */
bool heap_min_ordered_p (node *tree)
{
	if (!tree)
		return true;
	else if (!tree->left && !tree->right)
		return true;
	else if (!tree->left && tree->right)
		return false;
	else if (!tree->right && tree->left)
		return tree->item <= tree->left->item;
	else if (tree->item <= tree->left->item && tree->item <= tree->right->item)
		return heap_min_ordered_p (tree->left) && heap_min_ordered_p (tree->right);
	return false;
}
