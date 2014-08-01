#include <stdio.h>
#include <string.h>

enum {
    MAX_N = 1000000,
    MAX_M = 10,
};

int max(int x, int y)
{
    return x > y ? x : y;
}

int main()
{
    int n;
    int m;
    int max_m;
    int move[MAX_M];
    char res[MAX_N+1];

    int i;
    int j;

    while (scanf("%d", &n) == 1) {
        scanf("%d", &m);
        for (i = 0; i < m; ++i) {
            scanf("%d", &move[i]);
        }

#if DEBUG
        printf("move = ");
        for (i = 0; i < m; ++i) {
            printf("%d ", move[i]);
        }
        printf("\n");
#endif

        /*
         * Remove 1 and > n
         */
        max_m = 0;
        for (i = 0; i < m; ++i) {
            if (move[i] == 1 || move[i] > n) {
                memmove(&move[i], &move[i+1], m-i);
                --m;
                --i;
            } else {
                max_m = max(max_m, move[i]);
            }
        }

#if DEBUG
        printf("move = ");
        for (i = 0; i < m; ++i) {
            printf("%d ", move[i]);
        }
        printf("\n");
#endif

        /*
         * res[n] = | 1 if current user wins
         *          | -1 if current user loses
         *          | 0 if unknown
         *
         * res[move[i]] = 1
         * res[0] = -1;
         *
         * res[i] = | if res[i-move[i]] == -1 (force your opponent to lost)
         *          |     res[i] = 1
         *          | else
         *          |     res[i] = -res[i-1] (pick one stone because we cannot force opponent to lost)
         *          |
         *
         */

        memset(res, 0, sizeof(res));

        res[0] = -1;
        res[1] = 1;
        for (i = 0; i < m; ++i) {
            res[move[i]] = 1;
        }

#if DEBUG
        printf("res = ");
        for (i = 0; i <= n; ++i) {
            printf("%d ", res[i]);
        }
        printf("\n");
#endif

        for (i = 2; i < max_m; ++i) {
            if (res[i] != 0) {
                continue;
            }

            res[i] = -res[i-1];
            for (j = 0; j < m; ++j) {
                if (i - move[j] > 0 && res[i-move[j]] == -1) {
                    res[i] = 1;
                    break;
                }
            }
        }

#if DEBUG
        printf("res = ");
        for (i = 0; i <= n; ++i) {
            printf("%d ", res[i]);
        }
        printf("\n");
#endif

        for (i = max_m + 1; i <= n; ++i) {
            res[i] = -res[i-1];
            for (j = 0; j < m; ++j) {
                if (res[i-move[j]] == -1) {
                    res[i] = 1;
                    break;
                }
            }
        }

#if DEBUG
        printf("res = ");
        for (i = 0; i <= n; ++i) {
            printf("%d ", res[i]);
        }
        printf("\n");
#endif

        if (res[n] == 1) {
            printf("Stan wins\n");
        } else {
            printf("Ollie wins\n");
        }

    }

    return 0;
}
