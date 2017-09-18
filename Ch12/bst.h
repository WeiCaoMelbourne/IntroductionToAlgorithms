
#ifndef CW_BST_H
#define CW_BST_H

#include <stdlib.h>

struct tree_node
{
    int data;
    struct tree_node* left;
    struct tree_node* right;
    struct tree_node* parent;
};

typedef struct tree_node* BST;

struct tree_node* bst_maximum(BST t);
struct tree_node* bst_successor(BST t);
struct tree_node* bst_search(BST t, int x);
BST initialize_bst();
void bst_insert(BST t, int data);
void bst_transplant(BST t, struct tree_node* u, struct tree_node* v);
void bst_delete(BST t, struct tree_node* z);
void bst_inorder_print(BST t);
void bst_inorder_str(BST t, char* output, size_t len);
void bst_destory(BST t);

#endif