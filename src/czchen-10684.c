#include <stdio.h>

int max(int x, int y)
{
    return x > y ? x : y;
}

int main(int argc, char *argv[])
{
    int count;
    int i;

    while (scanf("%d", &count) == 1) {
        int i;

        int current_max = -1;
        int right_max = -1;
        int x;

        if (count == 0) {
            break;
        }

        /* Kadane's Algorithm */
        for (i = 0; i < count; ++i) {
            scanf("%d", &x);

            right_max += x;
            if (right_max < 0) {
                right_max = 0;
            }

            current_max = max(current_max, right_max);
        }

        if (current_max > 0) {
            printf("The maximum winning streak is %d.\n", current_max);
        } else {
            printf("Losing streak.\n");
        }
    }

    return 0;
}
