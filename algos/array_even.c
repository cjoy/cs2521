#include <stdio.h>

int array_even (int a[], int lo, int hi)
{
  if (lo == hi) return a[lo] % 2 == 0;

  return a[lo] % 2 == 0
    && a[hi] % 2 == 0
    && array_even(a, lo+1, hi)
    && array_even(a, lo, hi-1);
}

int main()
{
  int a[] = {1, 4, 5, 3, 5, 5, 6, 34, 45, 5, 4};
  printf ("even: %d\n", array_even(a, 0, 9));

  int b[] = {34, 42, 94, 30, 46 , 30, 12, 20, 32, 8754};
  printf ("even: %d\n", array_even(b, 0, 9));
}