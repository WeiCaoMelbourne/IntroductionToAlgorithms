#include "rbt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct rbt_node* brt_minimum(RBT t);
static void rbt_left_rotate(RBT t, struct rbt_node* x);
static void rbt_right_rotate(RBT t, struct rbt_node* y);
static void rbt_insert_fixup(RBT t, struct rbt_node* z);
static void rbt_transplant(RBT t, struct rbt_node* u, struct rbt_node* v);
static void rbt_delete_fixup(RBT t, struct rbt_node* x);

RBT Initialize_rbt()
{
    RBT t = malloc(sizeof(struct rbt_node));
    t->key = 0;
    t->left = t->right = t->parent = NULL;
    t->color = BLACK;

    return t;
}

/*
     x               y
    / \             / \
   a   y      ==>  x   c 
      / \         / \
     b   c       a   b
*/
static void rbt_left_rotate(RBT t, struct rbt_node* x)
{
    struct rbt_node* y = x->right;
    x->right = y->left;
    if (y->left)
        y->left->parent = x;

    y->parent = x->parent;

    if (x == t)
        t = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

/*
         y            x             
        / \          / \         
       x   c   ==>  a   y   
      / \              / \          
     a   b            b   c     
*/
static void rbt_right_rotate(RBT t, struct rbt_node* y)
{
    struct rbt_node* x = y->left;
    y->left = x->right;
    if (x->right)
        x->right->parent = y;

    x->parent = y->parent;

    if (y == t)
        t = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

/*
4 nodes: G for gradpa, P for parent, U for uncle, N for new.
    G
   / \
  P   U
   \
    N 
N is always RED. So if P is BLACK, done. 
case 1#:
    N, P, U are all RED (and G must be BLACK). If G is RED, so set
    G to RED, N and P to BLACK. then treat G as N, re-do this recursively.

    G(B)             G(R)   
   /   \            /   \                 
  P(R)  U(R)  =>   P(B)  U(B)                 
   \                \                   
    N(R)             N(R)            

case 2#:
    N, P are RED, U is BLACK or NULL. 1. rotate on P(left or right, depend on
    if N is right child or left child). 2. Put N BLACK, G RED. 3. rotate
    on G (left or right, depend on if N is left child or right child). 
    Do it recursively.

    G(B)             G(R)          G(R)           N(B)
   /   \            /   \          /  \           /  \
  P(R)  U(B)  =>   N(R)  U(B) => N(B)  U(B) =>   P(R) G(R)   
   \              /              /                     \
    N(R)         P(R)           P(R)                   U(B)

*/
static void rbt_insert_fixup(RBT t, struct rbt_node* z)
{
    while (z->parent && z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            struct rbt_node* y = z->parent->parent->right;
            if (y->color == RED)
            {   /* case 1# */
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else if (z == z->parent->right)
            {   /* case 2# */
                z = z->parent;
                rbt_left_rotate(t, z);
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbt_right_rotate(t, z->parent->parent);
            }
        }
        else
        {
            struct rbt_node* y = z->parent->parent->left;
            if (y->color == RED)
            {   /* case 1# */
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else if (z == z->parent->left)
            {   /* case 2# */
                z = z->parent;
                rbt_right_rotate(t, z);
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbt_left_rotate(t, z->parent->parent);
            }
        }
    }

    t->color = BLACK;
}

void Rbt_insert(RBT t, int key)
{
    if (!t)
    {
        printf("Empty tree, do not insert\n");
        return;
    }

    struct rbt_node* p = NULL;
    struct rbt_node* x = t;

    while (x)
    {
        p = x;
        if (key > x->key)
            x = x->right;
        else if (key < x->key)
            x = x->left;
        else
        {
            printf("%d already exists\n", key);
        }
    }

    struct rbt_node* new_node = (struct rbt_node*)malloc(sizeof(struct rbt_node));
    new_node->parent = p;
    new_node->key = key;
    new_node->color = RED;
    new_node->left = new_node->right = NULL;

    if (key < p->key)
        p->left = new_node;
    else
        p->right = new_node;

    rbt_insert_fixup(t, new_node);
}

void Rbt_inorder_print(RBT t)
{
    if (t->left)
        Rbt_inorder_print(t->left);
    printf("%d:%s ", t->key, (t->color == RED?"RED":"BLACK"));
    if (t->right)
        Rbt_inorder_print(t->right);
}

void Rbt_inorder_str(RBT t, char* output, size_t len)
{
    if (t->left)
        Rbt_inorder_str(t->left, output, len);
    char data_str[32];
    snprintf(data_str, sizeof(data_str), "%d:%s ", t->key, (t->color == RED?"RED":"BLACK"));
    strncat(output, data_str, len - strlen(data_str) - 1);
    if (t->right)
        Rbt_inorder_str(t->right, output, len);
}

/* Replace u with v */
static void rbt_transplant(RBT t, struct rbt_node* u, struct rbt_node* v)
{
    if (u->parent == NULL)
        t = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else 
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;
}

/*
N: the node to replace the deleted node. P: parent. S: uncle.
Because one node has been removed from P-N path, so that path is 1 BLACK less.
      P
     / \
    N   S
       / \
      SL  SR

case 1#: S is RED (SL and SR must be BLACK). 1. Put S BLACK and P RED
    2. left roate on P. Then leave it to case 2# & case 3#
    Because after case 1# process, the old SL is now S, so N and S are
    all BLACK by now.

      P(B)              S(B)                     
     /  \              /   \                 
    N(B) S(R)    =>  P(R)   SR(B)                  
        /  \         /  \                        
      SL(B) SR(B)  N(B)  SL(B)        

case 2#: N, S, SR, SL are all BLACK. simply put S to be RED. Because P-N path is 1
    BLACK less than P-S path, now P-N and P-S path are equal, but they are 1 BLACK
    less than all the other path. So set x = x->parent, and re-do the whole process.

      P(B)            P(B)                       
     /  \            /  \                    
    N(B) S(B)    => N(B) S(R)                      
        /  \            /  \                     
      SL(B) SR(B)     SL(B) SR(B)   

case 3#: N S, SR BLACK, SL RED OR NULL. 1) right rotate on S, swap color of S and its
    new father. 2) rotate left on P, set S BLACK. Now the path to N has 1 more BLACK,
    and the path to S remains the same BLACK. So it is done. 
                                                                                
      P(B)            P(B)               SL(B)                                       
     /  \            /  \               /  \                             
    N(B) S(B)    => N(B) SL(B)    =>   P(B) S(B)                                      
        /  \               \          /       \                          
      SL(R) SR(B)          S(R)      N(B)      SR(B)              
                             \                                   
                             SR(B)                                                                                                                   
*/
static void rbt_delete_fixup(RBT t, struct rbt_node* x)
{
    while (x != t && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            struct rbt_node* w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rbt_left_rotate(t, x->parent);
                w = x->parent->right;
            }

            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else if (w->right->color == BLACK)
            {
                w->left->color = BLACK;
                w->color = RED;
                rbt_right_rotate(t, w);
                w = x->parent->right;

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rbt_left_rotate(t, x->parent);
                x = t;
            }
        }
        else
        {
            struct rbt_node* w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rbt_right_rotate(t, x->parent);
                w = x->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else if (w->left->color == BLACK)
            {
                w->right->color = BLACK;
                w->color = RED;
                rbt_left_rotate(t, w);
                w = x->parent->left;

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rbt_right_rotate(t, x->parent);
                x = t;
            }
        }
    }

    x->color = BLACK;
}

static struct rbt_node* brt_minimum(RBT t)
{
    while (t->left)
        t = t->left;

    return t;
}

void Rbt_delete(RBT t, struct rbt_node* z)
{
    struct rbt_node* y = z;
    RBT_COLOR y_orig_color = y->color;

    struct rbt_node* x = NULL;

    if (z->left == NULL)
    {
        x = z->right;
        rbt_transplant(t, z, z->right);
    }
    else if (z->right == NULL)
    {
        x = z->left;
        rbt_transplant(t, z, z->left);
    }
    else
    {
        y = brt_minimum(z->right);
        y_orig_color = y->color;
        x = y->right;
        if (y->parent == z)
            x = y;
        else
        {
            rbt_transplant(t, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        rbt_transplant(t, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_orig_color == BLACK)
        rbt_delete_fixup(t, x);        
}

struct rbt_node* Rbt_search(RBT t, int x)
{
    if (t && x == t->key)
        return t;

    if (x > t->key)
        return Rbt_search(t->right, x);

    return Rbt_search(t->left, x);
}