#include <stdio.h>

const int COIN_TYPE[] = { 5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000 };

enum {
    MAX_CENTS = 300 * 100,
    MAX_TYPES = sizeof(COIN_TYPE) / sizeof(COIN_TYPE[0]),
    ADJUST    = 5,
};

int main()
{
    int dollar;
    int cent;
    int coin;
    int adj_coin_type[MAX_TYPES];
    unsigned long long ans[MAX_CENTS / ADJUST + 1][MAX_TYPES];
    int value;
    int ans_bound;
    int type;
    int x;

    /*
     * Adjust coin type so that the smallest coin has value 1
     */
    adj_coin_type[0] = 1;
    for (type = 1; type < MAX_TYPES; ++type) {
        adj_coin_type[type] = COIN_TYPE[type] / ADJUST;
    }

    /*
     * coin_type[i] = value of i-th coin. Start from 1 cent.
     *
     * change[v, i] = Types of change for valuen cents, using coin from 0 ~ i.
     *
     * change[v, i] = change[v, i-1] + change[v-coin_type[i], i] (if v-coin_type[i] >= 0)
     *
     * With the following initial value:
     *
     * coin[0, i] = 1
     * coin[v, 0] = 1
     */

    for (type = 0; type < MAX_TYPES; ++type) {
        ans[0][type] = 1;
    }

    for (value = 1; value <= adj_coin_type[MAX_TYPES-1]; ++value) {
        ans[value][0] = 1;
    }

    for (type = 1; type < MAX_TYPES; ++type) {
        for (value = 1; value <= adj_coin_type[MAX_TYPES-1]; ++value) {
            ans[value][type] = ans[value][type-1];

            x = value - adj_coin_type[type];
            if (x >= 0) {
                ans[value][type] += ans[x][type];
            }
        }
    }
    ans_bound = adj_coin_type[MAX_TYPES-1];

    while (scanf("%d.%d", &dollar, &cent) == 2) {
        coin = (dollar * 100 + cent) / ADJUST;

        if (coin == 0) {
            break;
        }

        if (ans_bound < coin) {

            for (value = ans_bound; value <= coin; ++value) {
                ans[value][0] = 1;
            }

            for (type = 1; type < MAX_TYPES; ++type) {
                for (value = ans_bound; value <= coin; ++value) {
                    ans[value][type] = ans[value][type-1] + ans[value-adj_coin_type[type]][type];
                }
            }

            ans_bound = coin;
        }

        printf("%3d.%02d%17llu\n", dollar, cent, ans[coin][MAX_TYPES-1]);
    }

    return 0;
}
