#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_CATEGORY    20
#define MAX_VALUE       1000


int main() {
    int i, j, num_case, required_val, element_count;
    int value[MAX_CATEGORY + 1];
    bool dp[MAX_VALUE + 1][MAX_CATEGORY + 1];

    scanf("%d", &num_case);
    while (num_case > 0) {
        scanf("%d%d", &required_val, &element_count);

        dp[0][0] = true;
        for (i = 1 ; i <= element_count ; i++) {
            dp[0][i] = true;
            scanf("%d", &(value[i]));
        }
        
        for (i = 1 ; i <= required_val ; i++)
            dp[i][0] = false;

        if (required_val == 0) {
            printf("YES\n"); 
            num_case--;
            continue;       
        }

        /**
         * Recursive formula:
         * 1. dp[i][j]: The status to check if it is possible to fill the package with "i" value
         *              by considering the "j" categories of objects.
         *                                      
         * 2. dp[i][j] = | dp[i][j - 1], if value[j] > i.
         *               | dp[i][j - 1] (bitwise or) dp[i - value[j]][j - 1], otherwise. 
         */
    
        for (i = 1 ; i <= required_val ; i++) {
            for (j = 1 ; j <= element_count ; j++) {
                if (value[j] > i) {
                    dp[i][j] = dp[i][j - 1];                
                } else {
                    dp[i][j] = dp[i][j - 1] | dp[i - value[j]][j - 1];
                }
            }
        }
    
        if (dp[required_val][element_count] == true) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }

        num_case--;
    }

    return 0;
}
