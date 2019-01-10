typedef struct tree *Tree;
struct tree {
    int val;
    Tree left, right;
}

#define min(x, y) (x) < (y) ? (x) : (y)

int tree_min (Tree t)
{
    if (!t) return -1;

    int curr = t->val;
    
    if (t->left)
        curr = min (curr, tree_min (t->left));
    
    if (t->left)
        curr = min (curr, tree_min (t->left));
    
    return curr;
}
