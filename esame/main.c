#include <stdlib.h>
#include <stdio.h>
#include "st.h"
#include "graph.h"
//[MODIFICA] Dimenticato il "+ 1" necessario per '\0'
#define MAX_STR 15 + 1

int main(int argc, char **argv)
{
	FILE *fp;
	int i, j, n, c, d;				//[MODIFICA] Dimenticata la dichiarazione di j
	char nome1[MAX_STR], nome2[MAX_STR];
	St st;
	Graph g;

	fp = fopen(argv[1], "r");
	c = 0;
	n = 0;
	
	while(fscanf(fp, "%s %s", nome1, nome2) == 2)	//[MODIFICA] "== 2" e non "== 1"
		c++;

	rewind(fp);

	st = st_init(2*c);	//di sicuro ci saranno meno, o al piu` 2c persone

	while(fscanf(fp, "%s %s", nome1, nome2) == 2)
	{
		if(st_pos(st, nome1) == -1)
		{
			n++;	//contatore persone
			st_insert(st, nome1);
		}

		if(st_pos(st, nome2) == -1)
		{
			n++;
			st_insert(st, nome2);
		}
	}

	rewind(fp);
	g = graph_init(n);

	while(fscanf(fp, "%s %s", nome1, nome2) == 2)
	{
		graph_insert_edge(g, new_edge(st_pos(st, nome1), st_pos(st, nome2)));
	}

	fclose(fp);

	//CHECK DELLA SOLUZIONE

	fp = fopen(argv[2], "r");
	fscanf(fp, "%d", &c);		//c = numero di gruppi
	for(i = 0; i < c; i++)
	{
		fscanf(fp, "%d", &d);	//d = numero di persone del sottogruppo

		for(j = 0; j < d; j++)
		{
			fscanf(fp, "%s", nome1);
			graph_set_group(g, st_pos(st, nome1), i);
		}
	}
	fclose(fp);

	if(graph_check(g))
		printf("Soluzione valida\n");
	else
		printf("Soluzione NON valida\n");

	
	//GENERO SOLUZIONE OTTIMALE
	
	int min;
	int *sol = malloc(n * sizeof(int));
	
	min = graph_partition(g, sol);
	
	for(i = 0; i < min; i++)
	{
		printf("\nGruppo %d\n", i);
		for(j = 0; j < n; j++)
			if(sol[j] == i)
				printf("%s\n", st_get(st, j));
	}


	graph_destroy(g);				//[MODIFICA] Dimenticata la chiamta alle funzioni destroy
	st_destroy(st);

	return 0;
}
