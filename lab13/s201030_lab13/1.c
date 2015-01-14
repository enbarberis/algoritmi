#include <stdlib.h>
#include <stdio.h>
#include "hash_table.h"
#include "graph.h"

#define MAX_STR 12 + 1

int main(int argc, char **argv)
{
	int n, a, b, choice, ris, i, j;
	int *path;
	char tmp1[MAX_STR], tmp2[MAX_STR];
	Hash_table ht;
	Graph g;
	FILE *fp;

	if(argc < 2){
		fprintf(stderr, "Parameters error!\nUsage: %s <input file>\n", argv[0]);
		return -1;
	}

	if((fp=fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "Can't open file %s\n", argv[1]);
		return -2;
	}

	fscanf(fp, "%d", &n);
	ht = hash_table_init(n);
	g  = graph_init(n);

	while(fscanf(fp, "%s %s", tmp1, tmp2) == 2)
	{
		if((a = hash_table_get(ht, tmp1)) == -1)
			a = hash_table_insert(ht, tmp1);
		if((b = hash_table_get(ht, tmp2)) == -1)
			b = hash_table_insert(ht, tmp2);
		graph_insert(g, create_edge(a,b));
	}
	fclose(fp);

	printf( "===== G R A P H =====\n"
		"1 - Shortest simple path between two nodes\n"
		"2 - Longest simple path between two nodes\n"
		"3 - Number of all simple paths between two nodes\n"
		"4 - Show strong connected nodes\n"
		"5 - Show edges to strong connect the graph\n"
		"6 - Exit\n");

	do{
		printf("\nChoice: ");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				printf("Start node: ");
				scanf("%s", tmp1);
				printf("End node:   ");
				scanf("%s", tmp2);
				if(hash_table_get(ht, tmp1) != -1 && hash_table_get(ht, tmp2) != -1)
				{
					ris = graph_get_shortest_path(g, hash_table_get(ht, tmp1), hash_table_get(ht, tmp2), &path);
					if(ris > 0)
					{
						printf("\nDistance = %d\n\nPath:\n", ris);
						for(i=0; i<=ris; i++)
							printf("%s\n", hash_table_get_name(ht, path[i]));
						free(path);
					}
					else
						printf("There is no path between these two nodes\n");
				}
				else
					printf("Error, inexistent nodes\n");
			break;

			case 2:
				printf("Start node: ");
				scanf("%s", tmp1);
				printf("End node:   ");
				scanf("%s", tmp2);
				if(hash_table_get(ht, tmp1) != -1 && hash_table_get(ht, tmp2) != -1)
				{
					ris = graph_get_longest_path(g, hash_table_get(ht, tmp1), hash_table_get(ht, tmp2), &path);
					if(ris > 0)
					{
						printf("\nDistance = %d\n\nPath:\n", ris);
						for(i=0; i<=ris; i++)
							printf("%s\n", hash_table_get_name(ht, path[i]));
						free(path);
					}
					else
						printf("There is no path between these two nodes\n");
				} 
				else
					printf("Error, inexistent nodes\n");
			break;
			
			case 3:
				printf("Start node: ");
				scanf("%s", tmp1);
				printf("End node:   ");
				scanf("%s", tmp2);
				if(hash_table_get(ht, tmp1) != -1 && hash_table_get(ht, tmp2) != -1)
					printf("Number of simple paths: %d\n",
							graph_number_of_simple_path(g, hash_table_get(ht, tmp1), hash_table_get(ht, tmp2)));	
				else
					printf("Error, inexistent nodes\n");
			break;
			case 4:
				path = graph_get_scc(g);
				//for every scc group
				for(i=0; i<n; i++)
				{
					a = 0;	//counter
					for(j=0; j<n; j++)
						if(path[j] == i)
						{
							printf("%s\n", hash_table_get_name(ht, j));
							a++;
						}
					if(a != 0)
						printf("============\n");
					else
						break;
				}
			break;
		}
	}while(choice != 6);

	hash_table_destroy(ht);
	graph_destroy(g);

	return 0;
}
