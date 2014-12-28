#include <stdlib.h>
#include <stdio.h>
#include "item.h"
#include "graph.h"

int main(int argc, char **argv)
{
	Graph graph;
	Item item;
	FILE *fp;
	int i, n;

	if(argc < 2){
		fprintf(stderr, "Errore nei parametri!\nUtilizzo: %s <input_file>\n", argv[0]);
		return -1;
	}

	if((fp = fopen(argv[1],"r")) == NULL){
		fprintf(stderr, "Impossibile aprire il file %s\n", argv[1]);
		return -2;
	}

	fscanf(fp, "%d", &n);		//leggo il numero di nodi
	graph = graph_init(n);
	for(i=0; i<n; i++)
	{
		item = item_scan(fp);
		graph_insert_node(graph, item);
	}
	
	fclose(fp);
	return 0;
}
