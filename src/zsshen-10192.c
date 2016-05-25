#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


static const int BUF_SIZE = 256;

#define MAX(a, b) (((a) > (b)) ? (a) : (b))


int main()
{
    char* dummy;
    char src[BUF_SIZE], tge[BUF_SIZE];

    int idx_case = 1;
    while (true) {
        dummy = fgets(src, BUF_SIZE, stdin);
        if (src[0] == '#')
            break;
        dummy = fgets(tge, BUF_SIZE, stdin);

        /*
        // The classic LCS problem.
        //
        // Object Definition:
        //  dp[i][j] : The LCS calculated from the source(0, i) and target(0, j).
        //
        // Optimal Function:
        //             | 1 + dp[i - 1][j - 1], if source[i] == target[j].
        //  dp[i][j] = |
        //             | MAX{dp[i][j - 1], dp[i - 1][j]}, Otherwise.
        */

        int len_src = strlen(src) - 1;
        int len_tge = strlen(tge) - 1;
        short dp[len_src + 1][len_tge + 1];

        dp[0][0] = 0;
        int i;
        for (i = 1 ; i <= len_src ; ++i)
            dp[i][0] = 0;
        int j;
        for (j = 1 ; j <= len_tge ; ++j)
            dp[0][j] = 0;

        for (i = 1 ; i <= len_src ; ++i) {
            for (j = 1 ; j <= len_tge ; ++j) {
                if (src[i - 1] == tge[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = MAX(dp[i][j - 1], dp[i - 1][j]);
            }
        }

        printf("Case #%d: you can visit at most %d cities.\n", idx_case, dp[len_src][len_tge]);
        ++idx_case;
    }

    return 0;
}