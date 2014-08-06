#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>


#define MAX_REST_COUNT  201
#define MAX_DEPOT_COUNT 31


typedef struct _Position {
    int idx_begin;
    int idx_end;
    int idx_center;
} Position;


int main() {
    int i, j, k, l, count_rest, count_depot, count_round, min, sum, pivot;
    Position range;
    int location[MAX_REST_COUNT];    
    int dp[MAX_DEPOT_COUNT][MAX_REST_COUNT];
    Position ans[MAX_DEPOT_COUNT];
    Position dispatch[MAX_DEPOT_COUNT][MAX_REST_COUNT];

    count_round = 1;
    while (true) {
        scanf("%d%d", &count_rest, &count_depot);
        if ((count_rest == 0) && (count_depot == 0))
            break;

        for (i = 1 ; i <= count_rest ; i++)
            scanf("%d", &(location[i]));
                  
        /**
         * Recursive formula:
         * 1. dp[i][j] : The minimum cost when "i" depots and "j" restaurants are considered. 
         * 2. dp[i][j] = MIN{dp[i - 1][k - 1] + cost[k][j] | i <= k <= j}.
         *
         *               where cost[k][j] = SUM{ABS(d[l] - d[pivot]) | k <= l <= j}.
         *                 and pivot = (j - k) / 2 + k.
         */

        for (i = 1 ; i <= count_rest ; i++) {
            pivot = (i - 1) / 2 + 1;
            sum = 0;
            for (j = 1 ; j <= i ; j++)
                sum += abs(location[j] - location[pivot]);
            dp[1][i] = sum;
            dispatch[1][i].idx_begin = 1;
            dispatch[1][i].idx_end = i;
            dispatch[1][i].idx_center = pivot;
        }
        
        for (i = 2 ; i <= count_depot ; i++) {
            for (j = 1 ; j <= count_rest ; j++) {

                min = INT_MAX;
                for (k = i ; k <= j ; k++) {
                    sum = 0;
                    pivot = (j - k) / 2 + k;
                    for (l = k ; l <= j ; l++)
                        sum += abs(location[l] - location[pivot]);
                    sum += dp[i - 1][k - 1];
                    /*printf("dp[%3d][%3d] + cost[%3d][%3d] = %3d\n", i - 1, k - 1, k, j, sum);*/
                    if (sum < min) {
                        min = sum;
                        range.idx_begin = k;
                        range.idx_end = j;
                        range.idx_center = pivot;
                    }    
                }

                if (min != INT_MAX) {
                    dp[i][j] = min;
                    dispatch[i][j] = range;
                }
            }
        }
    
        printf("Chain %d\n", count_round);
        pivot = count_rest;
        for (i = count_depot ; i >= 1 ; i--) {
            ans[i].idx_begin = dispatch[i][pivot].idx_begin;
            ans[i].idx_end = dispatch[i][pivot].idx_end;
            ans[i].idx_center = dispatch[i][pivot].idx_center;
            pivot = ans[i].idx_begin - 1;
        }
        for (i = 1 ; i <= count_depot ; i++) {
            if ((ans[i].idx_end - ans[i].idx_begin) != 0)
                printf("Depot %d at restaurant %d serves restaurants %d to %d\n", i, 
                        ans[i].idx_center, ans[i].idx_begin, ans[i].idx_end);
            else
                printf("Depot %d at restaurant %d serves restaurant %d\n", i, 
                        ans[i].idx_center, ans[i].idx_begin);
        }
        printf("Total distance sum = %d\n\n", dp[count_depot][count_rest]);
        count_round++;
    }

    return 0;
}
