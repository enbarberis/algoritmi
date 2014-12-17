#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "item_customer.h"

struct item_customer
{
	char id[MAX_STR];
	char surname[MAX_STR];
	char name[MAX_STR];
	char category[MAX_STR];
	int  required_kb;
	int  connection_time;	
	int  number_of_accesses;	
};

int item_customer_compare(void *key_a, void *key_b)
{
	char *a = (char *) key_a;
	char *b = (char *) key_b;
	return strcmp(a, b);
}

int item_customer_hash(void *key, int M)
{
	char *k = (char *) key;
	int h = 0;
	for(; *k != '\0'; k++)
		h = (BASE*h + *k) % M;
	return h;
}

void *item_customer_get_key(void *item)
{
	Item_customer item_cpy = (Item_customer) item;
	return item_cpy->id;
}

char *item_customer_get_category(Item_customer item)
{
	return item->category;
}

void item_customer_add_kb(Item_customer item, int kb)
{
	item->required_kb += kb;
}

void item_customer_add_time(Item_customer item, int time)
{
	item->connection_time += time;
}

void item_customer_add_access(Item_customer item)
{
	item->number_of_accesses++;
}

Item_customer item_customer_scan(FILE *fp)
{
	Item_customer new = malloc(sizeof(*new));
	fscanf(fp, "%s %s %s %s", new->id, new->name, new->surname, new->category);
	new->required_kb = 0;
	new->connection_time = 0;
	new->number_of_accesses = 0;
	return new;
}

void item_customer_print(Item_customer item, FILE *fp)
{
	fprintf(fp, "%-25s %-25s %-25s %-25s %10d %10d %10d\n", item->id, item->surname, item->name, item->category, 
			item->number_of_accesses, item->required_kb, item->connection_time);
}

void item_customer_free(Item_customer item)
{
	free(item);
}
