
/*
compile: 
    cc ut.c heap.c sorts.c

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

int main()
{
    int ut_test_failure = 0;

    /* Insert sort test */
    int input1[1] = {12};
    int before1[1];
    copy_array(input1, sizeof(input1)/sizeof(int), before1);
    insert_sort(input1, sizeof(input1)/sizeof(int));
    if (input1[0] != 12)
    {
        printf("Failed to sort array with 1 item\n");
        printf("before:\n");
        print_array(before1, sizeof(input1)/sizeof(int));
        printf("after:\n");
        print_array(input1, sizeof(input1)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }
    else
    {
        printf("insert sort testcase 1:OK\n");
    }

    int input2[80] = {12, 37, 888, 54, 87, 818, 64, 21, 100, 50, 
                    -12, 34, 4, 618, 112, 128, 164, 2441, 999, 77, 
                    2, 35, 114, 6, 422, 118, -614, 211, 876, 50, 
                    877, 394, 14, 94, 44, -18, 8964, 21, -1024, 50, 
                    75, 364, 43, -6, 24, 218, 264, 48, 128, 0, 
                    43, 447, 78, 16, 4, 18, 773, 1121, 512, 50, 
                    877, 344, 44, 26, 63, 18, 12, -121, 110, 11, 
                    3, 36, 777, 461, 4, 118, 90, 231, 1, 21};
    int target2[80] = {-1024, -614, -121, -18, -12, -6, 0, 1, 2, 3,
                    4, 4, 4, 6, 11, 12, 12, 14, 16, 18,
                    18, 21, 21, 21, 24, 26, 34, 35, 36, 37,
                    43, 43, 44, 44, 48, 50, 50, 50, 50, 54,
                    63, 64, 75, 77, 78, 87, 90, 94, 100, 110,
                    112, 114, 118, 118, 128, 128, 164, 211, 218, 231,
                    264, 344, 364, 394, 422, 447, 461, 512, 618, 773,
                    777, 818, 876, 877, 877, 888, 999, 1121, 2441, 8964};
    int before2[80];
    copy_array(input2, sizeof(input2)/sizeof(int), before2);
    insert_sort(input2, sizeof(input2)/sizeof(int));
    if (!compare_arrays(input2, sizeof(input2)/sizeof(int), target2))
    {
        printf("Failed to sort array with 80 item\n");
        printf("before:\n");
        print_array(before1, sizeof(input2)/sizeof(int));
        printf("after:\n");
        print_array(input2, sizeof(input2)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }
    else
    {
        printf("insert sort testcase 2:OK\n");
    }

    int input3[10] = {12, 37, 888, 54, 87, 818, 64, 21, 100, 50};
    int target3[10] = {12, 21, 37, 50, 54, 64, 87, 100, 818, 888};
    int before3[80];
    copy_array(input3, sizeof(input3)/sizeof(int), before3);
    insert_sort(input3, sizeof(input3)/sizeof(int));
    if (!compare_arrays(input3, sizeof(input3)/sizeof(int), target3))
    {
        printf("Failed to sort array with 10 item\n");
        printf("before:\n");
        print_array(before1, sizeof(input2)/sizeof(int));
        printf("after:\n");
        print_array(input2, sizeof(input2)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }
    else
    {
        printf("insert sort testcase 3:OK\n");
    }

    /* Merge sort test */
    copy_array(before1, sizeof(input1)/sizeof(int), input1);
    merge_sort(input1, sizeof(input1)/sizeof(int));
    if (input1[0] != 12)
    {
        printf("Failed to sort array with 1 item\n");
        printf("before:\n");
        print_array(before1, sizeof(input1)/sizeof(int));
        printf("after:\n");
        print_array(input1, sizeof(input1)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }
    else
    {
        printf("merge sort testcase 1:OK\n");
    }

    copy_array(before2, sizeof(input2)/sizeof(int), input2);
    merge_sort(input2, sizeof(input2)/sizeof(int));
    if (!compare_arrays(input2, sizeof(input2)/sizeof(int), target2))
    {
        printf("Failed to sort array with 80 item\n");
        printf("before:\n");
        print_array(before1, sizeof(input2)/sizeof(int));
        printf("after:\n");
        print_array(input2, sizeof(input2)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }
    else
    {
        printf("merge sort testcase 2:OK\n");
    }

    copy_array(before3, sizeof(input3)/sizeof(int), input3);
    merge_sort(input3, sizeof(input3)/sizeof(int));
    if (!compare_arrays(input3, sizeof(input3)/sizeof(int), target3))
    {
        printf("Failed to sort array with 10 item\n");
        printf("before:\n");
        print_array(before3, sizeof(input3)/sizeof(int));
        printf("after:\n");
        print_array(input3, sizeof(input3)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }
    else
    {
        printf("merge sort testcase 3:OK\n");
    }

    /* Merge insert sort test */
    copy_array(before1, sizeof(input1)/sizeof(int), input1);
    merge_insert_sort(input1, sizeof(input1)/sizeof(int));
    if (input1[0] != 12)
    {
        printf("Failed to sort array with 1 item\n");
        printf("before:\n");
        print_array(before1, sizeof(input1)/sizeof(int));
        printf("after:\n");
        print_array(input1, sizeof(input1)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }
    else
    {
        printf("merge insert sort testcase 1:OK\n");
    }

    copy_array(before2, sizeof(input2)/sizeof(int), input2);
    merge_insert_sort(input2, sizeof(input2)/sizeof(int));
    if (!compare_arrays(input2, sizeof(input2)/sizeof(int), target2))
    {
        printf("Failed to sort array with 80 item\n");
        printf("before:\n");
        print_array(before2, sizeof(input2)/sizeof(int));
        printf("after:\n");
        print_array(input2, sizeof(input2)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }
    else
    {
        printf("merge insert sort testcase 2:OK\n");
    }

    copy_array(before3, sizeof(input3)/sizeof(int), input3);
    merge_insert_sort(input3, sizeof(input3)/sizeof(int));
    if (!compare_arrays(input3, sizeof(input3)/sizeof(int), target3))
    {
        printf("Failed to sort array with 10 item\n");
        printf("before:\n");
        print_array(before3, sizeof(input3)/sizeof(int));
        printf("after:\n");
        print_array(input3, sizeof(input3)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }
    else
    {
        printf("merge insert sort testcase 3:OK\n");
    }

    /* Heap sort test */
    copy_array(before1, sizeof(input1)/sizeof(int), input1);
    heap_sort(input1, sizeof(input1)/sizeof(int));
    if (input1[0] != 12)
    {
        printf("Failed to sort array with 1 item\n");
        printf("before:\n");
        print_array(before2, sizeof(input1)/sizeof(int));
        printf("after:\n");
        print_array(input1, sizeof(input1)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }
    else
    {
        printf("heap sort testcase 1:OK\n");
    }

    copy_array(before2, sizeof(input2)/sizeof(int), input2);
    heap_sort(input2, sizeof(input2)/sizeof(int));
    if (!compare_arrays(input2, sizeof(input2)/sizeof(int), target2))
    {
        printf("Failed to sort array with 80 item\n");
        printf("before:\n");
        print_array(before2, sizeof(input2)/sizeof(int));
        printf("after:\n");
        print_array(input2, sizeof(input2)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }
    else
    {
        printf("heap sort testcase 2:OK\n");
    }

    copy_array(before3, sizeof(input3)/sizeof(int), input3);
    heap_sort(input3, sizeof(input3)/sizeof(int));
    if (!compare_arrays(input3, sizeof(input3)/sizeof(int), target3))
    {
        printf("Failed to sort array with 10 item\n");
        printf("before:\n");
        print_array(before3, sizeof(input3)/sizeof(int));
        printf("after:\n");
        print_array(input3, sizeof(input3)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }
    else
    {
        printf("heap sort testcase 3:OK\n");
    }

    if (ut_test_failure == 0)
        printf("Success\n");

    /* Quick sort test */
    copy_array(before1, sizeof(input1)/sizeof(int), input1);
    quick_sort(input1, sizeof(input1)/sizeof(int));
    if (input1[0] != 12)
    {
        printf("Failed to sort array with 1 item\n");
        printf("before:\n");
        print_array(before1, sizeof(input1)/sizeof(int));
        printf("after:\n");
        print_array(input1, sizeof(input1)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }
    else
    {
        printf("quick sort testcase 1:OK\n");
    }

    copy_array(before2, sizeof(input2)/sizeof(int), input2);
    quick_sort(input2, sizeof(input2)/sizeof(int));
    if (!compare_arrays(input2, sizeof(input2)/sizeof(int), target2))
    {
        printf("Failed to sort array with 80 item\n");
        printf("before:\n");
        print_array(before2, sizeof(input2)/sizeof(int));
        printf("after:\n");
        print_array(input2, sizeof(input2)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }
    else
    {
        printf("quick sort testcase 2:OK\n");
    }

    copy_array(before3, sizeof(input3)/sizeof(int), input3);
    quick_sort(input3, sizeof(input3)/sizeof(int));
    if (!compare_arrays(input3, sizeof(input3)/sizeof(int), target3))
    {
        printf("Failed to sort array with 10 item\n");
        printf("before:\n");
        print_array(before3, sizeof(input3)/sizeof(int));
        printf("after:\n");
        print_array(input3, sizeof(input3)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }
    else
    {
        printf("quick sort testcase 3:OK\n");
    }

    if (ut_test_failure == 0)
        printf("Success\n");

    /* Counting sort test */
    copy_array(before1, sizeof(input1)/sizeof(int), input1);
    counting_sort(input1, sizeof(input1)/sizeof(int));
    if (input1[0] != 12)
    {
        printf("Failed to sort array with 1 item\n");
        printf("before:\n");
        print_array(before2, sizeof(input1)/sizeof(int));
        printf("after:\n");
        print_array(input1, sizeof(input1)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }
    else
    {
        printf("counting sort testcase 1:OK\n");
    }

    copy_array(before2, sizeof(input2)/sizeof(int), input2);
    counting_sort(input2, sizeof(input2)/sizeof(int));
    if (!compare_arrays(input2, sizeof(input2)/sizeof(int), target2))
    {
        printf("Failed to sort array with 80 item\n");
        printf("before:\n");
        print_array(before2, sizeof(input2)/sizeof(int));
        printf("after:\n");
        print_array(input2, sizeof(input2)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }
    else
    {
        printf("counting sort testcase 2:OK\n");
    }

    copy_array(before3, sizeof(input3)/sizeof(int), input3);
    counting_sort(input3, sizeof(input3)/sizeof(int));
    if (!compare_arrays(input3, sizeof(input3)/sizeof(int), target3))
    {
        printf("Failed to sort array with 10 item\n");
        printf("before:\n");
        print_array(before3, sizeof(input3)/sizeof(int));
        printf("after:\n");
        print_array(input3, sizeof(input3)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }
    else
    {
        printf("counting sort testcase 3:OK\n");
    }

    if (ut_test_failure == 0)
        printf("Success\n");

    /* radix sort test */
    copy_array(before1, sizeof(input1)/sizeof(int), input1);
    radix_sort(input1, sizeof(input1)/sizeof(int));
    if (input1[0] != 12)
    {
        printf("Failed to sort array with 1 item\n");
        printf("before:\n");
        print_array(before1, sizeof(input1)/sizeof(int));
        printf("after:\n");
        print_array(input1, sizeof(input1)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }
    else
    {
        printf("radix sort testcase 1:OK\n");
    }

    copy_array(before2, sizeof(input2)/sizeof(int), input2);
    radix_sort(input2, sizeof(input2)/sizeof(int));
    if (!compare_arrays(input2, sizeof(input2)/sizeof(int), target2))
    {
        printf("Failed to sort array with 80 item\n");
        printf("before:\n");
        print_array(before2, sizeof(input2)/sizeof(int));
        printf("after:\n");
        print_array(input2, sizeof(input2)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }
    else
    {
        printf("radix sort testcase 2:OK\n");
    }

    copy_array(before3, sizeof(input3)/sizeof(int), input3);
    radix_sort(input3, sizeof(input3)/sizeof(int));
    if (!compare_arrays(input3, sizeof(input3)/sizeof(int), target3))
    {
        printf("Failed to sort array with 10 item\n");
        printf("before:\n");
        print_array(before3, sizeof(input3)/sizeof(int));
        printf("after:\n");
        print_array(input3, sizeof(input3)/sizeof(int));
        printf("\n");
        ut_test_failure += 1;
    }
    else
    {
        printf("radix sort testcase 3:OK\n");
    }

    if (ut_test_failure == 0)
        printf("Success\n");

    return ut_test_failure;
    // print_array(input, sizeof(input)/sizeof(int));
}