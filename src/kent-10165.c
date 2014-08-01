#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    unsigned int N;
    unsigned int P, p;
    unsigned int i;

    while (scanf("%d",&N) != EOF && N != 0) {
        P = 0;
        for (i = 0; i < N; i++) {
            scanf("%d",&p);
            P ^= p;
        }
        if (P) {
            printf("Yes\n");
        }
        else {
            printf("No\n");
        }
    }
    return 0;
}
