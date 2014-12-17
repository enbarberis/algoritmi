#include <stdlib.h>
#include "st_hash.h"

typedef struct st_node *link;
struct st_node{
	void *item;			//item pointer
	link next;			//pointer to the next item
};

struct st_hash{
	link *heads;			//array of list heads
	int M;				//cells number
	int iterator;			//iterator to retrive all the items
	link actual_node;		//pointer to the actual node of the iteration
	int   (*compare)(void*, void*);	//compare function
	int   (*hash)(void*, int);	//hash function
	void *(*get_key)(void*);	//function to get the key of item
};


St_hash st_hash_init(int M, int(*compare)(void *key_a, void *key_b), int(*hash)(void *key, int M), void*(*get_key)(void *item))
{
	int i;
	St_hash st = malloc(sizeof(*st));
	
	st->M = M;
	st->iterator = 0;
	st->actual_node = NULL;
	st->compare = compare;
	st->hash = hash;
	st->get_key = get_key;
	st->heads = malloc(M*sizeof(link));
	for(i=0; i<M; i++)
		st->heads[i] = NULL;

	return st;
}

link new(void *item, link next)
{
	link n = malloc(sizeof(*n));
	n->item = item;
	n->next = next;
	return n;
}

void st_hash_insert(St_hash st, void *item)
{
	int pos = st->hash(st->get_key(item), st->M);
	st->heads[pos] = new(item, st->heads[pos]);
}

void *r_search(St_hash st, link p, void *key)
{
	if(p == NULL)
		return NULL;
	if(st->compare(st->get_key(p->item), key) == 0) 
		return p->item;
	return r_search(st, p->next, key);
}

void *st_hash_search(St_hash st, void *key)
{
	return r_search(st, st->heads[st->hash(key, st->M)], key);
}

void st_hash_start_iteration(St_hash st)
{
	st->iterator = 0;
	st->actual_node = st->heads[0];
}

void *st_hash_get_next_item(St_hash st)
{
	link res;

	while(st->actual_node == NULL)
	{
		st->actual_node = st->heads[++st->iterator];
		if(st->iterator >= st->M)
			return NULL;
	}
	res = st->actual_node->item;
	st->actual_node = st->actual_node->next;
		
	return res;
}

void st_hash_destroy(St_hash st)
{	
	int i;
	link p, next;

	for(i=0; i<st->M; i++)
	{
		p = st->heads[i];
		while(p != NULL)
		{
			next = p->next;
			free(p);	
			p = next;
		}
	}
	free(st->heads);
	free(st);
}
