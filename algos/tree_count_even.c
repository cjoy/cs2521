#include <stdbool.h>

typedef struct tree *Tree;
struct tree {
    int item;
    Tree left, right;
};

// Find size of tree (ie. number of nodes)
int tree_count_even (Tree t)
{
    if (!t) return 0;

    return (t->item % 2 == 0 ? 1 : 0)
        + tree_count_even (t->left)
        + tree_count_even (t->right);
}

