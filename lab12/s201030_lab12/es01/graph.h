#ifndef GRAFO_H_DEFINED
#define GRAFO_H_DEFINED

typedef struct graph *Graph;

Graph	graph_init(int size);
void	graph_insert_node(Graph graph, Item item);
void	graph_connect_nodes(Graph graph, char *key1, char *key2, int weight);
void	graph_print_all_degree(Graph graph);
void 	graph_print_all_nodes(Graph graph);
void 	graph_print_adj_nodes(Graph graph, char *key);
void 	graph_create_adjacency_matrix(Graph graph);
void	graph_intra_inter_flow(Graph graph, int *intra, int *inter);
void	graph_destroy(Graph graph);
#endif
