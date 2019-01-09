////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 -- Test a Stack ADT implementation.
//
// 2018-11-29	Jashank Jeremy <jashankj@cse.unsw.edu.au>
// 2018-12-06	Chris Joy <z5113243@student.unsw.edu.au>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "item.h"
#include "stack.h"
#include "testable.h"

static void test_empty_stack (void);
static void test_one_item_stack (void);
static void test_thousand_item_stack (void);
static void test_million_item_stack (void);
static void test_rapid_push_pop (void);

int main (void)
{
	white_box_tests ();

	test_empty_stack ();
	test_one_item_stack ();
	test_thousand_item_stack ();
	test_million_item_stack ();
	test_rapid_push_pop ();

	puts ("\nAll tests passed. You are awesome!");
	return EXIT_SUCCESS;
}

static void test_empty_stack (void)
{
	puts ("BB Test 1: testing an empty stack.");
	Stack s = stack_new ();
	assert (stack_size (s) == 0);
	stack_drop (s);
}

static void test_one_item_stack (void)
{
	puts ("BB Test 2: testing a stack with one item.");
	Stack s = stack_new ();
	stack_push (s, 1);
	assert (stack_size (s) == 1);
	assert (stack_pop (s) == 1);
	assert (stack_size (s) == 0);
	stack_drop (s);
}

static void test_thousand_item_stack (void)
{
	puts ("BB Test 3: testing a stack with a thousand items.");
	Stack s = stack_new ();
	for (Item i = 1; i <= 1000; i++)
		stack_push (s, i);
	assert (stack_size (s) == 1000);
	assert (stack_pop (s) == 1000);
	assert (stack_size (s) == 999);
	stack_drop (s);
}

static void test_million_item_stack (void)
{
	puts ("BB Test 4: testing a stack with a million items.");
	Stack s = stack_new ();
	for (Item i = 1; i <= 1000000; i++)
		stack_push (s, i);
	assert (stack_size (s) == 1000000);
	assert (stack_pop (s) == 1000000);
	assert (stack_size (s) == 999999);
	stack_drop (s);
}

static void test_rapid_push_pop (void)
{
	puts ("BB Test 5: testing a stack with rapid push & pop.");
	Stack s = stack_new ();
	for (Item i = 1; i <= 1000000; i++)
		stack_push (s, i);
	assert (stack_size (s) == 1000000);
	for (Item i = 1; i <= 500000; i++)
		stack_pop (s);
	assert (stack_size (s) == 500000);
	for (Item i = 1; i <= 250000; i++)
		stack_pop (s);
	assert (stack_size (s) == 250000);
	for (Item i = 1; i <= 250000; i++)
		stack_push (s, i);
	assert (stack_size (s) == 500000);
	for (Item i = 1; i <= 500000; i++)
		stack_pop (s);
	assert (stack_size (s) == 0);
	stack_push (s, 1);
	assert (stack_size (s) == 1);
	stack_drop (s);
}
