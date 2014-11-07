#include <stdio.h>
#include <string.h>

#define DEBUG 0

enum {
    MAX_SEQUENCE_LEN = 1000,
};

struct Data {
    int length;
    int count;
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

int main()
{
    int count;
    char sequence[MAX_SEQUENCE_LEN + 1];
    struct Data data[MAX_SEQUENCE_LEN + 1];

    int len;
    int i;
    int j;
    int length;

    int cand;

    scanf("%d", &count);

    while (count--) {
        scanf("%s", sequence);
        memset(data, 0, sizeof(data));

        len = strlen(sequence);

        for (i = 0; i < len - 1; ++i) {
            for (j = i + 1; j < len; ++j) {
                length = get_common_length(sequence + i, sequence + j);

                if (length > data[i].length) {
                    data[i].length = length;
                    data[i].count = 2;
                } else if (length != 0 && length == data[i].length) {
                    ++data[i].count;
                }
            }
        }

        cand = 0;
        for (i = 1; i < len; ++i) {
            if (data[i].length > data[cand].length) {
                cand = i;
            } else if (data[i].length == data[cand].length) {
                if (memcmp(sequence + i, sequence + cand, data[i].length) < 0) {
                    cand = i;
                }
            }
        }

        if (data[cand].count == 0) {
            printf("No repetitions found!\n");
        } else {
            sequence[cand + data[cand].length] = 0;
            printf("%s %d\n", sequence + cand, data[cand].count);
        }

#if DEBUG
        printf("sequence = %s\n", sequence);
        for (i = 0; i < len; ++i) {
            printf("(%d, %d)", data[i].length, data[i].count);
        }
        printf("\n");
#endif
    }

    return 0;
}
