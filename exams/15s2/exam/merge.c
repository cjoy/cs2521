#include <stdio.h>
#include <stdlib.h>

#define min(A,B) ((A < B) ? A : B)
void merge(char a[], int lo, int mid, int hi);

void mergesort(char a[], int lo, int hi)
{
   int i, m; // m = length of runs
   int end; // end of 2nd run
   for (m = 1; m <= hi-lo; m = 2*m) {
      for (i = lo; i <= hi-m; i += 2*m) {
         end = min(i+2*m-1, hi);
         merge(a, i, i+m-1, end);
      }
//      printf("%s\n", a);
   }
}

void merge(char a[], int lo, int mid, int hi)
{
   int  i, j, k, n = hi-lo+1;
   char *tmp = malloc(n*sizeof(char));
   i = lo; j = mid+1; k = 0;
   // scan both segments, copying to tmp
   while (i <= mid && j <= hi) {
     if (a[i] < a[j])
        tmp[k++] = a[i++];
     else
        tmp[k++] = a[j++];
   }
   // copy items from unfinished segment
   while (i <= mid) tmp[k++] = a[i++];
   while (j <= hi) tmp[k++] = a[j++];
   //copy tmp back to main array
   for (i = lo, k = 0; i <= hi; i++, k++)
      a[i] = tmp[k];
   free(tmp);
}

int main ()
{
    char *s = "sortingisawesome";
    mergesort(s, 0, 15);
}
