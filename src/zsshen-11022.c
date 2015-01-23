#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>


#define BUF_SIZE        80
#define LEFT_DRIVE      0
#define RIGHT_DRIVE     1


void factor_string(char *sz)
{
    int dp[BUF_SIZE][BUF_SIZE];
    int len_sz = strlen(sz);
    
    int range;
    for (range = 0 ; range < len_sz ; range++)
        dp[range][range] = 1;

    int i, j, k;
    int len_small, len_large, idx_small, idx_large;
    int val_min, val_tmp;
    bool check, direction;
    for (range = 1 ; range <= len_sz - 1 ; range++) {
        for (i = 0, j = i + range ; i < len_sz - range ; i++, j++) {
            val_min = INT_MAX;
            for (k = i ; k < j ; k++) {
                check = true;
                if ((k - i + 1) > (j - k)) {
                    len_large = k - i + 1;
                    len_small = j - k;
                    direction = RIGHT_DRIVE;
                } else {
                    len_large = j - k;
                    len_small = k - i + 1;
                    direction = LEFT_DRIVE;
                }
                if ((len_large % len_small) == 0) {
                    if (direction == LEFT_DRIVE) {
                        idx_small = idx_large = 0;
                        while (idx_large < len_large) {
                            if (sz[i + idx_small] != sz[k + 1 + idx_large]) {
                                check = false;
                                break;
                            }
                            idx_large++;
                            idx_small++;
                            if (idx_small == len_small)
                                idx_small = 0;
                        }
                    } else {
                        idx_small = idx_large = 0;
                        while (idx_large < len_large) {
                            if (sz[i + idx_large] != sz[k + 1 + idx_small]) {
                                check = false;
                                break;
                            }
                            idx_large++;
                            idx_small++;
                            if (idx_small == len_small)
                                idx_small = 0;
                        }    
                    }
                } else
                    check = false;
                /*
                printf("dp[%2d][%2d] = %2d\tdp[%2d][%2d] = %2d\tcheck%d\n",
                        i + 1, k + 1, dp[i][k], k + 2, j + 1, dp[k + 1][j], check);
                */
                if (check)
                    val_tmp = dp[i][k];
                else
                    val_tmp = dp[i][k] + dp[k + 1][j];
                if (val_tmp < val_min)
                    val_min = val_tmp;
            }
            dp[i][j] = val_min;
            /* printf("dp[%2d][%2d] = %2d\n", i + 1, j + 1, dp[i][j]); */
        }
    }
    
    printf("%d\n", dp[0][len_sz - 1]);
    return;
}


int main()
{
    char sz[BUF_SIZE + 1];

    while (scanf("%s", sz) != EOF) {
        if (sz[0] == '*')
            break;
    
        factor_string(sz);
    }

    return 0;
}
