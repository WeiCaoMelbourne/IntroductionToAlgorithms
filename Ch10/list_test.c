/*
cc stack.c sorts.c heap.c stack_test.c
*/

#include "linked_list.h"
#include <stdio.h>

int main()
{
    LIST_HEAD s;
    s.data = 0;
    s.next = 0;

    list_add(&s, 2);
    list_add(&s, 3);
    
    int error_count = 0;
    if (s.next->data != 2)
    {
        printf("test case 1# fails. Expected:%d, actual:%d\n",
            2, s.next->data);
        error_count ++;
    }
    if (s.next->next->data != 3)
    {
        printf("test case 1# fails. Expected:%d, actual:%d\n",
            3, s.next->next->data);
        error_count ++;
    }
    
    if (error_count == 0)
    {
        printf("list_add test succeeds\n");
    }

    error_count = 0;

    list_remove(&s, 2);
    if (s.next->data != 3)
    {
        printf("test case 2# fails. Expected:%d, actual:%d\n",
            3, s.next->data);
        error_count ++;
    }
    if (error_count == 0)
    {
        printf("list_remove test succeeds\n");
    }

    return 0;
}