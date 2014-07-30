#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_COUNT_STONE     1000000
#define MAX_SIZE_SET        10


int main() {
    int i, j, prev_idx, count_stone, size_set;
    bool is_game_point, tmp;
    int set[MAX_SIZE_SET];    
    bool dp[MAX_COUNT_STONE + 1];    

    while(scanf("%d", &count_stone) != EOF) {
        scanf("%d", &size_set);

        for (i = 0 ; i < size_set ; i++)
            scanf("%d", &(set[i]));
    
        /**
         * Recursive formula:
         * 1. In the view of Stan, we can define two game states:
         *      true : Stan has chance to control the game in the future (force Ollie to select bad counts).
         *      false: Stan does not have chance to control the game.
         *
         * 2. Backtracking from the wining point is appropriate to decide the intermidate states step by step.
         *
         * 3. dp[i] = OR{-dp[i + set[j]]}, if (i + set[j]) < wining_position
         *          = false              , otherwise.
         */    

        dp[count_stone] = false;
        for (i = count_stone - 1 ; i >= 0 ; i--) {
            is_game_point = false;
            for (j = 0 ; j < size_set ; j++) {
                prev_idx = i + set[j];
                if (prev_idx <= count_stone) {
                    tmp = !dp[prev_idx];      
                    is_game_point |= tmp;
                }
            }
            dp[i] = is_game_point;
        } 

        if (dp[0] == true)
            printf("Stan wins\n");
        else
            printf("Ollie wins\n");
    }


    return 0;
}
