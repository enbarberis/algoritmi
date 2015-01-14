#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "queue.h"

//ADJACENT LIST STRUCT
typedef struct node *link;
struct node{
	int v;		//adjacent node
	link next;	//link to the next adjacent node
};

//GRAPH STRUCT
struct graph{
	int n;		//number of nodes
	int e;		//number of edges
	link *adj;	//array of adjacent nodes
	link *tra;	//trasposed graph
	int *distance;	//distance[i] = distance of i from the start node of the visit
	int *parent;	//parent[i] = parent during the visit of i
	int *visited;	//if visited[i] == 1 then i is visited
	int *scc;	//scc[i] = "group" name of strongly connected component of i
};

edge create_edge(int a, int b)
{
	edge e;
	e.a = a;
	e.b = b;
	return e;
}

link new_link(int v, link next)
{
	link new = malloc(sizeof(*new));
	new->v = v;
	new->next = next;
	return new;
}

Graph graph_init(int n)
{
	int i;
	Graph g = malloc(sizeof(*g));
	g->n = n;
	g->e = 0;
	g->adj = malloc(n*sizeof(link));
	g->tra = malloc(n*sizeof(link));
	g->distance = malloc(n*sizeof(int));
	g->parent   = malloc(n*sizeof(int));
	g->visited  = malloc(n*sizeof(int));
	g->scc      = malloc(n*sizeof(int));
	for(i=0; i<n; i++)
		g->adj[i] = NULL;
	return g;
}

void graph_insert(Graph g, edge e)
{
	g->adj[e.a] = new_link(e.b, g->adj[e.a]);
	g->tra[e.b] = new_link(e.a, g->tra[e.b]); //direct creation of transposed graph
	g->e++;
}

int graph_get_shortest_path(Graph g, int start, int end, int **path)
{
	//reset
	int i;
	for(i=0; i<g->n; i++)
	{
		g->distance[i] = -1;
		g->parent[i] = -1;
	}
	g->distance[start] = 0;
	
	//bfs visit
	Queue q = queue_init();
	int v;
	link adj_node;

	queue_put(q, start);
	while(!queue_empty(q))
	{
		v = queue_get(q);
		adj_node = g->adj[v];
		while(adj_node != NULL)		//for every adjacent node
		{
			if(g->distance[adj_node->v] == -1)	//if not visited yet
			{
				g->parent[adj_node->v] = v;
				g->distance[adj_node->v] = g->distance[v] + 1;
				queue_put(q, adj_node->v);
			}
			adj_node = adj_node->next;
		}
	}

	queue_destroy(q);

	//does exist a path?
	if(g->distance[end] == -1)
		return -1;

	//path saving
	int* p = malloc((g->distance[end] + 1) * sizeof(int));	//path array
	int c = g->distance[end] - 1;
	v = end;
	p[g->distance[end]] = end;
	while(v != start)
	{
		v = g->parent[v];
		p[c--] = v;
	}
	*path = p;
	return g->distance[end];
}

void path_max(Graph g, int pos, int end, int *max, int *path)
{
	//if the actual solution is better
	if(pos == end && g->distance[end] > *max)
	{
		*max = g->distance[end];	//max distance save
		int c = g->distance[end] - 1;
		int v = end;			
		path[g->distance[end]] = end;	//path save
		while(v != -1 && c>=0)
		{
			v = g->parent[v];
			path[c--] = v;
		}	
	}
	else
	{
		g->visited[pos] = 1;		//mark as visited
		link adj_node = g->adj[pos];
		while(adj_node != NULL)		//for every adj. node
		{
			if(g->visited[adj_node->v] == 0)	//if it isn't visited
			{
				g->parent[adj_node->v] = pos;
				g->distance[adj_node->v] = g->distance[pos] + 1;
				path_max(g, adj_node->v, end, max, path);	
			}
			adj_node = adj_node->next;
		}
		g->visited[pos] = 0;		//mark as not visisted
	}
}

int graph_get_longest_path(Graph g, int start, int end, int **path)
{
	//reset
	int i;
	for(i=0; i<g->n; i++)
	{
		g->distance[i] = 0;
		g->visited[i] = 0;
		g->parent[i] = -1;
	}
	//max path calculation
	i=-1;
	int *p = malloc(g->n * sizeof(int));
	path_max(g, start, end, &i, p);
	*path = p;
	return i;
}

int path_ric(Graph g, int pos, int end)
{
	if(pos == end)
		return 1;	//if I found a path then return 1
	
	g->visited[pos] = 1;	//mark as visited
	int sum = 0;
	link adj_node = g->adj[pos];
	while(adj_node != NULL)
	{
		if(g->visited[adj_node->v] == 0)
			sum += path_ric(g, adj_node->v, end);
		adj_node = adj_node->next;
	}
	g->visited[pos] = 0;	//mark as not visited
	return sum;
}

int graph_number_of_simple_path(Graph g, int start, int end)
{
	int i;
	for(i=0; i<g->n; i++)
		g->visited[i] = 0;	//not visited
	return path_ric(g, start, end);
}

void dfs(Graph g, int pos, int *time)
{
	(*time)++;
	g->visited[pos] = 1;
	link adj_node = g->tra[pos];
	while(adj_node != NULL)
	{
		if(g->visited[adj_node->v] == 0) 	//if not visited
			dfs(g, adj_node->v, time);
		adj_node = adj_node->next;
	}
	g->distance[pos] = (*time)++;
}

void dfs_assign(Graph g, int pos, int val)
{
	g->visited[pos] = 1;
	g->scc[pos] = val;
	link adj_node = g->adj[pos];
	while(adj_node != NULL)
	{	
		if(g->visited[adj_node->v] == 0)
			dfs_assign(g, adj_node->v, val);

		adj_node = adj_node->next;
	}
}

int* graph_get_scc(Graph g)
{
	int i, time=0, max, c, pos, visited;

	//reset
	for(i=0; i<g->n; i++)
	{
		g->visited[i] = 0;
		g->distance[i] = 0;	//distance = post time of elaboration
	}

	//dfs on transposed graph
	for(i=0; i<g->n; i++)
	{
		if(g->visited[i] == 0)	//if not visited yet
		{
			dfs(g, i, &time);
		}
	}

	//re-reset
	for(i=0; i<g->n; i++)
		g->visited[i] = 0;

	//ssc value assignment
	c = 0;
	visited = 0;

	while(visited < g->n)
	{
		//searching node with max post value and not visited yet
		max = pos =-1;
		for(i=0; i<g->n; i++)
			if(g->distance[i] > max && g->visited[i] == 0)
			{
				pos = i;
				max = g->distance[i];
			}
		dfs_assign(g, pos, c++);
		
		//recalculate all visited nodes
		for(i = visited = 0; i<g->n; i++)
			if(g->visited[i])
				visited++;
	}
	return g->scc;
}

void graph_destroy(Graph g)
{
	free(g->distance);
	free(g->parent);
	free(g->visited);
	free(g->scc);

	link adj_node, tmp;
	int i;
	for(i=0; i<g->n; i++)
	{
		adj_node = g->adj[i];
		while(adj_node != NULL)
		{
			tmp = adj_node->next;
			free(adj_node);
			adj_node = tmp;
		}

		adj_node = g->tra[i];
		while(adj_node != NULL)
		{
			tmp = adj_node->next;
			free(adj_node);
			adj_node = tmp;
		}
	}
}
