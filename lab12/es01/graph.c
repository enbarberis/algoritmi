#include <stdlib.h>
#include <stdio.h>
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
	t_node *node;	//array of nodes
	int size;	//number of nodes
};

Graph graph_init(int size)
{
	int i;
	
	Graph graph = malloc(sizeof(*graph));
	graph->node = malloc(size * sizeof(t_node));
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

void add_edge(t_node *node, int node, int weight)
{
	
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

}
