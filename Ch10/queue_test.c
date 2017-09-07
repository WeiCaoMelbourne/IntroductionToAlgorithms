/*
cc stack.c sorts.c heap.c stack_test.c
*/

#include "queue.h"
#include <stdio.h>

int main()
{
    QUEUE s;
    s.head = 0;
    s.tail = 0;
    s.item_count = 0;

    enqueue(&s, 1);
    enqueue(&s, 2);
    enqueue(&s, 3);
    
    int x = dequeue(&s);
    if (x != 1)
    {
        printf("test case 1# stack_push or stack_pop fails. Expected:%d, actual:%d\n",
            1, x);
    }
    else
        printf("test case 1# succeeds\n");

    x = dequeue(&s);
    if (x != 2)
    {
        printf("test case 2# stack_push or stack_pop fails. Expected:%d, actual:%d\n",
            2, x);
    }
    else
        printf("test case 2# succeeds\n");

    x = dequeue(&s);
    if (x != 3)
    {
        printf("test case 3# stack_push or stack_pop fails. Expected:%d, actual:%d\n",
            3, x);
    }
    else
        printf("test case 3# succeeds\n");

    return 0;
}