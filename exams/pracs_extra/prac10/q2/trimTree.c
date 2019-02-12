#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "trimTree.h"
/*
    given a minimum and maximum value, only keep elements
    between min and max exclusive in a BST.

    return the resulting tree. memory must be free'd

    compile:
    gcc -Wall -Werror -O -o trimTreeTest trimTree.c testTrimTree.c
*/
treelink trimTree(treelink t, int min, int max) {
    if (!t) return t;

    // root case
    if (t->item <= min || t->item >= max) {
        t = NULL;
        return t;
    }

    // FILL THIS IN
    treelink curr = NULL;
    treelink prev = NULL;

    // find min node and free subtree (including root)
    for (curr = t, prev = curr; curr; prev = curr, curr = curr->left)
        if (curr->item <= min) {
            prev->left = prev->left->right;
            break;
        }


    // find max node and free subtree (including root)
    for (curr = t, prev = curr; curr; prev = curr, curr = curr->right)
        if (curr->item >= max) {
            prev->right = prev->right->left;
            break;
        }


    return t;
}