
#include <chrono>
#include <iomanip>
#include "matrix_graph.h"
#include "menu.h"

enum AlgorithmType {
    MST,
    SPP
};

enum Algorithm {
    PRIM,
    KRUSKAL,
    DIJKSTRA,
    BELLMAN_FORD
};

void dialogue_message(const std::string &message);

void prt_edg(edge *edges);

void test(Algorithm alg, bool is_matrix);

void prt_mat();

void prt_lst();

void mst_foo();

void spp_foo();

void ext_foo();

void rff_foo();

void gen_foo();

void prt_foo();

void prm_alg();

void krs_alg();

void dks_alg();

void bfd_alg();

void tst_foo();

void prm_foo();

void krs_foo();

void dks_foo();

void bfd_foo();

AlgorithmType curr_at;

int spp_start = -1;

matrix_graph matrix;
list_graph list;

menu_element mst_me("-  Minimum spanning tree problem   -", mst_foo);
menu_element spp_me("-  Shortest path problem           -", spp_foo);
menu_element tst_me("-  Run test                        -", tst_foo);
menu_element ext_me("-  Exit                            -", ext_foo);

menu_element rff_me("-  Read from file              -", rff_foo);
menu_element gen_me("-  Generate random graph       -", gen_foo);
menu_element prt_me("-  Print graph                 -", prt_foo);

menu_element prm_me("-  Prim's algorithm            -", prm_alg);
menu_element krs_me("-  Kruskal's algorithm         -", krs_alg);

menu_element dks_me("-  Dijkstra's algorithm        -", dks_alg);
menu_element bfd_me("-  Bellman-Ford algorithm      -", bfd_alg);

menu_element bck_me("-  Back                        -");

menu_element prm_tst("-  Test Prim's algorithm       -", prm_foo);
menu_element krs_tst("-  Test Kruskal's algorithm    -", krs_foo);
menu_element dks_tst("-  Test Dijkstra's algorithm   -", dks_foo);
menu_element bfd_tst("-  Test Bellman-Ford algorithm -", bfd_foo);

menu main_menu({mst_me, spp_me, tst_me, ext_me});
menu mst_menu({rff_me, gen_me, prt_me, prm_me, krs_me, bck_me});
menu spp_menu({rff_me, gen_me, prt_me, dks_me, bfd_me, bck_me});
menu tst_menu({prm_tst, krs_tst, dks_tst, bfd_tst, bck_me});


int main() {
    dialogue_message("Navigate using Arrow keys, Enter and Esc.");
    main_menu.run();
    return 0;
}


void mst_foo() {
    curr_at = MST;
    mst_menu.run();
}


void spp_foo() {
    curr_at = SPP;
    spp_menu.run();
}


void ext_foo() {
    exit(0);
}


void rff_foo() {
    std::cout << "Enter file name: ";
    std::string s;
    std::cin >> s;

    if (curr_at == SPP) {
        matrix.setDirected(true);
        std::fstream file(s);
        if (file) {
            file >> spp_start;
            file >> spp_start;
            file >> spp_start;
        } else {
            dialogue_message("Error occurred while loading graph from file " + s);
            return;
        }
    } else {
        matrix.setDirected(false);
    }

    if (matrix.load_from_file(s)) {
        std::cout << "Successfully loaded graph from file." << std::endl;
        if (curr_at == SPP) {
            std::cout << "Current SPP starting point: " << spp_start << std::endl;
        }
        list.copy(matrix.getAdjMat(), matrix.getNodeNum(), matrix.isDirected());
        std::cout << std::endl;
        prt_foo();
    } else {
        dialogue_message("Error occurred while loading graph from file " + s);
    }
}


void gen_foo() {
    std::cout << "Enter number of nodes of new graph: ";
    int n;
    std::cin >> n;

    std::cout << "Enter graph density: ";
    int p;
    std::cin >> p;

    std::cout << "Directed graph? (y/n): ";
    char c;
    std::cin >> c;
    if (c == 'y') {
        matrix.generate(n, p, true);
        std::cout << "Successfully generated directed graph." << std::endl;
        list.copy(matrix.getAdjMat(), matrix.getNodeNum(), true);
        prt_foo();
    } else if (c == 'n') {
        matrix.generate(n, p, false);
        std::cout << "Successfully generated undirected graph." << std::endl;
        list.copy(matrix.getAdjMat(), matrix.getNodeNum(), false);
        prt_foo();
    } else {
        dialogue_message("Error occurred while generating graph.");
    }
}


void prt_foo() {

    prt_lst();
    std::cout << std::endl;
    prt_mat();

    dialogue_message("");
}


void prm_alg() {
    if (matrix.getNodeNum() == 0) {
        dialogue_message("Graph is empty. Can't run Prim's algorithm.");
        return;
    }

    std::cout << "Running Prim's algorithm on adjacency list..." << std::endl;
    edge *edges_list = list.prim_alg();

    prt_edg(edges_list);

    std::cout << "Running Prim's algorithm on adjacency matrix..." << std::endl;
    edge *edges_mat = matrix.prim_alg();

    prt_edg(edges_mat);

    dialogue_message("");
}


void krs_alg() {
    if (matrix.getNodeNum() == 0) {
        dialogue_message("Graph is empty. Can't run Kruskal's algorithm.");
        return;
    }

    std::cout << "Running Kruskal's algorithm on adjacency list..." << std::endl;
    edge *edges_list = list.kruskal_alg();

    prt_edg(edges_list);

    std::cout << "Running Kruskal's algorithm on adjacency matrix..." << std::endl;
    edge *edges_mat = matrix.kruskal_alg();

    prt_edg(edges_mat);

    dialogue_message("");
}


void dks_alg() {
    if (matrix.getNodeNum() == 0) {
        dialogue_message("Graph is empty. Can't run Dijkstra's algorithm.");
        return;
    }

    if (spp_start == -1) {
        std::cout << "Stating node i not set. Enter new: ";
        std::cin >> spp_start;
    }

    std::cout << "Running Dijkstra's algorithm on adjacency list..." << std::endl;
    list_graph paths_list = list.dijkstra_alg(spp_start);

    std::cout << "Done. Shortest paths from node " << spp_start << ": " << std::endl;
    paths_list.print_as_paths(spp_start);

    std::cout << std::endl;

    std::cout << "Running Dijkstra's algorithm on adjacency matrix..." << std::endl;
    list_graph matrix_graph = list.dijkstra_alg(spp_start);

    std::cout << "Done. Shortest paths from node " << spp_start << ": " << std::endl;
    matrix_graph.print_as_paths(spp_start);

    dialogue_message("");
}


void bfd_alg() {
    if (matrix.getNodeNum() == 0) {
        dialogue_message("Graph is empty. Can't run Bellman-Ford algorithm.");
        return;
    }

    if (spp_start == -1) {
        std::cout << "Stating node is not set. Enter new: ";
        std::cin >> spp_start;
    }

    std::cout << "Running Bellman-Ford algorithm on adjacency list..." << std::endl;
    list_graph paths_list = list.bellman_ford_alg(spp_start);

    std::cout << "Done. Shortest paths from node " << spp_start << ": " << std::endl;
    paths_list.print_as_paths(spp_start);

    std::cout << std::endl;

    std::cout << "Running Bellman-Ford algorithm on adjacency matrix..." << std::endl;
    list_graph matrix_graph = list.bellman_ford_alg(spp_start);

    std::cout << "Done. Shortest paths from node " << spp_start << ": " << std::endl;
    matrix_graph.print_as_paths(spp_start);

    dialogue_message("");
}


void dialogue_message(const std::string &message) {
    std::cout << message << std::endl <<
              "press ENTER to continue...";
    int key = 1;
    while (key != Keys::ENTER) {
        key = _getch();
    }
}


void prt_mat() {
    int size = matrix.getNodeNum();
    std::cout << "Adjacency matrix view (size: " << size << "): " << std::endl;

    if (size != 0) {
        matrix.print();
    } else {
        std::cout << "null" << std::endl;
    }
}


void prt_lst() {
    int size = list.getNodeNum();
    std::cout << "Adjacency list view (size: " << size << "): " << std::endl;

    if (size != 0) {
        list.print();
    } else {
        std::cout << "null" << std::endl;
    }
}


void prt_edg(edge *edges) {
    std::cout << "Done. The Minimum spanning tree for the given graph is " << std::endl;
    int sum = 0;
    for (int i = 0; i < matrix.getNodeNum() - 1; i++) {
        std::cout << "Edge " << i << ": " << "(" << edges[i].start << ", "
                  << edges[i].end << "), cost: " << edges[i].cost << std::endl;
        sum += edges[i].cost;
    }
    std::cout << "Cost of Minimum spanning tree: " << sum << std::endl << std::endl;
}


void tst_foo() {
    tst_menu.run();
}


void prm_foo() {
    test(PRIM, true);
    test(PRIM, false);
    dialogue_message("Done.");
}


void krs_foo() {
    test(KRUSKAL, true);
    test(KRUSKAL, false);
    dialogue_message("Done.");
}


void dks_foo() {
    test(DIJKSTRA, true);
    test(DIJKSTRA, false);
    dialogue_message("Done.");
}


void bfd_foo() {
    test(BELLMAN_FORD, true);
    test(BELLMAN_FORD, false);
    dialogue_message("Done.");
}


void test(Algorithm alg, bool is_matrix) {
    int size;
    int cache = 10;
    int repeats = 40;
    int density = 0;
    int observe_spots = 7;
    double sum = 0;

    switch (alg) {
        case PRIM: {
            std::cout << "Speed test of Prim's algorithm." << std::endl;
            break;
        }

        case KRUSKAL: {
            std::cout << "Speed test of Kruskal's algorithm." << std::endl;
            break;
        }

        case DIJKSTRA: {
            std::cout << "Speed test of Dijkstra's algorithm." << std::endl;
            break;
        }

        case BELLMAN_FORD: {
            std::cout << "Speed test of Bellman-Ford algorithm." << std::endl;
            break;
        }
    }

    if (is_matrix) {
        std::cout << "Adjacency matrix: " << std::endl;
    } else {
        std::cout << "Adjacency list: " << std::endl;
    }

    for (int i = 0; i < 3; i++) {
        size = 40;

        if (i == 0) {
            density = 20;
        }
        if (i == 1) {
            density = 60;
        }
        if (i == 2) {
            density = 99;
        }

        std::cout << "Density: " << density << "%" << std::endl;
        for (int j = 0; j < observe_spots; j++) {
            size = size + cache;
            bool directed = !(alg == PRIM || alg == KRUSKAL);
            matrix.generate(size, density, directed);

            if (!is_matrix) {
                list.copy(matrix.getAdjMat(), matrix.getNodeNum(), matrix.isDirected());
            }

            for (int z = 0; z < repeats; z++) {
                auto start_time = std::chrono::high_resolution_clock::now();
                switch (alg) {
                    case PRIM: {
                        if (is_matrix) {
                            matrix.prim_alg();
                        } else {
                            list.prim_alg();
                        }
                        break;
                    }

                    case KRUSKAL: {
                        if (is_matrix) {
                            matrix.kruskal_alg();
                        } else {
                            list.kruskal_alg();
                        }
                        break;
                    }

                    case DIJKSTRA: {
                        if (is_matrix) {
                            matrix.dijkstra_alg(0);
                        } else {
                            list.dijkstra_alg(0);
                        }
                        break;
                    }

                    case BELLMAN_FORD: {
                        if (is_matrix) {
                            matrix.bellman_ford_alg(0);
                        } else {
                            list.bellman_ford_alg(0);
                        }
                        break;
                    }
                }
                auto end_time = std::chrono::high_resolution_clock::now();
                sum += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
            }
            std::cout << "Size: " << size << " result(nanoseconds): " << std::setprecision(15) << sum << std::endl;
        }
    }
}
