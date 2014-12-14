#ifndef BST_H_DEFINED
#define BST_H_DEFINED

#include "item.h"

typedef struct t_bst *BST;

BST bst_init();
void bst_insert_leaf(BST bst, Item i);
Item bst_search(BST bst, Item i);

#endif
