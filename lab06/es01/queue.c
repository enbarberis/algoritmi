#include "item.h"
#include "queue.h"
#include <stdlib.h>

typedef struct queue_node* link;

struct queue_node{
	Item item;
	link next;
};

struct queue{
	link head;
	link tail;
	int n;
};

Queue queue_init()
{
	Queue q = malloc(sizeof(*q));
	q->head = NULL;
	q->tail = NULL;
	q->n = 0;
}

int queue_empty(Queue q)
{
	return q->n == 0;
}

int queue_size(Queue q)
{
	return q->n;
}

link queue_new(Item item, link next)
{
	link l = malloc(sizeof(*l));
	l->item = item;
	l->next = next;
	return l;
}

void queue_push(Queue q, Item i)
{
	if(q->head == NULL)
	{
		q->tail = queue_new(i,NULL);
		q->head = q->tail;
	}	
	else
	{
		q->tail->next = queue_new(i,NULL);
		q->tail = q->tail->next;
	}	
	(q->n)++;
}

Item queue_pop(Queue q)
{
	if(q->head != NULL)
	{
		Item i = q->head->item;
		link tmp = q->head->next;
		free(q->head);
		q->head = tmp;
		if(q->head == NULL) q->tail = NULL;
		(q->n)--;
		return i;
	}
}

Item queue_head(Queue q)
{
	if(q->head != NULL)
		return q->head->item;
}

Item queue_tail(Queue q)
{
	if(q->tail != NULL)
		return q->tail->item;
}

void queue_print(Queue q)
{
	link p;
	for(p = q->head; p!=NULL; p=p->next)
		item_print(p->item);
}

void queue_destroy(Queue q)
{
	link p;
	for(p = q->head; p!=NULL; p=p->next)
	{
		item_free(p->item);
		free(p);
	}
	q->n = 0;
	q->tail = NULL;
	q->head = NULL;
}
