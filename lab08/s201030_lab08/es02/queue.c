#include "item.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct queue_node* link;

struct queue_node{
	Item item;
	link next;
	link prev;
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

link queue_new(Item item, link next, link prev)
{
	link l = malloc(sizeof(*l));
	l->item = item;
	l->next = next;
	l->prev = prev;
	return l;
}

void queue_push(Queue q, Item i)
{
	if(q->head == NULL)
	{
		q->tail = queue_new(i,NULL,NULL);
		q->head = q->tail;
	}	
	else
	{
		q->tail->next = queue_new(i,NULL,q->tail);
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
	return NULL;
}

int queue_delete(Queue q, Item i)
{
	link p;
	for(p = q->head; p!=NULL && compare_item(i,p->item)!=0; p=p->next);
	if(p == NULL)
		return 0;	//failure
	else
	{
		if(p == q->head)
			q->head = q->head->next;
		if(p == q->tail)
			q->tail = q->tail->prev;
		if(q->head != NULL)
		{
			if(p->next != NULL)
				p->next->prev = p->prev;
			if(p->prev != NULL)
				p->prev->next = p->next;
		}
		(q->n)--;
		free(p);
		return 1;	//success
	}
}

int queue_edit(Queue q, Item i)
{
	link p;
	for(p = q->head; p!=NULL && compare_item(i,p->item)!=0; p=p->next);
	if(p != NULL)
	{
		printf("\nIntroduce new data:\n");
		Item new = scan_item();
		free(i);
		p->item = new;
		return 1;	//success
	}
	else
		return 0;	//failure
}

void queue_print(Queue q)
{
	link p;
	for(p = q->head; p!=NULL; p=p->next)
		print_item(p->item);
}

void queue_destroy(Queue q)
{
	link p;
	for(p = q->head; p!=NULL; p=p->next)
	{
		free_item(p->item);
		free(p);
	}
	free(q);
}
