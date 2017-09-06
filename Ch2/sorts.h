
#ifndef CW_SORT_H
#define CW_SORT_H

#include <stdlib.h>

void insert_sort(int* input, size_t len);
void merge_sort(int* input, size_t len);
void merge_insert_sort(int* input, size_t len);
void quick_sort(int* input, size_t len);
void counting_sort(int* a, size_t len);

#endif