#include "item.h"
#include "priority_queue.h"
#include <stdlib.h>

typedef struct priority_queue_node* link;

struct priority_queue_node{
	Item item;
	link next;
	link prev;
};

struct priority_queue{
	link head;
	link tail;
	int n;
};

Priority_queue priority_queue_init()
{
	Priority_queue q = malloc(sizeof(*q));
	q->head = NULL;
	q->tail = NULL;
	q->n = 0;
	return q;
}

int priority_queue_empty(Priority_queue q)
{
	return q->n == 0;
}

int priority_queue_size(Priority_queue q)
{
	return q->n;
}

link new_priority_queue_node(Item i, link next, link prev)
{
	link x = malloc(sizeof(*x));
	x->item = i;
	x->next = next;
	x->prev = prev;
	return x;
}

void priority_queue_push(Priority_queue q, Item i, int (*compare)(Item a, Item b))
{
	//if there are no elements
	if(q->head == NULL)
	{
		q->head = new_priority_queue_node(i,NULL,NULL);
		q->tail = q->head;
	}
	else
	{
		link p;
		for(p=q->head; p->next!=NULL && compare(i,p->item) < 0; p=p->next);
		if(p->next == NULL && compare(i,p->item) < 0)
		{
			p->next = new_priority_queue_node(i,NULL,p);
			q->tail = p->next;
		}	
		else if(p->prev == NULL && compare(i,p->item) > 0)
		{
			p->prev = new_priority_queue_node(i,p,NULL);
			q->head = p->prev;
		}
		else
		{
			p->prev = new_priority_queue_node(i,p,p->prev);
			p->prev->prev->next = p->prev;
		}
	}
	(q->n)++;
}

Item priority_queue_pop(Priority_queue q)
{
	if(q->head != NULL)
	{
		Item i = q->head->item;
		link tmp = q->head->next;
		free(q->head);
		q->head = tmp;
		if(tmp != NULL) tmp->prev = NULL;
		if(q->head == NULL) q->tail = NULL;
		(q->n)--;
		return i;
	}
}

void priority_queue_print(Priority_queue q)
{
	link p;
	for(p=q->head; p!=NULL; p=p->next)
		item_print(p->item);
}

void priority_queue_destroy(Priority_queue q)
{
	link p;
	for(p=q->head; p!=NULL; p=p->next)
	{	
		item_free(p->item);
		free(p);
	}
	q->head = NULL;
	q->tail = NULL;
	q->n = 0;
}
