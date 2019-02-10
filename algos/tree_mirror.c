#include <stdbool.h>

typedef struct _tree *Tree;
struct _tree {
    int val;
    Tree left, right;
};

// Check if two trees are equal
bool tree_mirror (Tree t1, Tree t2)
{
    if (!t1 && !t2) return true;
    if (t1 && t2) {
        return (t1->val == t2->val)
            && tree_mirror (t1->right, t2->left)
            && tre_mirror (t1->left, t2->right);
    }
    return false;
}


// Check if a tree is symmetrical
bool tree_symmetric (Tree t)
{
    return tree_mirror (t, t);
}