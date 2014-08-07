#include <stdio.h>

enum {
    MAX_NODE = 250,
};

int min(int x, int y)
{
    return x > y ? y : x;
}

#define COST(i,j) (cost[(j)+1] - cost[(i)])

int main(int argc, char *argv[])
{
    int node_count;
    int tree[MAX_NODE][MAX_NODE];
    int cost[MAX_NODE+1];
    int i;
    int start;
    int size;
    int split;

    while (scanf("%d", &node_count) == 1) {
        cost[0] = 0;
        for (i = 0; i < node_count; ++i) {
            scanf("%d", &cost[i+1]);
            tree[i][i] = 0;
        }


#if DEBUG
        printf("===============================\n");
        printf("start new buffer with size %d\n", node_count);
        for (i = 0; i < node_count; ++i) {
            for (j = 0; j < node_count; ++j) {
                printf("%d\t", tree[i][j]);
            }
            printf("\n");
        }

        printf("cost\n");
        for (i = 0; i < node_count+1; ++i) {
            printf("%d ", cost[i]);
        }
        printf("\n");
#endif

        /*
         * tree(i, j) = minimal binary search tree between i ~ j (inclusive)
         * cost(i, j) = total cost between i ~ j (inclusive)
         *
         * tree(i, j) = min { tree(i, k) + cost(i, k) + tree(k, j) + cost(k, j) }
         */

        for (i = 1; i < node_count+1; ++i) {
            cost[i] += cost[i-1];
        }

#if DEBUG
        printf("accumulated cost\n");
        for (i = 0; i < node_count+1; ++i) {
            printf("%d ", cost[i]);
        }
        printf("\n");
#endif

        for (size = 2; size <= node_count; ++size) {
            for (start = 0; start+size <= node_count; ++start) {
                tree[start][start+size-1] = min(
                    tree[start+1][start+size-1] + COST(start+1, start+size-1),
                    tree[start][start+size-2] + COST(start, start+size-2)
                );

                for (split = start+1; split < start+size-1; ++split) {
                    tree[start][start+size-1] = min(
                        tree[start][start+size-1],
                        tree[start][split-1] + COST(start, split-1) +
                        tree[split+1][start+size-1] + COST(split+1, start+size-1)
                    );
                }
            }
#if DEBUG
            printf("start new buffer with size %d\n", node_count);
            for (i = 0; i < node_count; ++i) {
                for (j = 0; j < node_count; ++j) {
                    printf("%d\t", tree[i][j]);
                }
                printf("\n");
            }
#endif
        }

        printf("%d\n", tree[0][node_count-1]);
    }
    return 0;
}
