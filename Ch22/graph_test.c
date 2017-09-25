
/*
cc graph_test.c graph.c
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

    Graph_destroy(g);
    Graph_destroy(n);

    return 0;
}