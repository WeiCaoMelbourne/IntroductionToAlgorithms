
#include "sorts.h"
#include <stdlib.h>
#include <stdio.h>

int find_pair(int* array, size_t len, int x)
{
    merge_sort(array, len);

    size_t l_pos = 0;
    size_t r_pos = len - 1;

    while (l_pos < r_pos)
    {
        int sum = array[l_pos] + array[r_pos];
        if (sum == x)
        {
            printf("Found. %d + %d = %d\n", array[l_pos], array[r_pos], x);
            return 0;
        }
        else if (sum > x)
            r_pos --;
        else 
            l_pos ++;
    }

    printf("Not found\n");
    return 1;
}

int main()
{
    int array[10] = {2, 4, 23, 45, 12, -33, -3, 51, 9};
    int x = 68;

    if (find_pair(array, sizeof(array)/sizeof(int), x) == 0)
    {
        printf("Test case 1# succeeds\n");
    }

    int array2[10] = {2, 4, 23, 45, 12, -33, -3, 51, 9};
    x = 100;

    if (find_pair(array2, sizeof(array2)/sizeof(int), x) != 0)
    {
        printf("Test case 2# succeeds\n");
    }
    return 0;
}