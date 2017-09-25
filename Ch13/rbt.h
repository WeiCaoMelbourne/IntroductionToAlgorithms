
/* Black Red Tree */
#ifndef CW_RBT_H
#define CW_RBT_H

#include <stdlib.h>

typedef enum rbt_color
{
	BLACK = 0,
	RED = 1
} RBT_COLOR;

struct rbt_node
{
    int key;
    struct rbt_node* left;
    struct rbt_node* right;
    struct rbt_node* parent;
    RBT_COLOR color;
};

typedef struct rbt_node* RBT;

RBT Initialize_rbt();
void Rbt_insert(RBT t, int key);
void Rbt_inorder_print(RBT t);
void Rbt_inorder_str(RBT t, char* output, size_t len);
void Rbt_delete(RBT t, struct rbt_node* z);
struct rbt_node* Rbt_search(RBT t, int x);

#endif