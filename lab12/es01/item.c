#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "item.h"

struct item{
	char city[MAX_STR];
	char region[MAX_STR];
};

Item item_new(char *city, char *region)
{
	Item new = malloc(sizeof(*new));
	strcpy(new->city, city);
	strcpy(new->region, region);
	return new;
}

Item item_scan(FILE *fp)
{
	Item new = malloc(sizeof(*new));
	fscanf(fp, "%s %s", new->city, new->region);
	return new;
}

int item_compare(char *key_a, char *key_b)
{
	return strcmp(key_a, key_b);
}

int item_hash(char *key, int m)
{
	char *k = key;
	int h = 0;
	for(; *k != '\0'; k++)
		h = (BASE*h + *k) % m;
	return h;
}

char* item_get_key(Item item)
{
	return item->city;
}

char* item_get_region(Item item)
{
	return item->region;
}

void item_destroy(Item item)
{
	free(item);	
}
