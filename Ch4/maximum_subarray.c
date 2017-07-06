
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

int find_maximum_subarray_dp(int* array, int len, int* start, int* end)
{
    if (len <= 0)
    {
        printf("Invalid array\n");
        return 0;
    }

    /* dp[i] means max subarray that ends at i. */
    int* dp = malloc(sizeof(int) * len);

    int max_sum = dp[0] = array[0];
    *start = *end = 0;

    int i = 1;
    for (; i < len; i++)
    {
        if (array[i] > 0 && dp[i - 1] < 0)
        {
            dp[i] = array[i];
            *start = i;
            *end = i;
        }
        else
        {
            dp[i] = dp[i - 1] + array[i];
            if (array[i] > 0)
                *end = i;
        }

        if (dp[i] > max_sum)
        {
            max_sum = dp[i];
            *end = i;
        }
    }

    free(dp);

    return max_sum;
}

int find_maximum_subarray_linear(int* array, int len, int* start, int* end)
{
    if (len <= 0)
    {
        printf("Invalid array\n");
        return 0;
    }
    else if (len == 1)
        return array[0];

    int max_sum, max_ending_here;
    max_sum = max_ending_here = array[0];
    *start = *end = 0;

    int i = 1;
    for (; i < len; i++)
    {
        max_ending_here += array[i];
        if (array[i] > 0 && array[i] > max_ending_here)
        {
            max_ending_here = array[i];
            *start = i;
            *end = i;
        }

        if (max_ending_here > max_sum)
        {
            max_sum = max_ending_here;
            *end = i;
        }
    }

    return max_sum;
#if 0
    int this_sum, max_sum;
    this_sum = max_sum = array[0];
    *start = *end = 0;
    int temp = 0;

    int i = 1;
    for (; i < len; i++)
    {
        this_sum += array[i];

        if (this_sum > max_sum)
        {
            *end = i;
            *start = temp;
            max_sum = this_sum;
        }

        if (this_sum < 0)
        {
            this_sum = 0;
            temp = i + 1;
        }
    }

    return max_sum;
#endif

#if 0
    int temp = array[0];
    int sum = array[0];
    *start = 0;
    *end = 0;

    int i = 1;
    for (; i < len; i++)
    {
        if (array[i] > 0)
        {
            *end = i;
            if (temp < 0)
            {
                temp = 0;
                *start = i;
            }
        }

        temp += array[i];
        if (temp > sum)
            sum = temp;
    }

    return sum;
#endif
}

int main()
{
    int a[1] = {1};
    int start = 0;
    int end = 0;
    int sum = find_maximum_subarray(a, 0, sizeof(a)/sizeof(int) - 1, &start, &end);
    if (sum != 1 || start != 0 || end != 0)
    {
        printf("Test case 1# fails for find_maximum_subarray\n");
        printf("Sum: 1 vs %d, start:0 vs %d, end: 0 vs %d\n", sum, start, end);
    }
    else
    {
        printf("Test case 1# for find_maximum_subarray pass\n");
    }

    sum = find_maximum_subarray_linear(a, sizeof(a)/sizeof(int), &start, &end);
    if (sum != 1 || start != 0 || end != 0)
    {
        printf("Test case 1# fails for find_maximum_subarray_linear\n");
        printf("Sum: 1 vs %d, start:0 vs %d, end: 0 vs %d\n", sum, start, end);
    }
    else
    {
        printf("Test case 1# for find_maximum_subarray_linear pass\n");
    }

    sum = find_maximum_subarray_dp(a, sizeof(a)/sizeof(int), &start, &end);
    if (sum != 1 || start != 0 || end != 0)
    {
        printf("Test case 1# fails for find_maximum_subarray_dp\n");
        printf("Sum: 1 vs %d, start:0 vs %d, end: 0 vs %d\n", sum, start, end);
    }
    else
    {
        printf("Test case 1# for find_maximum_subarray_dp pass\n");
    }

    //2#
    int a2[10] = {1, 2, 5, 7, -10, 2, 3, 4, 9, -11};
    sum = find_maximum_subarray(a2, 0, sizeof(a2)/sizeof(int) - 1, &start, &end);
    if (sum != 23 || start != 0 || end != 8)
    {
        printf("Test case 2# fails for find_maximum_subarray\n");
        printf("Sum: 23 vs %d, start:0 vs %d, end: 8 vs %d\n", sum, start, end);
    }
    else
    {
        printf("Test case 2# pass for find_maximum_subarray pass\n");
    }

    sum = find_maximum_subarray_linear(a2, sizeof(a2)/sizeof(int), &start, &end);
    if (sum != 23 || start != 0 || end != 8)
    {
        printf("Test case 2# fails for find_maximum_subarray_linear\n");
        printf("Sum: 23 vs %d, start:0 vs %d, end: 8 vs %d\n", sum, start, end);
    }
    else
    {
        printf("Test case 2# pass for find_maximum_subarray_linear pass\n");
    }

    sum = find_maximum_subarray_dp(a2, sizeof(a2)/sizeof(int), &start, &end);
    if (sum != 23 || start != 0 || end != 8)
    {
        printf("Test case 2# fails for find_maximum_subarray_dp\n");
        printf("Sum: 23 vs %d, start:0 vs %d, end: 8 vs %d\n", sum, start, end);
    }
    else
    {
        printf("Test case 2# pass for find_maximum_subarray_dp pass\n");
    }

    //3#
    int a3[10] = {-1, -2, -5, -7, -10, -2, -3, -4, -9, -11};
    sum = find_maximum_subarray(a3, 0, sizeof(a3)/sizeof(int) - 1, &start, &end);
    if (sum != -1 || start != 0 || end != 0)
    {
        printf("Test case 3# fails for find_maximum_subarray\n");
        printf("Sum: -1 vs %d, start:0 vs %d, end: 0 vs %d\n", sum, start, end);
    }
    else
    {
        printf("Test case 3# pass for find_maximum_subarray\n");
    }

    sum = find_maximum_subarray_linear(a3, sizeof(a2)/sizeof(int), &start, &end);
    if (sum != -1 || start != 0 || end != 0)
    {
        printf("Test case 3# fails for find_maximum_subarray_linear\n");
        printf("Sum: -1 vs %d, start:0 vs %d, end: 0 vs %d\n", sum, start, end);
    }
    else
    {
        printf("Test case 3# pass for find_maximum_subarray_linear\n");
    }

    sum = find_maximum_subarray_dp(a3, sizeof(a2)/sizeof(int), &start, &end);
    if (sum != -1 || start != 0 || end != 0)
    {
        printf("Test case 3# fails for find_maximum_subarray_dp\n");
        printf("Sum: -1 vs %d, start:0 vs %d, end: 0 vs %d\n", sum, start, end);
    }
    else
    {
        printf("Test case 3# pass for find_maximum_subarray_dp\n");
    }

    //4#
    int a4[5] = {-1, 5, -6, 7, 8};
    sum = find_maximum_subarray(a4, 0, sizeof(a4)/sizeof(int) - 1, &start, &end);
    if (sum != 15 || start != 3 || end != 4)
    {
        printf("Test case 4# fails for find_maximum_subarray\n");
        printf("Sum: 15 vs %d, start:3 vs %d, end: 4 vs %d\n", sum, start, end);
    }
    else
    {
        printf("Test case 4# pass for find_maximum_subarray\n");
    }

    sum = find_maximum_subarray_linear(a4, sizeof(a4)/sizeof(int), &start, &end);
    if (sum != 15 || start != 3 || end != 4)
    {
        printf("Test case 4# fails for find_maximum_subarray_linear\n");
        printf("Sum: 15 vs %d, start:3 vs %d, end: 4 vs %d\n", sum, start, end);
    }
    else
    {
        printf("Test case 4# pass for find_maximum_subarray_linear\n");
    }

    sum = find_maximum_subarray_dp(a4, sizeof(a4)/sizeof(int), &start, &end);
    if (sum != 15 || start != 3 || end != 4)
    {
        printf("Test case 4# fails for find_maximum_subarray_dp\n");
        printf("Sum: 15 vs %d, start:3 vs %d, end: 4 vs %d\n", sum, start, end);
    }
    else
    {
        printf("Test case 4# pass for find_maximum_subarray_dp\n");
    }

    return 0;
}