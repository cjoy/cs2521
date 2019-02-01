#include <stdbool.h>
#include <stdlib.h>

typedef struct tree *Tree;
struct tree {
    int item;
    Tree left, right;
};

size_t max (int a, int b)
{
  return a > b ? a : b;
}

size_t tree_height (Tree t)
{
  if (!t) return 0;
  size_t rh = tree_height (t->right);
  size_t lh = tree_height (t->left);
  return 1 + max(rh, lh);
}


bool tree_balanced (Tree t)
{
  if (!t) return true;

  size_t rh = tree_height(t->right);
  size_t lh = tree_height(t->left);

  return (abs(rh - lh) < 2)
    && tree_balanced (t->left)
    && tree_balanced (t->right);
}
