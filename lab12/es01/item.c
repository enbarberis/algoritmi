#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include  "item.h"

typedef struct adjacent_node *link;
struct adjacent_node{
	int node;
	int weight;	
	link next;
};

struct item{
	char city[MAX_STR];
	char region[MAX_STR];
	link adjacent_nodes; 
};

int item_compare(void *key_a, void *key_b)
{
	return strcmp((char *)key_a, (char *)key_b);
}

int item_hash(void *key, int m)
{
	char *k = (char *) key;
	int h = 0;
	for(; *k != '\0'; k++)
		h = (BASE*h + *k) % m;
	return h;
}

Item item_new(char *city, char *region)
{
	Item new = malloc(sizeof(*new));
	strcpy(new->city, city);
	strcpy(new->region, region);
	new->adjacent_nodes = NULL;
	return new;
}

void item_add_adjacent_node(Item i, int node, int weight)
{
	link child = malloc(sizeof(*child));
	link p;

	child->node = node;
	child->weight = weight;
	child->next = NULL;
	p = i->adjacent_nodes;
	
	if(p == NULL)
	{
		i->adjacent_nodes = child;
		return;
	}

	while(p->next != NULL)
		p = p->next;
	p->next = child;
}

Item item_scan(FILE *fp)
{
	Item new = malloc(sizeof(*new));
	char tmp[MAX_STR];
	fscanf(fp, "%s", new->city);
	fscanf(fp, "%s", new->region);
	new->adjacent_nodes = NULL;
	return new;
}

void item_destroy(Item i)
{
	link p = i->adjacent_nodes;
	link next;

	while(p != NULL)
	{
		next = p->next;
		free(p);
		p = next;
	}
	free(i);
}
