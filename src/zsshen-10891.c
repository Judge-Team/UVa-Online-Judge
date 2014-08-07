#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_ELEMENT_COUNT   100
#define MIN_INT             -2147483647
#define Max(a, b)           (((a) > (b)) ? (a) : (b))


int main() {
    int i, j, k, range, count, element, total, tmp_max, region_max;
    int sum[MAX_ELEMENT_COUNT + 1][MAX_ELEMENT_COUNT + 1];
    int dp[MAX_ELEMENT_COUNT + 1][MAX_ELEMENT_COUNT + 1];

    while (true) {

        scanf("%d", &count);
        if (count == 0)
            break;

        /* Prepare the accumulation matrix. */
        total = 0;
        for (i = 1 ; i <= count ; i++) {
            scanf("%d", &element);
            total += element;
            sum[i][i] = element;
            sum[1][i] = total;
            sum[i][1] = total;
            for (j = 2 ; j < i ; j++) {
                sum[j][i] = total - sum[1][j - 1];
                sum[i][j] = sum[j][i];
            }
            dp[i][i] = element;
        }

        /**
         * Recursive formula:
         * dp[i][j]  : The optimal differencing score a player can tack at range from i to j.
         * sum[i][j] : The accumulative element sum at range from i to j.
         *
         * dp[i][j] = Max{Max{(sum[i][k] - dp[k + 1][j]), (sum[k + 1][j] - dp[i][k]) | i<=k<j }, sum[i][j]}
         */

        /* Main algorithm. */
        for (range = 1 ; range < count ; range++) {
            for (i = 1, j = i + range ; i <= count - range ; i++, j++) {
                region_max = MIN_INT;
                for (k = i ; k <= j ; k++) {
                    if (k < j)
                        tmp_max = Max(sum[i][k] - dp[k + 1][j], sum[k + 1][j] - dp[i][k]);
                    else
                        tmp_max = sum[i][k];

                    if (tmp_max > region_max)
                        region_max = tmp_max;
                }
                dp[i][j] = region_max;
            }
        }

        printf("%d\n", dp[1][count]);

    }

    return 0;
}

