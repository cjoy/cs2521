#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef unsigned long long Item;
#define key(A) (A)
#define less(A,B) (key(A) < key(B))

typedef enum {
  NAIVE,
  RANDOM
} PivotMode;

static inline void swap_idx (Item items[], size_t a, size_t b);
void sort_quick (Item items[], size_t lo, size_t hi, PivotMode mode);
static size_t partition (Item items[], size_t lo, size_t hi, PivotMode mode);
void qs_median3 (Item a[], size_t lo, size_t hi);
void sort_quick_m3 (Item a[], size_t lo, size_t hi, PivotMode mode);
void print_list (Item a[], size_t n);

int main (int argc, char **argv) {
  Item n;
  printf("Enter data size: ");
  scanf("%lld", &n);

  char *option = "";
  Item *a = malloc(sizeof(Item) * n);
  
  puts ("Enter data:");
  for (size_t i = 0; i < n; i++)
    scanf("%lld", &a[i]);

  if (argc >= 2 && strcmp (argv[1], "-pn") == 0) {
    option = "naive pivot";
    sort_quick (a, 0, n-1, NAIVE);
  } else if (argc >= 2 && strcmp (argv[1], "-pm") == 0) {
    option = "median of three pivot";
    sort_quick_m3 (a, 0, n-1, NAIVE);
  } else if (argc >= 2 && strcmp (argv[1], "-pr") == 0) {
    option = "randomised pivot";
    sort_quick (a, 0, n-1, RANDOM);
  } else {
    puts ("invalid option");
    return EXIT_FAILURE;
  }

  printf ("Sorted with %s:\n", option);
  if (argc == 2) {
    print_list (a, n);
  }

  free(a);
  return EXIT_SUCCESS;
}

//////////////////////////////////////////////////////////////////////

void sort_quick (Item items[], size_t lo, size_t hi, PivotMode mode)
{
	if (hi <= lo) return;
	size_t part = partition (items, lo, hi, mode);
	sort_quick (items, lo, (part == 0) ? 0 : (part - 1), mode);
	sort_quick (items, part + 1, hi, mode);
}

//////////////////////////////////////////////////////////////////////

void qs_median3 (Item a[], size_t lo, size_t hi)
{
  size_t mid = (lo + hi) / 2;
  if (less (a[mid], a[lo])) swap_idx (a, lo, mid);
  if (less (a[hi], a[mid])) swap_idx (a, mid, hi);
  if (less (a[mid], a[lo])) swap_idx (a, lo, mid);
  // now, we have a[lo] <= a[mid] <= a[hi]
  // swap a[mid] to a[lo+1] to use as pivot
  swap_idx (a, lo+1, mid);
}

void sort_quick_m3 (Item a[], size_t lo, size_t hi, PivotMode mode)
{
  if (hi <= lo) return;
  qs_median3 (a, lo, hi);
  size_t part = partition (a, lo, hi, mode);
  sort_quick_m3 (a, lo, part ? (part - 1) : 0, mode);
  sort_quick_m3 (a, part + 1, hi, mode);
}

//////////////////////////////////////////////////////////////////////

static size_t partition (Item items[], size_t lo, size_t hi, PivotMode mode)
{
	Item v = items[lo];

  // random pivot
  if (mode == RANDOM)
    v = items[(unsigned long)rand()%hi];

	size_t i = lo + 1, j = hi;

	for (;;) {
		while (less (items[i], v) && i < j) i++;
		while (less (v, items[j]) && i < j) j--;
		if (i == j) break;
		swap_idx (items, i, j);
	}

	j = less (items[i], v) ? i : i - 1;
	swap_idx (items, lo, j);
	return j;
}

static inline void swap_idx (Item items[], size_t a, size_t b)
{
	Item t = items[b]; items[b] = items[a]; items[a] = t;
}

void print_list (Item a[], size_t n)
{
  for (size_t i = 0; i < n; i++)
    printf("%lld ", a[i]);
  puts("");
}
