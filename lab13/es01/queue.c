#include <stdlib.h>
#include "queue.h"

typedef struct queue_node* link;

struct queue_node{
	int item;
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

link queue_new(int item, link next)
{
	link l = malloc(sizeof(*l));
	l->item = item;
	l->next = next;
	return l;
}

void queue_put(Queue q, int i)
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

int queue_get(Queue q)
{
	if(q->head != NULL)
	{
		int i = q->head->item;
		link tmp = q->head->next;
		free(q->head);
		q->head = tmp;
		if(q->head == NULL) q->tail = NULL;
		(q->n)--;
		return i;
	}
}

void queue_destroy(Queue q)
{
	link p;
	for(p = q->head; p!=NULL; p=p->next)
		free(p);	
	free(q);
}
