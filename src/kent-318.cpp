#include <stdio.h>
#include <stdlib.h>

#define	MAX_N		501
#define	INFINITE 	999999999


int adj[MAX_N][MAX_N];
int dijk[MAX_N];
int pie[MAX_N];
int S[MAX_N];
int S_ptr;
int node_num , link_num;

void relax( int u , int v )
{
	if ( dijk[v] > dijk[u] + adj[u][v] ){
		dijk[v] = dijk[u] + adj[u][v];
		pie[v] = u;
	}
}

int find_minimum_u()
{
	int i ,u;
	int min = -1;
	for ( i = 1 ; i <= node_num ; i++ ){
		if ( S[i] != 1 ){
			if ( min > dijk[i] || min == -1 ){
				min = dijk[i];
				u = i;
			}
		}
	}
	return u;
}

int main()
{
	int counter;
	int i , j , k , x , y , z;
	int v , u;
	int max_time;
	int src , dst , cost;
	double	finish_time;
	int flag;
	int a , b;

	for ( counter = 1 ; scanf("%d%d",&node_num,&link_num) != EOF ; counter++ ){
		if ( node_num == 0 && link_num == 0 )
			break;
		// init 
		for ( i = 0 ; i < MAX_N ; i++ ){
			for ( j = 0 ; j < MAX_N ; j++ ){
				adj[i][j] = 0;
			}
			// dijk algorithm init
			pie[i] = 0;
			dijk[i] = INFINITE;
			S[i] = 0;
		}
		dijk[1] = 0;
		S_ptr = 0;


		for ( i = 0 ; i < link_num ; i++ ){
			scanf("%d%d%d",&src,&dst,&cost);
			adj[src][dst] = cost;
			adj[dst][src] = cost;
		}

		// run Dijkstra algorithm 

		for ( i = 1 ; i <= node_num ; i++ ){
			u = find_minimum_u();
			S[u] = 1;
			for ( j = 1 ; j <= node_num ; j++ ){
				if ( adj[u][j] > 0 ){
					relax( u , j );
				}
			}
		}
		max_time = 0;
		for ( i = 1 ; i <= node_num ; i++ ){
			if ( max_time < dijk[i] ){
				max_time = dijk[i];
				u = i;
			}
		}
		flag = 0;
		finish_time = max_time;
		for ( i = 1 ; i <= node_num ; i++ ){
			if ( adj[u][i] > 0 && pie[u] != i ){
				x = dijk[u] - dijk[i];
				x = adj[u][i] - x;

				if ( finish_time < max_time + (double)x/2 ){
					finish_time = max_time + (double)x/2;
					v = i;
					if (  dijk[u] == dijk[i] ){
						a = u;
						b = v;
					} else {
						a = v;
						b = u;
					}
					flag = 1;
				}

			}
		}

		printf("System #%d\n",counter);
		if ( flag == 1 ){
			printf("The last domino falls after %0.1lf seconds, between key dominoes %d and %d.\n",finish_time , a , b );	
		} else {
			printf("The last domino falls after %0.1lf seconds, at key domino %d.\n",finish_time,u);
		}
		printf("\n");
	}
}
