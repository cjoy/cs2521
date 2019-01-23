# Hold Your Horses!
Consider the following simple table of enrolments, sorted by course code:

course	name	program
COMP1927	Jane	3970
COMP1927	John	3978
COMP1927	Pete	3978
MATH1231	John	3978
MATH1231	Adam	3970
PSYC1011	Adam	3970
PSYC1011	Jane	3970
Now we wish to sort it by student name, so that we can easily see what courses each student is studying. Show an example of what the final table would look like…

if we used a stable sorting algorithm
if we used a non-stable sorting algorithm
It is fairly easy to write a function to determine whether an array of integers is sorted. A trickier problem is to determine whether the sort algorithm that produced a sorted array is stable.

Assume that the array is composed of Items with two fields, as in:
```C
typedef struct { int a; int b; } Item;
```
Assume also that the array has been sorted on the Item.a field.

Given the final sorted array alone, you cannot determine whether the sort was stable. We also assume that the sorting client keeps a copy of the original array, which is available for checking.

Given the above, write a function that takes the original array, the sorted array, and determines whether the sort was stable. Use this prototype:

```C
bool stable_sort_p (Item *unsorted, Item *sorted, int lo, int hi);
```

## Solution
```C
bool stable_sort_p (Item *unsorted, Item *sorted, int lo, int hi)
{
  
}
```

# Sort it out! (I)
/*  1 */	void sort_insertion (int items[], size_t n)
/*  2 */	{
/*  3 */		for (size_t i = 1; i < n; i++) {
/*  4 */			int item = items[i];
/*  5 */			size_t j = i;
/*  6 */			for (/* j */; j > 0; j--) {
/*  7 */				if (item < items[j - 1]) {
/*  8 */					// item shifts along to make room
/*  9 */					items[j] = items[j - 1];
/* 10 */				} else {
/* 11 */					break;
/* 12 */				}
/* 13 */			}
/* 14 */			items[j] = item;
/* 15 */		}
/* 16 */	}
Show each of the following arrays as they are sorted by the program above. For each one, count the number of comparisons and number of shifts.

{
3
,
2
,
4
,
8
,
1
}
,
{
1
,
2
,
3
,
4
,
5
}
,
{
5
,
4
,
3
,
2
,
1
}
.
For each line of code, determine a cost and a formula expressing the number of times the statement on that line will be executed when sorting 
n
 items, in the worst case.

What is the asymptotic worst-case time complexity of the algorithm implemented by this program?

What is the time complexity of the algorithm implemented by this program, in the best case?

Is this sorting algorithm stable?

Sort it out! (II)
Consider the implementations of the following sorting functions.
```C
/// Bubble-sort.
void sort_bubble (int items[], size_t n)
{
	for (size_t i = n - 1; i > 0; i--)
		for (size_t j = 1; j <= i; j++)
			if (items[j] < items[j - 1])
				swap_idx (items, j, j - 1);
}

/// Bubble-sort with early exit.
void sort_bubble_ee (int items[], size_t n)
{
	bool no_swaps = false;
	for (size_t i = n - 1; i > 0 && !no_swaps; i--) {
		no_swaps = true;
		for (size_t j = 1; j <= i; j++)
			if (items[j] < items[j - 1]) {
				no_swaps = false;
				swap_idx (items, j, j - 1);
			}
	}
}

/// Selection sort.
void sort_selection (int items[], size_t n)
{
	for (size_t i = 0; i < n; i++) {
		size_t low = i;
		for (size_t j = i + 1; j < n; j++)
			if (items[j] < items[low])
				low = j;
		swap_idx (items, i, low);
	}
}
```
Show how each of the functions behaves when given this array:

int nums[8] = { 4, 6, 2, 7, 8, 5, 1, 3 };
Which implementations are adaptive?

Which implementations are stable?

(b)Link, and you’ll miss it
Write a version of selection sort that builds a new sorted list from an original unsorted linked list. The original list should not be modified during the sorting.

Here’s a linked list definition –
```C
struct node {
	int item;
	node *next;
};
```
– and here’s a prototype:
```C
node *list_sort_selection (node *ls);
```

## Solution
```C
node *list_sort_selection (node *ls)
{
  node *min = NULL;

  for (node *curr = ls; curr; curr = curr->next) {
    if (min == NULL) {
      min = curr;
    } else {

    }
  }
}
```

Is your implementation stable?

# What the Shell!
Consider the following Shell sort algorithm, based on Sedgewick’s implementation:
```C
void sort_shell (int items[], size_t n)
{
	// Calculate starting `h'-value
	size_t h;
	for (h = 1; h <= (n - 1) / 9; h = (3 * h) + 1)
		printf("%zu ", h);
	puts ("");

	for (/* h */; h > 0; h /= 3) {
		// when `h' = 1, this is an insertion sort.
		for (size_t i = h; i < n; i++) {
			int key = items[i];
			size_t j = i;
			for (/* j */; j >= h && key < items[j - h]; j -= h)
				items[j] = items[j - h];
			items[j] = key;
		}
	}
}
```
Describe how this would sort an array containing the first 100 positive integers sorted in descending order (i.e. [100, 99, 98, 97, 96, 95 , ⋯ , 1]).

