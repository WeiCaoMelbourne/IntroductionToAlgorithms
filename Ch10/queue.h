#ifndef CW_QUEUE_H
#define CW_QUEUE_H

#define MAX_QUEUE_SIZE 20

struct queue
{
    int a[MAX_QUEUE_SIZE];
    int head;
    int tail;
    int item_count;
};

typedef struct queue* Queue;

void Queue_enqueue(Queue q, int x);
int Queue_dequeue(Queue q);
int Queue_empty(Queue q);

#endif