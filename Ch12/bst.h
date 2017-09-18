
#ifndef CW_BST_H
#define CW_BST_H

#include <stdlib.h>

struct bst_node
{
    int data;
    struct bst_node* left;
    struct bst_node* right;
    struct bst_node* parent;
};

typedef struct bst_node* BST;

struct bst_node* bst_maximum(BST t);
struct bst_node* bst_successor(BST t);
struct bst_node* bst_search(BST t, int x);
BST initialize_bst();
void bst_insert(BST t, int data);
void bst_transplant(BST t, struct bst_node* u, struct bst_node* v);
void bst_delete(BST t, struct bst_node* z);
void bst_inorder_print(BST t);
void bst_inorder_str(BST t, char* output, size_t len);
void bst_destory(BST t);

#endif