#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

const int MAX_NORTH_SOUTH = 100;
const int MAX_EAST_WEST   = 100;

const int INPUT_SIZE = 1000;

int main(int argc, char *argv[])
{
    int count;

    int east_west;
    int north_south;

    unsigned long long map[MAX_EAST_WEST][MAX_NORTH_SOUTH];
    char block[MAX_EAST_WEST][MAX_NORTH_SOUTH];
    char input[INPUT_SIZE];

    int current_east_west;
    int current_north_south;
    char *token;

    int i;
    int j;

    scanf("%d", &count);

    for (; count > 0; --count) {
        memset(block, 0, sizeof(block));

        scanf("%d %d\n", &east_west, &north_south);

        for (i = 0; i < east_west; ++i) {
            fgets(input, sizeof(input), stdin);

#if DEBUG
            printf("input: %s", input);
#endif

            token = strtok(input, " ");
            current_east_west = strtol(token, NULL, 0);

            while ((token = strtok(NULL, " ")) != NULL) {
                current_north_south = strtol(token, NULL, 0);
                block[current_east_west - 1][current_north_south - 1] = 1;
            }
        }

        /*
         * map(i, j) = | map(i-1, j) + map(i, j-1)  if (i, j) is not blocked
         *             | 0                          if (i, j) is blocked
         *
         * map(0, x) = | map(0, x-1)  if (0, x-1) is not blocked
         *             | 0            if (0, x-1) is blocked
         *
         * map(x, 0) = | map(x-1, 0)  if (x-1, 0) is not blocked
         *             | 0            if (x-1, 0) is blocked
         *
         * map(0, 0) = | 1  if (0, 0) is not blocked
         *             | 0  if (0, 0) is blocked
         */

        if (block[0][0]) {
            map[0][0] = 0;
        } else {
            map[0][0] = 1;
        }

        for (i = 1; i < east_west; ++i) {
            if (block[i][0]) {
                map[i][0] = 0;
            } else {
                map[i][0] = map[i - 1][0];
            }
        }

        for (i = 1; i < north_south; ++i) {
            if (block[0][i]) {
                map[0][i] = 0;
            } else {
                map[0][i] = map[0][i - 1];
            }
        }

#if DEBUG
        printf("Fill edge map:\n");
        for (i = 0; i < east_west; ++i) {
            for (j = 0; j < north_south; ++j) {
                printf("%lld\t", map[i][j]);
            }
            printf("\n");
        }
#endif

        for (i = 1; i < east_west; ++i) {
            for (j = 1; j < north_south; ++j) {
                if (block[i][j]) {
                    map[i][j] = 0;
                } else {
                    map[i][j] = map[i-1][j] + map[i][j-1];
                }
            }
        }

#if DEBUG
        printf("Final map:\n");
        for (i = 0; i < east_west; ++i) {
            for (j = 0; j < north_south; ++j) {
                printf("%lld\t", map[i][j]);
            }
            printf("\n");
        }
        printf("Answer:\n");
#endif

        printf("%llu\n", map[east_west - 1][north_south - 1]);
        if (count != 1) {
            printf("\n");
        }
    }

    return 0;
}
