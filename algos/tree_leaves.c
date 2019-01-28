typedef struct tree *Tree;
struct tree {
    int item;
    Tree left, right;
};

// Find size of tree (ie. number of nodes)
int tree_leaves (Tree t)
{
  if (!t) return 0;

  if (!t->left && !t->right) return 1;

  return tree_leaves (t->left) + tree_leaves (t->right);
}

