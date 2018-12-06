////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 -- Test a Queue ADT implementation.
//
// 2018-12-01	Jashank Jeremy <jashankj@cse.unsw.edu.au>
// YYYY-mm-dd	Your Name Here <zNNNNNNN@student.unsw.edu.au>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "item.h"
#include "queue.h"
#include "testable.h"

void test_empty_queue(void);
void test_one_item_queue(void);
void test_two_item_queue(void);

int main (void)
{
	white_box_tests ();

	test_empty_queue();
	test_one_item_queue();
	test_two_item_queue();

	puts ("\nAll tests passed. You are awesome!");
	return EXIT_SUCCESS;
}

void test_empty_queue (void)
{
	puts ("BB Test 1: testing an empty queue.");
	Queue q = queue_new ();
	assert(queue_size(q) == 0);
	queue_drop(q);
}

void test_one_item_queue(void)
{
	puts ("BB Test 2: testing an one item queue.");
	Queue q = queue_new ();
	queue_en (q, 1);
	assert(queue_size(q) == 1);
	assert(queue_de(q) == 1);
	assert(queue_size(q) == 0);
	queue_drop(q);
}

void test_two_item_queue(void)
{
	puts ("BB Test 3: testing an two item queue.");
	Queue q = queue_new ();
	queue_en (q, 1);
	queue_en (q, 2);
	assert(queue_size(q) == 2);
	assert(queue_de(q) == 1);
	assert(queue_de(q) == 2);
	assert(queue_size(q) == 0);
	queue_drop(q);
}
