#include <stdio.h>

const int COIN_TYPE[] = { 50, 25, 10, 5, 1, 0 };

static int find_change(int coin, const int *type)
{
    if (coin == 0) {
        return 1;
    } else if (coin < 0 || type[0] == 0) {
        return 0;
    } else {
        return find_change(coin, type+1) + find_change(coin-type[0], type);
    }
}

int main()
{
    int coin;
    int ans;

    while (scanf("%d", &coin) == 1) {
        ans = find_change(coin, COIN_TYPE);
        printf("%d\n", ans);
    }

    return 0;
}
