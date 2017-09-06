#include "heap.h"

void max_heapify(int* A, size_t len, int i)
{
    int l = (i + 1) * 2 - 1;    /* C array starts with 0 */
    int r = (i + 1) * 2;
    int largest = i;
    if (l < len && A[l] > A[i])
        largest = l;
    if (r < len && A[r] > A[largest])
        largest = r;
    if (largest != i)
    {
        int temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        max_heapify(A, len, largest);
    }
}

void build_max_heap(int* A, size_t len)
{
    int start_point = len / 2;
    for (; start_point >= 0; start_point --)
        max_heapify(A, len, start_point);
}


