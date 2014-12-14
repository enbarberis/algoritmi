#include <stdlib.h>
#include <stdio.h>
#include "item.h"
#include "bst.h"

typedef struct bst_node *link;

struct bst_node{
	Item item;		//node item
	link left;		//left child
	link right;		//right child
	int n;			//size of sub-tree
};

struct t_bst{
	link root;
};

BST bst_init()
{
	BST bst = malloc(sizeof(*bst));
	bst->root = NULL;
	return bst;
}

link new_node(Item i, link l, link r, int n)
{
	link new = malloc(sizeof(*new));
	new->item = i;
	new->left = l;
	new->right = r;
	new->n = n;
	return new;
}

void bst_insert_leaf(BST bst, Item i)
{
	//if empty bst
	if(bst->root == NULL)
	{
		bst->root = new_node(i, NULL, NULL, 1);
		return;
	}

	//if not empty bst
	link p = bst->root;	//father
	link x = p;		//actual pointer
	while(x != NULL)
	{
		p = x;
		x->n++;
		if(item_compare(i, x->item) < 0)
			x = x->left;
		else
			x = x->right;
	}
	x = new_node(i, NULL, NULL, 1);
	if(item_compare(i, p->item) < 0)
		p->left = x;
	else
		p->right = x;
}


Item bst_search(BST bst, Item i)
{
	//if empty bst
	if(bst->root == NULL)
		return NULL;

	//if not empty bst
	link p = bst->root;	//father
	link x = p;		//actual pointer
	while(x != NULL)
	{
		p = x;
		x->n++;
		if(item_compare(i, x->item) < 0)
			x = x->left;
		else
			x = x->right;
	}
	return p->item;
}
