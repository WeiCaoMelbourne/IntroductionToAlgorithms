
#include "graph.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

static struct edge_node* create_edge_node(int vertex);

Graph Graph_create(int v)
{
    Graph g = (struct graph*)malloc(sizeof(struct graph));
    g->v = v;
    g->adj_lists = (struct adj_node**)malloc(sizeof(struct adj_node*) * v);

    int i = 0;
    for (; i < v; i++)
    {
        g->adj_lists[i] = (struct adj_node*)malloc(sizeof(struct adj_node));
        g->adj_lists[i]->vertex = i;
        g->adj_lists[i]->first_edge = NULL;
    }

    return g;
}

void Graph_print(Graph g)
{
    int i = 0;
    for (; i < g->v; i++)
    {
        printf("V%d: ", g->adj_lists[i]->vertex);
        struct edge_node* node = g->adj_lists[i]->first_edge;
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
        struct edge_node* node = s->adj_lists[i]->first_edge;
        if (!node)
            continue;

        struct edge_node* new_node = create_edge_node(s->adj_lists[i]->first_edge->vertex);
        g->adj_lists[i]->first_edge = new_node;

        node = node->next;
        struct edge_node* prev_node = new_node;
        while (node)
        {
            new_node = create_edge_node(node->vertex);
            prev_node->next = new_node;

            prev_node = new_node;
            node = node->next;
        }
    }

    return g;
}

static struct edge_node* create_edge_node(int vertex)
{
    struct edge_node* node = (struct edge_node*)malloc(sizeof(struct edge_node));
    node->vertex = vertex;
    node->next = NULL;
    return node;
}

void Graph_add_edge(Graph g, int src, int dest)
{
    struct edge_node* node = create_edge_node(dest);
    node->next = g->adj_lists[src]->first_edge;
    g->adj_lists[src]->first_edge = node;

    struct edge_node* node2 = create_edge_node(src);
    node2->next = g->adj_lists[dest]->first_edge;
    g->adj_lists[dest]->first_edge = node2;
}

void Graph_destroy(Graph g)
{
    int i = 0;
    for (; i < g->v; i++)
    {
        struct adj_node* node = g->adj_lists[i];
        struct edge_node* edge_node = node->first_edge;
        free(node);
        
        while (edge_node)
        {
            struct edge_node* next_edge = edge_node->next;
            free(edge_node);
            edge_node = next_edge;
        }
    }

    free(g);
}

void Graph_BFS(Graph g)
{
    int visited[g->v];
    int i = 0;
    for (; i < g->v; i++)
        visited[i] = 0;

    Queue q = (Queue)malloc(sizeof(struct queue));
    i = 0;
    for (; i < g->v; i ++)
    {
        if (!visited[i])
        {
            visited[i] = 1;
            printf("visiting %d\n", i);
            Queue_enqueue(q, i);

            while (!Queue_empty(q))
            {
                int vertex = Queue_dequeue(q);
                struct edge_node* node = g->adj_lists[vertex]->first_edge;

                while (node)
                {
                    if (!visited[node->vertex])
                    {
                        visited[node->vertex] = 1;
                        printf("%d ", node->vertex);
                        Queue_enqueue(q, node->vertex);
                    }
                    node = node->next;
                }
            }
            printf("\n");
        }
    }
    free(q);
}

static void DFS(Graph g, int i, int* visited)
{
    visited[i] = 1;
    printf("%d ", i);

    struct edge_node* node = g->adj_lists[i]->first_edge;
    while (node)
    {
        if (!visited[node->vertex])
            DFS(g, node->vertex, visited);
        node = node->next;
    }
}

void Graph_DFS(Graph g)
{
    int visited[g->v];
    int i = 0;
    for(; i < g->v; i++)
        visited[i] = 0;

    i = 0;
    for (; i < g->v; i ++)
    {
        if (!visited[i])
        {
            printf("Visting %d\n", i);
            DFS(g, i, visited);
        }
    }
}