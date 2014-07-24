#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	WHITE	0
#define	GRAY	1
#define	BLACK	2

/*
 *	N	0
 *
 *	W	1
 *
 *	S	2
 *
 *	E	3
 *
 * */

struct point {
	int r;
	int c;
	int way;
};

struct node {
	int pass_way[3];
	char pass[4];
	int color;
	int d;
	struct point pie;
};
struct node map[10][10][4];
int start_r , start_c;
int end_r, end_c;

struct point queue[400];
int Q_start , Q_end;

int insertQueue( int r , int c , int way )
{
	queue[Q_end].r = r;
	queue[Q_end].c = c;
	queue[Q_end].way = way;
	Q_end = (Q_end + 1)%400 ;
}

int outputQueue(){
	int ptr;
	ptr = Q_start;
	Q_start = (Q_start+1)%400;
	return ptr;
}

int get_way( char d )
{
	if ( d == 'N' )
		return 0;
	if ( d == 'W' )
		return 1;
	if ( d == 'S' )
		return 2;
	if ( d == 'E' )
		return 3;
}

int move_point( int r , int c , int way , int pass_way , int *new_r , int *new_c )
{
	int new_way;
	if ( pass_way == 0 ){ // LEFT
		new_way = (way+1)%4;
	} else if ( pass_way == 1 ){ // FORWARD 
		new_way = way;
	
	} else if ( pass_way == 2 ){ // RIGHT
		new_way = (way-1+4)%4;
	}
	*new_r = r;
	*new_c = c;
	if ( new_way == 0 ){	// N
		*new_r = r - 1;
	}
	if ( new_way == 1 ){	// W
		*new_c = c - 1;
	}
	if ( new_way == 2 ){	// S
		*new_r = r + 1;
	}
	if ( new_way == 3 ){	// E
		*new_c = c + 1;
	}
	return new_way;
}

int main()
{
	int i , j , k ,l;
	char caseName[20];
	int r1 ,r2 ,c1 ,c2; 
	int way , start_way , new_way;
	int flag;
	char buffer[5];
	int ptr;

	while ( scanf("%s",caseName) != EOF ){
		if ( strcmp(caseName,"END") == 0 )
			break;

		// init 
		for ( i = 0 ; i < 10 ; i++ ){
			for ( j = 0 ; j < 10 ; j++ ) {
				for ( k = 0 ; k < 4 ; k++ ) {
					for ( l = 0 ; l < 3 ; l++ ) {
						map[i][j][k].pass_way[l] = 0;
					}
					map[i][j][k].color = WHITE;
					map[i][j][k].pie.r = 0;
					map[i][j][k].pie.c = 0;

				}
			}
		}


		scanf("%d%d%s%d%d",&r1,&c1,buffer,&r2,&c2);
		start_r = r1;
		start_c = c1;
		//map[start_r][start_c][get_way(buffer[0])].pass_way[1] = 1;	// forward
		start_way = get_way(buffer[0]);
		end_r = r2;
		end_c = c2;

		while ( scanf("%d",&r1) != EOF ){
			if ( r1 == 0 )
				break;
			scanf("%d",&c1);
			i = 0;
			while (1){
				scanf("%s",buffer);
				if ( buffer[0] == '*' ){
					break;
				}
				// mark each node can pass way
				strncpy( map[r1][c1][get_way(buffer[0])].pass , buffer+1 , strlen(buffer)-1 );
				for ( i = 1 ; i < strlen(buffer) ; i++ ){
					if ( buffer[i] == 'L' )
						map[r1][c1][get_way(buffer[0])].pass_way[0] = 1;
					if ( buffer[i] == 'F' )
						map[r1][c1][get_way(buffer[0])].pass_way[1] = 1;
					if ( buffer[i] == 'R' )
						map[r1][c1][get_way(buffer[0])].pass_way[2] = 1;
				}
			}
		}

		// start BFS 

		Q_start = 0;
		Q_end = 0;
		//insertQueue( start_r , start_c , start_way );
		map[start_r][start_c][start_way].color = GRAY;
		map[start_r][start_c][start_way].d = 0;
		new_way = move_point(start_r,start_c,start_way,1,&r2,&c2);
		map[r2][c2][new_way].color = GRAY;
		map[r2][c2][new_way].d = map[start_r][start_r][start_way].d + 1;
		map[r2][c2][new_way].pie.r = start_r;
		map[r2][c2][new_way].pie.c = start_c;
		map[r2][c2][new_way].pie.way = start_way;
		insertQueue( r2 , c2 , new_way );
		
		flag = false;
		while ( Q_start != Q_end ){

			ptr = outputQueue();
			r1 = queue[ptr].r;
			c1 = queue[ptr].c;
			way = queue[ptr].way;

			if ( r1 == end_r && c1 == end_c ){
				
				flag = true;
				break;
			}

			// go for each point adj r1 , r2 , way
			//for ( j = 0 ; j < strlen(map[r1][c1][way].pass) ; j++ ){
			//	if ( map[r1][c1][way].pass[j] == 'L' )
			//		i = 0;
			//	if ( map[r1][c1][way].pass[j] == 'F' )
			//		i = 1;
			//	if ( map[r1][c1][way].pass[j] == 'R' )
			//		i = 2;
			for ( i = 0 ; i < 3 ; i++ ){
				if ( map[r1][c1][way].pass_way[i] == 1 ){
					new_way = move_point( r1 , c1 , way , i , &r2 , &c2);
					if ( map[r2][c2][new_way].color == WHITE ){
						map[r2][c2][new_way].color = GRAY;
						map[r2][c2][new_way].d = map[r1][c1][way].d + 1;
						map[r2][c2][new_way].pie.r = r1;
						map[r2][c2][new_way].pie.c = c1;
						map[r2][c2][new_way].pie.way = way;
						insertQueue( r2 , c2 , new_way );
					}
				}
			}
			map[r1][c1][way].color = BLACK;
		}


		// print out the answer
		Q_start = 0;
		Q_end = 0;
		if ( flag == true ){
			while ( !(r1 == 0 && c1 == 0) ){
				insertQueue(r1,c1,way);
				r2 = map[r1][c1][way].pie.r;
				c2 = map[r1][c1][way].pie.c;
				way = map[r1][c1][way].pie.way;
				r1 = r2;
				c1 = c2;
			}
			printf("%s\n ",caseName);
			i = 0;
			while (Q_start != Q_end){
				ptr = --Q_end;
				printf(" (%d,%d)",queue[ptr].r,queue[ptr].c);
				if ( i == 9 && Q_start != Q_end ){
					printf("\n ");
					i = 0;
				}else{
					i++;
				}
			}
			printf("\n");
		} else {
			printf("%s\n  No Solution Possible\n",caseName);
		}
		
	}
}
