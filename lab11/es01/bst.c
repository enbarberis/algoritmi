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

void pre_order(link p, FILE *fp)
{
	item_print(p->item, fp);
	if(p->left != NULL)
		pre_order(p->left, fp);
	if(p->right != NULL)
		pre_order(p->right, fp);
}

void in_order(link p, FILE *fp)
{
	if(p->left != NULL)
		in_order(p->left, fp);
	item_print(p->item, fp);
	if(p->right != NULL)
		in_order(p->right, fp);
}

void post_order(link p, FILE *fp)
{
	if(p->left != NULL)
		post_order(p->left, fp);
	if(p->right != NULL)
		post_order(p->right, fp);
	item_print(p->item, fp);
}

void bst_print_pre_order(BST bst, FILE *fp)
{
	pre_order(bst->root, fp);
}

void bst_print_in_order(BST bst, FILE *fp)
{
	in_order(bst->root, fp);
}

void bst_print_post_order(BST bst, FILE *fp)
{
	post_order(bst->root, fp);
}

void destroy(link p)
{
	if(p->left != NULL)
		destroy(p->left);
	if(p->right != NULL)
		destroy(p->right);
	item_free(p->item);
}

void bst_destroy(BST bst)
{
	if(bst->root != NULL)
		destroy(bst->root);
	free(bst);
}
