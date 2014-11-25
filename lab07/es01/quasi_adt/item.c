#include <stdio.h>
#include "item.h"
#include <stdlib.h>
#include <string.h>

Item item_scan()
{
	Item i = malloc(sizeof(*i));
	
	printf("\nString: ");
	scanf("%s", i->s);

	printf("Number: ");
	scanf("%d", &i->n);
	
	return i;
}

Item item_new(char *s, int n)
{
	Item i = malloc(sizeof(*i));
	strcpy(i->s, s);
	i->n = n;
	return i;
}

void item_print(Item i, FILE *fp)
{
	fprintf(fp,"\n%s\n%d\n", i->s, i->n);
}

void item_free(Item i)
{
	free(i);
}
