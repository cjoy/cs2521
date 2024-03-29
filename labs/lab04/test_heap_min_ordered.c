#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "heap_min_ordered.h"

static void test_ordered_minheaps(void);
static void test_unordered_minheaps(void);

int main (void)
{
	// Stops output being buffered;
	// we get all printf output before crashes/aborts
	setbuf (stdout, NULL);

	test_ordered_minheaps();
	test_unordered_minheaps();

	puts ("\nAll tests passed. You are awesome!");
	return EXIT_SUCCESS;
}


static void test_ordered_minheaps (void)
{
	node *tree = NULL;
	puts ("ordered: test 1: empty tree");
	assert (heap_min_ordered_p (tree));

	tree = malloc (sizeof *tree);
	(*tree) = (node) { .item = 9, .left = NULL, .right = NULL };

	puts ("ordered: test 2: tree size 1");
	assert (heap_min_ordered_p (tree));

	node *leaf = malloc (sizeof *leaf);
	(*leaf) = (node) { .item = 15, .left = NULL, .right = NULL };
	tree->left = leaf;

	puts ("ordered: test 3: tree size 2");
	assert (heap_min_ordered_p (tree));

	node *leaf1 = malloc (sizeof *leaf1);
	(*leaf1) = (node) { .item = 13, .left = NULL, .right = NULL };
	tree->right = leaf1;
	puts ("ordered: test 4: tree size 3");
	assert (!heap_min_ordered_p (tree));

	node *leaf2 = malloc (sizeof *leaf1);
	(*leaf2) = (node) { .item = 13, .left = NULL, .right = NULL };
	tree->right->left = leaf2;
	puts ("unordered: test 4: tree size 3");
	assert (!heap_min_ordered_p (tree));

	free (leaf2);
	free (leaf1);
	free (tree);
}

static void test_unordered_minheaps (void)
{
	node *tree = malloc (sizeof *tree);
	(*tree) = (node) { .item = 9, .left = NULL, .right = NULL };

	node *leaf = malloc (sizeof *leaf);
	(*leaf) = (node) { .item = 8, .left = NULL, .right = NULL };
	tree->left = leaf;

	puts ("unordered: test 1: tree size 2");
	assert (!heap_min_ordered_p (tree));

	free (leaf);
	free (tree);
}
