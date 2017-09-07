#ifndef CW_LINKEDLIST_H
#define CW_LINKEDLIST_H

struct list_node
{
    int data;
    struct list_node* next;
};

typedef struct list_node LIST_NODE;
typedef struct list_node LIST_HEAD;

void list_add(LIST_HEAD* l, int x);
void print_list(LIST_HEAD* l);

#endif