// COMP2521 19T0 ... lab 01: a linked list implementation
//
// 2018-11-24	Jashank Jeremy <jashank.jeremy@unsw.edu.au>
// 2018-11-26	Chris Joy <z5113243@student.unsw.edu.au>

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include "lists.h"

/** Traverses and prints the list. */
void list_print (link list)
{
	for (; list; list = list->next)
		printf ("[%d]->", list->item);
	puts ("|");
}

/** Create a new node, initialised with the item provided.
 * Return a pointer to node (link) */
link node_new (Item it)
{
	link node = malloc (sizeof (*node));
	if (!node) err (1, "couldn't allocate");
	node->item = it;
	node->next = NULL;
	return node;
}

/** Insert a new node into a given non-empty list.
 * The node is inserted directly after the head of the list. */
void list_insert_next (link list, link node)
{
	assert (list);
	assert (node);
	node->next = list->next;
	list->next = node;
}

/** Return the sum of all items in list */
int list_sum_items (link list)
{
	int sum = 0;
	for (; list; list = list->next)
		sum += list->item;
	return sum;
}

/** Frees all memory used in the list */
void list_drop (link list)
{
	link start_node = list;
	link node;
	while (list) {
		node = list;
		list = list->next;
		free(node);
		if (list == start_node) break;
	}
}

/** Create a circular list with the specified number of nodes,
 * with each link storing data from 1 to the number of nodes. */
link clist_new (int n_nodes)
{
	if (n_nodes <= 0) return NULL;
	link clist = node_new(1);
	link head = clist;
	for (int i = 2; i <= n_nodes; i++) {
		link node = node_new(i);
		list_insert_next(clist, node);
		clist = clist->next;
	}
	clist->next = head;
	return head;
}

/** print the data in a circular fashion starting from any node */
void clist_print (link clist)
{
	if (!clist) return;
	link start_node = clist;
	printf ("[%d]->", clist->item);
	for (clist = clist->next; clist; clist = clist->next) {
		if (clist == start_node) {
			printf ("|\n");
			break;
		}
		printf ("[%d]->", clist->item);
	}
}

/** Create a double-linked list which contains the same values,
 * in the same order as 'list' */
dlink new_dnode (Item it)
{
	dlink dnode = malloc(sizeof *dnode);
	if (!dnode) err (1, "couldn't allocate");
	dnode->item = it;
	dnode->next = NULL;
	dnode->prev = NULL;
	return dnode;		
}

dlink dlist_new_from_list (link list)
{
	if (!list) return NULL;
	dlink dlist = new_dnode(list->item);
	dlink head = dlist;
	list = list->next;
	while(list) {
		dlist->next = new_dnode(list->item);
		dlist->next->prev = dlist;
		dlist = dlist->next;
		list = list->next;
	}
	return head;
}

/** Print a doubly-linked list. */
void dlist_print (dlink list)
{
	for (int spaces = 0; list; list = list->next) {
		printf("%*s", spaces*10, "");
		if (list->prev) printf("[%d]->", list->prev->item);
		if (list) printf("[%d]", list->item);
		if (list->next) printf("->[%d]", list->next->item);
		printf("\n");
		spaces++;
	}
}

/** Frees all the memory used in the double-linked list */
void dlist_drop (dlink list)
{
	dlink node;
	while (list) {
		node = list;
		list = list->next;
		free(node);
	}
}
