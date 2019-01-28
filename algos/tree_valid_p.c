#include <stdbool.h>

typedef struct tree *Tree;
struct tree {
  int item;
  Tree left, right;
};

bool tree_valid_p (Tree t)
{
	if (!t) return true;

	if (t->left && t->left->item > t->item)
		return false;
	
	if (t->right && t->right->right < t->item)
		return false;

	if (!tree_valid_p(t->left) || !tree_valid_p(t->right))
		return false;
	
	return true;	
}