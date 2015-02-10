#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
#define MAX_ELEMENT         1000000
#define DIRECTION_LEFT      0
#define DIRECTION_RIGHT     1
#define DIRECTION_NONE      2


typedef struct _LISTNODE {
    int ofst_occur;
    struct _LISTNODE *next;
} LISTNODE;


typedef struct _TREENODE {
    int element;
    struct _TREENODE *left, *right;
    LISTNODE *head, *tail;
} TREENODE;



void insert_list(TREENODE *curr, int ofst_occur)
{
    LISTNODE *new = (LISTNODE*)malloc(sizeof(LISTNODE));
    new->next = NULL;
    new->ofst_occur = ofst_occur;

    if (curr->head == NULL)
        curr->head = curr->tail = new;
    else {
        curr->tail->next = new;
        curr->tail = new;
    }

    return;
}


void new_tree_node(TREENODE **p_new, int element, int ofst_occur)
{
    *p_new = (TREENODE*)malloc(sizeof(TREENODE));
    TREENODE *new = *p_new;
    new->left = new->right = NULL;
    new->head = new->tail = NULL;
    new->element = element;
    insert_list(new, ofst_occur);

    return;
}


void insert_tree(TREENODE *curr, int element, int ofst_occur)
{
    bool direct;
    TREENODE *pred;

    while (curr != NULL) {
        if (curr->element == element) {
            insert_list(curr, ofst_occur);
            return;
        } else {
            if (element < curr->element) {
                direct = DIRECTION_LEFT;
                pred = curr;
                curr = curr->left;
            } else {
                direct = DIRECTION_RIGHT;
                pred = curr;
                curr = curr->right;
            }
        }
    }

    new_tree_node(&curr, element, ofst_occur);
    if (direct == DIRECTION_RIGHT)
        pred->right = curr;
    else
        pred->left = curr;

    return;
}


void construct_record(int num_element, TREENODE **p_root)
{
    int element, dummy;
    dummy = scanf("%d", &element);
    new_tree_node(p_root, element, 1);
    TREENODE *root = *p_root; 

    int idx;
    for (idx = 1 ; idx < num_element ; idx++) {
        dummy = scanf("%d", &element);
        insert_tree(root, element, idx + 1);
    }

    return;
}


void traverse_tree(TREENODE *curr, int element, int time_occur)
{
    while (curr != NULL) {
        if (curr->element == element) {
            int idx = 0;
            LISTNODE *iter = curr->head;
            while (iter) {
                idx++;
                if (idx == time_occur) {
                    printf("%d\n", iter->ofst_occur);
                    return;
                }
                iter = iter->next;
            }
            printf("0\n");
            return;
        } else {
            if (element < curr->element)
                curr = curr->left;
            else
                curr = curr->right;
        }
    }

    printf("0\n");
    return;
}


void query_record(int num_query, TREENODE *root)
{
    int idx;
    for (idx = 0 ; idx < num_query ; idx++) {
        int element, time_occur, dummy;
        dummy = scanf("%d%d", &time_occur, &element);
        traverse_tree(root, element, time_occur);
    }

    return;
}


void remove_list(LISTNODE *curr)
{
    LISTNODE *pred;
    while (curr != NULL) {
        pred = curr;
        curr = curr->next;
        free(pred);
    }

    return;
}


void remove_tree(TREENODE *curr)
{
    if (curr) {
        remove_tree(curr->left);
        remove_tree(curr->right);
        remove_list(curr->head);
        free(curr); 
    }

    return;
}


int main()
{
    int num_element, num_query;

    while (scanf("%d%d", &num_element, &num_query) != EOF) {
        TREENODE *root;
        construct_record(num_element, &root);
        query_record(num_query, root);
        remove_tree(root);
    }

    return 0;
}
*/

#define MAX_COUNT_ELEMENT       (1000000)
#define FACTOR_RESIZE           (2)
#define INIT_CAPACITY           (2)


typedef struct _VECTOR {
    int size;
    int capacity;
    int *buffer;
} VECTOR;


void vector_push_back(VECTOR *vec, int ofst_occur)
{
    if (vec->size == vec->capacity) {
        int new_capacity = vec->capacity * FACTOR_RESIZE;
        vec->buffer = (int*)realloc(vec->buffer, sizeof(int) * new_capacity);
        vec->capacity = new_capacity;
    }

    vec->buffer[vec->size] = ofst_occur;
    vec->size++;

    return;
}


void vector_new(VECTOR **p_vec)
{
    *p_vec = (VECTOR*)malloc(sizeof(VECTOR));
    (*p_vec)->buffer = (int*)malloc(sizeof(int) * INIT_CAPACITY);
    (*p_vec)->size = 0;
    (*p_vec)->capacity = INIT_CAPACITY;

    return;
}


void vector_delete(VECTOR *vec)
{
    if (vec) {
        free(vec->buffer);
        free(vec);
    }

    return;
}


int main()
{
    VECTOR **arr_vec = (VECTOR**)malloc(sizeof(VECTOR*) * (MAX_COUNT_ELEMENT + 1));

    int num_element, num_query;
    while (scanf("%d%d", &num_element, &num_query) != EOF) {
        int idx;
        for (idx = 1 ; idx <= MAX_COUNT_ELEMENT ; idx++)
            arr_vec[idx] = NULL;

        for (idx = 1 ; idx <= num_element ; idx++) {
            int element, dummy;
            dummy = scanf("%d", &element);
            if (!arr_vec[element])
                vector_new(&(arr_vec[element]));
            vector_push_back(arr_vec[element], idx);
        }

        for (idx = 1 ; idx <= num_query ; idx++) {
            int element, time_occur, dummy;
            dummy = scanf("%d%d", &time_occur, &element);
            if (arr_vec[element]) {
                if (time_occur <= arr_vec[element]->size)
                    printf("%d\n", arr_vec[element]->buffer[time_occur - 1]);
                else
                    printf("0\n");
            } else
                printf("0\n");
        }

        for (idx = 1 ; idx <= MAX_COUNT_ELEMENT ; idx++)
            vector_delete(arr_vec[idx]);
    }

    free(arr_vec);

    return 0;
}


