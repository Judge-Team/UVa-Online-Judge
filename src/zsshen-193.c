#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define COLOR_WHITE         0
#define COLOR_BLACK         1
#define MAX_NODE_COUNT      100


typedef struct _Node {
    int idx_node;
    struct _Node *next;
} Node;


typedef struct _Graph {
    int  num_node;
    int  max_num_black;
    Node **adj_list;
    Node **list_tail;
    bool *color;
    bool *opt_color;
} Graph;


/* This function constructs the graph adjacency list. */
void graph_init(Graph**);


/* This function releases the resource hold by graph structure. */
void graph_deinit(Graph*);


/* This function applies brute-force backtracking to enumerate all approaches of
   graph coloring and records the one with maximum number of black nodes. */
void graph_draw_black(Graph*, int, int);


int main() {
    int   i, j, rc, round, num_black;
    Graph *graph;

    rc = scanf("%d", &round);
    while (round > 0) {
        graph_init(&graph);

        graph_draw_black(graph, 1, 0);

        /* Show the optimal coloring approach. */
        printf("%d\n", graph->max_num_black);
        num_black = false;
        for (i = 1 ; i <= graph->num_node ; i++) {
            if ((graph->opt_color)[i] == COLOR_BLACK) {
                printf("%d", i);                
                num_black++;
                if (num_black < graph->max_num_black) {
                    printf(" ");
                }
            }
        }
        printf("\n");

        graph_deinit(graph);
        round--;
    }    

    return 0;
}


void graph_init(Graph **p_graph) {
    int   i, rc, num_node, num_edge, idx_src, idx_tge;
    Graph *graph;
    Node  *curr;
    Node  **adj_list, **list_tail;

    *p_graph = (Graph*)malloc(sizeof(Graph));
    graph = *p_graph;

    rc = scanf("%d%d", &num_node, &num_edge);

    /* Initialize the graph member structures. */
    graph->num_node = num_node;    
    graph->max_num_black = 0;
    graph->adj_list = (Node**)malloc(sizeof(Node*) * (num_node + 1));
    graph->list_tail = (Node**)malloc(sizeof(Node*) * (num_node + 1));
    graph->color = (bool*)malloc(sizeof(bool) * (num_node + 1));
    graph->opt_color = (bool*)malloc(sizeof(bool) * (num_node + 1));

    for (i = 1 ; i <= num_node ; i++) {
        (graph->adj_list)[i] = NULL;
        (graph->list_tail)[i] = NULL;
        (graph->color)[i] = COLOR_WHITE;
    }

    /* Construct the adjacency list. */
    adj_list = graph->adj_list;
    list_tail = graph->list_tail;
    for (i = 0 ; i < num_edge ; i++) {
        rc = scanf("%d%d", &idx_src, &idx_tge);
        
        /* Link the forward direction. */        
        curr = adj_list[idx_src];
        while (curr != NULL) {
            if (curr->idx_node == idx_tge) {
                break;
            }
            curr = curr->next;        
        }        

        if (curr != NULL) {
            continue;
        }

        curr = (Node*)malloc(sizeof(Node));
        curr->idx_node = idx_tge;
        curr->next = NULL;
        if (adj_list[idx_src] == NULL) {
            adj_list[idx_src] = curr;
            list_tail[idx_src] = curr;
        } else {
            (list_tail[idx_src])->next = curr;
            list_tail[idx_src] = curr;
        }

        /* Link the backward direction. */
        curr = (Node*)malloc(sizeof(Node));
        curr->idx_node = idx_src;
        curr->next = NULL;
        if (adj_list[idx_tge] == NULL) {
            adj_list[idx_tge] = curr;
            list_tail[idx_tge] = curr;
        } else {
            (list_tail[idx_tge])->next = curr;
            list_tail[idx_tge] = curr;
        }
    }

    return;
}


void graph_deinit(Graph *graph) {
    int  i;    
    Node *curr, *pred;

    /* Destruct the adjacency list. */
    for (i = 1 ; i <= graph->num_node ; i++) {
        curr = (graph->adj_list)[i];
        while (curr != NULL) {
            pred = curr;
            curr = curr->next;
            free(pred);
        }
    }
    
    free(graph->adj_list);
    free(graph->list_tail);
    free(graph->color);
    free(graph->opt_color);
    free(graph);

    return;
}


void graph_draw_black(Graph *graph, int idx_src, int num_black) {
    int  i, idx_tge, num_node; 
    bool is_colorable;    
    bool *color;
    Node *tge;
    Node **adj_list;

    color = graph->color;
    adj_list = graph->adj_list;
    num_node = graph->num_node;

    if (idx_src > num_node) {
        /* If we can find the better coloring approach, we should update the old record. */
        if (num_black > graph->max_num_black) {
            graph->max_num_black = num_black;
            for (i = 1 ; i <= num_node ; i++) {
                (graph->opt_color)[i] = color[i];
            }
        }    
    } else {
        /* Check if the current node is black colorable. */
        is_colorable = true;    
        tge = adj_list[idx_src];
        while (tge != NULL) {
            idx_tge = tge->idx_node;
            if (color[idx_tge] == COLOR_BLACK) {
                is_colorable = false;
                break;
            }
            tge = tge->next;
        }

        /* If the current node is black-colorable, there are two selections for further traversal. */
        if (is_colorable == true) {
            color[idx_src] = COLOR_BLACK;
            graph_draw_black(graph, idx_src + 1, num_black + 1);
        }
        color[idx_src] = COLOR_WHITE;
        graph_draw_black(graph, idx_src + 1, num_black);
    }

    return;
}


