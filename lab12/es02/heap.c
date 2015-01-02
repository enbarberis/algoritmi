#include <stdlib.h>
#include <stdio.h>
#include "item.h"
#include "heap.h"
#define left(i)		((i*2) + 1)
#define right(i)	((i*2) + 2)
#define parent(i)	((i-1) / 2)

struct heap{
	Item *v;	//array of items
	int n;		//number of items (heapsize)
	int size;	//space avilable
};

Heap heap_init()
{
	Heap h = malloc(sizeof(*h));
	h->n = 0;
	h->size = INIT_SIZE;
	h->v = malloc(INIT_SIZE * sizeof(Item));
	return h;
}

void swap(Heap h, int a, int b)
{
	Item tmp = h->v[a];
	h->v[a] = h->v[b];
	h->v[b] = tmp;
}

void heap_insert(Heap h, Item i)
{
	int node_index;

	//if there isn't enough space
	if(h->n  >= h->size)
	{
		h->size *= 2;
		h->v = realloc(h->v, h->size * sizeof(Item));
	}
	
	h->v[h->n] = i;
	node_index = h->n++;
	
	while(node_index != 0)
	{
		//if child is greater than the parent
		if(item_compare(h->v[node_index], h->v[parent(node_index)]) > 0)
		{
			swap(h, node_index, parent(node_index));
			node_index = parent(node_index);
		}
		else
		{
			break;
		}
	}
}

void heapify(Heap h, int i)
{
	int l, r, largest;
	l = left(i);
	r = right(i);
	if(l < h->n && item_compare(h->v[l], h->v[i]) > 0)
		largest = l;
	else
		largest = i;
	if(r < h->n && item_compare(h->v[r], h->v[largest]) > 0)
		largest = r;
	if(largest != i)
	{
		swap(h, i, largest);
		heapify(h, largest);
	}
}

Item heap_extract(Heap h)
{
	if(h->n <= 0) 
		return NULL;
	Item max = h->v[0];
	h->n--;
	h->v[0] = h->v[h->n];
	heapify(h, 0);
	return max;
}

void heap_destroy(Heap h)
{
	int i;
	for(i=0; i<h->n; i++)
		item_destroy(h->v[i]);
	free(h->v);
	free(h);
}
