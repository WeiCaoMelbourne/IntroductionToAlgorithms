#include "queue.h"
#include <stdio.h>

void enqueue(QUEUE* q, int x)
{
    if (q->item_count == MAX_QUEUE_SIZE)
    {
        printf("full\n");
        return;
    }

    q->item_count ++;
    q->a[q->tail] = x;
    if (q->tail == MAX_QUEUE_SIZE - 1)
        q->tail = 0;
    else
        q->tail ++;
}

int dequeue(QUEUE* q)
{
    if (q->item_count == 0)
    {
        printf("empty\n");
        return -1;
    }

    q->item_count --;
    int x = q->a[q->head];
    if (q->head == MAX_QUEUE_SIZE - 1)
        q->head = 0;
    else
        q->head ++;

    return x;
}

