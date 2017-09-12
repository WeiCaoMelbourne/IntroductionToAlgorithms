
/*

*/

#include "hash.h"
#include <stdio.h>

#define MIN_TABLE_SIZE 10

int main()
{
    HASH_TABLE H = initilize_hash(12);
    int table_size = H->table_size;

    if (table_size != 13)
    {
        printf("initilize_hash failed. Table size, expected:%d, actual:%d\n",
            13, table_size);
    }
    else
    {
        printf("initilize_hash succeeds\n");
    }

    const int TARGET = 9;
    insert_hash(H, TARGET);
    struct list_node* hash_node = find_hash(H, TARGET);
    if (!hash_node)
    {
        printf("Either insert_hash or find_hash failed\n");
    }
    else
    {
        if (hash_node->data != TARGET)
        {
            printf("insert_hash failed. expected:%d, actual:%d\n",
                TARGET, hash_node->data);
        }
        else
        {
            printf("insert_hash succeeds\n");
        }
    }

    remove_hash(H, TARGET);
    hash_node = find_hash(H, TARGET);
    if (!hash_node)
    {
        printf("remove_hash succeeds\n");
    }
    else
    {
        printf("remove_hash failed\n");
    }

    destory_hash(H);
    
    return 0;
}