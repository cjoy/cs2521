////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 -- Test a Queue ADT implementation.
//
// 2018-12-01	Jashank Jeremy <jashankj@cse.unsw.edu.au>
// 2018-12-06	Chris Joy <z5113243@student.unsw.edu.au>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "item.h"
#include "queue.h"
#include "testable.h"

void test_empty_queue(void);
void test_one_item_queue(void);
void test_two_item_queue(void);
void test_multiple_queue(void);

int main (void)
{
	white_box_tests ();

	test_empty_queue();
	test_one_item_queue();
	test_two_item_queue();
	test_multiple_queue();

	puts ("\nAll tests passed. You are awesome!");
	return EXIT_SUCCESS;
}

void test_empty_queue (void)
{
	puts ("BB Test 1: an empty queue.");
	Queue q = queue_new ();
	assert(queue_size(q) == 0);
	queue_drop(q);
}

void test_one_item_queue(void)
{
	puts ("BB Test 2: add one item to a queue.");
	Queue q = queue_new ();
	queue_en (q, 1);
	assert(queue_size(q) == 1);
	assert(queue_de(q) == 1);
	assert(queue_size(q) == 0);
	queue_drop(q);
}

void test_two_item_queue(void)
{
	puts ("BB Test 3: add two items to a queue.");
	Queue q = queue_new ();
	queue_en (q, 1);
	queue_en (q, 2);
	assert(queue_size(q) == 2);
	assert(queue_de(q) == 1);
	assert(queue_de(q) == 2);
	assert(queue_size(q) == 0);
	queue_drop(q);
}

void test_multiple_queue(void)
{
	puts ("BB Test 4: multiple enq and deq.");
	Queue q = queue_new ();
	for (Item i = 1; i <= 10; i++)
		queue_en (q, i);
	assert(queue_size(q) == 10);
	assert(queue_de(q) == 1);
	assert(queue_de(q) == 2);
	assert(queue_size(q) == 8);
	queue_drop(q);
}
