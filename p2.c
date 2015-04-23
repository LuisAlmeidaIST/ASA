#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
 
struct Edge
{
    int src, dest, weight;
};
 
struct Graph
{
    int node, edg;
 
    struct Edge* edge;
};
 
struct Graph* createGraph(int node, int edg)
{
    struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph) );
    graph->node = node;
    graph->edg = edg;
 
    graph->edge = (struct Edge*) malloc( graph->edg * sizeof( struct Edge ) );
 
    return graph;
}

void printArr(int dist[], int node,int vec[])
{
	int i;
    for (i = 1; i <= node; ++i)
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
 

void BellmanFord(struct Graph* graph, int src)
{
    int node = graph->node;
    int edg = graph->edg;
    int i,j;
    int dist[node+1];
    int vec[node+1];
 

    for (i = 1; i <= node; i++){
        dist[i] = INT_MAX;
        vec[i]=0;
    }

    dist[src] = 0;
 

    for (i = 1; i <= node+1; i++)
    {
        for (j = 1; j <= edg; j++)
        {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight; 
        }
    }
 
    for(j=0;j<3;j++){
    for (i = 1; i <= edg; i++)
    {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]){
        	dist[v] = dist[u] + weight; 
         	vec[v]=1; 
        }
    }
}
 
    printArr(dist, node, vec);
 
    return;
}
 
int main()
{

    int node,edg,i,src;
    scanf("%d%d",&node,&edg);
 	scanf("%d",&src);

    struct Graph* graph = createGraph(node, edg);

 	for(i=1;i<=edg;i++){
 		scanf("%d%d%d",&graph->edge[i].src,&graph->edge[i].dest,&graph->edge[i].weight);
 	}
 
 
    BellmanFord(graph, src);
 
    return 0;
}