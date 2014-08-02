#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_ROW_COUNT 11
#define MAX_COL_COUNT 101


bool check_order(char(*)[MAX_ROW_COUNT][MAX_COL_COUNT] , int, int, int);


int main() {
    int   i, j, k, num_row, num_col, row_idx;
    long  min_val;
    long  input[MAX_ROW_COUNT][MAX_COL_COUNT];
    long  dp[MAX_ROW_COUNT][MAX_COL_COUNT];
    char  step[MAX_ROW_COUNT][MAX_COL_COUNT];

    while (scanf("%d%d", &num_row, &num_col) != EOF) {
        for (i = 1 ; i <= num_row ; i++)
            for (j = 1 ; j <= num_col ; j++)
                scanf("%ld", &(input[i][j]));

        /**
         * Recursive Formula:
         * 
         * dp[i][j] = input[i][j] + Min{dp[i - 1][j - 1], dp[i][j - 1], dp[i + 1][j - 1]}
         * Let S denote the set containing the row indicies of the elements with minimum value.  
         * step[i][j] = Min{row | row belonged to S}
         */
        for (i = 1 ; i <= num_row ; i++)
            dp[i][1] = input[i][1];

        for (j = 2 ; j <= num_col ; j++) {
            for (i = 1 ; i <= num_row ; i++) {
                k = i - 1;
                if (k < 1)
                    k = num_row;
                min_val = dp[k][j - 1];
                row_idx = k;  

                k = i;
                if (dp[k][j - 1] < min_val) {
                    min_val = dp[k][j - 1];
                    row_idx = k;
                } else if (dp[k][j - 1] == min_val) {
                    if (check_order(&step, row_idx, k, j - 1) == false)
                        row_idx = k;
                }              

                k = i + 1;
                if (k > num_row)
                    k = 1; 
                if (dp[k][j - 1] < min_val) {
                    min_val = dp[k][j - 1];
                    row_idx = k;
                } else if (dp[k][j - 1] == min_val) {
                    if (check_order(&step, row_idx, k, j - 1) == false)
                        row_idx = k;
                }

                dp[i][j] = min_val + input[i][j];
                step[i][j] = row_idx;
            }
        }        

        /*
        printf("INPUT:\n");
        for (i = 1 ; i <= num_row ; i++) {
            for (j = 1 ; j <= num_col ; j++)
                printf("%5ld ", input[i][j]);
            printf("\n");
        }
        printf("DP:\n");
        for (i = 1 ; i <= num_row ; i++) {
            for (j = 1 ; j <= num_col ; j++)
                printf("%5ld ", dp[i][j]);
            printf("\n");
        }
        printf("STEP:\n");
        for (i = 1 ; i <= num_row ; i++) {
            for (j = 2 ; j <= num_col ; j++)
                printf("%5d ", step[i][j]);
            printf("\n");
        }
        printf("\n");
        */

        min_val = dp[1][num_col];
        row_idx = 1;
        for (i = 2 ; i <= num_row ; i++) {
            if (dp[i][num_col] < min_val) {
                min_val = dp[i][num_col];
                row_idx = i;
            } else if (dp[i][num_col] == min_val) {
                if (check_order(&step, row_idx, i, num_col) == false)
                    row_idx = i;
            }
        }

        /* Retrieve the path with minimum weight. */
        step[0][num_col] = row_idx;
        for (i = num_col ; i >= 2 ; i--) {
            row_idx = step[row_idx][i];
            step[0][i - 1] = row_idx;
        }

        for (i = 1 ; i < num_col ; i++)
            printf("%d ", step[0][i]);
        printf("%d\n", step[0][num_col]);
        printf("%ld\n", min_val);
    }

    return 0;
}


bool check_order(char (*p_step)[MAX_ROW_COUNT][MAX_COL_COUNT], int src_row, int tge_row, int pred_col) {
    int  i, j;
    bool check;
    char line_src[MAX_COL_COUNT], line_tge[MAX_COL_COUNT];
        
    line_src[pred_col] = src_row;
    line_tge[pred_col] = tge_row;
    for (i = pred_col, j = i - 1; i >= 2 ; i--, j--) {
        src_row = (*p_step)[src_row][i];
        tge_row = (*p_step)[tge_row][i];
        line_src[j] = src_row;
        line_tge[j] = tge_row;
    }

    check = true;
    for (i = 1 ; i <= pred_col ; i++) {
        if (line_src[i] > line_tge[i]) {
            check = false;
            break;        
        }
    }
    
    /*
    for (i = 1 ; i <= pred_col ; i++)
        printf("%3d ", line_src[i]);
    printf("\n");
    for (i = 1 ; i <= pred_col ; i++)
        printf("%3d ", line_tge[i]);
    printf("\n");
    */

    return check;
}
