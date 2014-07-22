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

int has_negative_cycle(int start, double data[MAX_DIM][MAX_DIM], int dim)
{
    int step;
    int dest;
    int i;

    struct BellmanFord buf1[MAX_DIM];
    struct BellmanFord buf2[MAX_DIM];

    struct BellmanFord *curr;
    struct BellmanFord *next;
    struct BellmanFord *tmp;

    memset(buf1, 0, sizeof(buf1));

    for (dest = 0; dest < dim; ++dest) {
        buf1[dest].cost = data[start][dest];
        buf1[dest].path_len = 1;
        buf1[dest].path[0] = dest;
    }

    curr = buf1;
    next = buf2;

    for (step = 1; step <= dim; ++step) {
        for (dest = 0; dest < dim; ++dest) {
            next[dest] = curr[dest];
            for (i = 0; i < dim; ++i) {
                if (next[dest].cost > curr[i].cost + data[i][dest]) {
                    next[dest] = curr[i];
                    next[dest].cost += data[i][dest];
                    ++next[dest].path_len;
                    next[dest].path[curr[i].path_len] = dest;
                }
            }
        }

        tmp = curr;
        curr = next;
        next = tmp;

#if 0
        for (i = 0; i < dim; ++i) {
            int j;
            printf("cost = %f, ", curr[i].cost);
            for (j = 0; j < curr[i].path_len; ++j) {
                printf("%d -> ", curr[i].path[j]);
            }
            printf("\n");
        }
#endif

        if (curr[start].cost < 0) {
            printf("%d", start + 1);
            for (i = 0; i < curr[start].path_len; ++i) {
                printf(" %d", curr[start].path[i] + 1);
            }
            printf("\n");
            return 1;
        }
    }

    return 0;
}

void find_arbitrage(double data[MAX_DIM][MAX_DIM], int dim)
{
    int i;
    for (i = 0; i < dim; ++i) {
        int ret = has_negative_cycle(i, data, dim);
        if (ret) {
            return;
        }
    }
    printf("no arbitrage sequence exists\n");
}

int main(int argc, char *argv[])
{
    int dim;
    int i;
    int j;
    double data[MAX_DIM][MAX_DIM];

    while (scanf("%d", &dim) == 1) {
        memset(data, 0, sizeof(data));
        for (i = 0; i < dim; ++i) {
            for (j = 0; j < dim; ++j) {
                if (i == j) {
                    continue;
                }

                scanf("%lf", &data[i][j]);

                data[i][j] = -log(data[i][j]);
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
         * E[a,b] * E[b,c] * E[c,d] ... > 1
         * log(E[a,b]) + log(E[b,c]) + log(E[c,d]) ... > log(1) = 0
         * -log(E[a,b]) + -log(E[b,c]) + -log(E[c,d]) ... < 0
         *
         * The solution becomes negative cycle in all pair shortest path problem.
         * It can be solved by Bellman-Ford algorithm.
         */

        find_arbitrage(data, dim);
    }

    return 0;
}
