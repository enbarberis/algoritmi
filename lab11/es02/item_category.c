#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "item_category.h"

typedef struct customer_node *link;
struct customer_node{
	char id[MAX_STR];
	link next;
};

struct item_category{
	char id[MAX_STR];
	int required_kb;
	link customers;
};

int item_category_compare(void *key_a, void *key_b)
{
	char *a = (char *) key_a;
	char *b = (char *) key_b;
	return strcmp(a, b);
}

int item_category_hash(void *key, int M)
{
	char *k = (char *) key;
	int h = 0;
	for(; *k != '\0'; k++)
		h = (BASE*h + *k) % M;
	return h;
}

void *item_category_get_key(void *item)
{
	Item_category item_cpy = (Item_category) item;
	return item_cpy->id;
}

Item_category item_category_new(char *id)
{
	Item_category new = malloc(sizeof(*new));
	strcpy(new->id, id);
	new->required_kb = 0;
	new->customers = NULL;
	return new;
}

void item_category_add_kb(Item_category item, int kb)
{
	item->required_kb += kb;
}

link new_customer(char *customer_id, link next)
{
	link x = malloc(sizeof(*x));
	strcpy(x->id, customer_id);
	x->next = next;
	return x;
}

void item_category_add_customer(Item_category item, char *customer_id)
{
	item->customers = new_customer(customer_id, item->customers);
}

void item_category_print_customers(Item_category item, FILE *fp)
{
	fprintf(fp, "%-25s\n", item->id);
	link p = item->customers;
	while(p != NULL)
	{
		fprintf(fp, "\t%s\n", p->id);
		p = p->next;
	}
}

void item_category_print_kb(Item_category item, FILE *fp)
{
	fprintf(fp, "%-25s %d\n", item->id, item->required_kb);
}

void item_category_free(Item_category item)
{
	link p = item->customers;
	link next;

	while(p != NULL)
	{
		next = p->next;
		free(p);
		p = next;
	}
	free(item);
}
