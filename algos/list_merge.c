typedef struct _node *List;
struct _node {
    int data;
    List next;
};

List list_merge (List A, List B) {
    if (!A) return B;
    if (!B) return A;

    List result;

    if (A->data <= B->data) {
        result = A;
        result->next = list_merge (A->next, B);
    } else {
        result = B;
        result->next = list_merge (A, B->next);
    }

    return result;
}
