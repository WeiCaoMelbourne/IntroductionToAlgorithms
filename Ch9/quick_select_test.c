#include "quick_select.h"
#include <stdio.h>

int main()
{
    int a[10] = {-1, 3, 4, 15, 132, 54, 8, 10, -33, 1024};
    int ith = 1;
    int i = quick_select(a, 0, 9, ith);

    if (i != -33)
    {
        printf("Failed to get 0-th item. Expected:%d, actual:%d\n",
            -33, i);
    }
    else
    {
        printf("Getting 0-th item succeeds\n");
    }

    ith = 5;
    i = quick_select(a, 0, 9, ith);
    if (i != 8)
    {
        printf("Failed to get 5-th item. Expected:%d, actual:%d\n",
            8, i);
    }
    else
    {
        printf("Getting 5-th item succeeds\n");
    }

    ith = 10;
    i = quick_select(a, 0, 9, ith);
    if (i != 1024)
    {
        printf("Failed to get 10-th item. Expected:%d, actual:%d\n",
            1024, i);
    }
    else
    {
        printf("Getting 10-th item succeeds\n");
    }
}