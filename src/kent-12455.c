#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(x,y) (x > y)?x:y

int bars[20];
int p;

int dpFunction(int idx, int len)
{
    int t;
    if (len == 0) {
        return 1;
    }
    if (len < 0) {
        return 0;
    }
    if (idx == p) {
        return 0;
    }

    return MAX(dpFunction(idx+1,len), dpFunction(idx+1,len - bars[idx]));
}

int comp(const void *p, const void *q)
{
    return (*(int*)p - *(int*)q);
}

int main() {
    int t;
    int i, j, k;
    int n;
    scanf("%d",&t);

    for (i = 0; i < t; i++){
        scanf("%d",&n);
        scanf("%d",&p);
        for (j = 0; j < p; j++) {
            scanf("%d",&bars[j]);
        }
        qsort(bars,p,sizeof(int),comp);
        if (dpFunction(0,n) == 1) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }
    return 0;
}
