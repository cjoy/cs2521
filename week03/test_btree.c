////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 -- Test a binary search tree implementation.
//
// 2018-12-08	Jashank Jeremy <jashankj@cse.unsw.edu.au>
// 2018-12-13	Chris Joy <z5113243@student.unsw.edu.au>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "item_int.h"
#include "btree.h"
#include "testable.h"

BTreeNode arr_to_btree (const int arr[], size_t n);
static void node_print (BTreeNode node);

int main (void)
{
	white_box_tests ();
	{
		puts ("BB Test: Testing empty tree");
		BTreeNode tree = NULL;
		assert (btree_size (tree) == 0);
		assert (btree_size_leaf (tree) == 0);
		btree_drop (tree);
	}
	{
		puts ("BB Test: Testing tree with 5 nodes and 1 leaf");
		const int items[] = {1, 2, 3, 4, 5};
		const size_t n = 5;
		BTreeNode tree = arr_to_btree (items, n);
		assert (btree_size (tree) == n);
		assert (btree_size_leaf (tree) == 1);
		btree_drop (tree);
	}
	{
		puts ("BB Test: Testing tree with 4 nodes and 2 leaves");
		const int items[] = {4, 2, 1, 3};
		const size_t n = 4;
		BTreeNode tree = arr_to_btree (items, n);
		assert (btree_size (tree) == n);
		assert (btree_size_leaf (tree) == 2);
		btree_drop (tree);
	}
	{
		const int items[] = {1, 2, 3, 4, 5};
		const size_t n = 5;
		BTreeNode tree = arr_to_btree (items, n);
		btree_traverse (tree, BTREE_TRAVERSE_LEVEL, node_print);
		btree_drop (tree);
	}
	puts ("\nAll tests passed. You are awesome!");
	return EXIT_SUCCESS;
}

BTreeNode arr_to_btree (const int arr[], size_t n)
{
	BTreeNode tree = NULL;
	for (size_t i = 0; i < n; i++)
		tree = btree_insert (tree, _int_item_new (arr[i]));
	return tree;
}

static void node_print (BTreeNode node)
{
	Item nvalue = btree_node_value (node);
	char *str = item_show (nvalue);
	printf ("%s ", str);
	free (str);
}
