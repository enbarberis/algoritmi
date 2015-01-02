#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "item.h"
#include "graph.h"

typedef struct t_edge *edge;
struct t_edge{
	int node;
	int weight;
	edge next;
};

typedef struct t_node{
	Item item;
	int degree;
	edge edges;
} t_node;

struct graph{
	t_node *node;		//array of nodes
	int **adj_matrix;	//adjacency_matrix
	int size;		//number of nodes
};

Graph graph_init(int size)
{
	int i;
	
	Graph graph = malloc(sizeof(*graph));
	graph->node = malloc(size * sizeof(t_node));
	graph->adj_matrix = NULL;
	graph->size = size;
	for(i=0; i<size; i++)
	{
		graph->node[i].item = NULL;
		graph->node[i].degree = 0;
		graph->node[i].edges = NULL;
	}
	return graph;
}

void graph_insert_node(Graph graph, Item item)
{
	int h = item_hash(item_get_key(item), graph->size);
	while(graph->node[h].item != NULL)
		h = (h + 1) % graph->size;
	graph->node[h].item = item;
}

void add_edge(t_node *node, int adj_node, int weight)
{
	edge e = malloc(sizeof(*e));
	edge p = node->edges;
	e->node = adj_node;
	e->weight = weight;
	e->next = NULL;
	
	if(node->edges == NULL)
	{
		node->edges = e;
		return;
	}

	while(p->next != NULL)
		p = p->next;
	p->next = e;
}

void graph_connect_nodes(Graph graph, char *key1, char *key2, int weight)
{
	int pos1, pos2;
	
	pos1 = item_hash(key1, graph->size);
	while(item_compare(item_get_key(graph->node[pos1].item), key1) != 0)
		pos1 = (pos1 + 1) % graph->size;
	
	pos2 = item_hash(key2, graph->size);
	while(item_compare(item_get_key(graph->node[pos2].item), key2) != 0)
		pos2 = (pos2 + 1) % graph->size;

	graph->node[pos1].degree++;
	graph->node[pos2].degree++;
	add_edge(&graph->node[pos1], pos2, weight);
	add_edge(&graph->node[pos2], pos1, weight);
}

void graph_print_all_degree(Graph graph)
{
	int i;
	for(i=0; i<graph->size; i++)
		printf("%-20s\t%d\n", item_get_key(graph->node[i].item), graph->node[i].degree);
}

void graph_print_all_nodes(Graph graph)
{
	int i;
	printf("%d nodes\n", graph->size);
	for(i=0; i<graph->size; i++)
		printf("%d\t%s\n", i, item_get_key(graph->node[i].item));
}

void graph_print_adj_nodes(Graph graph, char *key)
{
	int c = 0;
	int pos = item_hash(key, graph->size);
	
	while(item_compare(item_get_key(graph->node[pos].item), key) != 0 && c <= graph->size)
	{	
		pos = (pos + 1) % graph->size;
		c++;
	}
	
	if(c >= graph->size)
	{
		printf("City not found\n");
		return;
	}
	
	printf("%d adjacent nodes\n", graph->node[pos].degree);
	edge e = graph->node[pos].edges;
	while(e != NULL)
	{
		printf("%-20s %d\n", item_get_key(graph->node[e->node].item), e->weight);
		e = e->next;
	}
}

void graph_create_adjacency_matrix(Graph graph)
{
	int i,j;
	edge e;
	
	//malloc
	graph->adj_matrix = malloc(graph->size * sizeof(int *));
	for(i=0; i<graph->size; i++)
		graph->adj_matrix[i] = malloc(graph->size * sizeof(int));
	
	//reset
	for(i=0; i<graph->size; i++)
		for(j=0; j<graph->size; j++)
			graph->adj_matrix[i][j] = 0;

	//creation
	for(i=0; i<graph->size; i++)
	{
		e = graph->node[i].edges;
		while(e != NULL)
		{
			graph->adj_matrix[i][e->node] = e->weight;
			e = e->next;
		}
	}
	
	//print
	printf("       ");
	for(i=0; i<graph->size; i++)
		printf("%4d ", i);
	printf("\n      ");
	for(i=0; i<graph->size; i++)
		printf("_____");
	printf("\n");
	for(i=0; i<graph->size; i++)
	{
		printf("%4d | ", i);
		for(j=0; j<graph->size; j++)
			printf("%4d ", graph->adj_matrix[i][j]);
		printf("\n");
	}
}

void graph_intra_inter_flow(Graph graph, int *intra, int *inter)
{
	(*intra) = 0;
	(*inter) = 0;
	int i;
	edge e;
	for(i=0; i<graph->size; i++)	//for every node
	{
		e = graph->node[i].edges;
		while(e != NULL)	//for every edge
		{
			if(strcmp(item_get_region(graph->node[i].item),
				  item_get_region(graph->node[e->node].item)) == 0)
				(*intra) += e->weight;	//if node region is equal to adj. node region
			else
				(*inter) += e->weight;

			e = e->next;
		}
	}
	(*inter) /= 2;
	(*intra) /= 2;
}

void graph_destroy(Graph graph)
{
	int i;
	edge e,n;
	
	//adj. matrix free
	if(graph->adj_matrix != NULL)
	{
		for(i=0; i<graph->size; i++)
			free(graph->adj_matrix[i]);
		free(graph->adj_matrix);
	}
	
	//edges free
	for(i=0; i<graph->size; i++)
	{
		e = graph->node[i].edges;
		while(e != NULL)
		{
			n = e->next;
			free(e);
			e = n;
		}
	}
	//nodes free
	for(i=0; i<graph->size; i++)
		item_destroy(graph->node[i].item);
	free(graph->node);
}
