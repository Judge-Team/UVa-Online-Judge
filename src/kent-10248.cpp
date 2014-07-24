#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int Adj[10][10];
int edg[10];
int node_has_use[10];
int num_use[100];
int stack[1000];
int S;

int min_s;
int min_ans[1000];
void push(int i)
{
	stack[S++] = i;
}

int check_all_use()
{
	int i;
	int flag = 0;
	for ( i = 0 ; i < 10 ; i++ ){
		if ( node_has_use[i] == 0 )
			flag = 1;
	}

	if ( flag == 1 )
		return 0;
	else 
		return 1;
}

void find_circuit( int i )
{
	int j;
	node_has_use[i] = 1;
	if ( edg[i] == 0 ){
		//push(i);
		return;
	}
	// && check_all_use() == 0
	for ( j = 0 ; j < 10 ; j++ ){
		if ( Adj[i][j] > 0 ){
			//printf("%d->%d\n",i,j);
			Adj[i][j]--;
			edg[i]--;
			push(j);
			find_circuit(j);
			//push(j);
		}
	}
	//push(i);
}

int main()
{
	int n , m;
	int i , j , k , x , y;
	char buffer[1000];
	char *ptr;
	int flag;
	int index;

	while ( scanf("%d%d",&m,&n) != EOF ){
		for ( i = 0 ; i < 1000 ; i++ ){
			buffer[i] = 0;
			min_ans[i] = 0;
		}
		
		ptr = buffer;
		for ( i = m ; i <= n ; i++ ){
			sprintf(ptr,"%d",i);
			if ( i < 10 )
				ptr++;
			else 
				ptr+=2;
		} 
		min_s = 999;
		for ( index = 1 ; index < 10 ; index++ ){

			for ( i = 0 ; i < 10 ; i++ ){
				for ( j = 0 ; j < 10 ; j ++ ){
					Adj[i][j] = 0;
				}
				edg[i] = 0;
			}
			for ( i = 0 ; i < strlen(buffer) -1 ; i++ ){
				j = buffer[i] - '0';
				k = buffer[i+1] - '0';
				if ( Adj[j][k] < 1  )
					Adj[j][k]++;
				edg[j]++;
			}
			//j = buffer[i] - '0';
			//k = buffer[0] - '0';
			//if ( Adj[j][k] < 1 )
			//	Adj[j][k]++;
			//edg[j]++;

			/*for ( x = 0 ; x < 10 ; x++ ){
				if ( node_has_use[x] == 1 && x != i ){
					j = buffer[i] - '0';
					k = buffer[x] - '0';
					Adj[i][x]++;
					edg[i]++;
				}
			}*/

		
			for ( i = 0 ; i < 1000 ; i++ )
				stack[i] = 0;
			S = 0;

			for ( i = 0 ; i < 10 ; i++ )
				node_has_use[i] = 0;

			/*for ( i = 1 ; i < 10 ; i++ ){
				flag = 0;
				for ( j = 0 ; j < 10 ; j++ ){
					if ( Adj[i][j] > 0 )
						flag = 1;
				}
				if ( flag > 0 )
					break;
			}*/

			for ( i = 0 ; i < 100 ; i++ )
				num_use[i] = 0;

			push(index);
			find_circuit(index);
			k = 0;
			for ( i = m ; i <= n ; i++ ){
				if ( i > 9 ){
					x = i/10;
					y = i%10;
					for ( j = 0 ; j <= S ; j++ ){
						if ( stack[j] == x && stack[j+1] == y ){
							num_use[i] = 1;	
							if ( k < j+1 )
								k = j+1;
							break;
						}
					}
				} else {
					x = i;
					for ( j = 0 ; j < S ; j++ ){
						if ( stack[j] == x ){
							num_use[i] = 1;
							if ( k < j )
								k = j;
							break;
						}
					}
				}
			}


			
			flag = 0;
			for ( i = m ; i <= n ; i++ ){
				if ( num_use[i] == 0 ){
					flag = 1;
				}
			}
			if (flag == 1){
				continue;
			}
			
			//for ( i = 0 ; i <= k ; i++ )
			//	printf("%d",stack[i]);
			//printf("\n");


			if ( min_s > k ){
				min_s = k;
				for ( i = 0 ; i <= min_s ; i++ )
					min_ans[i] = stack[i];
			}

		}
		for ( i = 0 ; i <= min_s ; i++ ){
			printf("%d",min_ans[i]);
		}
		printf("\n");
	}
	
}
