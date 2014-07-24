#include <stdio.h>
#include <string.h>

enum {
    MAX_LEN = 1000,
    MAX_CUT = 50,
};

int min(int x, int y)
{
    return x > y ? y : x;
}

int main(int argc, char *argv[])
{
    int len;
    int cut_count;
    int buf[MAX_CUT + 1][MAX_CUT + 1];
    int cut[MAX_CUT + 2];

    int i;
    int stick_size;
    int start;
    int cut_point;

    while (scanf("%d", &len) == 1) {
        if (len == 0) {
            break;
        }

        scanf("%d", &cut_count);

        for (i = 0; i < cut_count; ++i) {
            scanf("%d", &cut[i + 1]);
        }
        cut[0] = 0;
        cut[cut_count + 1] = len;
        memset(buf, 0, sizeof(buf));

        /*
         * The formula:
         *
         * cut[i, j] = cost[i, j] + min { cut[i, k] + cut[k + 1, j] }
         */

        for (stick_size = 2; stick_size <= cut_count + 1; ++stick_size) {
            for (start = 0; start + stick_size <= cut_count + 1; ++start) {
                int fix_cost = cut[start + stick_size] - cut[start];
                int dyn_cost = buf[start][start + 1] + buf[start + 1][start + stick_size];

                for (cut_point = start + 2; cut_point < start + stick_size; ++cut_point) {
                    dyn_cost = min(dyn_cost, buf[start][cut_point] + buf[cut_point][start + stick_size]);
                }

                buf[start][start + stick_size] = fix_cost + dyn_cost;
            }
        }

        printf("The minimum cutting is %d.\n", buf[0][cut_count + 1]);
    }

}
