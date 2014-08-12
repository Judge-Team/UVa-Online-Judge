#include <stdio.h>

int main()
{
    int count;
    int i;

    int a;
    int b;

    scanf("%d", &count);
    for (i = 0; i < count; ++i) {
        scanf("%d%d", &a, &b);

        if (b % a) {
            printf("-1\n");
        } else {
            printf("%d %d\n", a, b);
        }
    }

    return 0;
}
