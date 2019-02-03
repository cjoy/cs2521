#include <stdbool.h>

typedef struct _node *List;
struct _node {
  int data;
  List next;
};

bool list_even (List l) {
  if (!l) return true;
  return (l->data % 2 == 0)
    && list_even(l->next);
}


