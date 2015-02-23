#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define MAX(a, b)       (((a) > (b))? (a) : (b))


typedef struct _NODE {
    int freq;
    int end_left, end_right;
    struct _NODE *br_left, *br_right;
} NODE;


int get_value_coverage(int *arr_int, int num_int, int idx_left, int end_left,
                       int idx_right, int end_right)
{
    int freq = 2;
    int idx_temp = idx_left - 1;
    while ((idx_temp >= end_left) && (arr_int[idx_temp] == arr_int[idx_left])) {
        freq++;
        idx_temp--;
    }
    idx_temp = idx_right + 1;
    while ((idx_temp <= end_right) && (arr_int[idx_temp] == arr_int[idx_right])) {
        freq++;
        idx_temp++;
    }

    return freq;
}


int construct_tree(int *arr_int, int num_int, NODE **p_nd_new,
                   int end_left, int end_right)
{
    if (end_left == end_right) {
        *p_nd_new = (NODE*)malloc(sizeof(NODE));
        NODE *nd_new = *p_nd_new;
        nd_new->end_left = end_left;
        nd_new->end_right = end_right;
        nd_new->freq = 1;
        nd_new->br_left = nd_new->br_right = NULL;
        return 1;
    }
    
    int idx_mid = (end_left + end_right) / 2;
    NODE *nd_left;
    int freq_left = construct_tree(arr_int, num_int, &nd_left, end_left, idx_mid);
    NODE *nd_right;
    int freq_right = construct_tree(arr_int, num_int, &nd_right, (idx_mid + 1), end_right);

    int freq_max;
    *p_nd_new = (NODE*)malloc(sizeof(NODE));
    NODE *nd_new = *p_nd_new;
    nd_new->end_left = end_left;
    nd_new->end_right = end_right;
    if (arr_int[idx_mid] == arr_int[idx_mid + 1]) {
        int freq_cover = get_value_coverage(arr_int, num_int, idx_mid, end_left,
                                            (idx_mid + 1), end_right);
        freq_max = MAX(freq_left, freq_right);
        freq_max = MAX(freq_max, freq_cover);
    } else
        freq_max = MAX(freq_left, freq_right);
    nd_new->freq = freq_max;
    nd_new->br_left = nd_left;
    nd_new->br_right = nd_right;

    return freq_max;
}


void destruct_tree(NODE *nd_curr)
{
    if (nd_curr) {
        destruct_tree(nd_curr->br_left);
        destruct_tree(nd_curr->br_right);
        free(nd_curr);
    }

    return;
}


int query_tree(int *arr_int, int num_int, NODE *nd_curr,
               int end_left, int end_right)
{
    if ((end_left == nd_curr->end_left) && (end_right == nd_curr->end_right))
        return nd_curr->freq;

    int idx_mid = (nd_curr->end_left + nd_curr->end_right) / 2;
    if (end_right <= idx_mid)
        return query_tree(arr_int, num_int, nd_curr->br_left, end_left, end_right);
    else if (end_left > idx_mid)
        return query_tree(arr_int, num_int, nd_curr->br_right, end_left, end_right);
    else {
        int freq_left = query_tree(arr_int, num_int, nd_curr->br_left, end_left, idx_mid);
        int freq_right = query_tree(arr_int, num_int, nd_curr->br_right, (idx_mid + 1), end_right);
        int freq_max = MAX(freq_left, freq_right);
        if (arr_int[idx_mid] == arr_int[idx_mid + 1]) {
            int freq_cover = get_value_coverage(arr_int, num_int, idx_mid, end_left,
                                                (idx_mid + 1), end_right);
            freq_max = MAX(freq_max, freq_cover);
        }
        return freq_max;
    }
}


int main()
{
    int num_int, num_ask, dummy;

    while (true) {
        dummy = scanf("%d", &num_int);
        if (num_int == 0)
            break;
        dummy = scanf("%d", &num_ask);
        
        /* Construct the interval tree. */
        int *arr_int = (int*)malloc(sizeof(int) * (num_int + 1));
        int idx_int;
        for (idx_int = 1 ; idx_int <= num_int ; idx_int++)
            dummy = scanf("%d", &(arr_int[idx_int]));
        NODE *nd_root;
        construct_tree(arr_int, num_int, &nd_root, 1, num_int);       
        
        /* Query the tree to get the most frequently appearing value within the range. */
        int idx_ask, end_left, end_right, freq;
        for (idx_ask = 1 ; idx_ask <= num_ask ; idx_ask++) {
            dummy = scanf("%d%d", &end_left, &end_right);
            freq = query_tree(arr_int, num_int, nd_root, end_left, end_right);
            printf("%d\n", freq);
        }

        destruct_tree(nd_root);
        free(arr_int);
    }    

    return 0;
}
