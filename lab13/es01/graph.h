#ifndef GRAPH_H_DEFINED
#define GRAPH_H_DEFINED

typedef struct edge{
	int a;
	int b;
} edge;
edge create_edge(int a, int b);

typedef struct graph *Graph;

Graph 	graph_init(int n);
void	graph_insert(Graph g, edge e);
int	graph_get_shortest_path(Graph g, int start, int end, int **path);
int	graph_get_longest_path(Graph g, int start, int end, int **path);
int	graph_number_of_simple_path(Graph g, int start, int end);
int*	graph_get_scc(Graph g);
void	graph_destroy(Graph g);

#endif
