#include "rbt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

RBT initialize_rbt()
{
    RBT t = malloc(sizeof(struct rbt_node));
    t->key = 0;
    t->left = t->right = t->parent = NULL;
    t->color = BLACK;

    return t;
}
