#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define BUF_SIZE    (2000)


int ComputeCost(char* str, int len)
{
    int cost[len][len];
    bool palin[len][len];

    int i;
    for (i = 0 ; i < len ; ++i) {
        cost[i][i] = 0;
        palin[i][i] = true;
    }

    int l;
    for (l = 1 ; l < len ; ++l) {
        for (i = 0 ; i < len - l ; ++i) {
            int j = i + l;

            bool is_palin;
            if (i + 1 <= j - 1)
                is_palin = (str[i] == str[j]) && palin[i + 1][j - 1];
            else
                is_palin = (str[i] == str[j]);

            if (is_palin) {
                cost[i][j] = 0;
                palin[i][j] = true;
                continue;
            }

            int min;
            if (str[i] != str[j]) {
                if (i + 1 <= j - 1)
                    min = cost[i + 1][j - 1] + 1;
                else
                    min = 1;
            } else
                min = cost[i + 1][j - 1];

            if (cost[i + 1][j] + 1 < min)
                min = cost[i + 1][j] + 1;
            if (cost[i][j - 1] + 1 < min)
                min = cost[i][j - 1] + 1;

            cost[i][j] = min;
            palin[i][j] = false;
        }
    }

    return cost[0][len - 1];
}


int main()
{
    int num_case;
    scanf("%d", &num_case);

    char str[BUF_SIZE];
    int idx_case = 1;
    while (idx_case <= num_case) {
        scanf("%s", str);

        int len = strlen(str);
        int ans;
        if (len <= 1)
            ans = 0;
        else
            ans = ComputeCost(str, len);
        printf("Case %d: %d\n", idx_case, ans);

        ++idx_case;
    }

    return 0;
}
