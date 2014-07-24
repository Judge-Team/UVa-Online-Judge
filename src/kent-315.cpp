#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define	N	100
#define	NODE	10000
#define WHITE      1
#define GRAY       2
#define BLACK      3


int head[NODE];
int tail[NODE];
int index[NODE];
int adj[N];

int color[N];
int pie[N];
int time;


int link_num;

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

int DFS_visit( int v );

int main()
{
	int i,j;
	int tmp;
	int n;
	int t , c;
	int src , dst;
	int critical;
	int block_num;
	FILE *in;
	char buf[1024];
	
	in = stdin;

	while ( fscanf(in,"%d",&n) != EOF ){
		if ( n == 0 )
			break;
		// init 
		for ( i = 0 ; i < NODE ; i++ ){
			head[i] = 0;
			tail[i] = 0;
		}
		for ( i = 0 ; i < n ; i++ ){
			adj[i] = -1;
		}

		for ( j = 0 , i = 0 ; j <= n ; j++ ){
			scanf("%d",&src);
			if ( src == 0 )
				break;
			while (1){

				if ( (c = fgetc(in)) == '\n') 
					break; 
				else if ( isspace(c)) 
					continue; 
				else 
					ungetc(c,in);
				scanf("%d",&dst);
				head[i] = src;
				tail[i] = dst;
				index[i] = i++;
				head[i] = dst;
				tail[i] = src;
				index[i] = i++;
			}
		}
		link_num = i;
		qsort( index , link_num , sizeof(index[0]) , comp_func );
		
		for ( i = 0 , t = 0 ; i < link_num ; i++ ){
			if ( t < head[index[i]] ){
				t = head[index[i]];
				adj[t-1] = i;
			}
		}

		for ( j = 0 , critical = 0 ; j < n ; j++ ){
			// init DFS
			for ( i = 0 ; i < n ; i++ ){
				if ( adj[i] != -1 ){
					if ( i != j )
						color[i] = WHITE;
					else
						color[i] = BLACK;
					pie[i] = -1;
				} else{
					color[i] = BLACK;
				}
				pie[i] = -1;
			}
			time = 0;
			for ( i = 0 , t = 0 ; i < n ; i++ ){
				if ( color[i] == WHITE ){
					DFS_visit(i);
					t++;
				}
			}
			if ( t > 1 )
				critical++;
		}
		printf("%d\n",critical);
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
