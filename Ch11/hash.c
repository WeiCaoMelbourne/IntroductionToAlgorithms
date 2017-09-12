#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

#define MIN_TABLE_SIZE 10

static int next_prime(int n)
{
    int i, is_prime;
    while (1)
    {
        i = 2;
        is_prime = 1;
        for (; i < n; i++)
        {
            if (n % i == 0)
            {
                is_prime = 0;
                break;
            }
        }

        if (is_prime)
            break;

        n += 1;
    }

    return n;
}

HASH_TABLE initilize_hash(int table_size)
{
    HASH_TABLE H;

    if (table_size < MIN_TABLE_SIZE)
    {
        printf("Table size too small\n");
        return NULL;
    }

    H = (HASH_TABLE)malloc(sizeof(struct hash_tbl));
    H->table_size = next_prime(table_size);
    H->the_lists = (struct list_node**)malloc(H->table_size * sizeof(struct list_node*));

    int i = 0;
    for (; i < H->table_size; i ++)
    {
        H->the_lists[i] = (struct list_node*)malloc(sizeof(struct list_node));
        H->the_lists[i]->next = NULL;
    }

    return H;
}

void destory_hash(HASH_TABLE H)
{
    int i = 0;
    for (; i < H->table_size; i ++)
    {
        free(H->the_lists[i]);
    }

    free(H->the_lists);
}

int hash(int x, HASH_TABLE H)
{
    return x % H->table_size;
}

struct list_node* find_hash(HASH_TABLE H, int key)
{
    struct list_node* l = H->the_lists[hash(key, H)];
    while (l)
    {
        if (l->data == key)
            return l;

        l = l->next;
    }

    return NULL;
}

void insert_hash(HASH_TABLE H, int x)
{
    struct list_node* pos = find_hash(H, x);
    if (!pos)
    {
        struct list_node* new_node = (struct list_node*)malloc(sizeof(struct list_node));
        new_node->data = x;

        struct list_node* list_head = H->the_lists[hash(x, H)];
        new_node->next = list_head->next;
        list_head->next = new_node;
    }
}

void remove_hash(HASH_TABLE H, int x)
{
    struct list_node* pos = find_hash(H, x);
    if (pos)
    {
        struct list_node* head = H->the_lists[hash(x, H)];
        struct list_node* prev = 0;
        struct list_node* cur = head;
        while (cur)
        {
            if (cur->data == x && prev)
            {
                prev->next = cur->next;
                free(cur);
                break;
            }
            cur = cur->next;
            prev = cur;
        }
    }
}