/*
 * Oliver Tan
 *
 * finish the function createSequentialList(int n);
 * that takes in n and create a list from 1 to n inclusive
 *
 * e.g. createSequentialList(3)
 * [1]->[2]->[3]->[X]
 * e.g. createSequentialList(0);
 * [X]
 * note you return the first element of the linked list.
 * note there is createNode to help you.
 *
 * Compile: gcc -Wall -Werror -O -o testList testList.c list.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Node createNode(int i) {
    Node n = malloc(sizeof(struct _node));
    n->next = NULL;
    n->data = i;
    return n;
}

Node createSequentialList(int n) {
    if (n < 1) return NULL;
    Node list = createNode(1);
    Node head = list;
    for (int i = 2; i <= n; i++) {
        Node new = createNode(i);
        list->next = new;
        list = list->next;
    }
    return head;
}
