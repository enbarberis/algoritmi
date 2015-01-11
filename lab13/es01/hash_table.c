#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

struct hash_table{
	int n;		//number of elements
	char** v;	//array of elements (strings)
};

Hash_table hash_table_init(int n)
{
	int i;
	Hash_table ht = malloc(sizeof(*ht));
	ht->n = n;
	ht->v = malloc(n * sizeof(char *));
	for(i=0; i<n; i++)
		ht->v[i] = NULL;
	return ht;
}

int hash(char *str, int M)
{
	char *k = str;
	int h = 0;
	for(; *k != '\0'; k++)
		h = (BASE*h + *k) % M;
	return h;
}

int hash_table_insert(Hash_table ht, char *name)
{
	//calculation of hash code
	int h = hash(name, ht->n);

	//searching first position available
	while(ht->v[h] != NULL)
		h = (h + 1) % ht->n;

	//insertion of the element
	ht->v[h] = malloc((strlen(name) + 1) * sizeof(char));
	strcpy(ht->v[h], name);

	return h;
}

int hash_table_get(Hash_table ht, char *name)
{
	int h = hash(name, ht->n);
	int c = 0;

	//if it doesn't exist return -1
	if(ht->v[h] == NULL) 
		return -1;
	while(strcmp(ht->v[h], name) != 0 && c < ht->n)
	{
		c++;
		h = (h + 1) % ht->n;
	}
	if(c >= ht->n)
		return -1;
	return h;
}

char* hash_table_get_name(Hash_table ht, int pos)
{
	if(pos >=0 && pos < ht->n)
		return ht->v[pos];
	return NULL;
}

void hash_table_destroy(Hash_table ht)
{
	int i;
	for(i=0; i<ht->n; i++)
		free(ht->v[i]);
	free(ht);
}
