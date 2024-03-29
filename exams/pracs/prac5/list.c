/* 
 * Test files by Oliver Tan (otan@cse.unsw.edu.au)
 *
 * Question from 1927 13s2, Week 7 test (look where we are now)
 * This IS a harder question. Probably the last linked list question!
 *
 * Complete partition(List l, int val), which takes in a list
 * and returns a NEW list containing all items <= val, whilst
 * the existing list only contains items > val
 *
 * For example:
 * originalList: [0]->[4]->[3]->[6]->[5]->[2]->[X]
 * partition(originalList, 3);
 * newList (returned): [0]->[3]->[2]->[X]
 * originalList (retained): [4]->[6]->[5]->[X]
 *
 * NOTE: order relative to both lists must be maintained!
 * NOTE 2: assume l is NOT null
 * NOTE 3: there are a LOT of tests for this... don't be alarmed.
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
    n->data = i;
    return n;
}

/* ... or this */
List createList(void) {
    List l = malloc(sizeof(*l));
    l->first = NULL;
    return l;
}


void appendToList(List l, Node n) {
    if (!l->first) {
        l->first = n;
    } else {
        Node curr = l->first;
        for (; curr->next; curr = curr->next) {}
        curr->next = n;
    }
}

void removeFromList(List l, Node n) {
    if (l->first == n) {
        l->first = l->first->next;
    } else {
        Node curr = l->first;
        Node prev = NULL;
        for (; curr && curr != n; prev = curr, curr = curr->next) {}
        prev->next = curr->next;
    }
}

/* but do change this! */
List partition(List l, int val) {
    List l2 = createList();
    
    Node prev = NULL;
    Node next = NULL;
    for (Node curr = l->first; curr; curr = next) {
        if (curr->data <= val) {
            // add to new list
            appendToList(l2, createNode(curr->data));
            // remove from existing list
            removeFromList(l, curr);
        }
        prev = curr;
        next = curr->next;
    }

    return l2;
}
