typedef struct tree *Tree;
struct tree {
    int val;
    Tree left, right;
}

#define max(x, y) (x) > (y) ? (x) : (y)

int tree_max (Tree t)
{
    if (!t) return -1;

    int curr = t->val;
    
    if (t->left)
        curr = max (curr, tree_max(t->left));
    
    if (t->left)
        curr = max (curr, tree_max(t->left));
    
    return curr;
}
