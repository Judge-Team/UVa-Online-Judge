#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

enum {
    MAX_SEQUENCE_LEN = 1000,
};

int get_common_length(const char *x, const char *y)
{
    int length = 0;

    while (*x && *y) {
        if (*x != *y) {
            break;
        }

        ++length;
        ++x;
        ++y;
    }

    return length;
}

int compare(const void *x, const void *y, void *arg)
{
    char *sequence = (char *) arg;

    int xx = *(const int *) x;
    int yy = *(const int *) y;

    return strcmp(sequence + xx, sequence + yy);
}

int main()
{
    int count;

    char sequence[MAX_SEQUENCE_LEN + 1];
    int suffix[MAX_SEQUENCE_LEN + 1];

    int len;
    int i;

    scanf("%d", &count);

    int cand;
    int cand_len;
    int cand_size;
    int is_prev;
    int common_len;

    while (count--) {
        scanf("%s", sequence);
        memset(suffix, 0, sizeof(suffix));

        len = strlen(sequence);

        /*
         * The algorithm is divided into the following steps:
         *
         * 1. Setup a suffix array. This is O(n).
         *
         * 2. Sort the suffix array. Since the comparison function needs O(n),
         *    the recursive formula will be T(n) = 2T(n/2) + n^2. This is
         *    O(n^2).
         *
         * 3. Compare adjust string in sorted suffix array. This is O(n^2)
         *
         * The overall complexity is O(n + n^2 + n^2) = O(n^2).
         */

        for (i = 0; i < len; ++i) {
            suffix[i] = i;
        }

        qsort_r(suffix, len, sizeof(suffix[0]), compare, sequence);

#if DEBUG
        for (i = 0; i < len - 1; ++i) {
            printf("%s ", sequence + suffix[i]);
        }
        printf("\n");
#endif

        cand = 0;
        cand_len = 0;
        cand_size = 0;
        is_prev = 0;

        for (i = 0; i < len - 1; ++i) {
            common_len = get_common_length(sequence + suffix[i], sequence + suffix[i + 1]);

            if (common_len > cand_len) {
                cand = suffix[i];
                cand_len = common_len;
                cand_size = 2;
                is_prev = 1;
#if DEBUG
                printf("i = %d, set cand = %d, cand_len = %d\n", i, cand, cand_len);
#endif

            } else if (common_len == cand_len && is_prev) {
                ++cand_size;

            } else {
                is_prev = 0;
            }
        }

        if (cand_len == 0) {
            printf("No repetitions found!\n");
        } else {
            sequence[cand + cand_len] = 0;
            printf("%s %d\n", sequence + cand, cand_size);
        }
    }

    return 0;
}
