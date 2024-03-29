/* 
 * COMP1927 13s2 prac exam question again! so you should be able to do it!
 * Test files by Oliver Tan (otan@cse.unsw.edu.au)
 *
 * Complete "append", which insert l2 at the end of list l1
 * (then l2 becomes an empty list)
 * l1 & l2 are guarenteed to be not null
 *
 * Compile: gcc -Wall -Werror -O -o testList testList.c list.c
 * Run: ./testList
*     
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* do you want the program to work? if so, don't change this */
Node createNode(int i) {
    Node n = malloc(sizeof(struct _node));
    n->next = NULL;
    n->prev = NULL;
    n->data = i;
    return n;
}

/* ... or this */
List createList(void) {
    List l = malloc(sizeof(*l));
    l->first = NULL;
    l->last = NULL;
    l->size = 0;
    return l;
}

/* but do change this! */
void append(List l1, List l2) {
    if ((!l1 && !l2) || !l2) return;
    if ((!l1->first && !l2->first) || !l2->first) return;
    if (!l1->first && l2->first) {
        l1->size = l2->size;
        l1->first = l2->first;
        l1->last = l2->last;
        l2->first = l2->last = NULL;
        l2->size = 0;
        return;
    }

    l1->last->next = l2->first;
    l2->first->prev = l1->last;
    l1->last = l2->last;
    l1->size += l2->size;
    l2->last = l2->first = NULL;
    l2->size = 0;
}
