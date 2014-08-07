#include <stdio.h>
#include <stdlib.h>


#define MAX_K       1009
#define MAX_N       5000
#define Min(a, b)   (((a) < (b)) ? (a) : (b))


int knap_dp[MAX_K][MAX_N];


/* Hint function to guid the qsort library. */
int compare(const void *p_src, const void *p_tge) {

    if (*((int*)p_src) == *((int*)p_tge))
        return 0;
    else {
        if (*((int*)p_src) < *((int*)p_tge))
            return 1;
        else
            return -1;
    }
}


int main() {
    int count_round, i, j, idx_i, idx_j_inter, idx_j_consec;
    int total_round, val_k, val_n, val_pair, base_idx;
    int knap_val[MAX_N];
    int knap_pair[MAX_N];

    scanf("%d", &total_round);

    for (i = 0 ; i < MAX_N ; i++)
        knap_dp[0][i] = 0;

    for (count_round = 0 ; count_round < total_round ; count_round++) {

        /* Prepare the value of each chopstick. */
        scanf("%d%d", &val_k, &val_n);
        for (i = 0 ; i < val_n ; i++)
            scanf("%d", &(knap_val[i]));
        qsort(knap_val, val_n, sizeof(int), compare);

        /* Prepare the badness value of each pair of chopsticks. */
        for (i = 2 ; i < val_n ; i++) {
            val_pair = knap_val[i] - knap_val[i - 1];
            val_pair *= val_pair;
            knap_pair[i - 1] = val_pair;
        }

        /*
         *   Recursive Formula:
         *   1. Let i be the number of selected pairs.
         *   2. Let j be the index of a chopstick pair.
         *   3.
         *      dp[i, j] = Min{badness[j] + dp[i - 1][j - 3], badness[j] + dp[i - 1][j - 2]} if (i == boundary)
         *               = Min{dp[i][j - 1], badness[j] + dp[i - 1][j - 2]}                  if (i > boundary)
         */
        for (i = 1 ; i <= val_k + 8 ; i++) {
            base_idx = 3 * i - 2;

            idx_i = i - 1;
            idx_j_inter = base_idx - 3;
            idx_j_consec = base_idx - 2;
            if (idx_i < 0) idx_i = 0;
            if (idx_j_inter < 0) idx_j_inter = 0;
            if (idx_j_consec < 0) idx_j_consec = 0;
            knap_dp[i][base_idx] = Min(knap_pair[base_idx] + knap_dp[idx_i][idx_j_inter],
                                       knap_pair[base_idx] + knap_dp[idx_i][idx_j_consec]);

            for (j = base_idx + 1; j <= val_n - 2; j++) {
                idx_i = i - 1;
                if (idx_i < 0) idx_i = 0;
                knap_dp[i][j] = Min(knap_dp[i][j - 1], knap_pair[j] + knap_dp[i - 1][j - 2]);
            }
        }

        printf("%d\n", knap_dp[val_k + 8][val_n - 2]);
    }

    return 0;
}
