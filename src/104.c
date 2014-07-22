#include <math.h>
#include <stdio.h>
#include <string.h>

enum {
    MIN_DIM = 2,
    MAX_DIM = 20,
};

struct BellmanFord {
    double cost;
    int path_len;
    int path[MAX_DIM];
};

struct Ans {
    int solved;
    int path_len;
    int start;
    int path[MAX_DIM];
};

void has_negative_cycle(int start, double data[MAX_DIM][MAX_DIM], int dim, struct Ans *ans)
{
    int dest;
    int i;
    int j;

    struct BellmanFord buf1[MAX_DIM];
    struct BellmanFord buf2[MAX_DIM];

    struct BellmanFord *curr;
    struct BellmanFord *next;
    struct BellmanFord *tmp;

    memset(buf1, 0, sizeof(buf1));

    for (dest = 0; dest < dim; ++dest) {
        buf1[dest].cost = data[start][dest];
        buf1[dest].path_len = 0;
    }

    curr = buf1;
    next = buf2;

    for (i = 0; i < dim - 1; ++i) {
        for (dest = 0; dest < dim; ++dest) {
            next[dest] = curr[dest];
            for (j = 0; j < dim; ++j) {
                if (next[dest].cost < curr[j].cost * data[j][dest]) {
                    next[dest] = curr[j];
                    next[dest].cost *= data[j][dest];
                    ++next[dest].path_len;
                    next[dest].path[curr[j].path_len] = j;
                }
            }
        }

        /* Bellman-Ford early termination. */
        if (memcmp(curr, next, sizeof(buf1)) == 0) {
            break;
        }

        tmp = curr;
        curr = next;
        next = tmp;

#if 0
        for (i = 0; i < dim; ++i) {
            printf("cost = %f, ", curr[i].cost);
            for (j = 0; j < curr[i].path_len; ++j) {
                printf("%d -> ", curr[i].path[j]);
            }
            printf("\n");
        }
#endif

        if (curr[start].cost >= 1.01) {
            /*
             * Update ans only when there is no solution, or the current
             * solution is shortest then previous one.
             */
            if (!ans->solved || curr[start].path_len < ans->path_len) {
                ans->solved = 1;
                ans->path_len = curr[start].path_len;
                ans->start = start;
                memcpy(ans->path, curr[start].path, sizeof(ans->path[0]) * curr[start].path_len);
            }
            return;
        }
    }

    return;
}

void find_arbitrage(double data[MAX_DIM][MAX_DIM], int dim)
{
    int i;
    struct Ans ans;

    ans.solved = 0;
    for (i = 0; i < dim; ++i) {
        has_negative_cycle(i, data, dim, &ans);
    }

    if (ans.solved) {
        printf("%d ", ans.start + 1);
        for (i = 0; i < ans.path_len; ++i) {
            printf("%d ", ans.path[i] + 1);
        };
        printf("%d\n", ans.start + 1);
    } else {
        printf("no arbitrage sequence exists\n");
    }
}

int main(int argc, char *argv[])
{
    int dim;
    int i;
    int j;
    double data[MAX_DIM][MAX_DIM];

    while (scanf("%d", &dim) == 1) {
        for (i = 0; i < dim; ++i) {
            for (j = 0; j < dim; ++j) {
                if (i == j) {
                    data[i][j] = 1;
                    continue;
                }

                scanf("%lf", &data[i][j]);
            }
        }

#if 0
        for (i = 0; i < dim; ++i) {
            for (j = 0; j < dim; ++j) {
                printf("%f ", data[i][j]);
            }
            printf("\n");
        }
#endif

        /*
         * Assume E[a,b] means exchange from current a to current b.
         *
         * We want to solve a,b,c,d, ... in the following equation:
         *
         * E[a,b] * E[b,c] * E[c,d] ... > 1.01
         *
         * log(E[a,b]) + log(E[b,c]) + log(E[c,d]) ... > log(1.01)
         * -log(E[a,b]) + -log(E[b,c]) + -log(E[c,d]) ... < -log(1.01)
         *
         * The solution becomes negative cycle in all pair shortest path problem.
         * It can be solved by Bellman-Ford algorithm.
         */

        find_arbitrage(data, dim);
    }

    return 0;
}
