#ifndef CW_HASH_H
#define CW_HASH_H

struct list_node
{
    int data;
    struct list_node* next;
};


struct hash_tbl
{
    int table_size;
    struct list_node** the_lists;
};

typedef struct hash_tbl* HASH_TABLE;

HASH_TABLE initilize_hash(int table_size);
struct list_node* find_hash(HASH_TABLE H, int key);
void destory_hash(HASH_TABLE H);
void insert_hash(HASH_TABLE H, int x);
void remove_hash(HASH_TABLE H, int x);

#endif