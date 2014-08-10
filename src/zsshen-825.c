#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define MAX_ROW_COL 100


int main() {
    int i, j, round, num_row, num_col, turn, idx_row, idx_col;
    char *token;
    char input[MAX_ROW_COL * MAX_ROW_COL];
    unsigned long long  dp[MAX_ROW_COL + 1][MAX_ROW_COL + 1];
    bool map[MAX_ROW_COL + 1][MAX_ROW_COL + 1];

    scanf("%d", &round);
    while (round > 0) {
        scanf("%d %d\n", &num_row, &num_col);        

        for (i = 1 ; i <= num_row ; i++) {
            memset(input, 0, sizeof(char) * MAX_ROW_COL * MAX_ROW_COL);
            fgets(input, MAX_ROW_COL * MAX_ROW_COL, stdin);            

            for (j = 1 ; j <= num_col ; j++) {
                map[i][j] = true;
                dp[i][j] = 0;            
            }

            turn = 0;
            token = strtok(input, " ");
            while (token != NULL) {
                if (turn == 0)
                    idx_row = atoi(token);
                else {
                    idx_col = atoi(token);
                    map[idx_row][idx_col] = false;
                }                
                token = strtok(NULL, " ");
                turn++;
            }        
        }

        /**
         * Recursive formula:
         * 1. dp[i][j] : The number of ways to reach location (i, j).
         * 2. if map[i][j] == false, dp[i][j] = 0.
         *    else dp[i][j] = | dp[i - 1][j] + dp[i][j - 1], if i > 1 and j > 1.
         *                    | dp[i - 1][j]               , if j == 1.
         *                    | dp[i][j - 1]               , if i == 1.
         */

        dp[1][1] = 1;
        for (i = 1 ; i <= num_row ; i++) {
            for (j = 1 ; j <= num_col ; j++) {
                if (map[i][j] == false)
                    dp[i][j] = 0;
                else {
                    if (i > 1)
                        dp[i][j] += dp[i - 1][j];
                    if (j > 1)
                        dp[i][j] += dp[i][j - 1]; 
                }                
            }
        }

        printf("%llu\n", dp[num_row][num_col]);

        round--;
        if (round > 0)
            printf("\n");
    }

    return 0;
}
