# Linked Lists
* A sequence of collection of 'nodes' holding value + pointer(s)
* No random access
* Easy to add, rearrange, remove nodes...
* List nodes references other list nodes:
  * Singly Linked List: `next`
  * Doubly Linked List: `next` `prev`

## Struct
```C
typedef struct node *Link;
typedef struct node {
  Item data;
  link next;
} node;

// Allocating memory
link x = malloc (sizeof *x);
link y = malloc (sizeof (node));

// Wrong allocation
link z = malloc (sizeof (link));
```

## Traversal
```C
link curr = ...
for (; curr; curr = curr->next)
  // do something
```

## Insert
```C
// Insert new node at the front of a list
link insert_front (link list, link new)
{
  new->next = list;
  return new;
}

// Insert new node at the back of a list
link insert_back (link list, link new)
{
  link curr = list;
  for (; curr; curr = curr->next)
  curr->next = new;
  return list;
}

// Why wont this work?
void insert_front (link list, link new);
// Because we loose track of what the reference
// to the head is.
```

## Delete an item from the list
* Deleting is awkward as we have to keep track of the previous node
* We may need to traverse the whole list to find the predecessor and that's if we even have a reference to the head

# Doubly Linked Lists
## Struct
```C
typedef struct dnode *dlink;
typedef struct dnode {
  Item data;
  dlink prev, next;
} dnode;
```
* Moving forward and backward in such a list
* Delete node in a constant number of steps
  - Deleting nodes is is easier and more efficient
  - 2x pointer manipulation necessary for most list operations
  - memory overheads in storing an additional pointer

# 