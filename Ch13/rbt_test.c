
/*
cc rbt_test.c rbt.c
*/

#include "rbt.h"
#include <stdio.h>
#include <string.h>

int main()
{
    RBT t = Initialize_rbt();

    /*
                10(B)
               /  \
              5(B) 15(B)
                  /  \
                 /    \
                13(R)  20(R)
    */
    const int ITEM_1 = 10;
    t->key = 10;

    const int ITEM_2 = 5;
    Rbt_insert(t, ITEM_2);

    const int ITEM_3 = 15;
    Rbt_insert(t, ITEM_3);

    const int ITEM_4 = 13;
    Rbt_insert(t, ITEM_4);

    const int ITEM_5 = 20;
    Rbt_insert(t, ITEM_5);

    printf("In order print of t:\n");
    Rbt_inorder_print(t);
    printf("\n");

    struct rbt_node* n = Rbt_search(t, ITEM_3);
    if (!n)
    {
        printf("Rbt_search failed\n");
    }
    else
    {
        Rbt_delete(t, n);
        printf("After delete %d:\n", ITEM_3);
        Rbt_inorder_print(t);
        printf("\n");
    }

    return 0;
}