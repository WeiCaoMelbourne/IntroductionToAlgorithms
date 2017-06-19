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

void merge(int* input, size_t l_pos, size_t r_pos, size_t center)
{
    int* temp = malloc(sizeof(int) * (r_pos - l_pos + 1));

    int i = 0;
    int left_i = l_pos;
    int right_i = center + 1;
    while (left_i <= center && right_i <= r_pos)
    {
        if (input[left_i] < input[right_i])
            temp[i++] = input[left_i++];
        else
            temp[i++] = input[right_i++];
    }

    while (left_i <= center)
        temp[i++] = input[left_i++];

    while (right_i <= r_pos)
        temp[i++] = input[right_i++];

    i = 0;
    for (; i < r_pos - l_pos + 1; i++)
        input[l_pos + i] = temp[i];

    free(temp);
}

static void m_sort(int* input, size_t l_pos, size_t r_pos)
{
    if (l_pos >= r_pos)
        return;

    int center = (r_pos + l_pos) / 2;
    m_sort(input, l_pos, center);
    m_sort(input, center + 1, r_pos);
    merge(input, l_pos, r_pos, center);
}

void merge_sort(int* input, size_t len)
{
    m_sort(input, 0, len - 1);
}

static void m_insert_sort(int* input, size_t l_pos, size_t r_pos, int key)
{
    if (r_pos - l_pos > key)
    {
        int center = (r_pos + l_pos) / 2;
        m_sort(input, l_pos, center);
        m_sort(input, center + 1, r_pos);
        merge(input, l_pos, r_pos, center);
    }
    else
    {
        insert_sort(input + l_pos, r_pos - l_pos + 1);
    }
}

void merge_insert_sort(int* input, size_t len)
{
    #define MERGE_INSERT_THESHOLD 43
    int k = MERGE_INSERT_THESHOLD;
    m_insert_sort(input, 0, len - 1, k);
}