# Algorithmic Complexity (I)
Consider two functions f() and g() which both perform the same task.

The time cost for f(n) is T(f(n)) = 100n, while the time cost for g(n) is T(g(n)) = 2n^2.
* Which function is faster for n=10?
* Which function is faster for n=20?
* Which function is faster for n=100?
* Which function is faster for n=1000?
* What is the crossover point where f() becomes more efficient than g()?
## Answer

# Algorithmic Complexity (III)
Calculate how long T(n) steps would take for different sizes of n for the various T(n) functions in the table below.
Assume you are running it on a computer that performs one billion steps per second (roughly on par with a current smartphone).

t(n)=
---------------------------------------------------------
|   n   |   logn  |   n   |   n^2   |   n^3   |   2^n   |
---------------------------------------------------------
|  10   |         |       |         |         |         |
---------------------------------------------------------
|  20   |         |       |         |         |         |
---------------------------------------------------------
|  50   |         |       |         |         |         |
---------------------------------------------------------
|  100  |         |       |         |         |         |
---------------------------------------------------------
|  1000 |         |       |         |         |         |
---------------------------------------------------------
|  10000|         |       |         |         |         |
---------------------------------------------------------

For what size of n does the computation time for T(n) = 2^n become too large to be practical? Would it help if we used a computer that was a million times faster?
## Answer

## Recursive Functions
Write a recursive function
```C
bool all_even (int a[], size_t l, size_t r);
```
which takes an array, and the left-most and right-most indices of the current segment of the array as arguments, and checks if all elements in an array are even.

Use a divide and conquer approach, by splitting the array in half, first checking if all the elements in the left half are even, and then, only if necessary, checking the right half.
## Solution
```C
bool all_even (int a[], size_t l, size_t r)
{
  if (l == r && a[l] % 2 == 0) return true;
  if (a[l] % 2 != 0) return false;
  if (a[r] % 2 != 0) return false;
  return all_even(a, l+1, r-1);
}
```
What would the worst-case time complexity be in big-O notation?
## Answer


# Binary Search Trees
Insert these keys into a BST, assuming normal integer ordering: [10,20,5,30,15,25,24].

What is the height of this tree?
## Answer

Delete [5,30,20], assuming we replace nodes with the left-most node of the right sub-tree when necessary.

What is the height of the tree after this deletion?
## Answer

Show the output obtained by traversing the tree and printing out each node in the following orders:
prefix (NLR):
postfix (LRN):
infix (LNR):
level-order:
## Answer


# Functions in a Binary Search Tree
Assume the following representation of a binary tree:

```C
typedef struct btree_node btree_node;

struct btree_node {
	Item item;
	btree_node *left;
	btree_node *right;
};
```

## int_btree_sum
Assume our binary tree holds items of type int. Write a function to recursively sum the items of a binary tree. Your function should have the following prototype:

### Solution
```C
int int_btree_sum (btree_node *tree)
{
  if (!tree) return 0;
  return tree->item + int_btree_sum(tree->left) + int_btree_sum(tree->right);
}
```

## btree_search
Write two functions that search for a given item in a binary search tree, returning true if the item is found, and false otherwise. One should be iterative; the other should be recursive:

### Solution
```C
bool btree_search_iter (btree_node *tree, Item key)
{

}

bool btree_search_rec (btree_node *tree, Item key)
{
  if (!tree) return false;
  if (tree->item == key) return true;
  if (tree->left) return btree_search_rec (tree->left, key);
  if (tree->right)  return btree_search_rec (tree->right, key);
  return false;
}
```

## btree_drop
Write a function that will free all the memory associated with a tree:
### Solution
```C
void btree_drop (btree_node *tree)
{
  if (!tree) return;
  if (tree->right) btree_drop(tree->right);
  if (tree->left) btree_drop(tree->left);
  free (tree);
}
```

## btree_traverse, with function pointers
Consider a function btree_traverse that traverses a binary tree, taking a function pointer. What would its prototype be? How would you call the function?

Assume it takes functions with prototypes like
```C
void item_show (Item it);
```
### Solution
```C
\\TODO
```
