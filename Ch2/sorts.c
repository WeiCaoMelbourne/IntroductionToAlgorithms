#include <stdlib.h>
#include "heap.h"

int partition(int* A, int p, int r)
{
    int pivot = A[r];
    int i = p - 1;
    int j = p;
    for (; j < r; j ++)
    {
        if (A[j] < pivot)
        {
            i ++;
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }

    int temp = A[i + 1];
    A[i + 1] = A[r];
    A[r] = temp;

    return i + 1;
}

static void recursive_quicksort(int* A, int p, int r)
{
    if (p < r)
    {
        int q = partition(A, p, r);
        recursive_quicksort(A, p, q - 1);
        recursive_quicksort(A, q + 1, r);
    }
}

void quick_sort(int* A, size_t len)
{
    return recursive_quicksort(A, 0, len - 1);
}

void counting_sort(int* a, size_t len)
{
    int max = a[0], min = a[0];

    int i = 1;
    for (; i < len; i ++)
    {
        if (a[i] > max)
            max = a[i];
        if (a[i] < min)
            min = a[i];
    }

    int* c = malloc(sizeof(int) * (max - min + 1));
    for (i = 0; i < max - min + 1; i ++)
        c[i] = 0;

    for (i = 0; i < len; i ++)
        c[a[i] - min] ++;

    int sum = 0;
    for (i = 0; i < max - min + 1; i ++)
    {
        sum += c[i];
        c[i] = sum;
    }

    int* b = malloc(sizeof(int) * len);
    for (i = len - 1; i >= 0; i --)
    {
        b[c[a[i] - min] - 1] = a[i];
        c[a[i] - min] --;
    }

    for (i = 0; i < len; i++)
        a[i] = b[i];

    free(c);
    free(b);
}

static void radix_sort_2(int* a, size_t len)
{
    int max = a[0];

    int i = 1;
    for (; i < len; i ++)
    {
        if (a[i] > max)
            max = a[i];
    }

    const int BASE = 10;
    int exp = 1;
    while (max / exp > 0)
    {
        int c[BASE];
        int i = 0;
        for (; i < BASE; i ++)
            c[i] = 0;

        for (i = 0; i < len; i ++)
            c[(abs(a[i]) / exp) % BASE] ++;

        for (i = 1; i < BASE; i ++)
            c[i] += c[i - 1];
        
        int* b = malloc(sizeof(int) * len);
        for (i = len - 1; i >= 0; i --)
        {
            b[c[(abs(a[i]) / exp) % BASE] - 1] = a[i];
            c[(abs(a[i]) / exp) % BASE] --;
        }

        for (i = 0; i < len; i++)
            a[i] = b[i];

        free(b);

        exp *= BASE;
    }
}

void radix_sort(int* a, size_t len)
{
    int negative_count = 0;

    int i = 0;
    for (; i < len; i ++)
    {
        if (a[i] < 0)
            negative_count ++;
    }

    int* negatives = malloc(sizeof(int) * negative_count);
    int* positives = malloc(sizeof(int) * (len - negative_count));
    i = 0;
    negative_count = 0;
    int positive_count = 0;
    for (; i < len; i ++)
    {
        if (a[i] < 0)
            negatives[negative_count++] = 0 - a[i];
        else
            positives[positive_count++] = a[i];
    }

    radix_sort_2(negatives, negative_count);
    radix_sort_2(positives, positive_count);

    i = 0;
    for (; i < len; i ++)
    {
        if (i < negative_count)
            a[i] = 0 - negatives[negative_count - i - 1];
        else
            a[i] = positives[i - negative_count];
    }
}

void heap_sort(int* A, size_t len)
{
    build_max_heap(A, len);
    int i = len - 1;
    for (; i > 0; i --)
    {
        int temp = A[i];
        A[i] = A[0];
        A[0] = temp;

        max_heapify(A, i, 0);
    }
}

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