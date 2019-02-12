/* This is an edited interview question found commonly on glassdoor, and asked to me before.
 * There are two parts to this question.
 * 
 * Essence of question)
 * Check whether a doubly linked list, representing a string (without the NULL terminator) 
 * is a palindrome.
 *
 * Part 1) Take the literal meaning of a palindrome.
 * e.g. isPalindrome([a]<->[s]<->[a]) is True
 * e.g. isPalindrome([a]<->[a]) is True
 * e.g. isPalindrome([a]<->[s]<->[b]) is False
 *
 * Part 2) Ignore punctuation, numbers and case. Only letters have to match.
 * e.g. isPalindrome([A]<->[,]->[ ]->[a]) is True
 * e.g. isPalindrome([A]->[,]) is True
 * e.g. isPalindrome([A]->[,]->[b]) is False
 *
 * compile: gcc -Wall -Werror -O -o list list.c testList.c
 * test: ./list
 */

#include <stdio.h>
#include <stdlib.h>
// Note: toupper, isalpha is available in ctype.h
//   e.g. toupper('a') == 'A', toupper('A') == 'A', isalpha(' ') == 0, isalpha('A') == 1
#include <ctype.h>
#include "list.h"

/* do you want the program to work? if so, don't change this */
Node createNode(char i) {
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
    return l;
}

/* but do change this! */

// Recursive version - doesn't take into account punctuation
int isPalindromeRecursive(List l) {
    if (!l || (!l->first && !l->last) || (l->first == l->last)) {
        return 1;
    } else if (l->first->data != l->last->data) {
        return 0;
    } else {
        char first = l->first->data;
        char last = l->last->data;
        l->first = l->first->next;
        l->last = l->last->prev;
        return (first == last) && isPalindromeRecursive(l);
    }
}

// Iterative version
int isPalindromeIterative(List l) {
    return 0;
}

int isPalindrome(List l) {
    return isPalindromeIterative(l);
    // return isPalindromeRecursive(l);
}



