#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_ROW_COUNT 21
#define MAX_COL_COUNT 101


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
         * dp[i][j] = input[i][j] + Min{dp[i - 1][j + 1], dp[i][j + 1], dp[i + 1][j + 1]}
         * Let S denote the set containing the row indicies of the elements with minimum value.  
         * step[i][j] = Min{row | row belonged to S}
         */
        for (i = num_row ; i >= 1 ; i--) {
            dp[i][num_col] = input[i][num_col];
        }

        for (j = num_col - 1 ; j >= 1 ; j--) {
            for (i = 1 ; i <= num_row ; i++) {
                /* Check dp[i - 1][j + 1]*/                
                k = i - 1;
                if (k < 1)
                    k = num_row;
                min_val = dp[k][j + 1];
                row_idx = k;
 
                /* Check dp[i][j + 1] */
                k = i;
                if (dp[k][j + 1] < min_val) {
                    min_val = dp[k][j + 1];
                    row_idx = k;
                } else if (dp[k][j + 1] == min_val) {
                    if (k < row_idx)
                        row_idx = k;
                }

                /* Check dp[i + 1][j + 1] */
                k = i + 1;
                if (k > num_row)
                    k = 1; 
                if (dp[k][j + 1] < min_val) {
                    min_val = dp[k][j + 1];
                    row_idx = k;
                } else if (dp[k][j + 1] == min_val) {
                    if (k < row_idx)
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
            for (j = 1 ; j < num_col ; j++)
                printf("%5d ", step[i][j]);
            printf("\n");
        }
        printf("\n");
        */

        min_val = dp[1][1];
        row_idx = 1;
        for (i = 2 ; i <= num_row ; i++) {
            if (dp[i][1] < min_val) {
                min_val = dp[i][1];
                row_idx = i;
            }
        }

        /* Retrieve the path with minimum weight. */
        printf("%d", row_idx);
        for (i = 1 ; i < num_col ; i++) {
            row_idx = step[row_idx][i];
            printf(" %d", row_idx);
        }
        printf("\n");
        printf("%ld\n", min_val);
    }

    return 0;
}
