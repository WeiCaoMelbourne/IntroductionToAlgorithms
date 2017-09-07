#ifndef CW_STACK_H
#define CW_STACK_H

#define MAX_STACK_SIZE 10

struct stack
{
	int stk[MAX_STACK_SIZE];
	int top;
};

typedef struct stack STACK;

int stack_empty(STACK* s);
void stack_push(STACK* s, int x);
int stack_pop(STACK* s);

#endif