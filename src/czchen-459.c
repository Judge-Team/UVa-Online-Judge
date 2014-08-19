#include <stdio.h>
#include <string.h>

enum {
    MAX_NODE = 26,
    MAX_LINE_LEN = 5,
};

static void connect(char *node_leader, char x, char y)
{
    int curr;
    char tmp;
    char leader;

    curr = x;
    while (node_leader[curr] != curr) {
        curr = node_leader[curr];
    }
    leader = curr;

    curr = x;
    while (node_leader[curr] != curr) {
        tmp = node_leader[curr];
        node_leader[curr] = leader;
        curr = tmp;
    }

    curr = y;
    while (node_leader[curr] != curr) {
        tmp = node_leader[curr];
        node_leader[curr] = leader;
        curr = tmp;
    }
    node_leader[curr] = leader;
}

int main()
{
    int cases;
    char nodes;

    char line[MAX_LINE_LEN];

    int i;
    char node_leader[MAX_NODE];
    int ans;

    scanf("%d\n", &cases);

    for (; cases > 0; --cases) {
        /*
         * Use disjoint-set data structure to store connect component.
         */
        fgets(line, sizeof(line), stdin);
        nodes = line[0] - 'A' + 1;

        for (i = 0; i < nodes; ++i) {
            node_leader[i] = i;
        }

        for (;;) {
            line[0] = 0;
            fgets(line, sizeof(line), stdin);
            if (strlen(line) <= 1) {
                break;
            }
            connect(node_leader, line[0] - 'A', line[1] - 'A');
        }

#if DEBUG
        for (i = 0; i < nodes; ++i) {
            printf("%c ", node_leader[i] + 'A');
        }
        printf("\n");
#endif

        ans = 0;
        for (i = 0; i < nodes; ++i) {
            if (node_leader[i] == i) {
                ++ans;
            }
        }

        printf("%d\n", ans);
        if (cases != 1) {
            printf("\n");
        }
    }

    return 0;
}
