#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LINK    3000


int link_num , node_num;

int adj_map[52][52];
long long dijk[52];
int pie[52];
int S[52];

//int adj[MAX_LINK];
int index[MAX_LINK];
int head[MAX_LINK];
int tail[MAX_LINK];
int adj[52];

int chartoindex( char a )
{
	if ( a <= 'Z' ){
		return a - 'A' + 26;
	} else {
		return a - 'a';
	}
}


long long count_toll( int id , long long items )
{
	double t;
	if ( id < 26 ){
		return 1;
	} else {
		t = items;
		t = ceil(t/20);
		return (int) t;
	}
}

// x - ceil(x/20)  = y
long long count_items_toll( int id , long long items )
{
	long long t , f;
	if ( id < 26 ) { //village
		return 1;
	} else { // town
		t = (items+1)/19;
		t = items + t;
		//printf("%d\n",t);
		if ( t - count_toll(id,t) == items ){
			return (items+1)/19;
		}
		else
			return (items+1)/19 + 1;
	}
}


int find_minimum_u()
{
	int i , u;
	long long min = -1;
	for ( i = 0 ; i < 52 ; i++ ){
		if ( S[i] != 1 ){
			if ( ( min > dijk[i] || min == -1 ) && dijk[i] != -1 ){
				min = dijk[i];
				u = i;
			}
		}
	}
	return u;
}

void relax( int u , int v )
{
	int t = count_items_toll( u , dijk[u] );

	if ( dijk[v] == -1 && dijk[u] != -1 ){
		dijk[v] = dijk[u] + t;
		pie[v] = u;
	} else 	if ( ( dijk[v] > dijk[u] + t ) && dijk[u] != -1 ){
		dijk[v] = dijk[u] + t;
		pie[v] = u;
	}
}

int comp_func( const void *a , const void *b )
{
	int c,d;
	c = *(int*)a;
	d = *(int*)b;

	if ( head[c] > head[d] )
		return 1;  
	else if  ( head[c] < head[d] )
		return -1;
	else {
		if ( tail[c] > tail[d] )
			return 1;
		else if ( tail[c] < tail[d] )
			return -1;
		else
			return c - d;
	}

}

int main()
{
	int i , j , k , x , y ;
	int u , v;
	int start , end;
	int counter;
	char src , dst;
	char t1[10] , t2[10];
	char tmp;
	int items_num;
	int max_cost;


	for ( counter = 1 ; scanf("%d",&link_num) != EOF ; counter++ ){
		if ( link_num == -1 )
			break;

		// init 
		for ( i = 0 ; i < 52 ; i++ ){
			for ( j = 0 ; j < 52 ; j++ ){
				adj_map[i][j] = 0;
			}
			dijk[i] = -1;//INFINITE;
			S[i] = 0;
			pie[i] = -1;
			 
		}

		for ( i = 0 ; i < MAX_LINK ; i++ ){
			index[i] = 0;
			tail[i] = 0;
			head[i] = 0;    
		}

		node_num = 0;
		for ( i = 0 ; i < 2*link_num ; i++ ){
			scanf("%s%s",t1,t2);
			//printf("%c %c\n",src,dst);
			u = chartoindex(t1[0]);
			v = chartoindex(t2[0]);
			adj_map[u][v]++;
			adj_map[v][u]++;
			index[i] = i;
			head[i] = u;
			tail[i] = v;
			index[++i] = i;
			head[i] = v;
			tail[i] = u;
			node_num++;
		}

		qsort(index,2*link_num,sizeof(index[0]),comp_func);

		/*for ( i = 0 ; i < 2*link_num ; i++ ){
		  if ( head[index[i]] < 26 )
		  src = head[index[i]] + 'a';
		  else
		  src = head[index[i]] + 'A' - 26;
		  if ( tail[index[i]] < 26 )
		  dst = tail[index[i]] + 'a';
		  else
		  dst = tail[index[i]] + 'A' - 26;
		  printf("%c->%c\n",src,dst);
		  }*/

		x = 0;
		y = 0;
		for ( i = 0 ; i < 2*link_num ; i++ ){
			if ( x < head[index[i]] ){
				x = head[index[i]];
				adj[x] = i;
				y++;     
			}
		}
		node_num = y;

		scanf("%d%s%s",&items_num,t1,t2);
		start = chartoindex(t1[0]);
		end = chartoindex(t2[0]); 
		dijk[end] = items_num;// + count_items_toll(end,items_num);

		// run Dijkstra algorithm

		for ( i = 0 ; i < node_num ; i++ ){
			u = find_minimum_u();	 
			//printf("%d\n",u);
			S[u] = 1;
			for ( j = 0 ; j < 52 ; j++ ){
				if ( adj_map[u][j] > 0 ){
			//
			//for ( j = adj[u] ; head[index[j]] == head[index[adj[u]]] ; j++ ){
					relax( u , j );
			//}
				}
			}
			//for ( j = 0 ; j < 2*link_num ; j++ ){

			//}
		}

		// print answer 
		printf("Case %d:\n",counter);
		printf("%llu\n",dijk[start]);
		if ( start < 26 ){
			printf("%c",start + 'a' );
		} else {
			printf("%c",start + 'A' - 26 );
		}
		if ( pie[start] == -1 ){
			printf("\n");
		} else {
			printf("-");
		}
		for ( i = pie[start] ; i != -1 ; i = pie[i] ){
			if ( i < 26 ){
				tmp = i + 'a';
				printf("%c",tmp);
			} else {
				tmp = i + 'A' - 26;
				printf("%c",tmp);
			}
			if ( i == end )
				printf("\n");
			else
				printf("-");
		}
	}
}
