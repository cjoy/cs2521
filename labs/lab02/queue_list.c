////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 -- A Queue ADT implementation, using linked lists.
//
// 2018-12-01	Jashank Jeremy <jashankj@cse.unsw.edu.au>
// 2018-12-06	Chris Joy <z5113243@student.unsw.edu.au>

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include "item.h"
#include "queue.h"
#include "testable.h"

typedef struct queue queue;
typedef struct queue_node queue_node;

struct queue {
	size_t n_items;
	queue_node *head, *tail;
};

struct queue_node {
	Item item;
	queue_node *next;
};

static queue_node *queue_node_new (Item);

/** Create a new, empty Queue. */
queue *queue_new (void)
{
	queue *new = malloc (sizeof *new);
	if (new == NULL) err (EX_OSERR, "couldn't allocate queue");
	(*new) = (queue) { .n_items = 0, .head = NULL, .tail = NULL };
	return new;
}

/** Destroy a Queue, releasing all resources associated with it. */
void queue_drop (queue *q)
{
	assert (q != NULL);
	queue_node *curr = q->head;
	queue_node *next;
	for (; curr; curr = next) {
		next = curr->next;
		free(curr);
	}
	free(q);
}

/** Add an item to the end of a Queue.
 * Sometimes referred to as "enqueue" or "unshift". */
void queue_en (queue *q, Item it)
{
	queue_node *node = queue_node_new (it);
	if (!q->tail) {
		q->head = q->tail = node;
	} else {
		q->tail->next = node;
		q->tail = node;
	}
	q->n_items++;
}

/** Remove an item from the front of a Queue.
 * Sometimes referred to as "dequeue" or "shift". */
Item queue_de (queue *q)
{
	Item it = q->head->item;
	queue_node *del = q->head;
	q->head = q->head->next;
	free (del);
	q->n_items--;
	return it;
}

/** Get the number of items in a Queue. */
size_t queue_size (queue *q)
{
	assert (q != NULL);
	return q->n_items;
}

static queue_node *queue_node_new (Item it)
{
	queue_node *new = malloc (sizeof *new);
	if (new == NULL) err (EX_OSERR, "couldn't allocate queue_node");
	(*new) = (queue_node) { .item = it, .next = NULL };
	return new;
}

void white_box_tests (void)
{
	{
		puts("WB Test 1: testing empty q");
		queue *q = queue_new();
		assert(q->n_items == 0);
		assert(q->head == NULL);
		assert(q->head == q->tail);
		queue_drop(q);
	}
	{
		puts("WB Test 2: testing enq on single item");
		queue *q = queue_new();
		queue_en(q, 1);
		assert(q->n_items == 1);
		assert(q->head == q->tail);		
		queue_drop(q);
	}
	{
		puts("WB Test 3: testing enq with 1mil items");
		queue *q = queue_new();
		Item n = 1000000;
		for (Item i = 1; i <= n; i++)
			queue_en(q, i);
		assert(q->n_items == (size_t)n);
		queue_drop(q);
	}
	{
		puts("WB Test 4: testing deq with 1mil items");
		queue *q = queue_new();
		Item n = 1000000;
		for (Item i = 1; i <= n; i++)
			queue_en(q, i);
		for (Item i = 1; i <= n; i++)
			assert(queue_de(q) == i);
		assert(q->n_items == 0);
		queue_drop(q);
	}
}
