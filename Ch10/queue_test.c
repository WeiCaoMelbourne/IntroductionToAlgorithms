/*
cc queue_test.c queue.c
*/

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    Queue s = (Queue)malloc(sizeof(struct queue));
    s->head = 0;
    s->tail = 0;
    s->item_count = 0;

    if (Queue_empty(s))
    {
        printf("Queue_empty test 1# succeeds\n");
    }
    else
    {
        printf("Queue_empty test 1# failed\n");
    }

    Queue_enqueue(s, 1);
    Queue_enqueue(s, 2);
    Queue_enqueue(s, 3);

    if (!Queue_empty(s))
    {
        printf("Queue_empty test 2# succeeds\n");
    }
    else
    {
        printf("Queue_empty test 2# failed\n");
    }
    
    int x = Queue_dequeue(s);
    if (x != 1)
    {
        printf("test case 1# stack_push or stack_pop fails. Expected:%d, actual:%d\n",
            1, x);
    }
    else
        printf("test case 1# succeeds\n");

    x = Queue_dequeue(s);
    if (x != 2)
    {
        printf("test case 2# stack_push or stack_pop fails. Expected:%d, actual:%d\n",
            2, x);
    }
    else
        printf("test case 2# succeeds\n");

    x = Queue_dequeue(s);
    if (x != 3)
    {
        printf("test case 3# stack_push or stack_pop fails. Expected:%d, actual:%d\n",
            3, x);
    }
    else
        printf("test case 3# succeeds\n");

    free(s);

    return 0;
}