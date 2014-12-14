#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

struct t_item{
	int key;
	char str[MAX_STR];
};

int item_compare(Item a, Item b)
{
	return a->key - b->key;
}

Item item_scan(FILE *fp)
{
	Item new = malloc(sizeof(*new));
	
	if(fp == stdin)
	{
		printf("\nKey: ");
		scanf("%d", &new->key);
		printf("String: ");
		scanf("%s", new->str);
	}
	else
	{
		fscanf(fp, "%d %s", &new->key, new->str);
	}

	return new;
}

Item item_new(int key, char *str)
{
	Item new = malloc(sizeof(*new));
	new->key = key;
	strcpy(new->str, str);
	return new;
}

void item_print(Item a, FILE *fp)
{
	fprintf(fp,"%d %s\n", a->key, a->str);
}

void item_free(Item a)
{
	free(a);
}
