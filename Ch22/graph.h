#ifndef CW_GRAPH_H
#define CW_GRAPH_H

/*
    1 - 2   
    | / |  
    3 - 4   
    
 the first row is adj_node, all the rests are edge node.
    1 -> 2 -> 3
    2 -> 1 -> 3 -> 4
    3 -> 1 -> 2 -> 4
    4 -> 3 -> 2

*/

/* The reason to distinguish edge node from adj node is because
edge node has weight. If it is an unweighted graph, they can be the 
same */
struct edge_node
{
    int vertex;
    int weight;
    struct edge_node* next;
};

struct adj_node
{
    int in;         /* in of this vertice; for topological sort*/
    int vertex;
    struct edge_node* first_edge;
};

struct graph
{
    int v;
    struct adj_node** adj_lists;
};

typedef struct graph* Graph;

struct graph* Graph_create(int v);
void Graph_add_edge(Graph g, int src, int dest);
void Graph_print(Graph g);
Graph Graph_copy(Graph s);
void Graph_destroy(Graph g);
void Graph_BFS(Graph g);
int Graph_topological_sort(Graph g);
void Graph_add_weightededge(Graph g, int src, int dest, int weight);

#endif