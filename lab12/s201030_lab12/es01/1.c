#include <stdlib.h>
#include <stdio.h>
#include "item.h"
#include "graph.h"

int main(int argc, char **argv)
{
	Graph graph;
	Item item;
	FILE *fp;
	int i, n, w, scelta;
	char citta1[MAX_STR], citta2[MAX_STR];
	int inter, intra;
	
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
	
	//carico archi
	while(fscanf(fp,"%s %s %d", citta1, citta2, &w) == 3)
		graph_connect_nodes(graph, citta1, citta2, w);
	
	fclose(fp);

	printf( "===== M E N U =====\n"
		"1 - Stampa il grado di ogni vertice`\n"
		"2 - Stampa tutti i vertici\n"
		"3 - Stampa i nodi adiacenti ad un nodo\n"
		"4 - Genera la matrice di adiacenza\n"
		"5 - Calcolare flusso inter-regionale e intra-regionale\n"
		"6 - Esci");
	do{
		printf("\nScelta: ");
		scanf("%d", &scelta);
		switch(scelta)
		{
			case 1:
				graph_print_all_degree(graph);
			break;
			case 2:
				graph_print_all_nodes(graph);
			break;
			case 3:
				printf("Introduci la citta` di cui vuoi sapere quali sono i nodi adiacenti: ");
				scanf("%s", citta1);
				graph_print_adj_nodes(graph, citta1);
			break;
			case 4:
				graph_create_adjacency_matrix(graph);
			break;
			case 5:
				graph_intra_inter_flow(graph, &intra, &inter);			
				printf("Flusso intra-regionale: %d\n", intra);	
				printf("Flusso inter-regionale: %d\n", inter);
			break;
		}
	
	}while(scelta != 6);

	graph_destroy(graph);

	return 0;
}
