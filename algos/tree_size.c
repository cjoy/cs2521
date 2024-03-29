#include <stdbool.h>

typedef struct tree *Tree;
struct tree {
    int val;
    Tree left, right;
};

// Find size of tree (ie. number of nodes)
int tree_size (Tree t)
{
    if (!t) return 0;

    return 1
        + tree_size (t->left)
        + tree_size (t->right);
}

