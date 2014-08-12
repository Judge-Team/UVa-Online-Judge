#include <stdio.h>

enum {
    MAX_NODE = 10000,
};

void print_tree(int *start, int *end)
{
    int root;
    int *split;

    if (start >= end) {
        return;
    }

    if (start + 1 == end) {
        printf("%d\n", *start);
        return;
    }

    root = *start;

    for (split = start + 1; split < end; ++split) {
        if (*split > root) {
            break;
        }
    }

    print_tree(start + 1, split);
    print_tree(split, end);

    printf("%d\n", root);
}

int main()
{
    int node[MAX_NODE];
    int node_count;

    node_count = 0;
    while (scanf("%d", &node[node_count]) == 1) {
        ++node_count;
    }

    print_tree(node, node + node_count);

    return 0;
}
