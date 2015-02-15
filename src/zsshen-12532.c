#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define FLAG_POSITIVE   (1)
#define FLAG_NEGATIVE   (-1)
#define FLAG_ZERO       (0)


typedef struct _NODE {
    int end_left;
    int end_right;
    char flag;
    struct _NODE *child_left;
    struct _NODE *child_right;
} NODE;


char construct_tree(NODE **p_curr, int end_left, int end_right)
{
    if (end_left == end_right) {
        *p_curr = (NODE*)malloc(sizeof(NODE));
        NODE *curr = *p_curr;

        int value, dummy;
        dummy = scanf("%d", &value);
        if (value == 0)
            curr->flag = FLAG_ZERO;
        else {
            if (value > 0)
                curr->flag = FLAG_POSITIVE;
            else
                curr->flag = FLAG_NEGATIVE;
        }

        curr->end_left = end_left;
        curr->end_right = end_right;
        curr->child_left = curr->child_right = NULL;
        return curr->flag;
    }

    *p_curr = (NODE*)malloc(sizeof(NODE));
    NODE *curr = *p_curr;
    NODE *child_left, *child_right;

    int idx_mid = (end_left + end_right) / 2;
    curr->flag = construct_tree(&child_left, end_left, idx_mid) *
                 construct_tree(&child_right, (idx_mid + 1), end_right);

    curr->end_left = end_left;
    curr->end_right = end_right;
    curr->child_left = child_left;
    curr->child_right = child_right;

    return curr->flag;
}


void destruct_tree(NODE *curr)
{
    if (curr) {
        destruct_tree(curr->child_left);
        destruct_tree(curr->child_right);
        free(curr);
    }

    return;
}


void change_node_flag(NODE *curr, int idx_element, char flag)
{
    if ((curr->end_left == idx_element) &&
        (curr->end_right == idx_element)) {
        curr->flag = flag;
        return;
    }

    int idx_mid = (curr->end_left + curr->end_right) / 2;
    if (idx_element <= idx_mid)
        change_node_flag(curr->child_left, idx_element, flag);
    else
        change_node_flag(curr->child_right, idx_element, flag);

    curr->flag = curr->child_left->flag * curr->child_right->flag;
    return;
}


char query_range_product(NODE *curr, int range_left, int range_right)
{
    if ((curr->end_left == range_left) &&
        (curr->end_right == range_right))
        return curr->flag;

    int idx_mid = (curr->end_left + curr->end_right) / 2;
    if (range_right <= idx_mid)
        return query_range_product(curr->child_left, range_left, range_right);
    else if (range_left > idx_mid)
        return query_range_product(curr->child_right, range_left, range_right);
    else
        return query_range_product(curr->child_left, range_left, idx_mid) *
               query_range_product(curr->child_right, (idx_mid + 1), range_right);
}


int main()
{
    int cnt_element, cnt_query;

    while (scanf("%d%d", &cnt_element, &cnt_query) != EOF) {

        /* Read the array of elements and construct the interval tree. */
        NODE *tree;
        construct_tree(&tree, 1, cnt_element);

        /* Update the tree values and acquire the range properties. */
        int idx, dummy;
        char absorb;
        dummy = scanf("%c", &absorb);
        for (idx = 0 ; idx < cnt_query ; idx++) {
            char command;
            dummy = scanf("%c", &command);
            if (command == 'C') {
                int idx_element, value;
                dummy = scanf("%d%d%c", &idx_element, &value, &absorb);
                char flag;
                if (value == 0)
                    flag = FLAG_ZERO;
                else {
                    if (value > 0)
                        flag = FLAG_POSITIVE;
                    else
                        flag = FLAG_NEGATIVE;    
                }
                change_node_flag(tree, idx_element, flag);
            } else {
                int range_left, range_right;
                dummy = scanf("%d%d%c", &range_left, &range_right, &absorb);
                char flag = query_range_product(tree, range_left, range_right);
                switch(flag) {
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

        destruct_tree(tree);
    }

    return 0;
}
