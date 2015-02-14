#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define FLAG_POSITIVE   (1)
#define FLAG_NEGATIVE   (-1)
#define FLAG_ZERO       (0)
#define BUF_SIZE        (1024)


#define LEFT(node)      (node << 1)
#define RIGHT(node)     (node << 1 | 1)
#define TOTAL(node)     ((node + 1) * node / 2 + 1)


typedef struct _NODE {
    int end_left;
    int end_right;
    char flag_value;
} NODE;


int construct_tree(NODE *tree, int idx_node, int end_left, int end_right)
{
    if (end_left == end_right) {
        int value, dummy;
        dummy = scanf("%d", &value);
        if (value == 0)
            tree[idx_node].flag_value = FLAG_ZERO;
        else {
            if (value > 0)
                tree[idx_node].flag_value = FLAG_POSITIVE;
            else
                tree[idx_node].flag_value = FLAG_NEGATIVE;    
        }
        tree[idx_node].end_left = end_left;
        tree[idx_node].end_right = end_right;
        return tree[idx_node].flag_value;
    }

    int idx_mid = (end_left + end_right) / 2;
    int child_left = LEFT(idx_node);
    int child_right = RIGHT(idx_node);
    tree[idx_node].flag_value = construct_tree(tree, child_left, end_left, idx_mid) *
                                construct_tree(tree, child_right, (idx_mid + 1), end_right);
    tree[idx_node].end_left = end_left;
    tree[idx_node].end_right = end_right;
    return tree[idx_node].flag_value;                            
}


void change_node_flag(NODE *tree, int idx_node, int idx_element, char flag_value)
{
    if (tree[idx_node].end_left == idx_element &&
        tree[idx_node].end_right == idx_element) {
        tree[idx_node].flag_value = flag_value;
        return;
    }

    int idx_mid = (tree[idx_node].end_left + tree[idx_node].end_right) / 2;
    int child_left = LEFT(idx_node);
    int child_right = RIGHT(idx_node);
    if (idx_element <= idx_mid)
        change_node_flag(tree, child_left, idx_element, flag_value);
    else
        change_node_flag(tree, child_right, idx_element, flag_value);

    tree[idx_node].flag_value = tree[child_left].flag_value *
                                tree[child_right].flag_value;
    return;
}


char query_range_product(NODE *tree, int idx_node, int range_left, int range_right)
{
    if (tree[idx_node].end_left == range_left &&
        tree[idx_node].end_right == range_right)
        return tree[idx_node].flag_value;

    int idx_mid = (tree[idx_node].end_left + tree[idx_node].end_right) / 2;
    int child_left = LEFT(idx_node);
    int child_right = RIGHT(idx_node);
    if (range_right <= idx_mid)
        return query_range_product(tree, child_left, range_left, range_right);
    else if (range_left > idx_mid)
        return query_range_product(tree, child_right, range_left, range_right);
    else
        return query_range_product(tree, child_left, range_left, idx_mid) *
               query_range_product(tree, child_right, (idx_mid + 1), range_right);
}


int main()
{
    int cnt_element, cnt_query;

    while (scanf("%d%d", &cnt_element, &cnt_query) != EOF) {
        NODE *tree = (NODE*)malloc(sizeof(NODE) * TOTAL(cnt_element));
        construct_tree(tree, 1, 1, cnt_element);

        int idx, dummy;
        char absorb;
        dummy = scanf("%c", &absorb);
        for (idx = 0 ; idx < cnt_query ; idx++) {
            char command;
            dummy = scanf("%c", &command);
            if (command == 'C') {
                int idx_element, value;
                dummy = scanf("%d%d%c", &idx_element, &value, &absorb);
                char flag_value;
                if (value == 0)
                    flag_value = FLAG_ZERO;
                else {
                    if (value > 0)
                        flag_value = FLAG_POSITIVE;
                    else
                        flag_value = FLAG_NEGATIVE;    
                }
                change_node_flag(tree, 1, idx_element, flag_value);
            } else {
                int range_left, range_right;
                dummy = scanf("%d%d%c", &range_left, &range_right, &absorb);
                char flag_result = query_range_product(tree, 1, range_left, range_right);
                switch(flag_result) {
                  case FLAG_POSITIVE:
                    printf("+");
                    break;
                  case FLAG_ZERO:
                    printf("0");
                    break;
                  case FLAG_NEGATIVE:
                    printf("-");
                    break;
                }
            }
        }
        printf("\n");

        free(tree);
    }

    return 0;
}
