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
    if (!t) return 0;

    int l = tree_height (t->left);
    int r = tree_height (t->right);

    return 1 + max (l, r);
}
