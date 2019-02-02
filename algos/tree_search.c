#include <stdbool.h>
#include <stdlib.h>

typedef struct tree *Tree;
struct tree {
  int item;
  Tree left, right;
};

Tree tree_search (Tree t, int key) {
  if (!t) return NULL;

  if (t->item == key) {
    return t;
  } else if (t->item < key) {
    return tree_search (t->right);
  } else if (t->item > key) {
    return tree_search (t->left);
  }

  return NULL;
}