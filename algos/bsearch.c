int bsearch (int key, int a[], int lo, int hi)
{
    if (lo > hi) return -1;

    int mid = (lo + hi) / 2;
    if (key < a[mid]) {
        return bsearch (key, a, lo, mid);
    } else if (key > a[mid]) {
        return bsearch (key, a, mid, hi);
    } else {
        return mid;
    }

    return -1;
}
