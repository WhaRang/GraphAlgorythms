
#include "list_graph.h"


list_graph::list_graph() {
    this->head = nullptr;
    this->node_num = 0;
    this->edge_num = 0;
    this->directed = false;
}


list_graph::list_graph(int node_num, bool directed) : node_num(node_num), directed(directed) {
    this->edge_num = 0;
    this->head = new node *[node_num];
    for (int i = 0; i < this->node_num; i++) {
        head[i] = nullptr;
    }
}


bool list_graph::connect(int v, int u, int cost) {
    if (v >= node_num || u >= node_num || v < 0 || u < 0) {
        return false;
    }

    node *new_node = new node;
    new_node->value = u;
    new_node->cost = cost;
    new_node->next = nullptr;

    node *curr_node = head[v];
    node *prev_node = curr_node;

    if (head[v] == nullptr) {
        head[v] = new_node;
    } else {
        while (curr_node != nullptr) {
            if (curr_node->value > new_node->value) {
                if (prev_node == curr_node) {
                    head[v] = new_node;
                    new_node->next = curr_node;
                } else {
                    prev_node->next = new_node;
                    new_node->next = curr_node;
                }
                break;
            } else if (curr_node->value == new_node->value) {
                this->edge_num++;
                return true;
            }
            prev_node = curr_node;
            curr_node = curr_node->next;
        }

        if (curr_node == nullptr) {
            prev_node->next = new_node;
        }
    }

    if (!this->directed) {
        return connect(u, v, cost);
    }

    return true;
}


bool list_graph::disconnect(int v, int u) {
    if (v >= node_num || u >= node_num || v < 0 || u < 0) {
        return false;
    }
    node *curr_node = head[v];
    node *prev_node = curr_node;

    if (head[v] == nullptr) {
        return true;
    } else {
        while (curr_node != nullptr) {
            if (curr_node->value > u) {
                this->edge_num--;
                return true;
            } else if (curr_node->value == u) {
                if (curr_node->next != nullptr) {
                    if (prev_node != curr_node) {
                        prev_node->next = curr_node->next;
                    } else {
                        head[v] = curr_node->next;
                    }
                } else {
                    if (prev_node->next != nullptr) {
                        prev_node->next = nullptr;
                    } else {
                        head[v] = nullptr;
                    }
                }
                curr_node = nullptr;
                delete curr_node;
                break;
            }

            prev_node = curr_node;
            curr_node = curr_node->next;
        }
    }

    if (!this->directed) {
        return disconnect(u, v);
    }

    return true;
}


void list_graph::print() {
    if (head == nullptr) {
        std::cout << "null" << std::endl;
    }
    for (int i = 0; i < node_num; i++) {
        std::cout << i;
        node *curr_node = head[i];
        std::cout << ": ";
        while (curr_node != nullptr) {
            std::cout << curr_node->value << "[" << curr_node->cost << "]" << " -> ";
            curr_node = curr_node->next;
        }
        std::cout << "null" << std::endl;
    }
}


bool list_graph::isDirected() const {
    return this->directed;
}


void list_graph::setDirected(bool _directed) {
    this->directed = _directed;
}


void list_graph::add() {
    node **new_head;
    int new_node_num = this->node_num + 1;
    new_head = new node *[new_node_num];
    for (int i = 0; i < this->node_num; i++) {
        new_head[i] = head[i];
    }

    new_head[this->node_num] = nullptr;
    delete[] this->head;

    this->head = new_head;
    this->node_num++;
}


void list_graph::prim_alg() {
    bool done = false;

    bool *visited = new bool[this->node_num];
    for (int i = 0; i < this->node_num; i++) {
        visited[i] = false;
    }
    int curr_vert = 0;

    edge *edges = new edge[this->node_num - 1];
    int edge_count = -1;

    while (!done) {
        visited[curr_vert] = true;
        edge_count++;

        node *curr_node = nullptr;
        node *new_node = new node;
        new_node->next = nullptr;
        bool detected = false;
        int min_edge = 0;
        for (int i = 0; i < this->node_num; i++) {
            if (visited[i]) {
                if (head[i] == nullptr) {
                    return;
                }
                curr_node = head[i];
                while (curr_node != nullptr) {
                    if ((curr_node->cost < min_edge || !detected) && !visited[curr_node->value]) {
                        curr_vert = curr_node->value;
                        min_edge = curr_node->cost;
                        edges[edge_count].cost = min_edge;
                        edges[edge_count].start = i;
                        edges[edge_count].end = curr_vert;
                        detected = true;
                    }
                    curr_node = curr_node->next;
                }
            }
        }

        done = true;
        for (int i = 0; i < this->node_num; i++) {
            if (!visited[i]) {
                done = false;
                break;
            }
        }
    }

    int sum = 0;
    std::cout << "Prim's algorithm. The Minimum spanning tree for the given graph is:" << std::endl;
    for (int i = 0; i < edge_count; i++) {
        std::cout << "Edge " << i << ": " << "(" << edges[i].start << ", "
                  << edges[i].end << "), cost: " << edges[i].cost << std::endl;
        sum += edges[i].cost;
    }
    std::cout << "Cost of Minimum spanning tree: " << sum << std::endl;
}


void list_graph::kruskal_alg() {
    if (head == nullptr) {
        return;
    }

    int edge_count = 0;

    list_graph adj_tree(this->node_num, this->directed);

    edge *edges = new edge[this->edge_num];
    edge *tree = new edge[this->node_num - 1];

    edge new_edge{};
    node *curr_node;

    for (int i = 0; i < this->node_num; i++) {
        curr_node = head[i];
        while (curr_node != nullptr) {
            if (i <= curr_node->value) {
                new_edge.cost = curr_node->cost;
                new_edge.start = i;
                new_edge.end = curr_node->value;
                edges[edge_count] = new_edge;
                edge_count++;
            }
            curr_node = curr_node->next;
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

    edge_count = 0;
    for (int i = 0; i < this->edge_num; i++) {
        bool cycle;

        cycle = adj_tree.is_connected(edges[i].start, edges[i].end,
                                      new bool[adj_tree.getNodeNum()]);

        if (!cycle) {
            adj_tree.connect(edges[i].start, edges[i].end, edges[i].cost);
            tree[edge_count] = edges[i];
            edge_count++;
        }
    }

    int sum = 0;
    std::cout << "Kruskal's algorithm. The Minimum spanning tree for the given graph is:" << std::endl;
    for (int i = 0; i < edge_count; i++) {
        std::cout << "Edge " << i << ": " << "(" << tree[i].start << ", "
                  << tree[i].end << "), cost: " << tree[i].cost << std::endl;
        sum += tree[i].cost;
    }
    std::cout << "Cost of Minimum spanning tree: " << sum << std::endl;
}


int list_graph::getEdgeNum() const {
    return edge_num;
}


bool list_graph::is_connected(int v, int u, bool *visited) {
    node *curr_node = this->head[v];
    while (curr_node != nullptr) {
        if (curr_node->value == u) {
            return true;
        } else {
            if (!visited[curr_node->value]) {
                visited[curr_node->value] = true;
                bool result = this->is_connected(curr_node->value, u, visited);
                if (result) {
                    return result;
                }
            }
        }
        curr_node = curr_node->next;
    }

    return false;
}


int list_graph::getNodeNum() const {
    return node_num;
}


node **list_graph::getHead() const {
    return head;
}


list_graph &list_graph::dijkstra_alg(int u) {

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

    node *curr_node = head[u];
    while (curr_node != nullptr) {
        distances[curr_node->value] = curr_node->cost;
        paths->connect(curr_node->value, curr_node->value, curr_node->cost);
        curr_node = curr_node->next;
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

        node *check_node;
        check_node = this->head[node_order];
        node *curr_path;

        visited[node_order] = true;

        while(check_node != nullptr) {
            int weight = check_node->cost;
            if (!visited[check_node->value]) {
                int curr_dist = distances[node_order] + weight;
                if (curr_dist < distances[check_node->value]) {
                    distances[check_node->value] = curr_dist;
                    paths->connect(node_order, check_node->value, check_node->cost);
                    curr_path = paths->getHead()[node_order];
                    paths->set_path(curr_path, check_node->value);
                    paths->disconnect(node_order, check_node->value);
                }
            }
            check_node = check_node->next;
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


int list_graph::edge_weight(node *first_node, node *second_node) {
    node *curr_node = this->head[first_node->value];
    while (curr_node != nullptr) {
        if (curr_node->value == second_node->value) {
            return curr_node->cost;
        }
        curr_node = curr_node->next;
    }

    return -1;
}


void list_graph::set_path(node *path, int i) {
    this->head[i] = new node;
    node *curr_node = path;
    while(curr_node != nullptr) {
        this->connect(i, curr_node->value, curr_node->cost);
        curr_node = curr_node->next;
    }
}

list_graph &list_graph::bellman_ford_alg(int u) {

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
                node* curr_node = this->head[j];
                while(curr_node != nullptr) {
                    int dist = curr_node->cost + distances[j];
                    if (dist < distances[curr_node->value]) {
                        distances[curr_node->value] = dist;
                        paths->connect(j, curr_node->value, curr_node->cost);
                        curr_path = paths->getHead()[j];
                        paths->set_path(curr_path, curr_node->value);
                        paths->disconnect(j, curr_node->value);
                        changed = true;
                    }
                    curr_node = curr_node->next;
                }
            }
        }
        if (!changed) {
            break;
        }
    }

    return *paths;
}
