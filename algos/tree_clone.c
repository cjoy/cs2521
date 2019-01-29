typedef struct tree *Tree;
struct tree {
    int item;
    Tree left, right;
};


Tree *tree_clone (Tree t)
{
  if (!t) return t;

  Tree new = malloc(sizeof(*new));
  new->item = t->item; // copy item from tree
  new->left = tree_clone(t->left);
  new->right = tree_clone(t->left);

  return new;
}
