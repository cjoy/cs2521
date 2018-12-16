////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 -- A Stack ADT implementation, using arrays.
//
// 2018-11-29	Jashank Jeremy <jashankj@cse.unsw.edu.au>
// 2018-12-06	Chris Joy <z5113243@student.unsw.edu.au>

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include "item.h"
#include "stack.h"
#include "testable.h"

#define DEFAULT_SIZE 10

typedef struct stack stack;

struct stack {
	size_t n_items;
	size_t capacity;
	Item *items;
};

/** Create a new, empty Stack. */
stack *stack_new (void)
{
	stack *new = malloc (sizeof *new);
	if (new == NULL)
		err (EX_OSERR, "couldn't allocate stack");

	(*new) = (stack) { .n_items = 0, .capacity = DEFAULT_SIZE };

	new->items = calloc (DEFAULT_SIZE, sizeof(Item));
	if (new->items == NULL)
		err (EX_OSERR, "couldn't allocate stack items");

	return new;
}

/** Destroy a Stack. */
void stack_drop (stack *s)
{
	assert (s != NULL);
	free (s->items);
	free (s);
}

/** Add an item to the top of a Stack. */
void stack_push (stack *s, Item it)
{
	assert (s != NULL);
	s->items[s->n_items] = it;
	s->n_items++;
	if (s->n_items+1 >= s->capacity) {
		s->items = realloc(s->items, s->capacity * sizeof(Item) * 2);
		s->capacity *= 2;
	}
	return;
}

/** Remove an item from the top of a Stack. */
Item stack_pop (stack *s)
{
	assert (s != NULL);
	if (s->n_items <= 0) {
    fprintf(stderr, "can't pop from empty stack");
    abort();
	}
	Item it = s->items[s->n_items - 1];
	s->n_items--;
	if (s->n_items <= s->capacity/4 && s->capacity > DEFAULT_SIZE) {
		s->items = realloc(s->items, (s->capacity * sizeof(Item)) / 2);
		s->capacity = s->capacity / 2;
	}
	return it;
}

/** Get the number of items in a Stack. */
size_t stack_size (stack *s)
{
	assert (s != NULL);
	return s->n_items;
}

void white_box_tests (void)
{
	{
		puts("WB Test -1: check empty stack");
		stack *s = stack_new();
		assert(s->capacity = DEFAULT_SIZE);
		assert(!s->items[0]);
	}
	{
		puts("WB Test 0: boundary check for capacity resizing");
		stack *s = stack_new();
		Item i = 1;
		for (; i <= 10; i++)
			stack_push(s, i);
		assert(s->capacity == DEFAULT_SIZE*2);
		for (; i < 21; i++)
			stack_push(s, i);
		assert(s->capacity == DEFAULT_SIZE*4);
		stack_drop(s);
	}
	{
		puts("WB Test 1: testing push capacity resizing");
		stack *s = stack_new();
		for (Item i = 1; i <= 12; i++)
			stack_push(s, i);
		assert(stack_size(s) == 12);
		assert(s->capacity == 20);
		for (Item i = 1; i <= 10; i++)
			stack_push(s, i);
		assert(stack_size(s) == 22);
		assert(s->capacity == 40);
		stack_drop(s);
	}
	{
		puts("WB Test 2: testing pop capacity resizing");
		stack *s = stack_new();
		stack_push(s, 1);
		stack_push(s, 2);
		stack_push(s, 3);
		assert(stack_size(s) == 3);
		stack_pop(s);
		stack_pop(s);
		assert(stack_size(s) == 1);
		assert(s->capacity == DEFAULT_SIZE);
		stack_pop(s);
		assert(stack_size(s) == 0);
		assert(s->capacity == DEFAULT_SIZE);
		stack_drop(s);
	}
	{
		puts("WB Test 3: testing push & pop capacity resizing");
		stack *s = stack_new();
		assert(s->capacity == DEFAULT_SIZE);
		for (Item i = 1; i <= 12; i++)
			stack_push(s, i);
		assert(stack_size(s) == 12);
		assert(s->capacity == 20);
		for (Item i = 1; i <= 10; i++)
			stack_push(s, i);
		assert(stack_size(s) == 22);
		assert(s->capacity == 40);
		for (Item i = 1; i <= 15; i++)
			stack_pop(s);
		assert(stack_size(s) == 7);
		assert(s->capacity == 20);
		stack_drop(s);
	}
}
