#include <stdlib.h>
#include <stdio.h>
#include "heightBalance.h"


int max(int a, int b) {
    return a > b ? a : b;
}

int height(treelink t) {
    if (!t) return 0;
    return 1 + max(height(t->left), height(t->right));
}

/*
    given a tree, check whether it is height balanced.

    height balance is defined as the |height of right tree - height of left tree| <= 1
    compile:
    gcc -Wall -Werror -O -o heightBalanceTest heightBalance.c testHeightBalance.c
*/
int isHeightBalanced(treelink t) {
    if (!t) return 1;
    return abs(height(t->left) - height(t->right)) < 2
        && isHeightBalanced(t->right)
        && isHeightBalanced(t->left);
}
