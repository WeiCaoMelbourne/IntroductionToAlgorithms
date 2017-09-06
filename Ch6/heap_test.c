
/*
static compile and link:
    1. cc -c heap.c 
    2. cc -c unitest.c
    3. cc heap_test.c heap.o unitest.o

#dynamic compile and link:
#    1. cc -shared -fPIC -o sorts.so sorts.c
#    2. cc ut.c ./sorts.so
*/

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int main()
{
    int a[1] = {1};
    int expected[1] = {1};
    build_max_heap(a, sizeof(a)/sizeof(int));
    if (a[0] != 1)
    {
        printf("Failed in test case 1#. expected:%d, result:%d\n", expected[0], a[0]);
    }
    else
    {
        printf("Test case 1# succeeds\n");
    }

    int a2[6] = {15,19,10,7,17,16};
    int expected2[6] = {19,17,16,7,15,10};
    build_max_heap(a2, sizeof(a2)/sizeof(int));
    if (!compare_arrays(a2, sizeof(a2)/sizeof(int), expected2))
    {
        printf("Failed in test case 2#\n");
        printf("result:\n");
        print_array(a2, sizeof(a2)/sizeof(int));
        printf("expected:\n");
        print_array(expected2, sizeof(expected2)/sizeof(int));
        printf("\n");
    }
    else
    {
        printf("Test case 2# succeeds\n");
    }

    return 0;
}