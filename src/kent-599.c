#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int color[26];
int graph[26][26];

int visitByDfs(int x) {
    int y;
    int count = 0;
    
    if (color[x] == 0 || color[x] == 2) {
        return 0;
    }
    
    color[x] = 2;
    count = 1;
    for (y = 0 ; y < 26; y++) {
        if (graph[x][y] == 1 && color[y] == 1) {
            count += visitByDfs(y);
        }
    }

    return count;
}

void init() {
    int i,j;
    for (i = 0; i < 26; i++) {
        color[i] = 0;
        for (j = 0; j < 26; j++) {
            graph[i][j] = 0;
        }
    }
}

int main() {
    int testCase;
    int i,j,k;
    int x,y;
    int tree, acorn;
    char buf[64];
    scanf("%d",&testCase);

    for (i = 0; i < testCase; i++){
        init();
        tree = 0;
        acorn = 0;
        while (1) {
            scanf("%s",buf);
            if (buf[0] == '(') {
                x = buf[1] - 'A';
                y = buf[3] - 'A';
                graph[x][y] = 1;
                graph[y][x] = 1;
            }
            else if (buf[0] == '*'){
                /* Do nothing */
            }
            else {
                for (j = 0; buf[j] != '\0'; j++){
                    if (buf[j] >= 'A' && buf[j] <= 'Z'){
                        x = buf[j] - 'A';
                        color[x] = 1;    
                    }
                }
                break;
            }
        }

        for (x = 0; x < 26; x++) {
            if (color[x] == 1) {
                k = visitByDfs(x);
                if (k == 1) {
                    acorn++;
                }
                else {
                    tree++;
                }
            }
        }
        printf("There are %d tree(s) and %d acorn(s).\n",tree,acorn);
    }
}
