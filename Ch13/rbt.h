
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

RBT initialize_rbt();

#endif