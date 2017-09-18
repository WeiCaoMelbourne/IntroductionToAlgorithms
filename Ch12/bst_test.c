
/*
cc bst_test.c bst.c
*/

#include "bst.h"
#include <stdio.h>
#include <string.h>

int main()
{
    BST t = initialize_bst();

    /*
                10
               /  \
              5    15
                  /  \
                 /    \
                13     20
                 \     /
                 14   18 
    */
    const int ITEM_1 = 10;
    t->data = 10;

    const int ITEM_2 = 5;
    bst_insert(t, ITEM_2);
    
    const int ITEM_3 = 15;
    bst_insert(t, ITEM_3);

    const int ITEM_4 = 13;
    bst_insert(t, ITEM_4);

    const int ITEM_5 = 14;
    bst_insert(t, ITEM_5);

    const int ITEM_6 = 20;
    bst_insert(t, ITEM_6);

    const int ITEM_7 = 18;
    bst_insert(t, ITEM_7);

    struct tree_node* node = bst_search(t, ITEM_7);
    if (!node)
    {
        printf("bst_insert failed\n");
    }
    else if (node->data != ITEM_7)
    {
        printf("bst_insert failed. Expected:%d, actual:%d\n", 
            node->data, ITEM_7);
    }
    else
    {
        printf("bst_insert succeeds\n");
    }

    printf("In order print of t:\n");
    bst_inorder_print(t);
    printf("\n");

    char* expected_inorder = "5 10 13 14 15 18 20 ";
    char inorder_str[64];
    memset(inorder_str, 0, sizeof(inorder_str));
    bst_inorder_str(t, inorder_str, sizeof(inorder_str));
    if (strcmp(expected_inorder, inorder_str) != 0)
    {
        printf("Something worng with either bst_insert or bst_inorder_str.\n");
        printf("Expected:%s, actual:%s|\n", expected_inorder, inorder_str);
    }
    else
    {
        printf("bst_insert/bst_inorder_str succeeds\n");
    }

    /* Delete 5:
                10
                  \
                   15
                  /  \
                 /    \
                13     20
                 \     /
                 14   18 

    */
    node = bst_search(t, ITEM_2);
    bst_delete(t, node);
    char* expected_inorder2 = "10 13 14 15 18 20 ";
    memset(inorder_str, 0, sizeof(inorder_str));
    bst_inorder_str(t, inorder_str, sizeof(inorder_str));
    if (strcmp(expected_inorder2, inorder_str) != 0)
    {
        printf("bst_delete failed.\n");
        printf("Expected:%s, actual:%s|\n", expected_inorder2, inorder_str);
    }
    else
    {
        printf("bst_delete (1 child) succeeds\n");
    }

    /* Delete 15:
                10
                  \
                   18
                  /  \
                 /    \
                13     20
                 \     
                 14   

    */
    node = bst_search(t, ITEM_3);
    bst_delete(t, node);
    char* expected_inorder3 = "10 13 14 18 20 ";
    memset(inorder_str, 0, sizeof(inorder_str));
    bst_inorder_str(t, inorder_str, sizeof(inorder_str));
    if (strcmp(expected_inorder3, inorder_str) != 0)
    {
        printf("bst_delete failed.\n");
        printf("Expected:%s, actual:%s|\n", expected_inorder3, inorder_str);
    }
    else
    {
        printf("bst_delete (2 children) succeeds\n");
    }

    bst_destory(t);

    return 0;
}