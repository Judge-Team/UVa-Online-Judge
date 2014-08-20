#include <stdio.h>


int cycle_len(unsigned int n) {
    unsigned int x = 1;
    while(n != 1) {
        if(n % 2) {
            n = 3 * n + 1;
        }
        else {
            n = n / 2;
        }
        x++;
    }
    return x;
}


int main(int argc, char **argv) {
    unsigned int i, j, max, temp;
    unsigned int index;
    while(scanf("%d %d", &i, &j) != EOF) {
        max = 0;
        for(index = ((i < j)?i:j); index <= ((i < j)?j:i); index++) {
            temp = cycle_len(index);
            max = ((max > temp) ? max : temp);
        }
        printf("%d %d %d\n", i, j, max);
    }
    return 0;
}
