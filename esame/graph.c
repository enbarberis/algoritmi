#include <stdlib.h>
//[MODIFICA] Includo limits.h invece di creare una costante MAX_INT
#include <limits.h>
#include "graph.h"

typedef struct adj_node *link;
struct adj_node{
	int v;
	link next;
};

typedef struct{
	int group;
	link next;
} node;

struct graph{
	int V;
	int E;
	node *adj;
};

edge new_edge(int a, int b)
{
	edge e;
	e.a = a;
	e.b = b;
	return e;
}

link new(int v, link next)
{
	link n = malloc(sizeof *n);
	n->v = v;
	n->next = next;
	return n;
}

Graph graph_init(int n)
{
	int i;

	Graph g = malloc(sizeof *g);
	g->V = n;
	g->E = 0;
	g->adj = malloc(n * sizeof(node));
	for(i=0; i<n; i++)
		g->adj[i].next = NULL;	//[MODIFICA] Dimenticato il ".next" 
	return g;			//[MODIFICA] Dimenticato di fare il return del grafo
}

void graph_insert_edge(Graph g, edge e)
{
	g->adj[e.a].next = new(e.b, g->adj[e.a].next);
	g->adj[e.b].next = new(e.a, g->adj[e.b].next);
	g->E++;
}

void graph_set_group(Graph g, int node, int group)
{
	g->adj[node].group = group;
}

int graph_check(Graph g)
{
	int i;
	link p;

	for(i = 0; i < g->V; i++)	//per ogni nodo
	{
		for(p = g->adj[i].next; p != NULL; p = p->next)	//per ogni suo nodo adiacente
		{
			if(g->adj[i].group == g->adj[p->v].group)
				return 0;
		}
	}

	return 1;
}

void colora(Graph g, int pos, int *min, int *sol)
{
	if(pos >= g->V)				//[MODIFICA] condizione di terminazione sbagliata in quanto il check va fatto
	{					//           dopo essersi accertati di aver preso tutti gli elementi
		if(graph_check(g))
		{
			int *preso = malloc(g->V * sizeof(int));	//[MODIFICA] Dimenticata allocazione dinamica del vettore
			int i, c;
			for(i = 0; i < g->V; i++)
				preso[i] = 0;
			c = 0;
			for(i = 0; i < g->V; i++)
			{
				if(!preso[g->adj[i].group])
				{
					c++;		//contatore di gruppi
					preso[g->adj[i].group] = 1;
				}
			}

			if(*min > c)			//se ottimale salvo soluzione
			{
				*min = c;
				for(i = 0; i < g->V; i++)
					sol[i] = g->adj[i].group;
			}
		
			free(preso);					//[MODIFICA]
	
		}
	}
	else
	{
		int i;
		for(i = 0; i < g->V; i++)
		{
			g->adj[pos].group = i;
			colora(g, pos + 1, min, sol);
		}
	}
}

int graph_partition(Graph g, int *solution)
{
	int min = INT_MAX;					//[MODIFICA] Uso costante di limits.h
	int *sol = malloc(g->V * sizeof(int));
	int i;

	colora(g, 0, &min, sol);

	for(i = 0; i < g->V; i++)
	{
		g->adj[i].group = sol[i];
		solution[i] = sol[i];
	}

	free(sol);
	return min;
}

void graph_destroy(Graph g)
{
	int i;
	link t, p;

	for(i = 0; i < g->V; i++)
	{
		t = g->adj[i].next;
		while(t != NULL)
		{
			p = t->next;
			free(t);
			t = p;
		}
	}

	free(g->adj);
	free(g);
}
