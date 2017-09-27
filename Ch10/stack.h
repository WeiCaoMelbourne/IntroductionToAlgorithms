#ifndef CW_STACK_H
#define CW_STACK_H

#define MAX_STACK_SIZE 10

struct stack
{
    int stk[MAX_STACK_SIZE];
    int top;
};

typedef struct stack* Stack;

int Stack_empty(Stack s);
void Stack_push(Stack s, int x);
int Stack_pop(Stack s);

#endif