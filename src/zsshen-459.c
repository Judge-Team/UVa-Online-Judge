#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define MAX_NODE_COUNT      26
#define BASE_NODE_ID        'A'
#define BUF_SIZE            4
#define INDEX_SOURCE_NODE   0
#define INDEX_TARGET_NODE   1


/* The node in the adjacency list. */
typedef struct _Node {
    int node_id;
    struct _Node *next;
} Node;


typedef struct _Component {
    int component_id;
    int rank;
    struct _Component *parent;
} Component;


/* This function generates graph using adjacency list and prepares disjoint set forest. */
void construct_graph(Node**(*), Component**(*), int);


/* This function release all the allocated memory spaces. */
void destruct_graph(Node**, Component**, int);


/* This function helps to debug the adjacency list and the disjoint set forest. */
void show_graph(Node**, Component**, int);


/* This function traverse the graph to find all the maximal connected components. */
void find_maximal_connected_components(Node**, Component**, int);


/* This function calculates the total count of maximal connected components. */
int count_maximal_connected_components(Node**, Component**, int);


/* The utility function to find the representative node of current component. */
Component* disjoint_find(Component*);


/* The utility function to unite two components. */
void disjoint_link(Component*, Component*);


int main() {
    int count_case, rc;
    char max_node_id, node_count, garbage, component_count;    
    Node **adj_list;
    Component **component_list;

    rc = scanf("%d", &count_case);
    rc = scanf("%c", &garbage);
    rc = scanf("%c", &garbage);

    while (count_case > 0) {

        rc = scanf("%c%c", &max_node_id, &garbage);

        /* Construct the adjacency list.*/
        node_count = max_node_id - BASE_NODE_ID + 1;
        construct_graph(&adj_list, &component_list, node_count);

        /* Traverse edge list to construct connected components. */
        find_maximal_connected_components(adj_list, component_list, node_count);

        /* Calculate the count of maximal connected components. */
        component_count = count_maximal_connected_components(adj_list, component_list, node_count);
        printf("%d\n", component_count);
        /* show_graph(adj_list, component_list, node_count); */

        /* Destruct the adjacency list. */
        destruct_graph(adj_list, component_list, node_count);

        count_case--;
        if (count_case > 0) {
            printf("\n");
        }
    }

    return 0;
}


void construct_graph(Node **(*p_adj_list), Component **(*p_component_list), int node_count) {
    int i, len, node_id_src, node_id_tge;    
    Node **adj_list, **adj_tail, *new, *curr;
    Component **component_list;
    char buf[BUF_SIZE];
        
    /* Initialize the adjacency list and the disjoint set forest. */
    *p_adj_list = (Node**)malloc(sizeof(Node*) * node_count);
    adj_tail = (Node**)malloc(sizeof(Node*) * node_count);
    adj_list = *p_adj_list;

    *p_component_list = (Component**)malloc(sizeof(Component*) * node_count);
    component_list = *p_component_list;

    for (i = 0 ; i < node_count ; i++) {
        adj_list[i] = adj_tail[i] = NULL;
        component_list[i] = (Component*)malloc(sizeof(Component));
        component_list[i]->component_id = i;
        component_list[i]->rank = 0;
        component_list[i]->parent = component_list[i];
    }   

    do {
        memset(buf, 0, sizeof(char) * BUF_SIZE);
        /* Check for the end of all input cases. */
        if (fgets(buf, BUF_SIZE, stdin) == NULL) {
            break;
        }                
        
        /* Check for the end of one input case. */    
        len = strlen(buf);
        if (len == 1) {
            break;
        }

        node_id_src = buf[INDEX_SOURCE_NODE] - BASE_NODE_ID;
        node_id_tge = buf[INDEX_TARGET_NODE] - BASE_NODE_ID;
        
        /* Link an edge from source node to target node if necessary. */
        if (adj_list[node_id_src] == NULL) {
            new = (Node*)malloc(sizeof(Node));        
            new->node_id = node_id_tge;
            new->next = NULL;        
            adj_list[node_id_src] = new;
            adj_tail[node_id_src] = new;
        } else {
            curr = adj_list[node_id_src];
            while (curr != NULL) {
                if (curr->node_id == node_id_tge) {
                    break;
                }
                curr = curr->next;            
            }
            if (curr == NULL) {
                new = (Node*)malloc(sizeof(Node));        
                new->node_id = node_id_tge;
                new->next = NULL;        
                adj_tail[node_id_src]->next = new;
                adj_tail[node_id_src] = new;
            }
        }
        
        /* Link an edge from target node to source node if necessary. */
        if (adj_list[node_id_tge] == NULL) {
            new = (Node*)malloc(sizeof(Node));        
            new->node_id = node_id_src;
            new->next = NULL;        
            adj_list[node_id_tge] = new;
            adj_tail[node_id_tge] = new;
        } else {
            curr = adj_list[node_id_tge];
            while (curr != NULL) {
                if (curr->node_id == node_id_src) {
                    break;
                }
                curr = curr->next;            
            }
            if (curr == NULL) {
                new = (Node*)malloc(sizeof(Node));        
                new->node_id = node_id_src;
                new->next = NULL;        
                adj_tail[node_id_tge]->next = new;
                adj_tail[node_id_tge] = new;
            }
        }
    } while (true);

    /* Free the help indexing array. */
    free(adj_tail);

    return;
}


void destruct_graph(Node **adj_list, Component **component_list, int node_count) {
    int i;
    Node *curr, *pred;
    
    for (i = 0 ; i < node_count ; i++) {
        curr = adj_list[i];    
        while (curr != NULL) {
            pred = curr;
            curr = curr->next;
            free(pred);
        }

        free(component_list[i]);
    }

    free(adj_list);
    free(component_list);

    return;
}   


void show_graph(Node **adj_list, Component **component_list, int node_count) {
    int i;
    Node *curr, *pred;

    printf("Adjacency List:\n");    
    for (i = 0 ; i < node_count ; i++) {
        curr = adj_list[i];    
        printf("%2d -> ", i);
        while (curr != NULL) {
            pred = curr;
            curr = curr->next;
            printf("%2d ", pred->node_id);
        }
        printf("\n");
    }

    printf("Disjoint Set Forest:\n");
    for (i = 0 ; i < node_count ; i++) {
        printf("(%2d -> %2d) ", i, component_list[i]->parent->component_id);
    }

    printf("\n");

    return;
}


void find_maximal_connected_components(Node **adj_list, Component **component_list, int node_count) {
    int i, node_id_src, node_id_tge;
    Node *curr;    
    Component *comp_src, *comp_tge, *rep_src, *rep_tge;

    for (i = 0 ; i < node_count ; i++) {
        curr = adj_list[i];
        node_id_src = i;
        comp_src = component_list[node_id_src];

        while (curr != NULL) {
            node_id_tge = curr->node_id;
            comp_tge = component_list[node_id_tge];

            /* Check if two components are already merged. */
            rep_src = disjoint_find(comp_src);
            rep_tge = disjoint_find(comp_tge);

            /* Link them if necessary. */
            if (rep_src != rep_tge) {
                disjoint_link(rep_src, rep_tge);
            }

            curr = curr->next;
        }
    }

    return;
}


int count_maximal_connected_components(Node **adj_list, Component **component_list, int node_count) {
    int i, component_count, rep_id;
    bool *map;
    Component *curr;

    component_count = 0;
    map = (bool*)malloc(sizeof(bool) * node_count);

    for (i = 0 ; i < node_count ; i++) {
        map[i] = false;
    }

    for (i = 0 ; i < node_count ; i++) {
        curr = component_list[i];
        while (curr->parent != curr) {
            curr = curr->parent;
        }
        rep_id = curr->component_id;
        map[rep_id] = true;
    }

    for (i = 0 ; i < node_count ; i++) {
        if (map[i] == true) {
            component_count++;
        }
    }

    free(map);

    return component_count;
}


Component* disjoint_find(Component *curr) {

    if (curr != curr->parent) {
        curr->parent = disjoint_find(curr->parent);
    }

    return curr->parent;
}


void disjoint_link(Component *src, Component *tge) {

    if (src->rank > tge->rank) {
        tge->parent = src;
    } else {
        src->parent = tge;
        if (src->rank == tge->rank) {
            tge->rank++;
        }
    }

    return;
}
