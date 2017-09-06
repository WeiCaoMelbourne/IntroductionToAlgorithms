
#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

int main()
{
    priority_queue p;
    p.length = 10;
    p.heap_size = 0;
    p.data = malloc(p.length * sizeof(int));

    priority_queue_insert(&p, 10);

    if (priority_queue_maximum(p) != 10 || p.heap_size != 1)
    {
        printf("priority_queue_insert failed\n");
    }
    else
        printf("priority_queue_insert 1 item succeeded\n");

    priority_queue_insert(&p, 14);
    print_array(p.data, p.heap_size);
    priority_queue_insert(&p, 16);
    print_array(p.data, p.heap_size);
    priority_queue_insert(&p, 116);
    // print_array(p.data, p.heap_size);
    priority_queue_insert(&p, 7);
    // print_array(p.data, p.heap_size);
    priority_queue_insert(&p, 9);

    int expected[6] = {116, 16, 14, 10, 7, 9};
    if (!compare_arrays(p.data, sizeof(expected)/sizeof(int), expected) || p.heap_size != 6)
    {
        printf("priority_queue_insert 6 items failed\n");
        printf("expected:\n");
        print_array(p.data, p.heap_size);
        printf("actual:\n");
        print_array(expected, sizeof(expected)/sizeof(int));
    }
    else
        printf("priority_queue_insert 6 items succeeded\n");

    priority_queue_extract_max(&p);
    int expected2[5] = {16, 14, 10, 7, 9};
    if (!compare_arrays(p.data, sizeof(expected2)/sizeof(int), expected2) || p.heap_size != 5)
    {
        printf("priority_queue_extract_max failed\n");
        printf("expected:\n");
        print_array(p.data, p.heap_size);
        printf("actual:\n");
        print_array(p.data, p.heap_size);
    }
    else
        printf("priority_queue_extract_max succeeded\n");

    priority_queue_increase_key(&p, 4, 80);
    int expected3[5] = {80, 14, 16, 7, 10};
    if (!compare_arrays(p.data, sizeof(expected3)/sizeof(int), expected3) || p.heap_size != 5)
    {
        printf("priority_queue_increase_key failed\n");
    }
    else
        printf("priority_queue_increase_key succeeded\n");
    
    return 0;
}
