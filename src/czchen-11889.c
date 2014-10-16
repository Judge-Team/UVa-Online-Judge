#include <stdio.h>

static int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a%b);
}

int main()
{
    int count;

    int a;
    int b;
    int c;

    int factor;
    int g;

    scanf("%d", &count);

    for (; count > 0; --count) {
        scanf("%d%d", &a, &c);

        /*
         * lcm(A, B) = C
         *
         * To calculate B, we first assume B = C / A. If GCD(A, B) == 1, B is
         * indeed C / A.
         *
         * However, if GCD(A, B) > 1, we know that some factors are both in A
         * and B, and B has higher degree in those factors.
         *
         * To find the factors, we use A' = A / gcd(A, B) to remove all factors
         * in A. Repeating do so we can finally remove all factors in A and use
         * that factor to find real B.
         */

        if (c % a) {
            printf("NO SOLUTION\n");
            continue;
        }

        b = c / a;

        factor = 1;
        g = gcd(a, b);

        while(g != 1)
        {
            factor *= g;
            a /= g;
            g = gcd(a, b);
        }

        printf("%d\n", b * factor);
    }

    return 0;
}
