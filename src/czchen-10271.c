#include <limits.h>
#include <stdio.h>
#include <string.h>

enum {
    MAX_PAIR = 1000 + 8,
    MAX_CHOPSTICK = 5000,
};

/*
 * Too large for auto variables.
 */
int chopstick[MAX_CHOPSTICK];
int buf[MAX_CHOPSTICK][MAX_PAIR + 1];

int min(int x, int y)
{
    return x > y ? y : x;
}

int cal_badness(int x, int y)
{
    int diff = x - y;
    return diff * diff;
}

int main(int argc, char *argv[])
{
    int case_count;
    int case_id;


    scanf("%d", &case_count);


    for (case_id = 0; case_id < case_count; ++case_id) {

        int pair_count;
        int pair_iter;

        int chopstick_count;
        int chopstick_iter;

        scanf("%d %d", &pair_count, &chopstick_count);
        pair_count += 8;

        for (chopstick_iter = 0; chopstick_iter < chopstick_count; ++chopstick_iter) {
            scanf("%d", &chopstick[chopstick_iter]);
        }

        /*
         * B[i, j] = badness value using chopstick from 0 ~ i, with j pairs.
         * b[i, j] = badness value when pairing i-th and j-th chopsticks.
         *
         * B[i, j] = min | B[i-1, j]
         *               | B[i-2, j-1] + b[i-1, i]
         */

        /*
         * Fill all buf[x * 2][x] since it only contains one valid cases.
         */
        memset(buf, 0, sizeof(buf));
        for (pair_iter = 1; pair_iter <= pair_count; ++pair_iter) {
            buf[pair_iter * 2][pair_iter] =
                cal_badness(chopstick[pair_iter * 2 - 2], chopstick[pair_iter * 2 - 1]) +
                buf[(pair_iter - 1) * 2][pair_iter - 1];
        }

        /*
         * B[i, j] = min | B[i-1, j]
         *               | B[i-2, j-1] + b[i-1, i]
         */
        for (pair_iter = 1; pair_iter <= pair_count; ++pair_iter) {
            for (chopstick_iter = pair_iter * 2 + 1; chopstick_iter < chopstick_count; ++chopstick_iter) {
                buf[chopstick_iter][pair_iter] = min(
                    buf[chopstick_iter - 1][pair_iter],
                    buf[chopstick_iter - 2][pair_iter - 1] + cal_badness(chopstick[chopstick_iter -1], chopstick[chopstick_iter])
                );
            }
        }

        printf("%d\n", buf[chopstick_count - 1][pair_count]);
    }

    return 0;
}
