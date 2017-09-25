
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

Graph Graph_create(int v)
{
    Graph g = (struct graph*)malloc(sizeof(struct graph));
    g->v = v;
    g->adj_lists = (struct adj_list_node**)malloc(sizeof(struct adj_list_node*) * v);

    int i = 0;
    for (; i < v; i++)
    {
        g->adj_lists[i] = (struct adj_list_node*)malloc(sizeof(struct adj_list_node));
        g->adj_lists[i]->vertex = i;
        g->adj_lists[i]->next = NULL;
    }

    return g;
}

void Graph_print(Graph g)
{
    int i = 0;
    for (; i < g->v; i++)
    {
        printf("V%d: ", g->adj_lists[i]->vertex);
        struct adj_list_node* node = g->adj_lists[i]->next;
        while (node)
        {
            printf("%d ", node->vertex);
            node = node->next;
        }
        
        printf("\n");
    }
}

Graph Graph_copy(Graph s)
{
    Graph g = Graph_create(s->v);

    int i = 0;
    for (; i < s->v; i++)
    {
        struct adj_list_node* prev_node = g->adj_lists[i];
        struct adj_list_node* node = s->adj_lists[i]->next;
        while (node)
        {
            struct adj_list_node* new_node = 
                (struct adj_list_node*)malloc(sizeof(struct adj_list_node));
            new_node->vertex = node->vertex;
            new_node->next = NULL;
            prev_node->next = new_node;

            prev_node = new_node;
            node = node->next;
        }
    }

    return g;
}

static struct adj_list_node* graph_new_node(int vertex)
{
    struct adj_list_node* node = (struct adj_list_node*)malloc(sizeof(struct adj_list_node));
    node->vertex = vertex;
    node->next = NULL;
    return node;
}

void Graph_add_edge(Graph g, int src, int dest)
{
    struct adj_list_node* node = graph_new_node(dest);
    node->next = g->adj_lists[src]->next;
    g->adj_lists[src]->next = node;

    struct adj_list_node* node2 = graph_new_node(src);
    node2->next = g->adj_lists[dest]->next;
    g->adj_lists[dest]->next = node2;
}

void Graph_destroy(Graph g)
{
    int i = 0;
    for (; i < g->v; i++)
    {
        struct adj_list_node* node = g->adj_lists[i];
        struct adj_list_node* next_node = node->next;
        
        while (node)
        {
            free(node);
            node = next_node;
            if (node)
                next_node = node->next;
        }
    }

    free(g);
}