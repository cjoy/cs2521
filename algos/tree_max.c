typedef struct tree *Tree;
struct tree {
    int item;
    Tree left, right;
};


int tree_max_recursive (Tree t)
{
    if (!t) return -1;

    if (!t->right) return t->item;
    
    return tree_min (t->right);
}

int tree_max_iterative (Tree t)
{
    if (!t) return -1;

    Tree curr = t;
    for (; curr->right; curr = curr->right)

    return curr->item;
}
