#include <stdio.h>
#include <stdlib.h>


int A[100][100];
int edg[100];
int M,N;

int main(){
	int i , j , x , y , z;

	while ( scanf("%d%d",&x,&y) != EOF ){
		if ( x == 0 && y == 0 )
			break;
		scanf( "%d",&z );

		for ( i = 0 ; i < 100 ; i++ ){
			for ( j = 0 ; j < 100 ; j++ ){
				A[i][j] = 0;
			}
			edg[i] = 0;
		}
		i = 0;
		A[x][y]++;
		A[y][x]++;
		edg[x]++;
		edg[y]++;
		i++;
		while ( scanf("%d%d",&x,&y) != EOF ){
			if ( x == 0 && y == 0 )
				break;
			scanf("%d",&z);
			A[x][y]++;
			A[y][x]--;
			edg[x]++;
			edg[y]++;
			i++;
		}
		M = i;
		for ( i = 0 , N = 0 ; i < 100 ; i++ ){
			if ( edg[i] > 0 )
				N++;
		}
		
		

		printf("%d\n",M);
	}

}
