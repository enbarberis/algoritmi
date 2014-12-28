#ifndef GRAFO_H_DEFINED
#define GRAFO_H_DEFINED

typedef struct graph *Graph;

Graph	graph_init(int size);
void	graph_insert_node(Graph graph, Item item);
void	graph_connect_nodes(Graph graph, char *key1, char *key2, int weight);

#endif
