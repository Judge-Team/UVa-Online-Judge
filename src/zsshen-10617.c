#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static const BUF_SIZE = 2048;

#define MAX(a, b) (((a) > (b))? (a) : (b))

/* ANCI C limitation.
inline MAX(int a, int b)
{
    return (a > b)? a : b;
}
*/


int LongestPalindromicSequence(char* str, int len)
{
    /*
    // Object Definition:
    //  dp[i][j] : The length of the longest palindromic subsequence for the
    //             substring(i, j).
    //
    // Optimal Function:
    //            | dp[i + 1][j - 1] + 2, if string[i] == string[j].
    // dp[i][j] = |
    //            | MAX{dp[i + 1][j], dp[i][j - 1]}, Otherwise.
    */

    short dp[len][len];

    int i;
    for (i = 0 ; i < len ; ++i)
        dp[i][i] = 1;

    int l;
    for (l = 1 ; l < len ; ++l) {
        for (i = 0 ; i < len - l ; ++i) {
            int j = i + l;
            if (str[i] == str[j]) {
                if (i + 1 <= j - 1)
                    dp[i][j] = 2 + dp[i + 1][j - 1];
                else
                    dp[i][j] = 2;
            } else
                dp[i][j] = MAX(dp[i + 1][j], dp[i][j - 1]);
        }
    }

    return dp[0][len - 1];
}


int main()
{
    int dummy;
    char garbage;
    int num_case;
    dummy = scanf("%d%c", &num_case, &garbage);

    char str[BUF_SIZE];
    int idx_case = 0;
    while (idx_case < num_case) {
        char* rtn = fgets(str, BUF_SIZE, stdin);
        int len = strlen(str);
        --len;

        int ans;
        if (len <= 1)
            ans = len;
        else
            ans = LongestPalindromicSequence(str, len);

        printf("%d\n", ans);
        ++idx_case;
    }

    return 0;
}