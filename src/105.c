#include <stdio.h>

enum {
    MAX_BUILD = 5000,
    MAX_COORDINATE = 10000,
};

int max(int x, int y)
{
    return x > y ? x : y;
}

int main(int argc, char *argv[])
{
    int skyline[MAX_COORDINATE] = { 0 };

    int left;
    int right;
    int height;
    int i;
    int prev_skyline;

    while (scanf("%d %d %d", &left, &height, &right) == 3) {
        for (i = left; i < right; ++i) {
            skyline[i] = max(skyline[i], height);
        }
    }

    prev_skyline = 0;

    for (i = 0; i < MAX_COORDINATE; ++i) {
        if (skyline[i] != 0) {
            printf("%d %d", i, skyline[i]);
            prev_skyline = skyline[i];
            break;
        }
    }

    for (; i < MAX_COORDINATE; ++i) {
        if (prev_skyline != skyline[i]) {
            printf(" %d %d", i, skyline[i]);
            prev_skyline = skyline[i];
        }
    }

    printf("\n");

    return 0;
}
