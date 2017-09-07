#include "stack.h"
#include <stdio.h>

int stack_empty(STACK* s)
{
    if (s->top == 0)
        return 1;

    return 0;
}

void stack_push(STACK* s, int x)
{
    if (s->top >= MAX_STACK_SIZE - 1)
    {
        printf("overflow\n");
        return;
    }
    
    s->stk[s->top++] = x;
}

int stack_pop(STACK* s)
{
    if (stack_empty(s))
    {
        printf("underflow\n");
        return;
    }

    return s->stk[--s->top];
}