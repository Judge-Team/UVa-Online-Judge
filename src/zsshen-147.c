#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef unsigned long long ullong;


#define MAX_QUANTITY 30000
#define MAX_CATEGORY 11


int main() {
    int i, j, idx, major, minor;
    ullong dp[MAX_QUANTITY + 1][MAX_CATEGORY + 1];
    ullong coin[] = {-1, 5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};

    /**
     * Recursive formula:
     * 1. dp[i][j] : The number of ways to change "i" dollars using coins from "1" to "j" categories.
     * 2. dp[i][j] = | dp[i][j - 1], if coin[j] > i.
     *               | (The value of category "j" is larger than "i" dollar.)
     *               |
     *               | dp[i][j - 1] + dp[i - coin[j]][j], otherwise.      
     *               | (Two ways to change: a. Do not use category "j". b. Use category "j" at least once.)
     */

    dp[0][0] = 1;
    for (i = 1 ; i <= MAX_QUANTITY ; i++)
        dp[i][0] = 0;
    for (i = 1 ; i <= MAX_CATEGORY ; i++)
        dp[0][i] = 1;

    for (i = 1 ; i <= MAX_QUANTITY ; i++) {
        for (j = 1 ; j <= MAX_CATEGORY ; j++) {
            if (coin[j] > i)
                dp[i][j] = dp[i][j - 1];
            else
                dp[i][j] = dp[i][j - 1] + dp[i - coin[j]][j];
        }
    }

    while (true) {
        scanf("%d.%d", &major, &minor);
        idx = major * 100+ minor;
        if (idx == 0)
            break;
        printf("%3d.%02d%17llu\n", major, minor, dp[idx][MAX_CATEGORY]);        
    }

    return 0;
}



