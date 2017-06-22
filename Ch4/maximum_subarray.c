
#include <stdio.h>
#include <stdlib.h>

static int find_maximum_crossing_subarray(
    int* array, int l_pos, 
    int r_pos, int center, 
    int* start, int* end)
{
    int sum = array[center];
    int temp = sum;
    *start = *end = center;
    if (center <= 0)
        return sum;
    
    int i = center - 1;
    while (i >= l_pos)
    {
        temp += array[i];
        if (temp > sum)
        {
            sum = temp;
            *start = i;
        }
        i -= 1;
    }

    i = center + 1;
    while (i <= r_pos)
    {
        temp += array[i];
        if (temp > sum)
        {
            sum = temp;
            *end = i;
        }
        i += 1;
    }

    return sum;
}

int find_maximum_subarray(int* array, 
    int l_pos, int r_pos, 
    int* start, int* end)
{
    if (l_pos < r_pos)
    {
        int center = (r_pos + l_pos) / 2;
        int start1, end1, start2, end2, start3, end3;
        int l_maximum = find_maximum_subarray(array, l_pos, center, &start1, &end1);
        int r_maximum = find_maximum_subarray(array, center + 1, r_pos, &start2, &end2);
        int c_maximum = find_maximum_crossing_subarray(array, l_pos, r_pos, center, &start3, &end3);

        if (l_maximum > r_maximum && l_maximum > c_maximum)
        {
            *start = start1;
            *end = end1;
            return l_maximum;
        }
        
        if (r_maximum > l_maximum && r_maximum > c_maximum)
        {
            *start = start2;
            *end = end2;
            return r_maximum;
        }

        if (c_maximum > l_maximum && c_maximum > r_maximum)
        {
            *start = start3;
            *end = end3;
            return c_maximum;
        }
    }

    *start = *end = l_pos;
    return array[l_pos];
}

int main()
{
    int a[1] = {1};
    int start = 0;
    int end = 0;
    int sum = find_maximum_subarray(a, 0, sizeof(a)/sizeof(int) - 1, &start, &end);
    if (sum != 1 || start != 0 || end != 0)
    {
        printf("Test case 1# fails. Sum: 1 vs %d, start:0 vs %d, end: 0 vs %d\n", sum, start, end);
    }
    else
    {
        printf("Test case 1# pass\n");
    }

    int a2[10] = {1, 2, 5, 7, -10, 2, 3, 4, 9, -11};
    sum = find_maximum_subarray(a2, 0, sizeof(a2)/sizeof(int) - 1, &start, &end);
    if (sum != 23 || start != 0 || end != 8)
    {
        printf("Test case 2# fails. Sum: 23 vs %d, start:0 vs %d, end: 8 vs %d\n", sum, start, end);
    }
    else
    {
        printf("Test case 2# pass\n");
    }

    int a3[10] = {-1, -2, -5, -7, -10, -2, -3, -4, -9, -11};
    sum = find_maximum_subarray(a3, 0, sizeof(a3)/sizeof(int) - 1, &start, &end);
    if (sum != -1 || start != 0 || end != 0)
    {
        printf("Test case 2# fails. Sum: -1 vs %d, start:0 vs %d, end: 0 vs %d\n", sum, start, end);
    }
    else
    {
        printf("Test case 2# pass\n");
    }

    return 0;
}