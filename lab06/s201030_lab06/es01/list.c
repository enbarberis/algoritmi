#include "item.h"
#include "list.h"
#include <stdlib.h>

typedef struct list_node* link;

struct list_node{
	Item item;
	link next;
	link prev;
};

struct list{
	link head;
	link tail;
	int n;
};

List list_init()
{
	List l = malloc(sizeof(*l));
	l->head = NULL;
	l->tail = NULL;
	l->n = 0;
	return l;
}

int list_empty(List l)
{
	return l->n == 0;
}

int list_size(List l)
{
	return l->n;
}

link new_list_node(Item i, link next, link prev)
{
	link x = malloc(sizeof(*x));
	x->item = i;
	x->next = next;
	x->prev = prev;
	return x;
}

void list_push_head(List l, Item i)
{
	if(l->head == NULL)	//if empty list
	{
		l->head = new_list_node(i,NULL,NULL);
		l->tail = l->head;
	}
	else
	{
		link n = new_list_node(i, l->head, NULL);
		l->head->prev = n;
		l->head = n;
	}
	(l->n)++;
}

void list_push_tail(List l, Item i)
{
	if(l->head == NULL)	//if empty list
	{
		l->head = new_list_node(i,NULL,NULL);
		l->tail = l->head;
	}
	else
	{
		link n = new_list_node(i, NULL, l->tail);
		l->tail->next = n;
		l->tail = n;
	}
	(l->n)++;
}

int list_extract(List l, Item i, int (*compare)(Item a, Item b))
{
	link p;
	//scan the list until reaching the end or finding the item 
	for(p=l->head; p!=NULL && compare(i,p->item)!=0; p=p->next);
	if(p!=NULL)
	{
		if(p->prev != NULL)
			p->prev->next = p->next;
		else
			l->head = p->next;

		if(p->next != NULL)
			p->next->prev = p->prev;
		else
			l->tail = p->prev;
		free(p);
		(l->n)--;
		return 1;
	}
	return 0;
}

void list_print_search(List l, Item i, int (*compare)(Item a, Item b))
{
	link p;
	for(p=l->head; p!=NULL; p=p->next)
		if(compare(p->item, i) == 0)
			item_print(p->item);
}


void list_print(List l)
{
	link p;
	for(p=l->head; p!=NULL; p=p->next)
		item_print(p->item);
}

void list_destroy(List l)
{
	link p;
	for(p=l->head; p!=NULL; p=p->next)
	{
		item_free(p->item);
		free(p);
	}
	l->head = NULL;
	l->tail = NULL;
	l->n = 0;
}
