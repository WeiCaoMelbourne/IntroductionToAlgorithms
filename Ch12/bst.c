#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bst_inorder(BST t)
{
    if (t)
    {
        bst_inorder(t->left);
        printf("%d\n", t->data);
        bst_inorder(t->right);
    }
}

struct tree_node* bst_search(BST t, int x)
{
    if (t && x == t->data)
        return t;

    if (x > t->data)
        return bst_search(t->right, x);

    return bst_search(t->left, x);
}

struct tree_node* bst_minimum(BST t)
{
    while (t->left)
        t = t->left;

    return t;
}

struct tree_node* bst_maximum(BST t)
{
    while (t->right)
        t = t->right;

    return t;
}

/* in order. successor of node t is the node with the smallest data greater than t.data */
struct tree_node* bst_successor(BST t)
{
    if (t->right)
        return bst_minimum(t);

    struct tree_node* y = t->parent;
    struct tree_node* x = t;

    while (y && x == y->right)
    {
        x = y;
        y = y->parent;
    }

    return y;
}

BST initialize_bst()
{
    BST t = malloc(sizeof(struct tree_node));
    t->left = t->right = t->parent = 0;
}

void bst_destory(BST t)
{
    if (!t)
        return;

    if (t->right)
        bst_destory(t->right);
    if (t->left)
        bst_destory(t->right);
    
    if (t->parent && t->parent->left == t)
        t->parent->left = NULL;
    if (t->parent && t->parent->right == t)
        t->parent->right = NULL;
    free(t);
}

void bst_insert(BST t, int data)
{
    if (!t)
    {
        printf("Empty tree, do not insert\n");
        return;
    }

    struct tree_node* p = NULL;
    struct tree_node* x = t;

    while (x)
    {
        p = x;
        if (data > x->data)
            x = x->right;
        else if (data < x->data)
            x = x->left;
        else
        {
            printf("%d already exists\n", data);
        }
    }

    struct tree_node* new_node = (struct tree_node*)malloc(sizeof(struct tree_node));
    new_node->parent = p;
    new_node->data = data;
    new_node->left = new_node->right = NULL;

    if (data < p->data)
        p->left = new_node;
    else
        p->right = new_node;
}

/* Replace u with v */
void bst_transplant(BST t, struct tree_node* u, struct tree_node* v)
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

/* Delete node y from tree t */
void bst_delete(BST t, struct tree_node* z)
{
    if (z->left == NULL)
        bst_transplant(t, z, z->right);
    else if (z->right == NULL)
        bst_transplant(t, z, z->left);
    else
    {
        struct tree_node* y = bst_minimum(z->right);
        if (y->parent != z)
        {
            bst_transplant(t, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        bst_transplant(t, z, y);
        y->left = z->left;
        y->left->parent = y;
    }

    free(z);
}

void bst_inorder_print(BST t)
{
    if (t->left)
        bst_inorder_print(t->left);
    printf("%d ", t->data);
    if (t->right)
        bst_inorder_print(t->right);
}

void bst_inorder_str(BST t, char* output, size_t len)
{
    if (t->left)
        bst_inorder_str(t->left, output, len);
    char data_str[32];
    snprintf(data_str, sizeof(data_str), "%d ", t->data);
    strncat(output, data_str, len - strlen(data_str) - 1);
    if (t->right)
        bst_inorder_str(t->right, output, len);
}