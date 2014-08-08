#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>


#define MAX_STR_LENGTH  81
#define OP_INSERT       0
#define OP_DELETE       1
#define OP_REPLACE      2
#define DIRECT_UP       0
#define DIRECT_LEFT     1
#define DIRECT_UP_LEFT  2


typedef struct _Operation {
    int idx;
    char opcode;
} Operation;


int main() {
    int i, j, len_src, len_tge, min, distance;
    /* char direct; */
    char str_src[MAX_STR_LENGTH], str_tge[MAX_STR_LENGTH];
    int  dp[MAX_STR_LENGTH][MAX_STR_LENGTH];
    /*
    char map_direct[MAX_STR_LENGTH][MAX_STR_LENGTH];
    Operation list_ops[MAX_STR_LENGTH];
    */

    do {
        memset(str_src, 0, sizeof(char) * MAX_STR_LENGTH);
        memset(str_tge, 0, sizeof(char) * MAX_STR_LENGTH);
        if (scanf("%s%s", str_src + 1, str_tge + 1) == EOF)
            break;
        len_src = strlen(str_src + 1);
        len_tge = strlen(str_tge + 1);

        for (i = 0 ; i <= len_tge ; i++)
            dp[0][i] = i;
        for (i = 0 ; i <= len_src ; i++)
            dp[i][0] = i;

        for (i = 1 ; i <= len_src ; i++) {
            for (j = 1 ; j <= len_tge ; j++) {
                if (str_src[i] == str_tge[j]) {
                    dp[i][j] = dp[i - 1][j - 1];
                    /* map_direct[i][j] = DIRECT_UP_LEFT; */
                }
                else {
                    min = INT_MAX;

                    distance = dp[i][j - 1] + 1;
                    if (distance < min) {
                        min = distance;
                        /* direct = DIRECT_UP; */
                    }

                    distance = dp[i - 1][j] + 1;
                    if (distance < min) {
                        min = distance;
                        /* direct = DIRECT_LEFT; */
                    }

                    distance = dp[i - 1][j - 1] + 1;
                    if (distance < min) {
                        min = distance;
                        /* direct = DIRECT_UP_LEFT; */
                    }

                    dp[i][j] = min;
                    /* map_direct[i][j] = direct; */
                }
            }
        }

        /*
        for (i = 1 ; i <= len_src ; i++) {
            for (j = 1 ; j <= len_tge ; j++)
                printf("%3d ", dp[i][j]);
            printf("\n");
        }
        printf("\n");
        for (i = 1 ; i <= len_src ; i++) {
            for (j = 1 ; j <= len_tge ; j++) {
                if (map_direct[i][j] == DIRECT_UP)
                    printf("%3c ", '|');
                else if (map_direct[i][j] == DIRECT_LEFT)
                    printf("%3c ", '-');
                else if (map_direct[i][j] == DIRECT_UP_LEFT)
                    printf("%3c ", '\\');
            }
            printf("\n");
        }
        printf("\n");
        */

        printf("%d\n", dp[len_src][len_tge]);

    } while (true);

    return 0;
}
