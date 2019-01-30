typedef struct tree *Tree;
struct tree {
  int item;
  Tree left, right;
};

void tree_reverse (Tree t)
{
  if (!t) return;
  
  Tree tmp = t->left;
  t->left = t->right;
  t->right = tmp;

  tree_reverse (t->left);
  tree_reverse (t->right);
}