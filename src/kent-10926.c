#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int edges[101][101];
int color[101];
int N;

void init()
{
    int i, j;
    for (i = 0; i < 101; i++){
        for (j = 0; j < 101; j++){
            edges[i][j] = 0;
        }
    }

}

void initColor()
{
    int i;
    for (i = 0; i < 101; i++){
        color[i] = 0;
    }
}

int DFS_Visit(int job)
{
    int i, j;
    int count = 0;
    if (color[job] != 0){
        return 0;
    }
    color[job] = 1;
    for (i = 1; i <= N; i++) {
        if (edges[job][i] == 1 && color[i] == 0){
            count += DFS_Visit(i);
        }
    }
    count++;
    return count;
}

int main(int argc, char const *argv[])
{
    int T;
    int max, ans;
    int i, j, k;
    while (scanf("%d",&N) && N != 0){
        init();
        for (i = 1; i <= N; i++) {
            scanf("%d",&T);
            for (j = 0; j < T; j++){
                scanf("%d",&k);
                edges[i][k] = 1;
            }
        }
        max = 0;
        ans = 1;
        for (i = 1; i <= N; ++i) {
            initColor();
            T = DFS_Visit(i);
            if (T > max) {
                max = T;
                ans = i;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}
