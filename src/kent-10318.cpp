#include <stdio.h>
#include <stdlib.h>

#define MAX	3000000

int puzz[3][3];
int R , C;
int map[5][5];
int Prs[26];
int tmp[26];
int flag = 0;
int Case , min;

void press( int r , int c , int k ){
	int dept;
	if ( k == 1 ){
		dept = c+1 + C*r;
		tmp[dept] = 1 - tmp[dept];
		map[r][c] = (puzz[1][1] + map[r][c] )%2;
		if ( r+1 != R )
			map[r+1][c] 	= 	( map[r+1][c] + puzz[2][1] )%2;
		if ( r-1 != -1 )
			map[r-1][c] 	= 	( map[r-1][c] + puzz[0][1] )%2;
		if ( c+1 != C )
			map[r][c+1] 	= 	( map[r][c+1] + puzz[1][2] )%2;
		if ( c-1 != -1 )
			map[r][c-1] 	= 	( map[r][c-1] + puzz[1][0] )%2;
		if ( r-1 != -1 && c+1 != C )
			map[r-1][c+1] = 	( map[r-1][c+1] + puzz[0][2] )%2;
		if ( r-1 != -1 && c-1 != -1 )
			map[r-1][c-1] = 	( map[r-1][c-1] + puzz[0][0] )%2;
		if ( r+1 != R && c+1 != C )
			map[r+1][c+1] = 	( map[r+1][c+1] + puzz[2][2] )%2;
		if ( r+1 != R && c-1 != -1 )
			map[r+1][c-1] = 	( map[r+1][c-1] + puzz[2][0] )%2;

	} 
}

int check()
{
	int i,j;
	for ( i = 0 ; i < R ; i++ ){
		for ( j = 0 ; j < C ; j++ ){
			if (map[i][j] == 0 )
				return 0;
		}
	}
	return 1;
}

void panel( int r , int c ){
	int i , j , k, total;
	int dept = c+1 + C*r;
	for ( k = 0 ; k <= 1 ; k++){
		flag = false;
		press( r , c , k );
		if ( r >= 2 ){
			for ( i = 0 ; i < r-2 ; i++ ){
				for ( j = 0 ; j < c ; j++ ){
					if ( map[i][j] == 0 )
						flag = true;
				}
			}
		}

		if ( flag == false && dept == R*C ){
			if ( check() == 1 ){
				total = 0;
				for ( i = 1 ; i <= R*C ; i++ ){
					total += tmp[i];
				}
				if ( total < min ){
					min = total;
					for ( i = 1 ; i <= R*C ; i++ ){
						Prs[i] = tmp[i];
						flag = true;
					}
				}
			}
			
		} else if ( flag == false ){
			if ( c+1 != C )
				panel( r , c+1 );
			else if ( r+1 != R )
				panel( r+1 , 0 );
		}
		press(r,c,k);
	}
}



int main()
{
	int i , j;
	int r , c;
	int ptr;
	int case_num;
	int flag;
	int sum;
	int depth;
	char buf[4];

	for ( case_num = 1 ; scanf("%d%d",&R,&C) != EOF ; case_num++ ){
		if ( R == 0 && C == 0 )
			break;
		for ( i = 0 ; i < 5 ; i++ )
			for ( j = 0 ; j < 5 ; j++ )
				map[i][j] = 0;

		for ( i = 0 ; i < 25; i++ ){
			tmp[i] = 0;
			Prs[i] = 0;
		}
		flag = false;
		for ( i = 0 ; i < 3 ; i++ ){
			scanf("%s",buf);
			for ( j = 0 ; j < 3 ; j++ ){
				if ( buf[j] == '*' ){
					puzz[i][j] = 1;
				} else {
					puzz[i][j] = 0;
				}
			}
		}
		panel(0,0);
		printf("Case #%d\n", case_num);
		if( min < R*C + 1 ){
			for( i = 1 ; i <= R*C ; i++){
				if( Prs[i] == 1 && min > 0 ){
					printf("%d", i); min--;
					if( min > 0 ) printf(" ");
				}
			}
			printf("\n");
		}
		else printf("Impossible.\n");
	}
	
}
