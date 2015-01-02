#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

struct item{
	int priority;
	char id[MAX_STR];
};

int item_compare(Item a, Item b)
{
	return a->priority - b->priority;
}

Item item_new(char *id, int priority)
{
	Item new = malloc(sizeof(*new));
	strcpy(new->id, id);
	new->priority = priority;
	return new;
}

void item_print(Item i, FILE *fp)
{
	fprintf(fp, "%s\t%d\n", i->id, i->priority);
}

void item_destroy(Item i)
{
	free(i);
}
