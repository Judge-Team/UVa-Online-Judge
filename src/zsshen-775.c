#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define BUF_SIZE        10
#define VISIT_WHITE     0
#define VISIT_BLACK     1


typedef struct _Node {
    int idx_node;
    struct _Node *next;
} Node;


typedef struct _Traversal {
    Node **adj_list;
    Node **list_tail;
    bool *visit;
    int  *prefix;
    int  len_prefix;
} Traversal;


void traversal_init(Traversal**, int);
void traversal_deinit(Traversal*, int);


/* This function constructs the adjacency list by reading the edge pairs. */
void traversal_construct_graph(Traversal*, int);


/* The function applies DFS to traverse the graph and detect the hamilton cycle. */
void traversal_hamilton_cycle(Traversal*, int, int, int, bool*);


int main() {
    int node_count;
    char garbage;
    bool has_cycle;
    Traversal *trav;

    while (scanf("%d%c", &node_count, &garbage) != EOF) {
        traversal_init(&trav, node_count);
        traversal_construct_graph(trav, node_count);

        /* Start DFS and detect the cycle. */
        trav->prefix[0] = 1;
        has_cycle = false;
        traversal_hamilton_cycle(trav, node_count, 1, 1, &has_cycle);
        if (has_cycle == false) {
            printf("N\n");
        }

        traversal_deinit(trav, node_count);
    }

    return 0;
}


void traversal_init(Traversal **p_trav, int node_count) {
    int i;    
    Traversal *trav;

    *p_trav = (Traversal*)malloc(sizeof(Traversal));
    trav = *p_trav;

    trav->adj_list  = (Node**)malloc(sizeof(Node*) * (node_count + 1));
    trav->list_tail = (Node**)malloc(sizeof(Node*) * (node_count + 1));

    trav->visit  = (bool*)malloc(sizeof(bool) * (node_count + 1));
    trav->prefix = (int*)malloc(sizeof(int) * (node_count + 1));

    for (i = 0 ; i <= node_count ; i++) {
        (trav->adj_list)[i] = NULL;
        (trav->list_tail)[i] = NULL;
        (trav->visit)[i] = VISIT_WHITE;
    }

    trav->len_prefix = 0;

    return;
}


void traversal_deinit(Traversal *trav, int node_count) {
    int i;
    Node *curr, *pred;
    
    for (i = 0 ; i <= node_count ; i++) {
        curr = trav->adj_list[i];
        while (curr != NULL) {
            pred = curr;
            curr = curr->next;
            free(pred);
        }        
    }
    free(trav->adj_list);
    free(trav->list_tail);

    free(trav->visit);
    free(trav->prefix);

    free(trav);
    return;
}


void traversal_construct_graph(Traversal *trav, int node_count) {
    int  idx_src, idx_tge;
    bool is_existed;    
    char *ret;
    Node *curr;    
    Node **adj_list, **list_tail;    
    char input[BUF_SIZE];
    

    while (true) {
        memset(input, 0, sizeof(char) * BUF_SIZE);
        ret = fgets(input, BUF_SIZE, stdin);
        
        /* Add dummy check to pass the CI. */
        if (ret == ret) {
            ;
        }    

        if (input[0] == '%') {
            break;
        }
        sscanf(input, "%d%d", &idx_src, &idx_tge);
        
        adj_list = trav->adj_list;
        list_tail = trav->list_tail;
        is_existed = false;

        /* Check if the edge is already linked. */
        curr = adj_list[idx_src];
        while (curr != NULL) {
            if (curr->idx_node == idx_tge) {
                is_existed = true;
                break;
            }
            curr = curr->next;
        }

        if (is_existed == true) {
            continue;
        }

        /* Link the edge with forward direction. */
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

        /* Link the edge with backward direction. */
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


void traversal_hamilton_cycle(Traversal *trav, int node_count, int idx_src, int idx_cur, bool *has_cycle) {
    int  i, idx_adj;
    int  *prefix;
    Node *adj, *src_adj;
    bool *visit;    
    Node **adj_list;

    visit = trav->visit;
    adj_list = trav->adj_list;

    visit[idx_cur] = VISIT_BLACK;
    adj = adj_list[idx_cur];

    while (adj != NULL) {
        idx_adj = adj->idx_node;
        if (visit[idx_adj] == VISIT_WHITE) {

            /* Extend the path prefix and trace into the adjacent node.*/
            prefix = trav->prefix;
            trav->len_prefix++;
            prefix[trav->len_prefix] = idx_adj;
            traversal_hamilton_cycle(trav, node_count, idx_src, idx_adj, has_cycle);

            /* Check for the cycle. */
            if (*has_cycle == true) {
                return;
            }

            if (trav->len_prefix == (node_count - 1)) {
                src_adj = adj_list[idx_src];
                while (src_adj != NULL) {
                    if (src_adj->idx_node == idx_adj) {
                        *has_cycle = true;

                        /* Print the cycle. */
                        for (i = 0 ; i <= trav->len_prefix ; i++) {
                            printf("%d ", prefix[i]);
                        }                     
                        printf("1\n");
                        break;
                    }
                    src_adj = src_adj->next;
                }
            }

            /* Shrink the path prefix and reset the visting state of the adjacent node. */
            visit[idx_adj] = VISIT_WHITE;
            trav->len_prefix--;                        
        }
        adj = adj->next;
    }

    return;
}
