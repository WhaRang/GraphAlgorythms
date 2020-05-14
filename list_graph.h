
#ifndef SDIZO_PROJECT2_LIST_GRAPH_H
#define SDIZO_PROJECT2_LIST_GRAPH_H

#include <iostream>

struct edge {
    int start;
    int end;
    int cost;
};

struct node {
    int value;
    int cost;
    node *next;
};

class list_graph {

private:

    node **head;
    bool directed;
    int node_num;
    int edge_num;

public:

    list_graph();

    list_graph(int node_num, bool directed);

    bool connect(int v, int u, int cost);

    bool disconnect(int v, int u);

    void add();

    void print();

    bool isDirected() const;

    void setDirected(bool directed);

    void prim_alg();

    void kruskal_alg();

    int getEdgeNum() const;

    bool is_connected(int v, int u, bool *visited);

    int getNodeNum() const;

    void set_path(node *path, int i);

    list_graph &dijkstra_alg(int u);

    list_graph &bellman_ford_alg(int u);

    node **getHead() const;

    int edge_weight(node *first_node, node*second_node);
};


#endif //SDIZO_PROJECT2_LIST_GRAPH_H
