#include <stdio.h>
#include <stdlib.h>

#define WHITE      1
#define GRAY       2
#define BLACK      3

int M , N;

int adj[30000];
int head[1000000];
int tail[1000000];
int index[1000000];

int color[30000];
int pie[30000];
int time;


int comp_func( const void *a , const void *b )
{
	int c , d;
	c = *(int*)(a);
	d = *(int*)(b);

	if ( head[c] > head[d] )
		return 1;
	else if ( head[c] < head[d] )
		return -1;
	else {
		if( tail[c] > tail[d] )
			return 1;
		else if( tail[c] < tail[d] )
			return -1;
		else
			return (c-d);
	}
}

int DFS_visit( int v )
{
	int i;
	int u;

	int component_num = 0;

	color[v] = GRAY;
	time++;

	for ( i = adj[v] ;  head[index[i]] == head[index[adj[v]]] ; i++ ){
		u = tail[index[i]];
		if ( color[u-1] == WHITE ){
			pie[u-1] = v;
			component_num += DFS_visit(u-1);
		}
	}
	color[v] = BLACK;
	component_num ++;
	time++;
	return component_num;
}

int main()
{
	int case_num;

	FILE *in;
	int i , j , x , y;
	int vertex , link;


	in = stdin;//fopen("in.txt","r");

	fscanf(in,"%d",&case_num);

	for ( int C_count = 0 ; C_count < case_num ; C_count++ ){
		fscanf(in,"%d%d",&N,&M);

		/*init*/
		for ( i = 0 ; i <= N ; i++ ){
			adj[i] = -1;
		}
		for ( i = 0 ; i <= 2*M ; i++ ){
			head[i] = 0;
			tail[i] = 0;
			index[i] = 0;
		}


		for ( i = 0 ; i < 2*M ; i++ ){
			fscanf(in,"%d%d",&vertex,&link);   
			// add node
			index[i] = i;
			head[i] = vertex;
			tail[i] = link;
			i++;
			index[i] = i;
			head[i] = link;
			tail[i] = vertex;
		}
		qsort( index , 2*M , sizeof(index[0]) , comp_func );

		j = 0;
		for ( i = 0 ; i < 2*M ; i++ ){
			if ( j < head[index[i]] ){
				j = head[index[i]];
				adj[j-1] = i;
			}
		}

		/* init DFS */
		for ( i = 0 ; i < N ; i++ ){
			if ( adj[i] != -1 ){
				color[i] = WHITE;
				pie[i] = -1; 
			} else {
				color[i] = BLACK;
				pie[i] = -1;
			}
		}
		time = 0;
		x = 0;
		y = 0;
		for ( i = 0 ; i < N ; i++ ){
			if ( color[i] == WHITE ){
				x = DFS_visit(i);
				if ( x > y )
					y = x;
			}
		}
		printf("%d\n",y);
	}
}

