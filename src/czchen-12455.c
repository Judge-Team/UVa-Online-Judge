#include <stdio.h>
#include <string.h>

enum {
    MAX_LENGTH = 1000,
    MAX_BAR = 20,
};

static int update_buf(char *buf, int *bar, int bar_idx, int length)
{
    int i;

    for (i = length - bar[bar_idx]; i >= 0; --i) {
        if (buf[i]) {
            buf[i + bar[bar_idx]] = 1;
            if (buf[length]) {
                return 1;
            }
        }
    }

    return 0;
}

int main()
{
    int cases;

    int length;

    int bar_cnt;
    int bar[MAX_BAR];

    char buf[MAX_LENGTH+1];

    int i;
    int res;

    scanf("%d", &cases);
    for (; cases > 0; --cases) {
        scanf("%d", &length);
        scanf("%d", &bar_cnt);
        for (i = 0; i < bar_cnt; ++i) {
            scanf("%d", &bar[i]);
        }

        /*
         * buf[length, x] = | 1 if bar 0 ~ x can combine to length
         *                  | 0 otherwise
         *
         * bar[i] = length of bar i
         *
         * Then:
         *
         *     buf[length, x] = max { buf[length-bar[x], x-1], buf[length, x-1] }
         *
         * With the following initial conditions:
         *
         *     buf[0, 0] = 1
         *     buf[bar[0], 0] = 1
         */

        memset(buf, 0, sizeof(buf[0]) * (length + 1));
        buf[0] = 1;
        buf[bar[0]] = 1;
        res = 0;

        if (length == 0 || length == bar[0]) {
            res = 1;

        } else {
            for (i = 1; i < bar_cnt; ++i) {
                res = update_buf(buf, bar, i, length);
                if (res) {
                    break;
                }
            }
        }

        if (res) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}
