#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_CATEGORY    21
#define TARGET_PROFIT   1.01


int main() {
    int u, v, inter, category, step, length;
    bool found_ans;
    double new_weight;
    double weight[MAX_CATEGORY][MAX_CATEGORY];
    double dp[MAX_CATEGORY][MAX_CATEGORY][MAX_CATEGORY];
    char path[MAX_CATEGORY][MAX_CATEGORY][MAX_CATEGORY];
    char cycle[MAX_CATEGORY];

    while (scanf("%d", &category) != EOF) {
        
        for (u = 1 ; u <= category ; u++) {
            for (v = 1 ; v <= category ; v++) {
                if (u != v)
                    scanf("%lf", &(weight[u][v]));
                else
                    weight[u][v] = 1;
            }
        }

        for (step = 1 ; step <= category ; step++) {
            for (u = 1 ; u <= category ; u++) {
                for (v = 1 ; v <= category ; v++) {
                    if (step == 1) {
                        dp[step][u][v] = weight[u][v];
                        path[step][u][v] = u;
                    } else
                        dp[step][u][v] = -1;
                }
            }
        }

        /**
         * Recursive formula:
         * 1. dp[num][u][v]   : The maximum profit from currency "u" to currency "v" with "num" transition steps.
         * 2. path[num][u][v] : Under the above profit, the predecessor of currency "v".
         * 
         * 3. dp[num][u][v] = Max{dp[num - 1][u][inter] * weight[inter][v] | 1 <= k <= total_currency}
         */

        found_ans = false;
        for (step = 2 ; step <= category ; step++) {
            for (inter = 1 ; inter <= category ; inter++) {
                for (u = 1 ; u <= category ; u++) {
                    for (v = 1 ; v <= category ; v++) {

                        new_weight = dp[step - 1][u][inter] * weight[inter][v];
                        if (new_weight > dp[step][u][v]) {
                            dp[step][u][v] = new_weight;
                            path[step][u][v] = inter;
                        }

                        if ((u == v) && (dp[step][u][v] > TARGET_PROFIT)) {
                            length = step;
                            found_ans = true;
                            goto EXIT;
                        }
                    }
                }
            }         
        }

        EXIT:
        if (found_ans == true) {
            cycle[length] = v;
            while (length >= 0) {
                v = path[length][u][v];
                cycle[length - 1] = v;
                length--;
            }

            length++;
            while (length < step) {
                printf("%d ", cycle[length]);
                length++;
            }
            printf("%d\n", cycle[length]);
        } else {
            printf("no arbitrage sequence exists\n");
        }
    }

    return 0;
}
