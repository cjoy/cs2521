typedef struct tree *Tree;
struct tree {
    int item;
    Tree left, right;
};


int tree_min_recursive (Tree t)
{
    if (!t) return -1;

    if (!t->left) return t->item;
    
    return tree_min (t->left);
}

int tree_min_iterative (Tree t)
{
    if (!t) return -1;

    Tree curr = t;
    for (; curr->left; curr = curr->left)

    return curr->item;
}
