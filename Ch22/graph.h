#ifndef CW_GRAPH_H
#define CW_GRAPH_H


struct adj_list_node
{
    int vertex;
    struct adj_list_node* next;
};

struct graph
{
    int v;
    struct adj_list_node** adj_lists;
};

typedef struct graph* Graph;

struct graph* Graph_create(int v);
void Graph_add_edge(Graph g, int src, int dest);
void Graph_print(Graph g);
Graph Graph_copy(Graph s);
void Graph_destroy(Graph g);

#endif