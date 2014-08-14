#include <stdio.h>

int main()
{
    int count;
    int x;
    int lcm;

    scanf("%d", &count);

    for (; count > 0; --count) {
        scanf("%d%d", &x, &lcm);

        if (lcm % x) {
            printf("NO SOLUTION\n");
        } else {
            printf("%d\n", lcm/x);
        }
    }

    return 0;
}
