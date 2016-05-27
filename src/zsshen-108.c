#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


static const int MAX_N = 100;


int main()
{
    int dummy;
    int n;
    int mtx[MAX_N][MAX_N];
    int acc_mtx[MAX_N][MAX_N];

    while (scanf("%d", &n) != EOF) {
        int i, j;
        for (i = 0 ; i < n ; ++i) {
            for (j = 0 ; j < n ; ++j)
                dummy = scanf("%d", &(mtx[i][j]));
        }

        /*
        // The basic idea is to efficiently generate all the combinations of
        // sub-matrices via the helpful accumulation sub-matrix.
        // The time complexity is O(n^4).
        */

        int ans = INT_MIN;
        acc_mtx[0][0] = mtx[0][0];

        int k;
        for (i = 1 ; i < n ; ++i) {
            acc_mtx[i][0] = acc_mtx[i - 1][0] + mtx[i][0];
            if (acc_mtx[i][0] > ans)
                ans = acc_mtx[i][0];
            for (k = 0 ; k < i ; ++k) {
                int sum = acc_mtx[i][0] - acc_mtx[k][0];
                if (sum > ans)
                    ans = sum;
            }
        }

        int h;
        for (j = 1 ; j < n ; ++j) {
            acc_mtx[0][j] = acc_mtx[0][j - 1] + mtx[0][j];
            if (acc_mtx[0][j] > ans)
                ans = acc_mtx[0][j];
            for (h = 0 ; h < j ; ++h) {
                int sum = acc_mtx[0][j] - acc_mtx[0][h];
                if (sum > ans)
                    ans = sum;
            }
        }

        for (i = 1 ; i < n; ++i) {
            for (j = 1 ; j < n ; ++j) {
                /* Calculate the accumulation matrix. */
                acc_mtx[i][j] = acc_mtx[i - 1][j] + acc_mtx[i][j - 1] -
                                acc_mtx[i - 1][j - 1] + mtx[i][j];
                if (acc_mtx[i][j] > ans)
                    ans = acc_mtx[i][j];

                /* Generate the sub-matrices. */
                for (h = 0 ; h < j ; ++h) {
                    int sum = acc_mtx[i][j] - acc_mtx[i][h];
                    if (sum > ans)
                        ans = sum;
                }

                for (k = 0 ; k < i ; ++k) {
                    int sum = acc_mtx[i][j] - acc_mtx[k][j];
                    if (sum > ans)
                        ans = sum;

                    for (h = 0 ; h < j ; ++h) {
                        int sum = acc_mtx[i][j] - acc_mtx[k][j] - acc_mtx[i][h] +
                                  acc_mtx[k][h];
                        if (sum > ans)
                            ans = sum;
                    }
                }
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}