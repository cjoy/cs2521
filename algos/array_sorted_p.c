#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

bool array_sorted_p (int a[], int lo, int hi)
{
  if (lo == hi) return true;

  if (a[lo] > a[hi]) return false;

  return array_sorted_p (a, lo+1, hi)
      && array_sorted_p (a, lo, hi-1);
}

int main ()
{

  int a[] = {1, 43, 43, 54, 65, 75};
  assert (array_sorted_p (a, 0, 5) == true);

  int b[] = {1, 43, 43, 23, 65, 75};
  assert (array_sorted_p (b, 0, 5) == false);

  int c[] = {1};
  assert (array_sorted_p (c, 0, 0) == true);

  return 0;
}