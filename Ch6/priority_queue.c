
#include "heap.h"
#include "priority_queue.h"
#include <stdio.h>

int priority_queue_maximum(priority_queue p)
{
    return p.data[0];
}

int priority_queue_extract_max(priority_queue* p)
{
    if (p->heap_size <= 0)
    {
        printf("heap underflow\n");
        return -1;
    }

    int max = p->data[0];
    p->data[1] = p->data[p->heap_size - 1];
    p->heap_size --;
    max_heapify(p->data, p->heap_size, 1);
    return max;
}

void priority_queue_increase_key(priority_queue* p, int index, int new_value)
{
    if (new_value < p->data[index])
    {
        printf("new key is smaller than current key\n");
        return;
    }

    p->data[index] = new_value;
    int i = index;
    while (i > 0 && p->data[(i - 1) / 2] < p->data[i])
    {
        int temp = p->data[(i - 1)/2];
        p->data[(i - 1)/2] = p->data[i];
        p->data[i] = temp;
        i = (i - 1) / 2;
    }
}

void priority_queue_insert(priority_queue* p, int value)
{
    if (p->heap_size >= p->length)
    {
        printf("heap overflow\n");
        return;
    }
    p->heap_size ++;
    p->data[p->heap_size] = -100000;
    priority_queue_increase_key(p, p->heap_size - 1, value);
}