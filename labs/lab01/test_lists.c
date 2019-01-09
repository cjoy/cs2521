// COMP2521 19T0 ... lab 01: test a linked list implementation
//
// 2018-11-26	Chris Joy <z5113243@student.unsw.edu.au>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "lists.h"

link arr_to_ll(int*, int);

int main (void)
{
	// Intialise a linked list given an array
	int array[] = {1, 2, 3, 4};
	int array_length = sizeof(array)/sizeof(int);

	// 1.a Linked list
	printf("Linked list:\n");
	link list = arr_to_ll(array, array_length);
	list_print (list);
	// 1.b Sum of linked list
	printf ("Sum of items: %d\n", list_sum_items(list));
	
	// 2 Drop linked list
	list_drop (list);

	// 3.a Circular linked list
	printf("Circular linked list:\n");
	link clist = clist_new(5);
	// 3.b Drop clist
	clist_print (clist);
	// 3.c Drop clist
	list_drop (clist);

	// 4.a Create Doubly linked list from linked list
	printf("Doubly linked list:\n");
	list = arr_to_ll(array, array_length);	
	dlink dlist = dlist_new_from_list(list);
	// 4.b Print dlist
	dlist_print(dlist);
	// 4.c Drop both lists
	list_drop(list);
	dlist_drop(dlist);

	return EXIT_SUCCESS;
}

link arr_to_ll(int *array, int n)
{
	link list = node_new(array[0]);
	link head = list;
	for (int i = 1; i < n; i++) {
		link node = node_new(array[i]);
		list_insert_next(list, node);
		list = list->next;
	}
	return head;
}
