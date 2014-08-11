#include <stdio.h>

const int COIN_TYPE[] = { 1, 5, 10, 25, 50 };

enum {
    MAX_CENTS = 7489,
    MAX_TYPES = sizeof(COIN_TYPE) / sizeof(COIN_TYPE[0]),
};

int main()
{
    int coin;
    int ans[MAX_CENTS+1][MAX_TYPES];
    int value;
    int orig_value;
    int type;
    int x;

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

    for (value = 1; value <= COIN_TYPE[MAX_TYPES-1]; ++value) {
        ans[value][0] = 1;
    }

    for (type = 1; type < MAX_TYPES; ++type) {
        for (value = 1; value <= COIN_TYPE[MAX_TYPES-1]; ++value) {
            ans[value][type] = ans[value][type-1];

            x = value - COIN_TYPE[type];
            if (x >= 0) {
                ans[value][type] += ans[x][type];
            }
        }
    }
    value = COIN_TYPE[MAX_TYPES-1];

    while (scanf("%d", &coin) == 1) {
        if (value < coin) {
            orig_value = value;

            for (; value <= coin; ++value) {
                ans[value][0] = 1;
            }

            for (type = 1; type < MAX_TYPES; ++type) {
                for (value = orig_value; value <= coin; ++value) {
                    ans[value][type] = ans[value][type-1] + ans[value-COIN_TYPE[type]][type];
                }
            }

            value = coin;
        }

        printf("%d\n", ans[coin][MAX_TYPES-1]);
    }

    return 0;
}
