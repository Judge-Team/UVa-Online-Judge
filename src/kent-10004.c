#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WHITE   0
#define GREEN   1
#define BLUE    2

int color[200];
int edges[200][200];

int numNode;
int numEdge;
int isBicolorable;

int dfsVisit(int vNode, int byColor)
{
    int i;
    int newColor;
    color[vNode] = byColor;
    newColor = (byColor == GREEN)?BLUE:GREEN;

    for (i = 0; i < numNode; i++){
        if (i != vNode && edges[vNode][i] == 1) {
            if (color[i] == WHITE) {
                dfsVisit(i,newColor);
            }
            else if (color[i] == byColor){
                isBicolorable = 0;
            }
        }
    }
    return 0;
}

void initNodeAndEdge()
{
    int i,j;
    isBicolorable = 1;
    for (i = 0; i < 200; i++) {
        color[i] = 0;
        for (j=0; j < 200; j++){
            edges[i][j] = 0;
        }
    }
}

int main()
{
    int i;
    int x, y;

    while (scanf("%d",&numNode) != EOF && numNode != 0) {
        initNodeAndEdge();
        scanf("%d",&numEdge);
        for (i = 0; i < numEdge; i++) {
            scanf("%d%d",&x,&y);
            edges[x][y] = 1;
            edges[y][x] = 1;
        }
        for (i = 0 ; i < numNode; i++){
            if(color[i] == WHITE) {
                dfsVisit(i,GREEN);
            }
        }
        
        if (isBicolorable) {
            printf("BICOLORABLE.\n");
        }
        else {
            printf("NOT BICOLORABLE.\n");
        }
    }
    return 0;
}
