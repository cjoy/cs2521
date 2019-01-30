#include <stdio.h>

int array_max (int a[], int lo, int hi)
{
  if (lo == hi) return a[lo];

  return a[lo] < a[hi]
    ? array_max(a, lo+1, hi)
    : array_max(a, lo, hi-1);
}

int main()
{
  int a[] = {1, 4, 5, 3, 5, 5, 6, 34, 45, 5, 4};
  printf ("max: %d\n", array_max(a, 0, 9));

  int b[] = {34, 43, 93, 34, 43 , 34, 12, 23, 32, 23};
  printf ("max: %d\n", array_max(b, 0, 9));
}