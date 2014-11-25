#include <stdio.h>
#include "item.h"
#include <stdlib.h>
#include <string.h>


struct item{
	char *s;
	int n;
};

Item item_scan()
{
	char tmp[128];
	Item i = malloc(sizeof(*i));
	
	printf("\nString: ");
	scanf("%s", tmp);
	i->s = (char *) malloc((strlen(tmp)+1)*sizeof(char));
	strcpy(i->s, tmp);

	printf("Number: ");
	scanf("%d", &i->n);
	
	return i;
}

Item item_new(char *s, int n)
{
	Item i = malloc(sizeof(*i));
	i->s = s;
	i->n = n;
	return i;
}

void item_print(Item i, FILE *fp)
{
	fprintf(fp,"\n%s\n%d\n", i->s, i->n);
}

void item_free(Item i)
{
	free(i->s);
	free(i);
}
