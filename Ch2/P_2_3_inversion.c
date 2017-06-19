
#include <stdio.h>
#include <stdlib.h>

static int count_stride(int* input, size_t l_pos, size_t r_pos, size_t center)
{
    int* temp = malloc(sizeof(int) * (r_pos - l_pos + 1));

    int i = 0;
    int left_i = l_pos;
    int right_i = center + 1;
    int count_inversion = 0;

    while (left_i <= center && right_i <= r_pos)
    {
        if (input[left_i] < input[right_i])
        {
            temp[i++] = input[left_i++];
        }
        else
        {
            temp[i++] = input[right_i++];
            count_inversion += (center - left_i + 1);
       }
    }

    while (left_i <= center)
        temp[i++] = input[left_i++];    
    
    while (right_i <= r_pos)
        temp[i++] = input[right_i++];

    i = 0;
    for (; i < r_pos - l_pos + 1; i++)
        input[l_pos + i] = temp[i];

    free(temp);

    return count_inversion;
}

static int count_inversion(int* input, size_t l_pos, size_t r_pos)
{
    if (l_pos < r_pos)
    {
        int center = (r_pos + l_pos) / 2;
        int count_left = count_inversion(input, l_pos, center);
        int count_right = count_inversion(input, center + 1, r_pos);
        int count_s = count_stride(input, l_pos, r_pos, center);
        return count_left + count_right + count_s;
    }

    return 0;
}

int main()
{
    int a[5] = {2, 3, 8, 6, 1};
    int count = count_inversion(a, 0, sizeof(a)/sizeof(int) - 1);
    if (count != 5)
        printf("Wrong. {2, 3, 8, 6, 1} Expected:5, got:%d\n", count);
    else
        printf("Succeeds\n");

    int a2[6] = {12, 13, 18, 0, 1, 14};
    count = count_inversion(a2, 0, sizeof(a2)/sizeof(int) - 1);
    if (count != 7)
        printf("Wrong. {12, 13, 18, 0, 1, 14} Expected:7, got:%d\n", count);
    else
        printf("Succeeds\n");

    int a3[7] = {12, 13, 18, 0, 1, 14, 5};
    count = count_inversion(a3, 0, sizeof(a3)/sizeof(int) - 1);
    if (count != 11)
        printf("Wrong. {12, 13, 18, 0, 1, 14, 5} Expected:7, got:%d\n", count);
    else
        printf("Succeeds\n");

    return 0;
}