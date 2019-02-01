typedef struct tree *Tree;
struct tree {
    int item;
    Tree left, right;
};

int tree_size (Tree t)
{
  if (!t) return 0;
  return 1 + 
    tree_size (t->left) + 
    tree_size (t->right);
}

Tree tree_n (Tree t, int n)
{
  if (!t) return NULL;

  int left_size = tree_size(t->left);

  if (left_size == n)
    return t;

  if (left_size > n)
		return btree_nth (t->left, n);
  else
		return btree_nth (t->right, n - 1 - left_size);
}