#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

void list_add(LIST_HEAD* l, int x)
{
    LIST_NODE* node = (LIST_NODE*)malloc(sizeof(LIST_NODE));
    node->data = x;
    node->next = 0;

    LIST_NODE* t = l;
    while (t)
    {
        if (t->next == 0)
            break;
        t = t->next;
    }

    t->next = node;
}

void list_remove(LIST_HEAD* l, int x)
{
    LIST_NODE* t = l;
    LIST_NODE* prev = 0;
        
    while (t)
    {
        if (t->data == x && prev)
        {
            prev->next = t->next;
            free(t);
            return;
        }

        prev = t;
        t = t->next;
    }
}

void print_list(LIST_HEAD* l)
{
    LIST_NODE* t = l;
    while (t)
    {
        printf("%d\n", t->data);
        t = t->next;
    }
}

