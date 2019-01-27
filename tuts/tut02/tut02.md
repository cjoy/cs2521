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
## Solution
```C
struct queue {
  Stack head;
  Stack tail;
}
```
- Pop out all items from head stack and then push to tail stack so we can dequeue items in FIFO order.

Using two queue data structures, show how you can implement a stack data structure.
## Solution
```C
struct stack {
  Queue q1;
  Queue q2;
}
```
- Pushing items is basically just enqueing items to q1
- Poping items requires dequeing items from q1 and enqueing to q2 and store the last item in q1 in a tmp variable. After saving the last item, we need to transfer q2 items back to q1 and return the last item.

Using only the functions for manipulating stacks in the stack interface, write a function that joins two stacks stack1 and stack2, such that stack1 is “stacked” on stack2. (Note that the contents of stack1 do not need to be preserved.)
```C
void stack_stacks (Stack stack1, Stack stack2);
```
## Solution
```C
void stack_stacks (Stack stack1, Stack stack2)
{
  Stack tmp = NULL;
  // push items from stack 1 into temporary stack
  for (tmp = stack_new(); stack_size(stack1) > 0; stack_push(tmp, stack_pop(stack1)))
  // push items out from tmp into stack2
  for (; stack_size(stmp) > 0; stack_push(stack2, stack_pop(stack1)))
}
```

# Implementing a Stack with a Linked List
As we did in the lectures, implement from the Stack interface given in Exercise 1, using a linked list structure. How will you represent your stack?
```C
typedef struct stack stack;
typedef struct stack_node stack_node;

struct stack {
	// You need to decide what goes in here
};

struct stack_node {
	// You need to decide what goes in here
};
```
Assume you have the following local helper function to create nodes –
```C
static stack_node *stack_node_new (Item);
```
## Solution
```C
typedef struct stack stack;
typedef struct stack_node stack_node;

struct stack {
  stack_node *head;
  size_t size;
};

struct stack_node {
	Item item;
  stack_node *next;
};

static stack_node *stack_node_new (Item)
{
  
}
```

# Emordnilap!
An emordnilap is a string of characters which have the property that they can be read the same from either end, ignoring whitespace, punctuation, and case. It will always have an even number of characters that match: “tacocat” and “Madam, I’m Adam” are not emordnilaps, but “Hannah” and “rats live on no evil star” are.

Write a program which, given a string, will print “yes” if it is an emordnilap, and “no” otherwise.
```Bash
./emordnilap Hannah
yes
./emordnilap "rats live on no evil star"
yes
./emordnilap "tacocat"
no
./emordnilap "Madam, I'm Adam"
no
./emordnilap "Citation Needed"
no
```
HINT This is very similar to the balanced brackets problem from the lecture.

CHALLENGE Modify your solution to match palindromes.
## Solution
```C
\\ TODO
```

# On Testing
What is the difference between black box and white box testing?
## Answer


# On Black-Box Testing
Let’s say we have a set of tests in a file test_stack.c, which includes the stack.h interface from Exercise 1 –
```C
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main (void)
{
	printf ("Testing new stack\n");
	Stack s = stack_new();
	assert (s->size == 0);
	printf ("Test passed\n");
	return EXIT_SUCCESS;
}
```
When compiling my test file, I get the following compile error:

test_stack.c:11:5: error: dereferencing pointer to incomplete type
What does this mean?
## Answer
