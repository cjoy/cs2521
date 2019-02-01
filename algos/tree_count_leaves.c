#include <stdio.h>
#include <stdlib.h>

typedef struct tree *Tree;
struct tree {
  int item;
  Tree left, right;
};

Tree tree_new_node (int i);

int tree_count_leaves (Tree t)
{
  if (!t) return 0;

  if (!t->left && !t->right) return 1;
  
  return tree_count_leaves (t->left)
    + tree_count_leaves (t->right);
}

int main ()
{
  Tree t = tree_new_node(6);
  t->left = tree_new_node(1);
  t->right = tree_new_node(7);
  t->right->right = tree_new_node(8);

  int size = tree_count_leaves(t->left);

  printf ("%d", size);

  return 0;
}

Tree tree_new_node (int i)
{
  Tree t = malloc(sizeof(*t));
  t->item = i;
  t->left = t->left = NULL;
  return t;
}
