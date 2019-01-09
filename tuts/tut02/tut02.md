# Using Stacks and Queues
Consider the following interfaces given in lectures, for a stack and a queue:
```C
// ... queue.h

typedef struct queue *Queue;
Queue queue_new (void);
void queue_drop (Queue);
Item queue_de (Queue q);
void queue_en (Queue, Item);
size_t queue_size (Queue);
// ... stack.h

typedef struct stack *Stack;
Stack stack_new (void);
void stack_drop (Stack);
Item stack_pop (Stack s);
void stack_push (Stack, Item);
size_t stack_size (Stack);
```
Using two stack data structures, show how you can implement a queue data structure.
```C
struct queue {
  stack head;
  stack tail;
}
```

Using two queue data structures, show how you can implement a stack data structure.

Using only the functions for manipulating stacks in the stack interface, write a function that joins two stacks stack1 and stack2, such that stack1 is “stacked” on stack2. (Note that the contents of stack1 do not need to be preserved.)

void stack_stacks (Stack stack1, Stack stack2);
