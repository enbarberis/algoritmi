#ifndef BST_H_DEFINED
#define BST_H_DEFINED

#include "item.h"

typedef struct t_bst *BST;

BST bst_init();
void bst_insert_leaf(BST bst, Item i);
void bst_insert_root(BST bst, Item i);
Item bst_search(BST bst, Item i);
void bst_print_min_max(BST bst);
void bst_print_pre_order(BST bst, FILE *fp);
void bst_print_in_order(BST bst, FILE *fp);
void bst_print_post_order(BST bst, FILE *fp);
int  bst_tree_height(BST bst);
int  bst_root_size(BST bst);
int  bst_number_of_leafs(BST bst);
void bst_destroy(BST bst);
#endif
