typedef struct { int a; int b; } edge; 			//[MODIFICA] Errore nella dichiarazione della struct (edge va dopo)
edge new_edge(int a, int b);

typedef struct graph *Graph;
Graph	graph_init(int n);
void	graph_insert_edge(Graph g, edge e);
void	graph_set_group(Graph g, int node, int group);
int	graph_check(Graph g);				//controlla se il grafo e` accettabile come soluzione
int	graph_partition(Graph g, int *solution);	//genera una soluzione ottimale e ritorna il numero di gruppi
void	graph_destroy(Graph g);			
