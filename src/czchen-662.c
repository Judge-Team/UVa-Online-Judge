#include <limits.h>
#include <math.h>
#include <stdio.h>

enum {
    MAX_RESTAURANT = 200,
    MAX_DEPOT = 30,
};

struct DepotLocation {
    int cost;
    struct {
        int loc;
        int serve_start;
        int serve_end;
    } depot[MAX_DEPOT];
};

#if DEBUG
static void print_buf(struct DepotLocation *buf, int rest_count, int depot_count)
{
    int i;
    int j;

    for (i = depot_count-1; i < rest_count; ++i) {
        printf("from 0 ~ %d, cost = %d:\n", i, buf[i].cost);
        for (j = 0; j < depot_count; ++j) {
            printf("depot %d at %d serve %d ~ %d\n",
                j,
                buf[i].depot[j].loc,
                buf[i].depot[j].serve_start,
                buf[i].depot[j].serve_end);
        }
        printf("\n");
    }
}
#else
#define print_buf(x, y, z)
#endif


static void find_best_depot(
    int rest[MAX_RESTAURANT],
    int start,
    int end,
    int *depot,
    int *cost)
{
    int i;
    int curr_depot;
    int curr_cost;

    *cost = INT_MAX;

    for (curr_depot = start; curr_depot <= end; ++curr_depot) {
        curr_cost = 0;
        for (i = start; i <= end; ++i) {
            curr_cost += abs(rest[curr_depot] - rest[i]);
        }

        if (curr_cost < *cost) {
            *cost = curr_cost;
            *depot = curr_depot;
        }
    }
}

static void swap(struct DepotLocation **x, struct DepotLocation **y)
{
    struct DepotLocation *tmp;

    tmp = *x;
    *x = *y;
    *y = tmp;
}

int main(int argc, char *argv[])
{
    int rest_count;
    int rest[MAX_RESTAURANT];

    int depot_count;

    int i;
    int j;
    int n;
    int iter;

    struct DepotLocation buf1[MAX_RESTAURANT];
    struct DepotLocation buf2[MAX_RESTAURANT];

    struct DepotLocation *curr = buf1;
    struct DepotLocation *prev = buf2;

    int curr_depot;
    int curr_cost;

    for (iter = 0; scanf("%d%d", &rest_count, &depot_count) == 2; ++iter) {
        if (rest_count == 0 && depot_count == 0) {
            break;
        }

        for (i = 0; i < rest_count; ++i) {
            scanf("%d", &rest[i]);
        }

        /*
         * cost(0, i, n) = best shipping cost when using n deopts for restaurant
         *                 0 ~ i (inclusively)
         *
         * cost(0, i, n) = max { cost(0, j, n-1) + cost(j+1, i, 1) }
         *
         */

        /*
         * Fill cost(0, i, 1)
         */
        for (i = 0; i <= rest_count; ++i) {
            find_best_depot(rest, 0, i, &curr_depot, &curr_cost);
            curr[i].cost = curr_cost;
            curr[i].depot[0].loc = curr_depot;
            curr[i].depot[0].serve_start = 0;
            curr[i].depot[0].serve_end = i;
        }

        print_buf(curr, rest_count, 1);

        for (n = 2; n <= depot_count; ++n) {
            swap(&curr, &prev);

            i = n - 1;

            /*
             * When restaurant count = depot count.
             */
            curr[i].cost = 0;
            curr[i].depot[i].loc = n;
            curr[i].depot[i].serve_start = i;
            curr[i].depot[i].serve_end = i;

            ++i;
            for (; i < rest_count; ++i) {
                j = n - 1;

                find_best_depot(rest, j+1, i, &curr_depot, &curr_cost);
                curr[i] = prev[j];
                curr[i].cost += curr_cost;
                curr[i].depot[n-1].loc = curr_depot;
                curr[i].depot[n-1].serve_start = j + 1;
                curr[i].depot[n-1].serve_end = i;

                ++j;
                for (; j < i; ++j) {
                    find_best_depot(rest, j+1, i, &curr_depot, &curr_cost);

                    if (prev[j].cost + curr_cost < curr[i].cost) {
                        curr[i] = prev[j];
                        curr[i].cost += curr_cost;
                        curr[i].depot[n-1].loc = curr_depot;
                        curr[i].depot[n-1].serve_start = j + 1;
                        curr[i].depot[n-1].serve_end = i;
                    }
                }
            }

            print_buf(curr, rest_count, n);

        }

        printf("Chain %d\n", iter+1);
        for (i = 0; i < depot_count; ++i) {
            curr[rest_count-1].depot[i].loc;

            if (curr[rest_count-1].depot[i].serve_start == curr[rest_count-1].depot[i].serve_end) {
                printf("Depot %d at restaurant %d serves restaurant %d\n",
                    i+1,
                    curr[rest_count-1].depot[i].loc+1,
                    curr[rest_count-1].depot[i].serve_start+1
                );

            } else {
                printf("Depot %d at restaurant %d serves restaurants %d to %d\n",
                    i+1,
                    curr[rest_count-1].depot[i].loc+1,
                    curr[rest_count-1].depot[i].serve_start+1,
                    curr[rest_count-1].depot[i].serve_end+1
                );
            }
        }
        printf("Total distance sum = %d\n", curr[rest_count-1].cost);

    }

    return 0;
}
