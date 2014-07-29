#include <stdio.h>

enum {
    MAX_COUNT = 10000,
    INVALID = -1,
};

struct Buffer {
    int cnt;
    int curr;
    int prev;
};

int min(int x, int y)
{
    return x > y ? y : x;
}

int max(int x, int y)
{
    return x > y ? x : y;
}

void swap(int **x, int **y)
{
    int *tmp = *x;
    *x = *y;
    *y = tmp;
}

int main()
{
    int count;
    int item[MAX_COUNT];
    int i;
    int ans;
    int cnt;

    int head[MAX_COUNT];
    int tail[MAX_COUNT];

    int buf1[MAX_COUNT];
    int buf2[MAX_COUNT];

    int *curr = buf1;
    int *prev = buf2;

    while (scanf("%d", &count) == 1) {
        for (i = 0; i < count; ++i) {
            scanf("%d", &item[i]);
        }

        /*
         * Buf[i, cnt] = Use 0 ~ i-th item, when count is cnt, the minimal value
         *               at the last item.
         *
         * Item[i]     = value of i-th item
         *
         * Buf[i, cnt] = min | Buf[i-1, cnt]
         *                   | Item[i] if Item[i] > Buf[j, cnt-1], j < i
         *
         * Buf[i, 1] = min(item[0] ~ item[i])
         */

        prev[0] = item[0];
        head[0] = 1;
        for (i = 1; i < count; ++i) {
            prev[i] = min(prev[i-1], item[i]);
            head[i] = 1;
        }

#if DEBUG
        printf("cnt = 1, prev = ");
        for (i = 0; i < count; ++i) {
            printf("%d ", prev[i]);
        }
        printf("\n");
#endif

        for (cnt = 2; cnt <= count/2+1; ++cnt) {
            for (i = cnt-1; i < count; ++i) {
                if (prev[i-1] != INVALID && prev[i-1] < item[i]) {
                    curr[i] = item[i];
                    head[i] = cnt;
                    break;
                }

                curr[i] = INVALID;
            }

            ++i;

            for (; i < count; ++i) {
                curr[i] = curr[i-1];
                if (prev[i-1] < item[i]) {
                    curr[i] = min(curr[i], item[i]);
                }
                head[i] = cnt;
            }

#if DEBUG
            printf("cnt = %d, curr = ", cnt);
            for (i = 0; i < count; ++i) {
                printf("%d ", curr[i]);
            }
            printf("\n");

            printf("cnt = %d, head = ", cnt);
            for (i = 0; i < count; ++i) {
                printf("%d ", head[i]);
            }
            printf("\n");
#endif

            swap(&curr, &prev);
        }

        /*
         * Do it again in reverse order.
         */

        prev[count-1] = item[count-1];
        tail[count-1] = 1;
        for (i = count-2; i >= 0; --i) {
            prev[i] = min(prev[i+1], item[i]);
            tail[i] = 1;
        }

#if DEBUG
        printf("cnt = 1, prev = ");
        for (i = 0; i < count; ++i) {
            printf("%d ", prev[i]);
        }
        printf("\n");
#endif

        for (cnt = 2; cnt <= count/2+1; ++cnt) {
            for (i = count-cnt; i >= 0; --i) {
                if (prev[i+1] != INVALID && prev[i+1] < item[i]) {
                    curr[i] = item[i];
                    tail[i] = cnt;
                    break;
                }

                curr[i] = INVALID;
            }

            --i;

            for (; i >= 0; --i) {
                curr[i] = curr[i+1];
                if (prev[i+1] < item[i]) {
                    curr[i] = min(curr[i], item[i]);
                }
                tail[i] = cnt;
            }

#if DEBUG
            printf("cnt = %d, curr = ", cnt);
            for (i = 0; i < count; ++i) {
                printf("%d ", curr[i]);
            }
            printf("\n");

            printf("cnt = %d, tail = ", cnt);
            for (i = 0; i < count; ++i) {
                printf("%d ", tail[i]);
            }
            printf("\n");
#endif

            swap(&curr, &prev);
        }

        /*
         * Calculate ans.
         */

        ans = 1;

        for (i = 0; i < count; ++i) {
            ans = max(ans, min(head[i], tail[i]));
        }
        ans = ans * 2 - 1;
        printf("%d\n", ans);

    }
    return 0;
}
