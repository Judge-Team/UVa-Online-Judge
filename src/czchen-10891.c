#include <stdio.h>

enum {
    MAX_COUNT = 100,
};

#define DEBUG 0

#define VALUE(i, j) (accumulated_value[(j)+1] - accumulated_value[(i)])

int max(int x, int y)
{
    return x > y ? x : y;
}

int main(int argc, char *argv[])
{
    int count;
    int value[MAX_COUNT];
    int best[MAX_COUNT][MAX_COUNT];
    int accumulated_value[MAX_COUNT+1];

    int i;
    int j;
    int len;

    while (scanf("%d", &count) == 1) {
        if (count == 0) {
            break;
        }

        for (i = 0; i < count; ++i) {
            scanf("%d", &value[i]);
        }

        /*
         * best(i, j) = optimal way to get result in range i ~ j inclusively.
         * value(i, j)   = value sum in range i ~ j inclusively
         *
         * Assume each oppoment can get one token at a time:
         *
         *     best(i, j) = max | value(i, i) - best(i+1, j) <- choose left token
         *                      | value(j, j) - best(i, j-1) <- choose right token
         *
         * With the following initial value:
         *
         *     best(i, i) = value(i, i)
         *
         * Extend to get n token at a time:
         *
         *     best(i, j) = max | value(i, k) - best(k+1, j), i <= k < j, <- take from left
         *                      | value(k+1, j) - best(i, k), i <= k < j, <- take from left
         *                      | value(i, j) <- show hand
         */

        for (i = 0; i < count; ++i) {
            best[i][i] = value[i];
        }

        accumulated_value[0] = 0;
        for (i = 0; i < count; ++i) {
            accumulated_value[i+1] = value[i] + accumulated_value[i];
        }

#if DEBUG
        printf("value = ");
        for (i = 0; i < count; ++i) {
            printf("%d ", value[i]);
        }
        printf("\n");

        printf("accumulated_value = ");
        for (i = 0; i < count + 1; ++i) {
            printf("%d ", accumulated_value[i]);
        }
        printf("\n");
#endif

        for (len = 1; len < count; ++len) {
            for (i = 0; i + len < count; ++i) {
                /*
                 * show hand
                 */
                best[i][i+len] = VALUE(i, j);

#if DEBUG
                printf("best[%d][%d] = %d\n", i, i+len, best[i][i+len]);
#endif

                for (j = i; j < i + len; ++j) {
                    best[i][i+len] = max(
                        best[i][i+len],
                        VALUE(i, j) - best[j+1][i+len]
                    );

                    best[i][i+len] = max(
                        best[i][i+len],
                        VALUE(j+1, i+len) - best[i][j]
                    );
                }
            }
#if DEBUG
            printf("---\n");
            for (i = 0; i < count; ++i) {
                for (j = 0; j < count; ++j) {
                    printf("\t%d", best[i][j]);
                }
                printf("\n");
            }
#endif
        }

        printf("%d\n", best[0][count-1]);
    }
    return 0;
}

