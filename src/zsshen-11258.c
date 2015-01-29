#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>


typedef long long llint;


#define BUF_SIZE    200
#define NUM_DIGIT   10
#define RADIX_TEN   10
#define LLONG_MAX   9223372036854775807


/*
 * Time Complexity  : O(n^2)
 * Recursive Formula:
 * dp[i] =   MAX  {dp[i - j - 1] + ToInt(i - j, j)}
 *         0<=j<10
 * 
 * Boundaries:
 *           if i - j - 1 = 0, dp[i -j - 1] = 0.
 *           if i - j < 0, break.
 */


void find_max_partition_sum(char *sz)
{
    int len_sz = strlen(sz);

    int i, j;
    llint *dp = (llint*)malloc(len_sz * sizeof(llint));
    int **num = (int**)malloc(len_sz * sizeof(int*));

    for (i = 0 ; i < len_sz ; i++) {
        dp[i] = -1;
        num[i] = (int*)malloc(len_sz * sizeof(int));
        for (j = 0 ; j < len_sz ; j++) {
            num[i][j] = -1;
        }
    }

    /* Initialize the "to-int" array. */
    int k, range;
    llint value;
    for (i = 0 ; i < len_sz ; i++) {
        range = i + NUM_DIGIT;
        if (len_sz < range) 
            range = len_sz;
        for (j = i ; j < range ; j++) {
            value = 0;
            for (k = i ; k <= j ; k++) {
                value += sz[k] - '0';
                if (k < j)
                    value *= RADIX_TEN;
            }
            if (value <= INT_MAX)
                num[i][j] = (int)value;
            /* printf("num[%d][%d] = %d\n", i, j, dp[i][j]); */
        }
        /* printf("\n"); */
    }

    llint max;
    for (i = 0 ; i < len_sz ; i++) {
        max = 0;
        for(range = 0 ; range < 10 ; range++) {
            if ((i - range) < 0)
                break;

            if (num[i - range][i] != -1) {
                if ((i - range - 1) < 0)
                    value = num[i - range][i];
                else
                    value = num[i - range][i] + dp[i - range - 1];

                if (value <= LLONG_MAX) {
                    if (value > max)
                        max = value;
                }
            }
        }
        dp[i] = max;
    }

    printf("%lld\n", dp[len_sz - 1]);

    for (i = 0 ; i < len_sz ; i++)
        free(num[i]);
    free(dp);
    free(num);

    return;
}


int main()
{
    int dummy, cnt_case, idx_case;
    char sz_num[BUF_SIZE + 1];

    dummy = scanf("%d", &cnt_case);
    for (idx_case = 0 ; idx_case < cnt_case ; idx_case++) {
        dummy = scanf("%s", sz_num);
        find_max_partition_sum(sz_num);
    }

    return 0;
}
