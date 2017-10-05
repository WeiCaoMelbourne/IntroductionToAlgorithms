
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
    g->e = 0;
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

    g->e ++;
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

/* If 2 nodes connected. Breadth-first-search.*/
static int graph_connected(Graph g, int from, int to)
{
    int visited[g->v];
    int i = 0;
    for (; i < g->v; i++)
        visited[i] = 0;

    Queue q = (Queue)malloc(sizeof(struct queue));
    Queue_enqueue(q, from);

    while (!Queue_empty(q))
    {
        int vertex = Queue_dequeue(q);
        struct edge_node* node = g->adj_lists[vertex]->first_edge;

        while (node)
        {
            if (!visited[node->vertex])
            {
                visited[node->vertex] = 1;
                if (node->vertex == to)
                    return 1;
                Queue_enqueue(q, node->vertex);
            }
            node = node->next;
        }
    }

    free(q);
    return 0;
}

/* Miminum spanning tree. Kruskal algorithm */
int Graph_kruskal(Graph g)
{
    Graph g1 = Graph_create(g->v);

    struct edge_info
    {
        int from;
        int to;
        int weight;
        int flag;
    };

    struct edge_info edges[g->e];
    int i = 0;
    for (; i < g->e; i ++)
        edges[i].from = -1;

    /* put all edges into array edges */
    i = 0;
    int edge_count = 0;
    for (; i < g->v; i++)
    {
        if (edge_count >= g->e)
            break;

        struct edge_node* e = g->adj_lists[i]->first_edge;
        while (e)
        {
            int j = 0;
            for (; j < g->e; j ++)
            {
                if ((edges[j].from == i && edges[j].to == e->vertex)
                    || (edges[j].to == i && edges[j].from == e->vertex))
                    break;
            }

            if (j >= g->e)
            {
                edges[edge_count].from = i;
                edges[edge_count].to = e->vertex;
                edges[edge_count].weight = e->weight;
                edges[edge_count].flag = 0;
                edge_count ++;
            }

            e = e->next;
        }
    }

    int a[g->v];
    struct edge_info mst[g->v];
    int mst_count = 0;
    i = 0;
    for (; i < g->v; i++)
        a[i] = -1;

    while (1)
    {
        i = 0;
        for (; i < g->v; i++)
        {
            if (a[i] < 0) 
                break;
        }

        if (i >= g->v)      /* No more vertice */
            break;

        int minimal_weight = 65535;
        int edge_num = -1;
        i = 0;
        for (; i < g->e; i++)
        {
            if (edges[i].flag == 1) 
                continue;

            if (edges[i].weight < minimal_weight)
            {
                if (!graph_connected(g1, edges[i].from, edges[i].to))
                {
                    minimal_weight = edges[i].weight;
                    edge_num = i;
                }
            }
        }

        printf("Add %d in minimum spanning tree. linked to %d, wieght: %d\n",
            edges[edge_num].to, edges[edge_num].from, edges[edge_num].weight);
        edges[edge_num].flag = 1;
        a[edges[edge_num].from] = 1;
        a[edges[edge_num].to] = 1;
        Graph_add_weightededge(
            g1, edges[edge_num].from, edges[edge_num].to, edges[edge_num].weight);

        mst[mst_count].from = edges[edge_num].from;
        mst[mst_count].to = edges[edge_num].to;
        mst[mst_count].weight = edges[edge_num].weight;
        mst_count ++;
    }

    /* print minial spanning tree */
    i = 0;
    int total_weight = 0;
    for (; i < g->v - 1; i++)
    {
        printf("vertex:%d->%d, weight:%d\n", mst[i].from, mst[i].to, mst[i].weight);
        total_weight += mst[i].weight;
    }

    Graph_destroy(g1);

    return total_weight;
}

/* Shortest path. Dijkstra*/
void Graph_dijkstra(Graph g, int vertex)
{
    /* s: vertices that are handled. 
    distance: distance from this vertice to point vertex
    */
    int s[g->v], distance[g->v];
    int i = 0;
    for (; i < g->v; i++)
    {
        s[i] = -1;
        distance[i] = 65535;
    }

    s[vertex] = 0;
    distance[vertex] = 0;
    int v = vertex;
    while (1)
    {
        i = 0;
        for (; i < g->v; i++)
            if (s[i] < 0)
                break;

        if (i >= g->v)  /* all vertices are in set s */
            break;

        struct edge_node* e = g->adj_lists[v]->first_edge;
        int minimal_vetice = -1;
        while (e)
        {
            if (s[e->vertex] >= 0)  /* node already in s */
            {
                e = e->next;
                continue;
            }

            if (e->weight + distance[v] < distance[e->vertex])
                distance[e->vertex] = e->weight + distance[v];

            e = e->next;
        }

        /* put the mininal vertex in dist into s */
        i = 0;
        int minimal_weight = 65535;
        for (; i < g->v; i++)
        {
            if (s[i] >= 1)
                continue;

            if (distance[i] < minimal_weight)
            {
                minimal_weight = distance[i];
                minimal_vetice = i;
            }
        }
            
        v = minimal_vetice;
        s[v] = 1;
    }

    /* print all distance */
    i = 0;
    for (; i < g->v; i++)
    {
        printf("vertex:%d, distance from %d: %d\n", i, vertex, distance[i]);
    }
}

/*
Bellmen Ford. Shortest path.
1. every vertice: distance[g->v] = 65535;
2. Relax on every edge (g->v times).
*/
int Graph_bellman_ford(Graph g, int vertex)
{
    struct edge_info
    {
        int from;
        int to;
        int weight;
    };

    struct edge_info edges[g->e];
    int i = 0;
    for (; i < g->e; i ++)
        edges[i].from = -1;

    /* put all edges into array edges */
    i = 0;
    int edge_count = 0;
    for (; i < g->v; i++)
    {
        if (edge_count >= g->e)
            break;

        struct edge_node* e = g->adj_lists[i]->first_edge;
        while (e)
        {
            int j = 0;
            for (; j < g->e; j ++)
            {
                if ((edges[j].from == i && edges[j].to == e->vertex)
                    || (edges[j].to == i && edges[j].from == e->vertex))
                    break;
            }

            if (j >= g->e)
            {
                edges[edge_count].from = i;
                edges[edge_count].to = e->vertex;
                edges[edge_count].weight = e->weight;
                // edges[edge_count].flag = 0;
                edge_count ++;
            }

            e = e->next;
        }
    }

    /*step 1#: all vertice distances are 65535 */
    int distance[g->v];
    i = 0;
    for (; i < g->v; i++)
        distance[i] = 65535;
    distance[vertex] = 0;

    /* step 2#: relax for every edge */
    i  = 0;
    for (; i < g->v - 1; i++)
    {
        int j = 0;
        for (; j < g->e; j++)
        {
            if (distance[edges[j].from] + edges[j].weight < distance[edges[j].to])
                distance[edges[j].to] = distance[edges[j].from] + edges[j].weight;
        }
    }

    /* print all distance */
    i = 0;
    for (; i < g->v; i++)
    {
        printf("vertex:%d, distance from %d: %d\n", i, vertex, distance[i]);
    }

    /* check if there is negative-weight cycle */
    i = 0;
    for (; i < g->e; i++)
        if (distance[edges[i].from] + edges[i].weight < distance[edges[i].to])
            return -1;

    return 0;
}
