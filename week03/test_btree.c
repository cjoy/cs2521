////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 -- Test a binary search tree implementation.
//
// 2018-12-08	Jashank Jeremy <jashankj@cse.unsw.edu.au>
// 2018-12-13	Chris Joy <z5113243@student.unsw.edu.au>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "item_int.h"
#include "item_btree_node.h"
#include "btree.h"
#include "testable.h"

BTreeNode arr_to_btree (const int arr[], const size_t n);
static void node_print (BTreeNode node);
bool tree_cmp (const int truth[], BTreeNode *arr, const size_t n);

int main (void)
{
	{
		puts ("BB Test: Testing empty btree");
		BTreeNode tree = NULL;
		assert (btree_size (tree) == 0);
		assert (btree_size_leaf (tree) == 0);
		btree_drop (tree);
	}
	{
		puts ("BB Test: Testing btree with 5 nodes and 1 leaf");
		const int items[] = {1, 2, 3, 4, 5};
		const size_t n = 5;
		BTreeNode tree = arr_to_btree (items, n);
		assert (btree_size (tree) == n);
		assert (btree_size_leaf (tree) == 1);
		btree_drop (tree);
	}
	{
		puts ("BB Test: Testing btree with 4 nodes and 2 leaves");
		const int items[] = {4, 2, 1, 3};
		const size_t n = 4;
		BTreeNode tree = arr_to_btree (items, n);
		assert (btree_size (tree) == n);
		assert (btree_size_leaf (tree) == 2);
		btree_drop (tree);
	}
	{
		puts ("BB Test: Testing tree with for nodes using level order");
		const int items[] = {4, 2, 1, 3};
		const size_t n = 4;
		BTreeNode tree = arr_to_btree (items, n);
		BTreeNode *nodes = btree_traverse (tree, BTREE_TRAVERSE_LEVEL, NULL);
		printf("%d ->", BTreeNode_item (nodes[0]));
		// assert (tree_cmp (items, nodes, n) == true);
		btree_drop (tree);
	}
#if 0
	{
		puts ("BB Test: Testing tree ");
		const int items[] = {4, 2, 1, 3};
		const size_t n = 4;
		BTreeNode tree = arr_to_btree (items, n);
		btree_traverse (tree, BTREE_TRAVERSE_PREFIX, node_print);
		puts ("");
		btree_traverse (tree, BTREE_TRAVERSE_INFIX, node_print);
		puts ("");
		btree_traverse (tree, BTREE_TRAVERSE_POSTFIX, node_print);
		puts ("");
		btree_traverse (tree, BTREE_TRAVERSE_LEVEL, node_print);
		btree_drop (tree);
	}
#endif
	{
		puts ("BB Test: Testing empty btree");
		BTreeNode tree = NULL;
		assert (btree_count_if (tree, even_p) == 0);
		btree_drop (tree);
	}
	{
		puts ("BB Test: Testing btree with no even nodes");
		const int items[] = {1, 3, 5, 7};
		const size_t n = 4;
		BTreeNode tree = arr_to_btree (items, n);
		assert (btree_count_if (tree, even_p) == 0);
		btree_drop (tree);
	}
	{
		puts ("BB Test: Testing btree with 2 even nodes");
		const int items[] = {4, 2, 1, 3};
		const size_t n = 4;
		BTreeNode tree = arr_to_btree (items, n);
		assert (btree_count_if (tree, even_p) == 2);
		btree_drop (tree);
	}
	{
		puts ("BB Test: Testing btree with 3 odd nodes");
		const int items[] = {4, 2, 1, 3, 5};
		const size_t n = 5;
		BTreeNode tree = arr_to_btree (items, n);
		assert (btree_count_if (tree, odd_p) == 3);
		btree_drop (tree);
	}
	{
		puts ("BB Test: Testing btree with 1 odd node");
		const int items[] = {4, 2, 1, 3, -5};
		const size_t n = 5;
		BTreeNode tree = arr_to_btree (items, n);
		assert (btree_count_if (tree, negative_p) == 1);
		btree_drop (tree);
	}
	{
		puts ("BB Test: Testing btree with 3 odd nodes");
		const int items[] = {4, 2, -1, -3, -5};
		const size_t n = 5;
		BTreeNode tree = arr_to_btree (items, n);
		assert (btree_count_if (tree, negative_p) == 3);
		btree_drop (tree);
	}	
	puts ("\nAll tests passed. You are awesome!");
	return EXIT_SUCCESS;
}

BTreeNode arr_to_btree (const int arr[], const size_t n)
{
	BTreeNode tree = NULL;
	for (size_t i = 0; i < n; i++)
		tree = btree_insert (tree, int_item_new (arr[i]));
	return tree;
}

static void node_print (BTreeNode node)
{
	Item nvalue = btree_node_value (node);
	char *str = item_show (nvalue);
	printf ("%s ", str);
	free (str);
}

bool tree_cmp (const int truth[], BTreeNode *tree, const size_t n)
{
	for (size_t i = 0; i < n; i++)
		if (truth[i] != tree[i]->item)
			return false;
	return true;
}