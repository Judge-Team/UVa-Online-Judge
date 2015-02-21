#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define BUF_SIZE            (1024)


typedef struct _NODE {
    int idx_col;
    int element;
    struct _NODE *next;
} NODE;


typedef struct _ADJ_HEAD {
    int cnt_element;
    NODE *nd_bgn;
    NODE *nd_end;
} ADJ_HEAD;


void init_adjacency_list(ADJ_HEAD **p_list_adj, int size)
{
    *p_list_adj = (ADJ_HEAD*)malloc(sizeof(ADJ_HEAD) * (size + 1));
    int idx;
    ADJ_HEAD *list_adj = *p_list_adj;
    for (idx = 1 ; idx <= size ; idx++) {
        list_adj[idx].cnt_element = 0;
        list_adj[idx].nd_bgn = NULL;
        list_adj[idx].nd_end = NULL;
    }

    return;
}


void deinit_adjacency_list(ADJ_HEAD *list_adj, int size)
{
    int idx;
    NODE *nd_curr, *nd_pred;
    for (idx = 1 ; idx <= size ; idx++) {
        nd_curr = list_adj[idx].nd_bgn;
        while (nd_curr) {
            nd_pred = nd_curr;
            nd_curr = nd_curr->next;
            free(nd_pred);
        }   
    }
    free(list_adj);

    return;
}


void update_adjacency_list(ADJ_HEAD *list_adj, int idx_row, int idx_col, int element)
{
    NODE *nd_new = (NODE*)malloc(sizeof(NODE));
    nd_new->idx_col = idx_col;
    nd_new->element = element;
    nd_new->next = NULL;

    if (!(list_adj[idx_row].nd_bgn)) {
        list_adj[idx_row].nd_bgn = nd_new;
        list_adj[idx_row].nd_end = nd_new;
    } else {
        (list_adj[idx_row].nd_end)->next = nd_new;
        list_adj[idx_row].nd_end = nd_new;
    }
    (list_adj[idx_row].cnt_element)++;

    return;
}


void traverse_adjacency_list(ADJ_HEAD *list_adj, int num_row)
{
    char arr_element[BUF_SIZE];

    int idx_row, cnt_element;
    for (idx_row = 1 ; idx_row <= num_row ; idx_row++) {
        int cnt_element = list_adj[idx_row].cnt_element;
        if (cnt_element) {
            printf("%d", cnt_element);
            
            int idx_element = 0;
            NODE *nd_curr = list_adj[idx_row].nd_bgn;
            while (nd_curr) {
                printf(" %d", nd_curr->idx_col);
                arr_element[idx_element++] = nd_curr->element;
                nd_curr = nd_curr->next;
            }
            printf("\n");
            
            idx_element = 0;
            while (idx_element < (cnt_element - 1)) {
                printf("%d ", arr_element[idx_element]);
                idx_element++;
            }
            printf("%d\n", arr_element[idx_element]);
        } else
            printf("0\n\n");
    }

    return;
}


int main()
{
    ADJ_HEAD *list_adj;
    int list_real_col[BUF_SIZE];    

    int num_row, num_col;
    while (scanf("%d%d", &num_row, &num_col) != EOF) {

        /* Initialie the adjacency list. */
        init_adjacency_list(&list_adj, num_col);

        /* Construct the transposed matrix by reversing the row and column index. */
        int idx_row, idx_col;
        for (idx_row = 1 ; idx_row <= num_row ; idx_row++) {
            int num_real_col, dummy;
            dummy = scanf("%d", &num_real_col);
            if (num_real_col > 0) {
                int idx_real_col, element;
                for (idx_real_col = 0 ; idx_real_col < num_real_col ; idx_real_col++)
                    dummy = scanf("%d", &(list_real_col[idx_real_col]));
                for (idx_real_col = 0 ; idx_real_col < num_real_col ; idx_real_col++) {
                    dummy = scanf("%d", &element);
                    idx_col = list_real_col[idx_real_col];
                    update_adjacency_list(list_adj, idx_col, idx_row, element);
                }
            }
        }

        /* Output the transposed matrix. */
        printf("%d %d\n", num_col, num_row);
        traverse_adjacency_list(list_adj, num_col);

        /* Deinitialize the adjacency list. */
        deinit_adjacency_list(list_adj, num_col);
    }

    return 0;
}
