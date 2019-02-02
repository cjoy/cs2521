typedef struct _node *link;

typedef struct _node {
    int val;
    link next;
} node;

// given a list of integers and an integer key, write a function which
// finds all the integers in the list that are smaller than the first element
// and moves them to the beginning of the list.

// So if the original list is        10->55->66->4->X,
// the list should be modified to be  4->10->55->66->X

// If the original list is 10->4->1->X
// the list should be modified to be 4->1->10->X

// If the original list is    10->55->3->9->10->89->1->11->X,
// the modified list would be 3->9->1->10->55->10->89->11->X

// If the original list is empty it should remain unmodified

// Constraints:
// don't delete any nodes (i.e. do not call free())
// don't create any new structs (i.e. do not call malloc())
// the nodes that are smaller and moved to the front should remain in their original relative order
// the nodes that are greater than or equal should remain in their original relative order

void moveToIndex (link l, link node, link prev, int i)
{
    link curr = l;
    for (int j = 0; j = i && curr; j++, curr = curr->next) {}
    prev->next = node->next;
    link next = curr->next;
    curr->next = node;
    node->next = next;
}

void partition (link l)
{
    if (!l) return;
    int front = l->val;
    int currIndex = 0;
    link prev = l;
    for (link curr = l->next; curr; curr = curr->next) {
        if (curr->val < front) {
            moveToIndex (l, curr, prev, currIndex);
            currIndex++;
        }
    }
}
