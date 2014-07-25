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
         * The problem can be solved by the following DP:
         *
         * B[i, j] = badness value using chopstick from i ~ max, with j pairs.
         * b[i, j] = badness value when pairing i-th and j-th chopsticks.
         *
         * B[i, j] = | if (max - i) == j * 3
         *           |     B[i+3, j-1] + b[i, i+1] <- lock scenario.
         *           | else
         *           |     min(B[i+1, j], B[i+2, j-1] + b[i, i+1])
         *
         * start with B[max-3][1] = b[max-3][max-2]
         */

        /*
         * Initial condition
         */
        buf[chopstick_count - 3][1] = cal_badness(chopstick[chopstick_count - 2], chopstick[chopstick_count - 3]);

        for (pair_iter = 1; pair_iter <= pair_count; ++pair_iter) {
            chopstick_iter = chopstick_count - pair_iter * 3;

            /*
             * Lock scenario.
             */
            buf[chopstick_iter][pair_iter] =
                buf[chopstick_iter+3][pair_iter-1] +
                cal_badness(chopstick[chopstick_iter], chopstick[chopstick_iter+1]);

            --chopstick_iter;
            for (; chopstick_iter >= 0; --chopstick_iter) {
                buf[chopstick_iter][pair_iter] = min(
                    buf[chopstick_iter+1][pair_iter],
                    buf[chopstick_iter+2][pair_iter-1] + cal_badness(chopstick[chopstick_iter], chopstick[chopstick_iter+1])
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
