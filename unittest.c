
#include "unittest.h"
#include <stdlib.h>
#include <stdio.h>

void print_array(int* array, size_t len)
{
    int i = 0;
    for (; i < len; i ++)
        printf("%d,", array[i]);

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