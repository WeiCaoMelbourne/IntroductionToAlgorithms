
#include "graph.h"
#include "queue.h"
#include "stack.h"
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
        g->adj_lists[i]->in = 0;
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
            printf("%d(%d) ", node->vertex, node->weight);
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
    g->adj_lists[dest]->in ++;
}

void Graph_add_weightededge(Graph g, int src, int dest, int weight)
{
    struct edge_node* node = create_edge_node(dest);
    node->weight = weight;
    node->next = g->adj_lists[src]->first_edge;
    g->adj_lists[src]->first_edge = node;

    struct edge_node* node2 = create_edge_node(src);
    node2->weight = weight;
    node2->next = g->adj_lists[dest]->first_edge;
    g->adj_lists[dest]->first_edge = node2;
    g->adj_lists[dest]->in ++;
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

/* Basic logic of topological sort: 
1. Print all the vertices whose in is 0
2. Remove this vertices, and minus 1 from in of all the vertices that follows it
3. Redo 1 */
int Graph_topological_sort(Graph g)
{
    Stack s = (Stack)malloc(sizeof(struct stack));
    int count = 0;

    int i = 0;
    for (; i < g->v; i++)
        if (g->adj_lists[i]->in == 0)
            Stack_push(s, i);

    while (!Stack_empty(s))
    {
        int vertex = Stack_pop(s);
        printf("%d -> ", vertex);
        count ++;

        struct edge_node* e = g->adj_lists[vertex]->first_edge;
        while (e)
        {
            int t = e->vertex;
            g->adj_lists[t]->in --;
            if (g->adj_lists[t]->in == 0)
                Stack_push(s, t);

            e = e->next;
        }
    }

    /* count < g->v, means there is a loop */
    if (count < g->v)
        return 0;

    return 1;
}

/* Miminum spanning tree. Prim algorithm */
int Graph_prim(Graph g)
{
    int a[g->v];    /* >=0 means vertice in mst */
    int i = 0;
    for (; i < g->v; i++)
        a[i] = -1;
    
    struct mst_info
    {
        int from;
        int to;
        int weight;
    };

    struct mst_info mst[g->v];

    a[0] = 0;
    int count = 0;
    int total_weight = 0;
    
    while (1)
    {
        int j = 0;
        for (; j < g->v; j++)
        {
            if (a[j] < 0)
                break;
        }

        if (j >= g->v)
            break;  /* All vertices are in a */

        i = 0;
        int minimum_weight = 62535;
        int minimum_vertex = -1;
        int linked_vertex = -1;
        for (; i < g->v; i ++)
        {
            if (a[i] < 0)
                continue;

            struct edge_node* e = g->adj_lists[i]->first_edge;
            while (e)
            {
                if (a[e->vertex] >= 0)  /* already in mst */
                {
                    e = e->next;
                    continue;
                }

                if (e->weight < minimum_weight)
                {
                    minimum_weight = e->weight;
                    minimum_vertex = e->vertex;
                    linked_vertex = g->adj_lists[i]->vertex;
                }
                e = e->next;
            }
        }
        
        a[minimum_vertex] = minimum_vertex;
        mst[count].from = linked_vertex;
        mst[count].to = minimum_vertex;
        mst[count].weight = minimum_weight;
        count ++;
        total_weight += minimum_weight;

        printf("Add %d in minimum spanning tree. linked to %d, wieght: %d\n",
            minimum_vertex, linked_vertex, minimum_weight);
    }

    /* print minimum spanning tree */
    i = 0;
    for (; i < g->v - 1; i++)
    {
        printf("vertex:%d->%d, weight:%d\n", mst[i].from, mst[i].to, mst[i].weight);
    }

    return total_weight;
}