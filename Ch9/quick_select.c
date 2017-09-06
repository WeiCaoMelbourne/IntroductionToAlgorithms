#include "sorts.h"
#include <stdio.h>

/* p, r are range pairs */
int quick_select(int* A, int p, int r, int i)
{
    if (p == r)
        return A[p];

    int q = partition(A, p, r);
    int k = q - p + 1;
    // printf("k:%d, i:%d, q:%d\n", k, i, q);
    if (i == k)     /* the pivot value is the answer */
        return A[q];
    else if (i < k)
        return quick_select(A, p, q - 1, i);
    else
        return quick_select(A, q + 1, r, i - k);
}
