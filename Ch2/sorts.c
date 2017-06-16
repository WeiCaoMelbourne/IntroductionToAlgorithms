#include <stdlib.h>

void insert_sort(int* input, size_t len)
{
    if (!input)
        return;

    if (len <= 1)
        return;

    int i = 1;
    for (; i < len; i++)
    {
        int j = i - 1;
        int key = input[i];
        while (j >= 0 && input[j] > key)
        {
            input[j + 1] = input[j];
            j --;
        }
        input[j + 1] = key;
    }
}

void merge(int* input, size_t left, size_t right, size_t middle)
{
    int* temp = malloc(sizeof(int) * (right - left + 1));

    int i = 0;
    int left_i = left;
    int right_i = middle + 1;
    while (left_i <= middle && right_i <= right)
    {
        if (input[left_i] < input[right_i])
            temp[i++] = input[left_i++];
        else
            temp[i++] = input[right_i++];
    }

    for (; left_i <= middle; left_i++, i++)
        temp[i] = input[left_i];

    for (; right_i <= right; right_i++, i++)
        temp[i] = input[right_i];

    i = 0;
    for (; i < right - left + 1; i++)
        input[left + i] = temp[i];

    free(temp);
}

static void m_sort(int* input, size_t left, size_t right)
{
    if (left >= right)
        return;

    int middle = left + (right - left) / 2;
    m_sort(input, left, middle);
    m_sort(input, middle + 1, right);
    merge(input, left, right, middle);
}

void merge_sort(int* input, size_t len)
{
    m_sort(input, 0, len - 1);
}