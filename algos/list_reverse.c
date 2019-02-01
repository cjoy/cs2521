typedef struct _node *list;
struct _node {
    int val;
    list next;
};

void list_reverse (list l)
{
    if (!l || !l->next) return;

    list prev;
    list next = l->next;
    list curr = l;
    
    for (; curr->next; curr->next = next) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
    }

    curr->next = prev;
}

