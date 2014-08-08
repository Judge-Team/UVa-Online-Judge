#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#define TOTAL_ORDER 6


enum {
    B,
    G,
    C,
    COLOR_COUNT
};


typedef struct _Bin {
    int color[COLOR_COUNT];
} Bin;


typedef struct _Order {
    char str[COLOR_COUNT];
    int count;
} Order;


int main() {
    int i, sum, min, code, idx = 0;
    Bin bin_first, bin_second, bin_third;
    Order ans[TOTAL_ORDER];

    ans[0].str[0] = B; ans[0].str[1] = C; ans[0].str[2] = G;
    ans[1].str[0] = B; ans[1].str[1] = G; ans[1].str[2] = C;
    ans[2].str[0] = C; ans[2].str[1] = B; ans[2].str[2] = G;
    ans[3].str[0] = C; ans[3].str[1] = G; ans[3].str[2] = B;
    ans[4].str[0] = G; ans[4].str[1] = B; ans[4].str[2] = C;
    ans[5].str[0] = G; ans[5].str[1] = C; ans[5].str[2] = B;


    while (scanf("%d%d%d%d%d%d%d%d%d", &(bin_first.color[B]), &(bin_first.color[G]), &(bin_first.color[C]),
                                       &(bin_second.color[B]), &(bin_second.color[G]), &(bin_second.color[C]),
                                       &(bin_third.color[B]), &(bin_third.color[G]), &(bin_third.color[C])) != EOF) {

        min = INT_MAX;
        for (i = 0 ; i < TOTAL_ORDER ; i++) {
            sum = 0;

            code = ans[i].str[0];
            sum += bin_second.color[code];
            sum += bin_third.color[code];

            code = ans[i].str[1];
            sum += bin_first.color[code];
            sum += bin_third.color[code];

            code = ans[i].str[2];
            sum += bin_first.color[code];
            sum += bin_second.color[code];

            ans[i].count = sum;
            if (sum < min) {
                min = sum;
                idx = i;
            }
        }

        for (i = 0 ; i < COLOR_COUNT ; i++) {
            switch(ans[idx].str[i]) {
                case B: {
                    printf("B");
                    break;
                }
                case C: {
                    printf("C");
                    break;
                }
                case G: {
                    printf("G");
                    break;
                }
            }
        }
        printf(" %d\n", ans[idx].count);
    }

    return 0;
}

