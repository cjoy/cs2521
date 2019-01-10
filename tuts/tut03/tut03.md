## Recursive Functions
Write a recursive function

bool all_even (int a[], size_t l, size_t r);
which takes an array, and the left-most and right-most indices of the current segment of the array as arguments, and checks if all elements in an array are even.

Use a divide and conquer approach, by splitting the array in half, first checking if all the elements in the left half are even, and then, only if necessary, checking the right half.

What would the worst-case time complexity be in big-O notation?

### Solution
```C
bool all_even (int a[], size_t l, size_t r)
{
  if (l == r && a[l] % 2 == 0) return true;
  if (a[l] % 2 != 0) return false;
  if (a[r] % 2 != 0) return false;
  return all_even(a, l+1, r-1);
}
```

## Functions in a Binary Search Tree
Assume the following representation of a binary tree:

```C
typedef struct btree_node btree_node;

struct btree_node {
	Item item;
	btree_node *left;
	btree_node *right;
};
```

### int_btree_sum
Assume our binary tree holds items of type int. Write a function to recursively sum the items of a binary tree. Your function should have the following prototype:

#### Solution
```C
int int_btree_sum (btree_node *tree)
{
  if (!tree) return 0;
  return tree->item + int_btree_sum(tree->left) + int_btree_sum(tree->right);
}
```

## btree_search
Write two functions that search for a given item in a binary search tree, returning true if the item is found, and false otherwise. One should be iterative; the other should be recursive:

#### Solution
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

```C
void btree_drop (btree_node *tree)
{
  if (!tree) return;
  if (tree->right) btree_drop(tree->right);
  if (tree->left) btree_drop(tree->left);
  free (tree);
}
```