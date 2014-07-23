#include <stdio.h>

enum {
    MAX_BUILD = 5000,
    MAX_COORDINATE = 10000,
};

struct Build {
    int left;
    int height;
    int right;
};

int min(int x, int y)
{
    return x < y ? x : y;
}

int compare_build(void *x, void *y)
{
    struct Build *a = (struct Build *) x;
    struct Build *b = (struct Build *) y;

    return a->left - b->left;
}


int main(int argc, char *argv[])
{
    struct Build build[MAX_BUILD];
    int build_count = 0;
    int i;

    int skyline;
    int skyline_cand_start;

    while (scanf("%d %d %d", &build[build_count].left, &build[build_count].height, &build[build_count].right) == 3) {
        ++build_count;
    }

    qsort(build, build_count, sizeof(build[0]), compare_build);

    skyline = 0;
    skyline_cand_start = 0;
    printf("%d %d", build[skyline].left, build[skyline].height);

    return 0;
}
