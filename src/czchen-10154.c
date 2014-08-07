#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    MAX_TURTLE = 5607,
    INVALID = -1,
};

struct Turtle {
    int weight;
    int carry;
};

int compare_turtle(const void *x, const void *y)
{
    const struct Turtle *a = (const struct Turtle *) x;
    const struct Turtle *b = (const struct Turtle *) y;

    return a->carry - b->carry;
}

int min(int x, int y)
{
    return x > y ? y : x;
}

void swap(int **x, int **y)
{
    int *tmp = *x;
    *x = *y;
    *y = tmp;
}

int main(int argc, char *argv[])
{
    int turtle_count = 0;
    struct Turtle turtle[MAX_TURTLE];

    int buf1[MAX_TURTLE];
    int buf2[MAX_TURTLE];

    int *curr;
    int *prev;

    int cnt;
    int id;

#if DEBUG
    int i;
#endif

    while (scanf("%d %d", &turtle[turtle_count].weight, &turtle[turtle_count].carry) == 2) {
        ++turtle_count;
    }

    qsort(turtle, turtle_count, sizeof(turtle[0]), compare_turtle);

#if DEBUG
    printf("turtle info\n");
    for (i = 0; i < turtle_count; ++i) {
        printf("(w = %d, c = %d) ", turtle[i].weight, turtle[i].carry);
    }
    printf("\n");
#endif

    /*
     * Turtles are sorted by their carry.
     *
     * W[id, cnt] = minimal weight when using turtle from 0 ~ id, with cnt turtle(s).
     * w[id] = weight of turtle by id
     * c[id] = carry of turtle by id
     *
     * W[id, cnt] = min | W[id-1, cnt]
     *                  | W[id-1, cnt-1] + w[id] when c[id] >= W[?, cnt-1]
     *
     * Initial with W[0, 0] = w[0]
     *
     * stop when W[?, cnt] does not update.
     */
    curr = buf1;
    prev = buf2;
    prev[0] = turtle[0].weight;

    for (id = 1; id < turtle_count; ++id) {
        prev[id] = min(prev[id-1], turtle[id].weight);
    }

#if DEBUG
    printf("cnt = 1 => ");
    for (i = 0; i < turtle_count; ++i) {
        printf("\t%d", prev[i]);
    }
    printf("\n");
#endif

    for (cnt = 2; cnt <= turtle_count; ++cnt) {
        for (id = 0; id < cnt-1; ++id) {
            curr[id] = INVALID;
        }

        /*
         * Find the first id what has cnt turtles
         */
        for (id = cnt-1; id < turtle_count; ++id) {
            if (prev[id-1] != INVALID && turtle[id].carry - turtle[id].weight >= prev[id-1]) {
                curr[id] = prev[id-1] + turtle[id].weight;
                break;
            }
            curr[id] = INVALID;
        }

#if 0
        printf("[f] cnt = %d => ", cnt);
        for (i = 0; i < turtle_count; ++i) {
            printf("\t%d", curr[i]);
        }
        printf("\n");

        printf("id = %d\n", id);
#endif

        /*
         * Cannot find a combination that fulfull cnt turtles.
         */
        if (id == turtle_count) {
            printf("%d\n", cnt-1);
            return 0;
        }

        id++;

        for (; id < turtle_count; ++id) {
            curr[id] = curr[id-1];
            if (turtle[id].carry - turtle[id].weight >= prev[id-1]) {
                curr[id] = min(curr[id], prev[id-1] + turtle[id].weight);
            }
        }

#if DEBUG
        printf("cnt = %d => ", cnt);
        for (i = 0; i < turtle_count; ++i) {
            printf("\t%d", curr[i]);
        }
        printf("\n");
#endif

        swap(&curr, &prev);
    }

    printf("%d\n", turtle_count);

    return 0;
}
