#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
 
// a structure to represent a weighted edge in graph
struct Edge
{
    int src, dest, weight;
};
 
// a structure to represent a connected, directed and weighted graph
struct Graph
{
    // V-> Number of vertices, E-> Number of edges
    int V, E;
 
    // graph is represented as an array of edges.
    struct Edge* edge;
};
 
// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph) );
    graph->V = V;
    graph->E = E;
 
    graph->edge = (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );
 
    return graph;
}
 
// A utility function used to print the solution
void printArr(int dist[], int n,int vec[])
{
	int i;
    for (i = 1; i <= n; ++i)
    {
    	if(dist[i]==INT_MAX)
    		printf("U\n");

    	else{
    		if(vec[i]==1)
    			printf("I\n");
    		else{

        	printf("%d\n", dist[i]);
    		}
    	}
    }
}
 
// The main function that finds shortest distances from src to all other
// vertices using Bellman-Ford algorithm.  The function also detects negative
// weight cycle
void BellmanFord(struct Graph* graph, int src)
{
    int V = graph->V;
    int E = graph->E;
    int i,j;
    int dist[V+1];
    int vec[V+1];
 
    // Step 1: Initialize distances from src to all other vertices as INFINITE
    for (i = 1; i <= V; i++)
        dist[i] = INT_MAX;

    dist[src] = 0;
 
    // Step 2: Relax all edges |V| - 1 times. A simple shortest path from src
    // to any other vertex can have at-most |V| - 1 edges
    for (i = 1; i <= V+1; i++)
    {
        for (j = 1; j <= E; j++)
        {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight; 
        }
    }
 
    // Step 3: check for negative-weight cycles.  The above step guarantees
    // shortest distances if graph doesn't contain negative weight cycle.
    // If we get a shorter path, then there is a cycle.
    for (i = 1; i <= E; i++)
    {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        printf("i: %d s: %d -> %d  d: %d -> %d w: %d\n",i,u,dist[u],v,dist[v],weight);
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]){
         	vec[v]=1;
        }
    }
 
    printArr(dist, V,vec);
 
    return;
}
 
// Driver program to test above functions
int main()
{

    /* Let us create the graph given in above example */
    int V ;  // Number of vertices in graph
    int E ;  // Number of edges in graph
    int i;
    int src;
    scanf("%d%d",&V,&E);
 	scanf("%d",&src);

    struct Graph* graph = createGraph(V, E);

 	for(i=1;i<=E;i++){
 		scanf("%d%d%d",&graph->edge[i].src,&graph->edge[i].dest,&graph->edge[i].weight);
 	}
 
 
    BellmanFord(graph, src);
 
    return 0;
}