#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define COLOR_NONE          0
#define COLOR_BLACK         -1
#define COLOR_WHITE         1
#define MAX_NODE_COUNT      200
#define START_INDEX         0


#define STATE_UNVISITED     0
#define STATE_VISITING      1
#define STATE_VISITED       2


typedef struct _AdjacencyRecord {
    int idx_neighbor;
    struct _AdjacencyRecord *next;
} AdjacencyRecord;


typedef struct _GraphNode {
    char color;
    char visit;
} GraphNode;


typedef struct _Graph {
    int count_node;
    AdjacencyRecord **adj_head, **adj_tail;
    GraphNode *node;
} Graph;


/* Construct the adjacency list and the color table. */
void graph_init(Graph**, int);

/* Destruct the adjacency list and the color table. */
void graph_deinit(Graph*);

/* Show the adjacency list for debug. */
void graph_show(Graph*);

/* Detect if the graph is bicolorable. */
void graph_traversal(Graph*);


int main() {
    int count_node;
    Graph *graph;

    while(true) {
        scanf("%d", &count_node);
        if (count_node == 0)
            break;

        graph_init(&graph, count_node);
        graph_traversal(graph);
        graph_deinit(graph);
    }

    return 0;
}


void graph_init(Graph **p_graph, int count_node) {
    int i, count_edge, node_src, node_tge;
    Graph *graph;
    AdjacencyRecord *record_src, *record_tge;

    /* Prepare the graph structure. */
    *p_graph = (Graph*)malloc(sizeof(Graph));
    graph = *p_graph;
    graph->count_node = count_node;
    graph->adj_head = (AdjacencyRecord**)malloc(sizeof(AdjacencyRecord*) * count_node);
    graph->adj_tail = (AdjacencyRecord**)malloc(sizeof(AdjacencyRecord*) * count_node);
    graph->node = (GraphNode*)malloc(sizeof(GraphNode) * count_node);
    for (i = 0 ; i < count_node ; i++) {
        graph->adj_head[i] = NULL;
        graph->adj_tail[i] = NULL;
        (graph->node[i]).color = COLOR_NONE;
        (graph->node[i]).visit = STATE_UNVISITED;
    }

    scanf("%d", &count_edge);

    /* Construct the Adjacency list. */
    for (i = 0 ; i < count_edge ; i++) {
        scanf("%d%d", &node_src, &node_tge);

        /* The graph must be undirected. */
        record_tge = (AdjacencyRecord*)malloc(sizeof(AdjacencyRecord));
        record_tge->idx_neighbor = node_tge;
        record_tge->next = NULL;

        record_src = (AdjacencyRecord*)malloc(sizeof(AdjacencyRecord));
        record_src->idx_neighbor = node_src;
        record_src->next = NULL;

        if (graph->adj_head[node_src] == NULL) {
            graph->adj_head[node_src] = record_tge;
            graph->adj_tail[node_src] = record_tge;
        } else {
            graph->adj_tail[node_src]->next = record_tge;
            graph->adj_tail[node_src] = record_tge;
        }

        if (graph->adj_head[node_tge] == NULL) {
            graph->adj_head[node_tge] = record_src;
            graph->adj_tail[node_tge] = record_src;
        } else {
            graph->adj_tail[node_tge]->next = record_src;
            graph->adj_tail[node_tge] = record_src;
        }
    }

    return;
}


void graph_deinit(Graph *graph) {
    int i;
    AdjacencyRecord *curr, *pred;

    for (i = 0 ; i < graph->count_node ; i++) {
        curr = graph->adj_head[i];
        while (curr != NULL) {
            pred = curr;
            curr = curr->next;
            free(pred);
        }
    }

    free(graph->adj_head);
    free(graph->adj_tail);
    free(graph->node);
    free(graph);

    return;
}


void graph_show(Graph *graph) {
    int i;
    AdjacencyRecord *curr;

    /* Show the adjacency list. */
    for (i = 0 ; i < graph->count_node ; i++) {
        printf("%2d -> ", i);
        curr = graph->adj_head[i];
        while (curr != NULL) {
            printf("%2d ", curr->idx_neighbor);
            curr = curr->next;
        }
        printf("\n");
    }
    printf("\n");

    return;
}


void graph_traversal(Graph *graph) {
    bool found_err;
    char color_src, color_tge;
    int  front, rear, node_src, node_tge;
    AdjacencyRecord *curr;
    int queue[MAX_NODE_COUNT];

    found_err = false;

    /* Initialize the queue. */
    front = 0;
    rear = 1;
    (graph->node[START_INDEX]).color = COLOR_WHITE;
    (graph->node[START_INDEX]).visit = STATE_VISITING;
    queue[front] = START_INDEX;

    /* Apply the BFS to detect if the graph is bicolorable. */
    while (front != rear) {
        node_src = queue[front++];
        (graph->node[node_src]).visit = STATE_VISITED;
        color_src = (graph->node[node_src]).color;

        curr = graph->adj_head[node_src];
        while (curr != NULL) {
            node_tge = curr->idx_neighbor;

            if ((graph->node[node_tge]).visit == STATE_UNVISITED) {
                (graph->node[node_tge]).visit = STATE_VISITING;
                queue[rear++] = node_tge;
            }

            /* Check for the color confliction. */
            if ((graph->node[node_tge]).color == COLOR_NONE)
                (graph->node[node_tge]).color = -color_src;
            else {
                color_tge = (graph->node[node_tge]).color;
                if (-color_src != color_tge) {
                    found_err = true;
                    break;
                }
            }
            curr = curr->next;
        }
        if (found_err == true)
            break;
    }

    if (found_err == false)
        printf("BICOLORABLE.\n");
    else
        printf("NOT BICOLORABLE.\n");

    return;
}
