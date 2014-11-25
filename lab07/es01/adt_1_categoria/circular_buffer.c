#include <stdio.h>
#include "item.h"
#include "circular_buffer.h"
#include <stdlib.h>
#include <string.h>

struct circular_buffer{
	int size;
	int start;
	int end;
	Item *v;
};

Circular_buffer circular_buffer_init(int size)
{
	Circular_buffer cb = malloc(sizeof(*cb));
	cb->size = size + 1;
	cb->start = 0;
	cb->end = 0;
	cb->v = malloc(size*sizeof(Item));
	return cb;
}

int circular_buffer_size(Circular_buffer cb)
{
	if(cb->start <= cb->end)
		return cb->end - cb->start;
	else
		return cb->size - cb->start + cb->end;
}

void circular_buffer_enqueue(Circular_buffer cb, Item i)
{
	cb->v[cb->end] = i;
	cb->end = (cb->end + 1) % cb->size;
	if(cb->end == cb->start)
		cb->start = (cb->start + 1) % cb->size;
}

Item circular_buffer_dequeue(Circular_buffer cb)
{
	Item i = cb->v[cb->start];
	cb->start = (cb->start + 1) % cb->size;
	return i;
}

void circular_buffer_print(Circular_buffer cb, FILE *fp)
{
	int i = cb->start;
	while(i != cb->end)
	{
		item_print(cb->v[i], fp);
		i = (i + 1) % cb->size;
	}
}

void circular_buffer_destroy(Circular_buffer cb)
{	
	int i = cb->start;
	while(i != cb->end)
	{
		item_free(cb->v[i]);	
		i = (i + 1) % cb->size;
	}
	free(cb->v);
	cb->start = 0;
	cb->end = 0;
	cb->size = 0;
}
