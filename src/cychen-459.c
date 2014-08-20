#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int cases, i, j, lastdiff, diff1, diff2, temp;
    char lastchar, char1, char2, newline;
    int list[26] = {0};
    
    scanf("%d%c%c", &cases, &newline, &newline);
    int *result = malloc(sizeof(int) * cases);
    for(i = 0; i < cases; i++) {
        int group = 0;
        scanf("%c%c", &lastchar, &newline);
        lastdiff = lastchar - 'A';

        while(scanf("%c", &char1) == 1) {
            if(char1 == newline) break;
            scanf("%c%c", &char2, &newline);
            diff1 = char1 - 'A';
            diff2 = char2 - 'A';
            if(list[diff1] == 0 && list[diff2] == 0) {
                group++;
                list[diff1] = group;
                list[diff2] = group;
            }
            else if(list[diff1] == 0) {
                list[diff1] = list[diff2];
            }
            else if(list[diff2] == 0) {
                list[diff2] = list[diff1];
            }
            else if(list[diff1] == list[diff2]) {
                continue;
            }
            else if(list[diff1] > list[diff2]) {
                temp = list[diff1];
                for(j = 0; j <= lastdiff; j++) {
                    if(list[j] == temp) list[j] = list[diff2];
                    if(list[j] > temp) list[j]--;
                }
                group--;
            }
            else {
                temp = list[diff2];
                for(j = 0; j <= lastdiff; j++) {
                    if(list[j] == temp) list[j] = list[diff1];
                    if(list[j] > temp) list[j]--;
                }
                group--;
            }
        }
        for(j = 0; j <= lastdiff; j++) {
            if(list[j] == 0) group++;
            else list[j] = 0;
        }
        result[i] = group;
    }

    for(j = 0; j < cases; j++) {
        printf("%d\n", result[j]);
        if(cases - j - 1) printf("\n");        
    }
    return 0;
}
