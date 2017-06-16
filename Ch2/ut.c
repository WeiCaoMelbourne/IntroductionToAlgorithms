
/*
compile: 
    cc ut.c sorts.c

static compile and link:
    1. cc -c sorts.c
    2. cc ut.c sorts.o

dynamic compile and link:
    1. cc -shared -fPIC -o sorts.so sorts.c
    2. cc ut.c ./sorts.so
*/

#include <stdio.h>
#include <stdlib.h>

#include "sorts.h"

void print_array(int* array, size_t len)
{
    int i = 0;
    for (; i < len; i ++)
        printf("%d ", array[i]);

    printf("\n");
}

int main()
{
    int result = 0;
    int input1[0] = {12};
    insert_sort(input1, sizeof(input1)/sizeof(int));
    if (input[0] != 12)
    {
        
        result = 1;
    }

    int input[10] = {12, 34, 4, 6, 4, 18, 64, 21, 100, 50};
    // print_array(input, sizeof(input)/sizeof(int));
    insert_sort(input, sizeof(input)/sizeof(int));


    // print_array(input, sizeof(input)/sizeof(int));
}