typedef struct tree *Tree;
struct tree {
    int val;
    Tree left, right;
};

int max (int a, int b)
{
    return a > b ? a : b;
}

int tree_height (Tree t)
{
    int lh = tree_height (t->left);
    int rh = tree_height (t->right);

    return 1 + max (lh, rh);
}
