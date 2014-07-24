#include <stdio.h>

int cycle_length(int n)
{
    int len = 1;

    while (n != 1) {
        if (n % 2) {
            n = 3 * n + 1;
        } else {
            n /= 2;
        }
        ++len;
    }

    return len;
}

int main(int argc, char *argv[])
{
    int start, end, first, second, max;
    int i;

    while (scanf("%d %d", &first, &second) == 2) {

        if (first < second) {
            start = first;
            end = second;
        } else {
            start = second;
            end = first;
        }

        max = 0;

        for (i = start; i <= end; ++i) {
            int len = cycle_length(i);
            if (len > max) {
                max = len;
            }
        }
        printf("%d %d %d\n", first, second, max);
    }

    return 0;
}
