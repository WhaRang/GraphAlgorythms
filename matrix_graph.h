//
// Created by aleks on 4/16/2020.
//

#ifndef SDIZO_PROJECT2_MATRIX_GRAPH_H
#define SDIZO_PROJECT2_MATRIX_GRAPH_H

#include <iostream>
#include "list_graph.h"

class matrix_graph {

public:

    matrix_graph();

    matrix_graph(int vert, bool is_directed);

    void print();

    bool connect(int start_vert, int finish_vert, int edge);

    bool disconnect(int start_vert, int finish_vert);

    edge* prim_alg();

    edge* kruskal_alg();

    bool is_connected(int u, int v, bool *visited);

    int getNodeNum() const;

    list_graph &dijkstra_alg(int u);

    list_graph &bellman_ford_alg(int u);

    void generate(int n, int p, bool _directed);

    bool load_from_file(const std::string &file_name);

    void clear(int n, bool _directed);

    int **getAdjMat() const;

    int getEdgeNum() const;

    bool isDirected() const;

    void setDirected(bool directed);

private:

    bool directed;
    int **adj_mat{};
    int edge_num;
    int node_num;

};


#endif //SDIZO_PROJECT2_MATRIX_GRAPH_H
