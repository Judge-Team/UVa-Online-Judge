#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_CATEGORY    21
#define TARGET_PROFIT   1.01


int main() {
    int node_u, node_v, inter, category, step, length;
    bool found_ans;
    double new_weight;
    double weight[MAX_CATEGORY][MAX_CATEGORY];
    double dp[MAX_CATEGORY][MAX_CATEGORY][MAX_CATEGORY];
    char path[MAX_CATEGORY][MAX_CATEGORY][MAX_CATEGORY];
    char cycle[MAX_CATEGORY];

    while (scanf("%d", &category) != EOF) {
        
        for (node_u = 1 ; node_u <= category ; node_u++) {
            for (node_v = 1 ; node_v <= category ; node_v++) {
                if (node_u != node_v)
                    scanf("%lf", &(weight[node_u][node_v]));
                else
                    weight[node_u][node_v] = 1;
            }
        }

        for (step = 1 ; step <= category ; step++) {
            for (node_u = 1 ; node_u <= category ; node_u++) {
                for (node_v = 1 ; node_v <= category ; node_v++) {
                    if (step == 1) {
                        dp[node_u][node_v][step] = weight[node_u][node_v];
                        path[node_u][node_v][step] = node_u;
                    } else
                        dp[node_u][node_v][step] = 1;
                }
            }
        }

        found_ans = false;
        for (step = 2 ; step <= category ; step++) {
            for (inter = 1 ; inter <= category ; inter++) {
                for (node_u = 1 ; node_u <= category ; node_u++) {
                    for (node_v = 1 ; node_v <= category ; node_v++) {

                        new_weight = dp[node_u][inter][step - 1] * weight[inter][node_v];
                        if (new_weight > dp[node_u][node_v][step]) {
                            dp[node_u][node_v][step] = new_weight;
                            path[node_u][node_v][step] = inter;
                        }

                        if ((node_u == node_v) && (dp[node_u][node_v][step] > TARGET_PROFIT)) {
                            length = step;
                            found_ans = true;
                            //printf("%d %d %d %d\n", step, inter, node_u, node_v);
                            goto EXIT;
                        }
                    }
                }
            }         
        }

        EXIT:
        if (found_ans == true) {
            cycle[length] = node_v;
            while (length > 0) {
                node_v = path[node_u][node_v][length];
                cycle[length] = node_v;
                length--;
            }
            cycle[length] = node_u;

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
