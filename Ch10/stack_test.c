/*
cc stack.c sorts.c heap.c stack_test.c
*/

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    Stack s = (Stack)malloc(sizeof(struct stack));
    s->top = 0;

    if (!Stack_empty(s))
    {
        printf("stack_empty fails");
    }

    Stack_push(s, 1);
    if (Stack_empty(s))
    {
        printf("stack_empty or stack_push fails. top Expected:%d, actual:%d\n",
            1, s->top);
    }
    else
    {
        printf("stack_empty succeeds\n");
    }

    Stack_push(s, 2);
    // printf
    int x = Stack_pop(s);
    if (x != 2)
    {
        printf("test case 1# stack_push or stack_pop fails. Expected:%d, actual:%d\n",
            2, x);
    }
    else
        printf("test case 1# succeeds\n");

    x = Stack_pop(s);
    if (x != 1)
    {
        printf("test case 2# stack_push or stack_pop fails. Expected:%d, actual:%d\n",
            1, x);
    }
    else
        printf("test case 2# succeeds\n");

    free(s);

    return 0;
}