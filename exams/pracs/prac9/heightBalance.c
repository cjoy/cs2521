#include <stdlib.h>
#include <stdio.h>
#include "heightBalance.h"

int max(int a, int b) {
    return a > b ? a : b;
}

int height(treelink tree) {
    if (!tree) return 0;
    return 1 + max(height(tree->left), height(tree->right));
}

/*
    given a tree, check whether it is height balanced.

    height balance is defined as the |height of right tree - height of left tree| <= 1
    compile:
    gcc -Wall -Werror -O -o heightBalanceTest heightBalance.c testHeightBalance.c
*/
int isHeightBalanced(treelink tree) {
    if (!tree) return 1;
    int l = height (tree->left);
    int r = height (tree->right);
    return (abs(l - r) <= 1)
        && isHeightBalanced(tree->left)
        && isHeightBalanced(tree->right);
}
