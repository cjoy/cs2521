#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct QueueRep *Queue;
typedef struct tree *Item;
typedef struct tree *Tree;
struct tree {
  int item;
  Tree left, right;
};


typedef struct QueueRep {
  Item *item;   // array to hold Items
  int front;  // next Item to be removed
  int back;    // last Item added
  int nitems;   // # Items currently in queue
  int maxitems; // size of array
} QueueRep;

Queue newQueue (int);               // set up empty queue
void dropQueue (Queue);             // remove unwanted queue
void QueueJoin (Queue, Item);       // insert Item at back of queue
Item QueueLeave (Queue);            // remove Item from front of queue
bool QueueIsEmpty (Queue);          // check whether queue is empty
Tree tree_new_node (int i);

void tree_level_order_traversal (Tree t)
{
  if (!t) return;
  
  Queue q = newQueue(10);
  QueueJoin(q, t);

  while (!QueueIsEmpty(q)) {
    Item n = QueueLeave(q);
    printf("[%d] ", n->item);
    if (n->left) QueueJoin(q, n->left);
    if (n->right) QueueJoin(q, n->right);
    // check if tree is complete or not
    // if (n->right && !n->left) {
    //   puts("Not complete tree :(");
    // }
  }

  dropQueue(q);
}



int main ()
{
  Tree t = tree_new_node(6);
  t->left = tree_new_node(1);
  t->left->left = NULL;
  t->left->right = NULL;
  t->right = tree_new_node(7);
  t->right->right = tree_new_node(8);
  t->right->left = NULL;
  t->right->right->left = NULL;
  t->right->right->right = NULL;

  tree_level_order_traversal(t);

  return 0;
}

Tree tree_new_node (int i)
{
  Tree t = malloc(sizeof(*t));
  t->item = i;
  t->left = t->left = NULL;
  return t;
}


// set up empty queue
Queue newQueue (int n)
{
  Queue q = malloc (sizeof (QueueRep));
  assert (q != NULL);
  q->item = malloc (n * sizeof (Item));
  assert (q->item != NULL);
  q->front = q->back = 0;
  q->nitems = 0;
  q->maxitems = n;
  return q;
}

// remove unwanted queue
void dropQueue (Queue q)
{
  assert (q != NULL);
  free (q->item);
  free (q);
}

// insert item on top of queue
void QueueJoin (Queue q, Item it)
{
  assert (q->nitems < q->maxitems);
  q->item[q->front] = it;
  q->nitems++;
  q->front = (q->front + 1) % q->maxitems;
}

// remove item from front of queue
Item QueueLeave (Queue q)
{
  assert (q->nitems > 0);
  Item it = q->item[q->back];
  q->nitems--;
  q->back = (q->back + 1) % q->maxitems;
  return it;
}

// check whether queue is empty
bool QueueIsEmpty (Queue q)
{
  return (q->nitems == 0);
}
