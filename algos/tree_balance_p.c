#include <stdlib.h>
#include <stdbool.h>

typedef struct tree *Tree;
struct tree {
  int item;
  Tree left, right;
};

size_t tree_size (Tree t)
{
  if (!t) return 0;

  return 1
    + size(t->left)
    + size(t->right);
}

// Tree balance (size)
// | size(tree->R) - size(tree->L) | < 2
bool tree_balance_p (Tree t)
{
  if (!t) return true;

  return (abs(tree_size(t->left) - tree_size(t->right)) < 2)
    && tree_balance_p (t->left)
    && tree_balance_p (t->right);
}