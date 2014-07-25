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

        int prev_chopstick;
        int curr_chopstick;
        int badness[MAX_CHOPSTICK - 1];

        scanf("%d %d", &pair_count, &chopstick_count);
        pair_count += 8;

        scanf("%d", &prev_chopstick);
        for (chopstick_iter = 0; chopstick_iter < chopstick_count-1; ++chopstick_iter) {
            scanf("%d", &curr_chopstick);
            badness[chopstick_iter] = cal_badness(prev_chopstick, curr_chopstick);
            prev_chopstick = curr_chopstick;
        }

#if DEBUG
        printf("case_id = %d, pair_count = %d, chopstick_count = %d\n", case_id, pair_count, chopstick_count);
#endif

        /*
         * The problem can be solved by the following DP:
         *
         * B[c, p] = badness value using chopstick from i ~ max, with j pairs.
         * b[c, p] = badness value when pairing i-th and j-th chopsticks.
         *
         * B[c, p] = | if (max-c) == p * 3
         *           |     B[c+3, p-1] + b[c, c+1] <- lock scenario.
         *           | else
         *           |     min(B[c+1, p], B[c+2, p-1] + b[c, c+1])
         *
         * start with B[max-3][1] = b[max-2][max-3]
         */

        /*
         * Initial condition
         */
        buf[chopstick_count-3][1] = badness[chopstick_count-3];

        for (pair_iter = 1; pair_iter <= pair_count; ++pair_iter) {
            chopstick_iter = chopstick_count - pair_iter * 3;

            /*
             * Lock scenario.
             */
            buf[chopstick_iter][pair_iter] =
                buf[chopstick_iter+3][pair_iter-1] + badness[chopstick_iter];

            --chopstick_iter;
            for (; chopstick_iter >= 0; --chopstick_iter) {
                buf[chopstick_iter][pair_iter] = min(
                    buf[chopstick_iter+1][pair_iter],
                    buf[chopstick_iter+2][pair_iter-1] + badness[chopstick_iter]
                );
            }
        }


#if DEBUG
        printf("### final buf ###\n");
        for (chopstick_iter = 0; chopstick_iter < chopstick_count; ++chopstick_iter) {
            printf("[%d]\t", chopstick_iter);
            for (pair_iter = 0; pair_iter <= pair_count; ++pair_iter) {
                printf("%d\t", buf[chopstick_iter][pair_iter]);
            }
            printf("\n");
        }
#endif

        printf("%d\n", buf[0][pair_count]);
    }

    return 0;
}
