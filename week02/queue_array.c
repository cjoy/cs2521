////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 -- A Queue ADT implementation, using arrays.
//
// 2018-12-01	Jashank Jeremy <jashankj@cse.unsw.edu.au>
// 2018-12-06 Chris Joy <z5113243@student.unsw.edu.au>

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include "item.h"
#include "queue.h"
#include "testable.h"

#define DEFAULT_SIZE 10

typedef struct queue queue;

struct queue {
	size_t n_items;
	size_t capacity;
	ssize_t head;
	ssize_t tail;
	Item *items;
};

/** Create a new, empty Stack.  $ O(1) $. */
queue *queue_new (void)
{
	queue *new = malloc (sizeof *new);
	if (new == NULL)
		err (EX_OSERR, "couldn't allocate queue");
	(*new) = (queue) { .n_items = 0, .capacity = DEFAULT_SIZE, .head = -1, .tail = 0 };

	new->items = calloc (DEFAULT_SIZE, sizeof(Item));
	if (new->items == NULL)
		err (EX_OSERR, "couldn't allocate queue items");

	return new;
}

/** Destroy a Queue.  $ O(1) $. */
void queue_drop (queue *q)
{
	assert (q != NULL);
	free (q->items);
	free (q);
}


/** Add an item to the end of a Queue.  $ O(1) $.
 * Sometimes referred to as "enqueue" or "unshift". */
void queue_en (queue *q, Item it)
{
	assert (q != NULL);
	assert (q->n_items < q->capacity);

	if ((size_t)q->tail == q->capacity-1) {
		q->tail = 0;
	} else if (q->head == -1) { 
		q->head = 0;
	} else {
		q->tail++;
	}

	q->items[q->tail] = it;
	q->n_items++;
}

/** Remove an item from the front of a Queue.  $ O(n) $.
 * Sometimes referred to as "dequeue" or "shift". */
Item queue_de (queue *q)
{
	assert (q != NULL);
	if (q->n_items == 0) {
		fprintf (stderr, "queue underflow!\n");
		abort();
	}

	Item it = q->items[q->head];

	if ((size_t)q->head == q->capacity-1) {
		q->head = 0;
	} else {
		q->head++;
	}

	q->n_items--;

	return it;
}

/** Get the number of items in a Queue.  $ O(1) $. */
size_t queue_size (queue *q)
{
	assert (q != NULL);
	return q->n_items;
}

void white_box_tests (void)
{
	{
		puts("WB Test 1: simple index check for enq");
		Queue q = queue_new();
		queue_en(q, 1);
		assert(q->head == 0);
		assert(q->tail == 0);
		queue_en(q, 2);
		assert(q->head == 0);
		assert(q->tail == 1);
	}
	{
		puts("WB Test 2: checking if tail wraps around "
				 "array when tail reaches capacity");
		Queue q = queue_new();
		for (Item i = 0; (size_t)i < q->capacity; i++)
			queue_en(q, i);
		assert(queue_de(q) == 0);
		assert(queue_de(q) == 1);
		assert(queue_de(q) == 2);
		queue_en(q, 2);
		assert(q->tail == 0);
	}
	{
		puts("WB Test 2: checking if head wraps around "
				 "array when tail reaches capacity");
		Queue q = queue_new();
		for (Item i = 0; (size_t)i < q->capacity; i++)
			queue_en(q, i);
		assert(queue_de(q) == 0);
		assert(queue_de(q) == 1);
		queue_en(q, 34);
		assert(q->head == 2);
	}
}
