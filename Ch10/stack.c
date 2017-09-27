#include "stack.h"
#include <stdio.h>

int Stack_empty(Stack s)
{
    if (s->top == 0)
        return 1;

    return 0;
}

void Stack_push(Stack s, int x)
{
    if (s->top >= MAX_STACK_SIZE - 1)
    {
        printf("overflow\n");
        return;
    }
    
    s->stk[s->top++] = x;
}

int Stack_pop(Stack s)
{
    if (Stack_empty(s))
    {
        printf("underflow\n");
        return;
    }

    return s->stk[--s->top];
}