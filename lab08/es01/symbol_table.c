#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "symbol_table.h"

struct symbol_table
{
	int size;	//size del vettore
	Item *v;	//vettore degli item
};

void swap_item(Symbol_table st, int a, int b)
{
	Item tmp = st->v[a];
	st->v[a] = st->v[b];
	st->v[b] = tmp;
}

int partition(Symbol_table st, int l, int r)
{
	int i = l-1;
	int j = r;
	Item x = st->v[r];
	while(1)
	{
		while(compare_item(st->v[++i], x) < 0);
		while(compare_item(x, st->v[--j]) < 0)
			if(j == l)
				break;
		if(i >= j)
			break;
		swap_item(st, i, j);
	}
	swap_item(st, i, r);
	return i;
}

void quick_sort(Symbol_table st, int l, int r)
{
	int q;
	if(r <= l)
		return;
	q = partition(st, l, r);
	quick_sort(st, l, q-1);
	quick_sort(st, q+1, r);
}

Symbol_table symbol_table_init_from_file(FILE *fp)
{
	int j;
	Item i;
	char id[11], name[31], surname[31];
	int day, month, year;

	Symbol_table st = malloc(sizeof(*st));
	fscanf(fp,"%d", &st->size);
	st->v = (Item *) malloc(st->size*sizeof(Item));
	
	for(j=0; j<st->size; j++)
	{
		fscanf(fp, "%s %s %s %d%*c%d%*c%d", id, name, surname, &day, &month, &year); 
		i = new_item(id, name, surname, day, month, year);
		st->v[j] = i;
	}

	quick_sort(st, 0, st->size-1);

	return st;
}

Item symbol_table_search(Symbol_table st, Item i)
{
	int a, b, c;
	a = 0;
	b = st->size - 1;
	while(a <= b)
	{
		c = a + (b - a)/2;
		if(compare_item(st->v[c], i) == 0)
			return st->v[c];
		if(compare_item(st->v[c], i) <  0)
			a = c + 1;
		else
			b = c - 1;
	}

	return NULL;
}

void symbol_table_free(Symbol_table st)
{
	int i;
	for(i=0; i<st->size; i++)
		free_item(st->v[i]);
	free(st->v);
	free(st);
}
