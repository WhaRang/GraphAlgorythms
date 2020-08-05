
#include "matrix_graph.h"

matrix_graph::matrix_graph() : matrix_graph(0, false) {
}


matrix_graph::matrix_graph(int vert, bool is_directed) : node_num(vert), directed(is_directed) {
    this->edge_num = 0;

    if (vert < 0) {
        this->node_num = 0;
    } else {
        this->node_num = vert;
    }

    this->adj_mat = new int *[vert];
    for (int i = 0; i < vert; i++) {
        this->adj_mat[i] = new int[vert];
        for (int j = 0; j < vert; j++) {
            this->adj_mat[i][j] = 0;
        }
    }
}


bool matrix_graph::connect(int start_vert, int finish_vert, int edge) {
    if (start_vert < 0 || finish_vert < 0 ||
        start_vert > node_num || finish_vert > node_num) {
        return false;
    }

    this->edge_num++;
    this->adj_mat[start_vert][finish_vert] = edge;

    if (!this->directed) {
        this->adj_mat[finish_vert][start_vert] = edge;
    }

    return true;
}


bool matrix_graph::disconnect(int start_vert, int finish_vert) {
    if (start_vert < 0 || finish_vert < 0 ||
        start_vert > node_num || finish_vert > node_num) {
        return false;
    }

    if (adj_mat[start_vert][finish_vert] != 0) {
        this->edge_num--;
    }
    this->adj_mat[start_vert][finish_vert] = 0;

    if (!this->directed) {
        this->adj_mat[finish_vert][start_vert] = 0;
    }

    return true;
}


edge *matrix_graph::prim_alg() {

    bool *visited = new bool[this->node_num];
    for (int i = 0; i < this->node_num; i++) {
        visited[i] = false;
    }

    auto *edges = new edge[this->node_num - 1];
    int edge_count = -1;

    int curr_vert = 0;
    bool all_visited = false;

    while (!all_visited) {

        visited[curr_vert] = true;
        edge_count++;

        bool detected = false;
        int min_edge = 0;

        for (int i = 0; i < this->node_num; i++) {
            if (visited[i]) {
                for (int j = 0; j < this->node_num; j++) {
                    if ((adj_mat[i][j] < min_edge || !detected)
                        && !visited[j] && adj_mat[i][j] != 0) {
                        curr_vert = j;
                        min_edge = adj_mat[i][j];
                        edges[edge_count].cost = min_edge;
                        edges[edge_count].start = i;
                        edges[edge_count].end = j;
                        detected = true;
                    }
                }
            }
        }

        all_visited = true;
        for (int i = 0; i < this->node_num; i++) {
            if (!visited[i]) {
                all_visited = false;
                break;
            }
        }
    }

    return edges;
}


edge* matrix_graph::kruskal_alg() {

    int edge_count = 0;
    matrix_graph adj_tree(this->node_num, this->directed);

    auto *edges = new edge[this->edge_num];
    auto *tree = new edge[this->node_num - 1];

    edge new_edge{};

    for (int i = 0; i < this->node_num; i++) {
        for (int j = 0; j < this->node_num; j++) {
            if (this->adj_mat[i][j] != 0 && i <= j) {
                new_edge.start = i;
                new_edge.end = j;
                new_edge.cost = adj_mat[i][j];
                edges[edge_count] = new_edge;
                edge_count++;
            }
        }
    }

    for (int i = 0; i < edge_count - 1; i++) {
        for (int j = i + 1; j < edge_count; j++) {
            if (edges[i].cost > edges[j].cost) {
                edge r = edges[i];
                edges[i] = edges[j];
                edges[j] = r;
            }
        }
    }

    int r = edge_count;
    edge_count = 0;
    for (int i = 0; i < r; i++) {
        bool cycle;

        cycle = adj_tree.is_connected(edges[i].start, edges[i].end,
                                      new bool[adj_tree.getNodeNum()]);

        if (!cycle) {
            adj_tree.connect(edges[i].start, edges[i].end, edges[i].cost);
            tree[edge_count] = edges[i];
            edge_count++;
        }
    }

    return tree;
}


void matrix_graph::print() {
    for (int i = 0; i < node_num; i++) {
        for (int j = 0; j < node_num; j++) {
            std::cout << this->adj_mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


bool matrix_graph::is_connected(int u, int v, bool *visited) {
    for (int i = 0; i < this->node_num; i++) {
        if ((adj_mat[u][i] != 0)) {
            if (i == v) {
                return true;
            } else {
                if (!visited[i]) {
                    visited[i] = true;
                    if (i <= this->node_num && v <= this->node_num && i >= 0 && v >= 0) {
                        bool result = this->is_connected(i, v, visited);
                        if (result) {
                            return result;
                        }
                    }
                }
            }
        }
    }

    return false;
}


int matrix_graph::getNodeNum() const {
    return node_num;
}


list_graph &matrix_graph::dijkstra_alg(int u) {

    int *distances = new int[this->node_num];
    bool *visited = new bool[this->node_num];
    auto *paths = new list_graph(this->node_num, true);

    for (int i = 0; i < this->node_num; i++) {
        visited[i] = false;
        distances[i] = INT32_MAX;
        paths->connect(i, u, 0);
    }

    visited[u] = true;
    distances[u] = 0;

    for (int i = 0; i < this->node_num; i++) {
        if (this->adj_mat[i][u] != 0) {
            distances[i] = adj_mat[i][u];
            paths->connect(i, i, adj_mat[i][u]);
        }
    }

    bool all_visited = false;
    while (!all_visited) {
        int min_dist_for_node = INT32_MAX;
        int node_order = -1;
        for (int j = 0; j < this->node_num; j++) {
            if (distances[j] <= min_dist_for_node && !visited[j]) {
                node_order = j;
                min_dist_for_node = distances[j];
            }
        }

        node *curr_path;
        visited[node_order] = true;

        for (int i = 0; i < this->node_num; i++) {
            if (this->adj_mat[i][node_order] != 0) {
                int weight = adj_mat[i][node_order];
                if (!visited[i]) {
                    int curr_dist = distances[node_order] + weight;
                    if (curr_dist < distances[i]) {
                        distances[i] = curr_dist;
                        paths->force_connect(node_order, i, weight);
                        curr_path = paths->getHead()[node_order];
                        paths->set_path(curr_path, i);
                        paths->force_disconnect(node_order, i);
                    }
                }
            }
        }

        all_visited = true;
        for (int i = 0; i < this->node_num; i++) {
            if (!visited[i]) {
                all_visited = false;
                break;
            }
        }
    }

    return *paths;
}


list_graph &matrix_graph::bellman_ford_alg(int u) {
    auto *paths = new list_graph(this->node_num, true);
    node *curr_path;

    int *distances = new int[this->node_num];
    for (int i = 0; i < this->node_num; i++) {
        distances[i] = INT32_MAX;
        paths->connect(i, u, 0);
    }
    distances[u] = 0;

    bool changed = false;
    for (int i = 0; i < this->node_num - 1; i++) {
        for (int j = 0; j < this->node_num; j++) {
            if (distances[i] != INT32_MAX) {
                for (int o = 0; o < this->node_num; o++) {
                    int cost = adj_mat[o][j];
                    if (cost != 0) {
                        int dist = cost + distances[j];
                        if (dist < distances[o]) {
                            distances[o] = dist;
                            paths->force_connect(j, o, cost);
                            curr_path = paths->getHead()[j];
                            paths->set_path(curr_path, o);
                            paths->force_disconnect(j, o);
                            changed = true;
                        }
                    }
                }
            }
        }
        if (!changed) {
            break;
        }
    }

    return *paths;
}


void matrix_graph::generate(int n, int p, bool _directed) {

    clear(n, _directed);

    int max_edge = (n * n - n) / 2;
    int curr_edge = max_edge * p / 100;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist_edge(0, 10);

    for (int i = 0; i < this->node_num - 1; i++) {
        connect(i, i + 1, dist_edge(mt));
    }

    int counter = this->node_num - 1;

    if (counter < curr_edge) {
        for (int i = 0; i < this->node_num; i++) {
            for (int j = 0; j < this->node_num; j++) {
                if (this->adj_mat[i][j] == 0) {
                    connect(i, j, dist_edge(mt));
                    counter++;
                    if (counter == curr_edge) {
                        return;
                    }
                }
            }
        }
    }
}


bool matrix_graph::load_from_file(const std::string &file_name) {
    std::fstream file(file_name);

    if (!file) {
        return false;
    }

    int edges;
    file >> edges;

    int nodes;
    file >> nodes;

    std::string str;
    getline(file, str);

    clear(nodes, this->directed);
    this->node_num = nodes;

    this->adj_mat = new int *[nodes];
    for (int i = 0; i < nodes; i++) {
        this->adj_mat[i] = new int[nodes];
        for (int j = 0; j < nodes; j++) {
            this->adj_mat[i][j] = 0;
        }
    }

    int first;
    int second;
    int cost;
    for (int i = 0; i < edges; i++) {
        file >> first;
        file >> second;
        file >> cost;
        connect(first, second, cost);
    }
}


void matrix_graph::clear(int n, bool _directed) {
    for (int i = 0; i < this->node_num; i++) {
        delete[] this->adj_mat[i];
    }
    delete[] this->adj_mat;

    this->node_num = n;
    this->directed = _directed;
    this->adj_mat = new int *[this->node_num];

    for (int i = 0; i < this->node_num; i++) {
        this->adj_mat[i] = new int[this->node_num];
        for (int j = 0; j < this->node_num; j++) {
            this->adj_mat[i][j] = 0;
        }
    }
}

int **matrix_graph::getAdjMat() const {
    return adj_mat;
}

int matrix_graph::getEdgeNum() const {
    return edge_num;
}

bool matrix_graph::isDirected() const {
    return directed;
}

void matrix_graph::setDirected(bool _directed) {
    matrix_graph::directed = _directed;
}
