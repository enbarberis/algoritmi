#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "item.h"
#include "bst.h"

int main(int argc, char *argv)
{
	Item i;

	BST bst;
	bst = bst_init();

	i = item_scan(stdin);
	bst_insert_leaf(bst, i);

	i = item_scan(stdin);
	bst_insert_leaf(bst, i);

	i = item_scan(stdin);
	bst_insert_leaf(bst, i);


	i = item_scan(stdin);
	bst_insert_leaf(bst, i);


	return 0;
}
