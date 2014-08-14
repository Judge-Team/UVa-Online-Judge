#include <stdio.h>

enum {
    MAX_COUNT = 10000,
    INVALID   = -1,
};

struct Sequence {
    int start;
    int last;
};

static int min(int x, int y)
{
    return x > y ? y : x;
}

int main()
{
    int count;
    int i;
    int j;

    int value[MAX_COUNT];

    struct Sequence left[MAX_COUNT+1];
    int left_cnt;

    struct Sequence right[MAX_COUNT+1];
    int right_cnt;

    while (scanf("%d", &count) == 1) {
        for (i = 0; i < count; ++i) {
            scanf("%d", &value[i]);
        }

        /*
         * left[i] = information about strictly increasing sequence with size
         *           i.
         *
         *     start = The first start position of sequence.
         *     last  = The last value of this sequence.
         *
         * We will scan from left to right, to update left[] array. Also use the
         * same algorithm to create right[] array.
         *
         * Now we just need to find maximum i that fulfills the following
         * condition:
         *
         *     left[i].start <= right[i].start
         */

        left[0].start = INVALID;
        left[0].last = 0;
        left_cnt = 1;

        for (i = 0; i < count; ++i) {
            if (left[left_cnt-1].last < value[i]) {
                left[left_cnt].start = i;
                left[left_cnt].last = value[i];
                ++left_cnt;
            }

            for (j = left_cnt-2; j >=0; --j) {
                if (left[j].last < value[i] && left[j+1].last > value[i]) {
                    left[j+1].last = value[i];
                }
            }
        }

#if DEBUG
        for (i = 0; i < left_cnt; ++i) {
            printf("[%d] = (%d,%d), ", i, left[i].start, left[i].last);
        }
        printf("\n");
#endif

        right[0].start = INVALID;
        right[0].last = 0;
        right_cnt = 1;

        for (i = count-1; i >= 0; --i) {
            if (right[right_cnt-1].last < value[i]) {
                right[right_cnt].start = i;
                right[right_cnt].last = value[i];
                ++right_cnt;
            }

            for (j = right_cnt-2; j >=0; --j) {
                if (right[j].last < value[i] && right[j+1].last > value[i]) {
                    right[j+1].last = value[i];
                }
            }
        }

#if DEBUG
        for (i = 0; i < right_cnt; ++i) {
            printf("[%d] = (%d,%d), ", i, right[i].start, right[i].last);
        }
        printf("\n");
#endif

        for (i = min(left_cnt-1, right_cnt-1); i >=0; --i) {
            if (left[i].start <= right[i].start) {
                printf("%d\n", i*2-1);
                break;
            }
        }

    }

    return 0;
}
