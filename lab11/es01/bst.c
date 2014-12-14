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

link r_rotation(link h)
{
	link x = h->left;
	h->left = x->right;
	x->right = h;
	x->n = h->n;
	h->n = 1;
	if(h->right != NULL)
		h->n += h->right->n;
	if(h->left != NULL)
		h->n += h->left->n;
	return x;
}

link l_rotation(link h)
{
	link x = h->right;
	h->right = x->left;
	x->left = h;
	x->n = h->n;
	h->n = 1;
	if(h->right != NULL)
		h->n += h->right->n;
	if(h->left != NULL)
		h->n += h->left->n;
	return x;
}

link root_insert(link h, Item i)
{
	if(h == NULL)
		return new_node(i, NULL, NULL, 1);
	if(item_compare(i, h->item) < 0)
	{
		h->left = root_insert(h->left, i);
		h = r_rotation(h);
	}
	else
	{
		h->right = root_insert(h->right, i);
		h = l_rotation(h);
	}

	return h;
}

void bst_insert_root(BST bst, Item i)
{
	bst->root = root_insert(bst->root, i);
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

void bst_print_min_max(BST bst)
{
	if(bst->root == NULL){
		printf("Empty BST\n");
		return;
	}

	link p = bst->root;
	while(p->left != NULL)
		p = p->left;
	printf("MIN:\n");
	item_print(p->item, stdout);
	
	p = bst->root;
	while(p->right != NULL)
		p = p->right;
	printf("MAX:\n");
	item_print(p->item, stdout);
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
	if(bst->root != NULL)
		pre_order(bst->root, fp);
}

void bst_print_in_order(BST bst, FILE *fp)
{
	if(bst->root != NULL)
		in_order(bst->root, fp);
}

void bst_print_post_order(BST bst, FILE *fp)
{
	if(bst->root != NULL)
		post_order(bst->root, fp);
}

void height(link p, int level, int *max)
{
	if(level > *max)
		*max = level;
	if(p->left != NULL)
		height(p->left, level+1, max);
	if(p->right != NULL)
		height(p->right, level+1, max);
}

int bst_tree_height(BST bst)
{
	if(bst->root == NULL)
		return 0;
	int max = 1;
	height(bst->root, 1, &max);
	return max;
}

int bst_root_size(BST bst)
{
	if(bst->root == NULL)
		return 0;
	return bst->root->n;
}

void leafs(link p, int *n)
{
	if(p->right == NULL && p->left == NULL)
		(*n)++;
	if(p->left != NULL)
		leafs(p->left, n);
	if(p->right != NULL)
		leafs(p->right, n);
}

int bst_number_of_leafs(BST bst)
{
	if(bst->root == NULL)
		return 0;
	int n;
	leafs(bst->root, &n);
	return n;
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
