#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

size_t partition (int a[], size_t lo, size_t hi);
void sort_quick_naive (int a[], size_t lo, size_t hi);
void qs_median3 (int a[], size_t lo, size_t hi);
void sort_quick_m3 (int a[], size_t lo, size_t hi);

void swap_idx (int a[], size_t i, size_t j);


int main (int argc, char **argv) {
  size_t n;
  printf("Enter data size: ");
  scanf("%zu", &n);

  int *a = malloc(sizeof(int) * n);
  puts ("Enter data:");
  for (size_t i = 0; i < n; i++)
    scanf("%d", &a[i]);

  // sort_quick_naive (a, 0, n-1);
  // printf ("VALUE: %d", a[0]);
  sort_quick_m3 (a, 0, n-1);



  if (argc == 2) {
    puts("Sorted with -:");
    for (size_t i = 0; i < n; i++)
      printf("%d ", a[i]);
    puts("");
  }

  free(a);
  return EXIT_SUCCESS;
}



// Naive Implementation
size_t partition (int a[], size_t lo, size_t hi)
{
  int v = a[lo];
	size_t i = lo + 1, j = hi;

	while (true) {
		while (a[i] < v && i < j) i++;
		while (v < a[j] && i < j) j--;
		if (i == j) break;
		swap_idx (a, i, j);
	}

	j = a[i] < v ? i : i - 1;
	swap_idx (a, lo, j);
	return j;

}

void sort_quick_naive (int a[], size_t lo, size_t hi)
{
  if (hi <= lo) return;
  size_t part = partition (a, lo, hi);
  sort_quick_naive (a, lo, part ? (part - 1) : 0);
  sort_quick_naive (a, part + 1, hi);
}

// Median-of-Three Implementation

void qs_median3 (int a[], size_t lo, size_t hi)
{
  size_t mid = (lo + hi) / 2;
  if (a[mid] < a[lo]) swap_idx (a, lo, mid);
  if (a[hi] < a[mid]) swap_idx (a, mid, hi);
  if (a[mid] < a[lo]) swap_idx (a, lo, mid);
  // now, we have a[lo] <= a[mid] <= a[hi]
  // swap a[mid] to a[lo+1] to use as pivot
  swap_idx (a, lo+1, mid);

}

void sort_quick_m3 (int a[], size_t lo, size_t hi)
{
  if (hi <= lo) return;
  qs_median3 (a, lo, hi);
  size_t part = partition (a, lo + 1, hi - 1);
  sort_quick_m3 (a, lo, part ? (part - 1) : 0);
  sort_quick_m3 (a, part + 1, hi);
}

// Helpers

void swap_idx (int a[], size_t i, size_t j)
{
  int tmp = a[j];
  a[j] = a[i];
  a[i] = tmp;
}
