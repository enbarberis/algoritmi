#include <stdlib.h>
#include <string.h>
#include "st.h"

struct st{
	int M;		//numero massimo di elementi
	int n;		//numero di elementi inseriti attualmente
	char **v;	//vettore di stringhe
};

St st_init(int n)
{
	St st = malloc(sizeof *st);
	st->M = n;
	st->n = 0;
	st->v = malloc(n * sizeof(char *));
	
	return st;
}

void st_insert(St st, char *str)
{
	st->v[st->n] = malloc((strlen(str) + 1) * sizeof(char)); 
	strcpy(st->v[st->n++], str);
}

int st_pos(St st, char *str)
{
	int i;

	for(i = 0; i < st->n; i++)
		if(strcmp(str, st->v[i]) == 0)
			return i;
	
	return -1;
}

char* st_get(St st, int pos)
{
	return st->v[pos];
}

void st_destroy(St st)
{
	int i;
	
	for(i = 0; i < st->n; i++)
		free(st->v[i]);
	free(st);
}
