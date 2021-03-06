#ifndef CW_HEAP_H
#define CW_HEAP_H

#include <stdlib.h>

void build_max_heap(int* A, size_t len);
void max_heapify(int* A, size_t len, int i);

#endif