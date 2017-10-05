
/*
cc graph_test.c graph.c queue.c stack.c
*/

#include "graph.h"
#include <stdio.h>
#include <string.h>

int main()
{
    /*
    0  4
    | /
    1 -- 2 -- 3

    0->1
    1->0->4->2
    2->1->3
    3->2
    4->1
    */
    int vertice_num = 5;
    Graph g = Graph_create(vertice_num);

    Graph_add_edge(g, 0, 1);
    Graph_add_edge(g, 1, 4);
    Graph_add_edge(g, 1, 2);
    Graph_add_edge(g, 2, 3);

    /*Result should be:
    V0: 1
    V1: 2 4 0
    V2: 3 1
    V3: 2
    V4: 1
    */
    Graph_print(g);

    printf("\nCopy graph\n");
    Graph n = Graph_copy(g);
    Graph_print(n);

    printf("\nBreadth first search:\n");
    Graph_BFS(g);

    printf("\nDepth first search:\n");
    Graph_DFS(g);

    printf("\nTopological sort:\n");
    int ret = Graph_topological_sort(g);
    if (ret != 1)
    {
        printf("topological sort failed\n");
    }

    Graph_destroy(g);
    Graph_destroy(n);

    /* 
    0--(1)--1--(7)--2
    |     / | \     |
    |    /  |  \    |      
   (2) (3) (17)(6)(10)
    |  /    |    \  |
    | /     |     \ |
    3--(14)-4-(23)--5
      \     |     /
      (5)  (21)  (4)
        \   |   /
         \  |  /
            6
    */
    vertice_num = 7;
    Graph connected_g = Graph_create(vertice_num);

    Graph_add_weightededge(connected_g, 0, 1, 1);
    Graph_add_weightededge(connected_g, 0, 3, 2);
    Graph_add_weightededge(connected_g, 1, 2, 7);
    Graph_add_weightededge(connected_g, 1, 3, 3);
    Graph_add_weightededge(connected_g, 1, 4, 17);
    Graph_add_weightededge(connected_g, 1, 5, 6);
    Graph_add_weightededge(connected_g, 2, 5, 10);
    Graph_add_weightededge(connected_g, 3, 4, 14);
    Graph_add_weightededge(connected_g, 3, 6, 5);
    Graph_add_weightededge(connected_g, 4, 5, 23);
    Graph_add_weightededge(connected_g, 4, 6, 21);
    Graph_add_weightededge(connected_g, 5, 6, 4);

    printf("\nPrint connected_g:\n");
    Graph_print(connected_g);

    printf("\nGraph_prim:\n");
    int minimum_weight = Graph_prim(connected_g);
    const int MST_RESULT = 33;
    if (minimum_weight != MST_RESULT)
    {
        printf("Graph_prim failed. Expected:%d, actual:%d\n", MST_RESULT, minimum_weight);
    }
    else
    {
        printf("Graph_prim succeeds.\n");
    }

    printf("\nGraph_kruskal:\n");
    minimum_weight = Graph_kruskal(connected_g);
    if (minimum_weight != MST_RESULT)
    {
        printf("Graph_kruskal failed. Expected:%d, actual:%d\n", MST_RESULT, minimum_weight);
    }
    else
    {
        printf("Graph_kruskal succeeds.\n");
    }

    printf("\nGraph_dijkstra:\n");
    Graph_dijkstra(connected_g, 0);

    printf("\nGraph_bellman_ford:\n");
    Graph_bellman_ford(connected_g, 0);

    Graph_destroy(connected_g);
    return 0;
}