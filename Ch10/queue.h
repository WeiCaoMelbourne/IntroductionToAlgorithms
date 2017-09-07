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

typedef struct queue QUEUE;

void enqueue(QUEUE* q, int x);
int dequeue(QUEUE* q);

#endif