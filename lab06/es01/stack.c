#include "item.h"
#include "stack.h"
#include <stdlib.h>

typedef struct stack_node* link;

struct stack_node{
	Item item;
	link next;
};

struct stack{
	link top;
	int n;
};

Stack stack_init()
{
	Stack s = malloc(sizeof(*s));
	s->top = NULL;
	s->n = 0;
}

int stack_empty(Stack s)
{
	return s->n == 0;
}

int stack_size(Stack s)
{
	return s->n;
}

link stack_new(Item item, link next)
{
	link l = malloc(sizeof(*l));
	l->item = item;
	l->next = next;
	return l;
}

void stack_push(Stack s, Item i)
{
	if(s->top == NULL)
		s->top = stack_new(i,NULL);
	else
		s->top = stack_new(i, s->top);
	(s->n)++;
}

Item stack_pop(Stack s)
{
	if(s->top != NULL)
	{
		Item i = s->top->item;
		link tmp = s->top->next;
		free(s->top);
		s->top = tmp;
		(s->n)--;
		return i;
	}
}

Item stack_top(Stack s)
{
	if(s->top != NULL)
		return s->top->item;
}

void stack_print(Stack s)
{
	link p;
	for(p = s->top; p!=NULL; p=p->next)
		item_print(p->item);
}

void stack_destroy(Stack s)
{
	link p;
	for(p = s->top; p!=NULL; p=p->next)
	{
		item_free(p->item);
		free(p);
	}
	s->n = 0;
	s->top = NULL;
}
