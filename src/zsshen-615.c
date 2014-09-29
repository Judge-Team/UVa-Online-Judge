#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_NODE_COUNT 100000


typedef struct _Adjacency {
    int idx_node;
    struct _Adjacency *next;
} Adjacency;


typedef struct _Node {
    int degree_in;
    int degree_out;
    bool visit;
    Adjacency *adj_list;
    Adjacency *adj_help;
} Node;


void construct_graph(Node**, int, int);


bool examine_graph(Node**);


void examine_connectivity(Node**, int);


int main() {
    int i, rc, idx_src, idx_tge, idx_case;   
    bool check_tree;
    Adjacency *curr, *pred;
    Node *node;
    Node **graph;

    graph = (Node**)malloc(sizeof(Node*) * (MAX_NODE_COUNT + 1));
    for (i = 1 ; i <= MAX_NODE_COUNT ; i++) {
        graph[i] = NULL;
    }

    idx_case = 1;
    while (true) {
        rc = scanf("%d%d", &idx_src, &idx_tge);

        /* Terminate the algorithm. */        
        if ((idx_src == -1) && (idx_tge == -1)) {
            break;
        }

        /* Finish the input case. */
        else if ((idx_src == 0) && (idx_tge == 0)) {
     
            check_tree = examine_graph(graph);
            if (check_tree == true) {
                printf("Case %d is a tree.\n", idx_case);
            } else {
                printf("Case %d is not a tree.\n", idx_case);
            }

            for (i = 1 ; i <= MAX_NODE_COUNT ; i++) {
                if (graph[i] != NULL) {
                    node = graph[i];
                    curr = node->adj_list;
                    while (curr != NULL) {
                        pred = curr;
                        curr = curr->next;
                        free(pred);
                    }        
                    free(node);
                }
                graph[i] = NULL;
            }
            
            idx_case++;
        }

        /* Continue the tree construction for one input case. */
        else {
            construct_graph(graph, idx_src, idx_tge);
        }   
    }

    free(graph);
    return 0;
}


void construct_graph(Node **graph, int idx_src, int idx_tge) {
    Adjacency *new_adj;
    Node *node_src, *node_tge;

    if (graph[idx_src] == NULL) {
        graph[idx_src] = (Node*)malloc(sizeof(Node));
        graph[idx_src]->degree_in = 0;
        graph[idx_src]->degree_out = 0;
        graph[idx_src]->visit = false;
        graph[idx_src]->adj_list = NULL;
        graph[idx_src]->adj_help = NULL;
    }
    if (graph[idx_tge] == NULL) {
        graph[idx_tge] = (Node*)malloc(sizeof(Node));
        graph[idx_tge]->degree_in = 0;
        graph[idx_tge]->degree_out = 0;
        graph[idx_tge]->visit = false;
        graph[idx_tge]->adj_list = NULL;
        graph[idx_tge]->adj_help = NULL;
    }
    node_src = graph[idx_src];
    node_tge = graph[idx_tge];

    /* Update the node degree information. */
    node_src->degree_out++;
    node_tge->degree_in++;

    /* Link the connection edge. */
    new_adj = (Adjacency*)malloc(sizeof(Adjacency));
    new_adj->idx_node = idx_tge;
    new_adj->next = NULL;
    if (node_src->adj_list == NULL) {
        node_src->adj_list = new_adj;
        node_src->adj_help = new_adj;
    } else {
        node_src->adj_help->next = new_adj;
        node_src->adj_help = new_adj;
    }

    return;
}


bool examine_graph(Node **graph) {
    int i, idx_root;
    bool not_trivial;
    Node *node;

    /* Check for the degree information. */
    not_trivial = false;
    idx_root = -1;
    for (i = 1 ; i <= MAX_NODE_COUNT ; i++) {
        if (graph[i] != NULL) {
            node = graph[i];
            if (node->degree_in == 0) {
                idx_root = i;
            }

            /* If there is a node with in-degree larger than 1, the graph is not a legal tree. */
            if (node->degree_in > 1) {
                return false;
            }
            not_trivial = true;
        }
    }

    /* Check for the graph connectivity. */
    if (not_trivial == true) {

        /* If there is no root node, the graph is not a legal tree. */
        if (idx_root == -1) {
            return false;
        }

        examine_connectivity(graph, idx_root);
        for (i = 1 ; i <= MAX_NODE_COUNT ; i++) {
            if (graph[i] != NULL) {
                if (graph[i]->visit == false) {
                    return false;
                }
            }
        }
    }

    /* Note that the trivial graph without nodes should also be considered as tree. */
    return true;
}


void examine_connectivity(Node **graph, int idx_src) {
    int idx_tge;
    Adjacency *neighbor;
    
    graph[idx_src]->visit = true;
    neighbor = graph[idx_src]->adj_list;
    while (neighbor != NULL) {
        idx_tge = neighbor->idx_node;
        if (graph[idx_tge]->visit == false) {
            examine_connectivity(graph, idx_tge);
        }
        neighbor = neighbor->next;
    }

    return;
}

