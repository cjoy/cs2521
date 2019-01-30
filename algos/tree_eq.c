#include <stdbool.h>

typedef struct _tree *Tree;
struct _tree {
    int val;
    Tree left, right;
};

// Check if two trees are equal
bool tree_eq (Tree t1, Tree t2)
{
    if (!t1 && !t2) return true;
    if (t1 && t2) {
        return (t1->val == t2->val)
            && tree_eq (t1->left, t2->left)
            && tre_eq (t1->right, t2->right);
    }
    return false;
}
