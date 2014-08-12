#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_CITY_COUNT 50
#define MAX_TRANSITION_COUNT 19


int main() {
    int i, j, k, step, required_step, num_city, num_road;
    char new_weight;
    bool is_win;
    char weight[MAX_CITY_COUNT][MAX_CITY_COUNT];
    char dp[MAX_CITY_COUNT][MAX_CITY_COUNT];

    while (true) {

        scanf("%d%d%d", &num_city, &num_road, &required_step);
        if ((num_city == 0) && (num_road == 0) && (required_step == 0)) {
            break;
        }
        
        required_step -= 1;

        for (i = 0 ; i < num_city ; i++) {
            for (j = 0 ; j < num_city ; j++) {
                weight[i][j] = 0;
                dp[i][j] = 0;
            }
        }

        for (k = 0 ; k < num_road ; k++) {
            scanf("%d%d", &i, &j);
            weight[i][j] = -1;
            if (i == 0) {
                dp[1][j] = -1;
            }
        }    

        is_win = false;
        for (step = 2 ; step < MAX_CITY_COUNT ; step++) {
            for (i = 0 ; i < num_city ; i++) {
                for (j = 0 ; j < num_city ; j++) {
                    new_weight = dp[step - 1][i] + weight[i][j];
                    if (new_weight < dp[step][j]) {
                        dp[step][j] = new_weight;
                    }
                }
            }

            if ((step >= required_step) && (dp[step][num_city - 1] == -step)) {
                printf("%d\n", step + 1);
                is_win = true;
                break;
            } else if ((step == MAX_TRANSITION_COUNT) && (dp[step][num_city - 1] != -step)) {
                break;
            }
        }
        
        if (is_win == false) {
            printf("LOSER\n");
        }
    }

    return 0;
}
