#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static const int BUF_SIZE = 1024;
static const char* STAT_MSG[4] =
{
    "SIMPLE",
    "FULLY-GROWN",
    "MUTAGENIC",
    "MUTANT"
};
enum {
    STAT_SIMPLE = 0,
    STAT_FULLY_GROWN,
    STAT_MUTAGENIC,
    STAT_MUTANT
};


int main()
{
    int dummy;
    int num_case;
    dummy = scanf("%d", &num_case);

    char str[BUF_SIZE];
    int idx_case = 0;
    while (idx_case < num_case) {
        dummy = scanf("%s", str);

        int len = strlen(str);
        short dp[len][len];

        /*
        // Object Definition:
        //  dp[i][j] : The state for the substring(i, j).
        //
        // State Transition Function:
        //
        //  dp[i][i] = SIMPLE, for i <- 0 to length.
        //
        //  dp[i][i + 1] = MUTANT, for i <- 0 to (length - 1).
        //
        //             | FULLY-GROWN, if (dp[i][j - 2] != MUTANT) &&
        //             |              (string[j] == 'B' && string[j - 2] == 'A').
        //             |
        //  dp[i][j] = | MUTAGENIC, if (dp[i + 1][j - 1] != MUTANT) &&
        //             |              (string[i] == 'B' && string[j] == 'A').
        //             |
        //             | MUTANT, otherwise.
        */

        int i;
        for (i = 0 ; i < len ; ++i)
            dp[i][i] = (str[i] == 'A')? STAT_SIMPLE : STAT_MUTANT;
        for (i = 0 ; i < len - 1 ; ++i)
            dp[i][i + 1] = STAT_MUTANT;

        int l;
        for (l = 2 ; l < len ; ++l) {
            for (i = 0 ; i < len - l ; ++i) {
                int j = i + l;
                if (dp[i][j - 2] != STAT_MUTANT &&
                    str[j] == 'B' && str[j - 1] == 'A')
                    dp[i][j] = STAT_FULLY_GROWN;

                else if (dp[i + 1][j - 1] != STAT_MUTANT &&
                    str[i] == 'B' && str[j] == 'A')
                    dp[i][j] = STAT_MUTAGENIC;

                else
                    dp[i][j] = STAT_MUTANT;
            }
        }

        printf("%s\n", STAT_MSG[dp[0][len - 1]]);
        ++idx_case;
    }

    return 0;
}