#include <stdio.h>

int main()
{
    unsigned int count;
    unsigned int item;
    unsigned int ans;
    unsigned int i;

    while (scanf("%d", &count) == 1) {
        if (count == 0) {
            break;
        }

        ans = 0;

        for (i = 0; i < count; ++i) {
            scanf("%d", &item);
            ans ^= item;
        }

        /*
         * Jack loses the game if the piles are in pairs. If the piles are in
         * pairs, whatever Jack does, Jim can make it remain in pairs. At the
         * end, Jack will lose.
         */
        if (ans) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}
