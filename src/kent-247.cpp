#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  MAX        9999999

int name_index;
char name[25][26];
int A[25][25];
int D[25][25];

int insert_name( char *string )
{
	int i;
	// in list
	for ( i = 0 ; i < name_index ; i++ ){
		if ( strcmp( name[i] , string ) == 0 ){
			return i;     
		}
	}
	// not in list

	strncpy( name[name_index] , string , strlen(string) );
	name[name_index][strlen(string)] = '\0';
	name_index++;
	return name_index-1;


}

	int min( int a , int b ){
		if ( a < b )    
			return a;
		else
			return b;
	}

int main()
{
	FILE *in;
	int counter;
	int N , link;
	int i , j , k;
	char buf1[25] , buf2[25];
	int flag[25];

	in = stdin;
	for ( counter = 1 ; 1 ; counter++ ){
		fscanf(in,"%d%d",&N,&link);
		if ( N == 0 && link == 0 )
			break;
		else if ( counter != 1 )
			printf("\n");
		// init 
		for ( i = 0 ; i < 25 ; i++ ){
			for ( j = 0 ; j < 25 ; j++ ){
				if ( i == j )
					D[i][j] = 0;
				else
					D[i][j] = MAX; 
				A[i][j] = 0;   
			}
			name[i][0] = '\0';
			flag[i] = 1;
		}
		name_index = 0;
		for ( k = 0 ; k < link ; k++ ){
			fscanf(in,"%s%s",buf1,buf2);
			i = insert_name( buf1 );
			j = insert_name( buf2 );
			//printf("%s %s\n",buf1,buf2);
			//printf("%d %d\n",i,j);
			D[i][j] = 1;
		}

		//for ( i = 0 ; i < N ; i++ ){
		//    printf("%d %s\n",i,name[i]);
		//}

		for ( k = 0 ; k < N ; k++ ){
			for ( i = 0 ; i < N ; i++ ){
				for ( j = 0 ; j < N ; j++ ){
					D[i][j] = min( D[i][j] , D[i][k] + D[k][j] );
				}
			}    
		}

		for ( i = 0 ; i < N ; i++ ){
			for ( j = 0 ; j < N ; j++ ){
				if ( D[i][j] == MAX )
					A[i][j] = 0;
				else{
					A[i][j] = 1;
				}
			}
		}

		printf("Calling circles for data set %d:\n",counter);
		for ( i = 0 ; i < N ; i++ ){
			if ( flag[i] == 1 ){
				flag[i] = 0;
				printf("%s",name[i]);
				for ( j = i+1 ; j < N ; j++ ){
					if ( A[i][j] == 1 && A[j][i] == 1 ){
						flag[j] = 0;
						printf(", %s",name[j]);    
					}
				}
				printf("\n");
			}
		}

		//printf("\n");

	}
}
