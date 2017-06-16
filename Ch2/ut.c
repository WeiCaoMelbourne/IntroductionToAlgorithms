
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

void copy_array(int* array, size_t len, int* target)
{
    if (!target)
        return;

    int i = 0;
    for (; i < len; i ++)
        target[i] = array[i];
}

int compare_arrays(int* array, size_t len, int* target)
{
    if (!target)
        return;

    int i = 0;
    for (; i < len; i ++)
    {
        if (target[i] != array[i])
            return 0;
    }

    return 1;
}

int main()
{
    int ut_test_failure = 0;
    int input1[1] = {12};
    int before1[1];
    copy_array(input1, sizeof(input1)/sizeof(int), before1);
    insert_sort(input1, sizeof(input1)/sizeof(int));
    if (input1[0] != 12)
    {
        printf("Failed to sort array with 1 item\n");
        printf("before:\n");
        print_array(before1, sizeof(input1)/sizeof(int));
        printf("before:\n");
        print_array(input1, sizeof(input1)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }

    int input2[10] = {12, 34, 4, 6, 4, 18, 64, 21, 100, 50};
    int target2[10] = {4, 4, 6, 12, 18, 21, 34, 50, 64, 100};
    int before2[10];
    copy_array(input2, sizeof(input2)/sizeof(int), before2);
    insert_sort(input2, sizeof(input2)/sizeof(int));
    if (!compare_arrays(input2, sizeof(input2)/sizeof(int), target2))
    {
        printf("Failed to sort array with 1 item\n");
        printf("before:\n");
        print_array(before1, sizeof(input2)/sizeof(int));
        printf("before:\n");
        print_array(input2, sizeof(input2)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }

    if (ut_test_failure == 0)
        printf("Success\n");

    return ut_test_failure;
    // print_array(input, sizeof(input)/sizeof(int));
}