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