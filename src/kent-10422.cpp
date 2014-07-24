#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX	2000


int map[5][5];
int gold[5][5] = {
	{ 1,1,1,1,1 },
	{ 0,1,1,1,1 },
	{ 0,0,2,1,1 },
	{ 0,0,0,0,1 },
	{ 0,0,0,0,0 }
};

struct Q {
	int map[5][5];
	int depth;
};

struct Q queue[MAX];
struct Q queue2[MAX];

int esp , ebp; 
int push( int depth )
{
	int i , j;
	int ptr , flag;
	flag = true;
	for ( ptr = 0 ; ptr < esp ; ptr++ ){
		flag = false;
		for ( i = 0 ; i < 5; i++ ){
			for ( j = 0 ; j < 5 ;j++ ){
				if ( queue[ptr].map[i][j] != map[i][j] ){
					flag = true;
					break;
				}
			}
			if ( flag == true )
				break;
		}
		if ( flag == false )
			break;
	}
	if ( flag == false ){
		if ( depth < queue[ptr].depth ){
			queue[ptr].depth = depth;
		}
		return 0;
	}

	for ( i = 0 ; i < 5 ; i++ )
		for ( j = 0 ; j < 5; j++ )
			queue[esp].map[i][j] = map[i][j];
	queue[esp].depth = depth;
	esp = (esp+1)%MAX;
	return 1;
}

int push_2( int depth )
{
	int i , j;
	int ptr , flag;
	flag = true;
	for ( ptr = 0 ; ptr < esp ; ptr++ ){
		flag = false;
		for ( i = 0 ; i < 5; i++ ){
			for ( j = 0 ; j < 5 ;j++ ){
				if ( queue2[ptr].map[i][j] != map[i][j] ){
					flag = true;
					break;
				}
			}
			if ( flag == true )
				break;
		}
		if ( flag == false )
			break;
	}
	if ( flag == false ){
		if ( depth < queue2[ptr].depth ){
			queue2[ptr].depth = depth;
		}
		return 0;
	}

	for ( i = 0 ; i < 5 ; i++ )
		for ( j = 0 ; j < 5; j++ )
			queue2[esp].map[i][j] = map[i][j];
	queue2[esp].depth = depth;
	esp = (esp+1)%MAX;
	return 1;
}


int pop()
{
	int ptr = ebp;
	ebp = (ebp+1)%MAX;
	return ptr;
}

int main()
{
	int case_num;
	int case_counter;
	int i , j , t , k;
	int x , y;
	int ptr;
	int depth;
	int flag;
	int min_way;
	int Mtmp[5][5];
	char buf[10];
	char T;
	int counter;
	int esp_q1;
	int esp_q2;

	scanf("%d\n",&case_num);
	//scanf("%c");
	//getchar();
	for ( case_counter = 0 ; case_counter < case_num ; case_counter++ ){	
		//scanf("\n");
		for ( i = 0 ; i < 5 ; i++ ){
			gets(buf);
			for ( j = 0 ; j < 5 ; j++ ){
				//if ( j == 4 )
				//	scanf("%c\n",&T);
				//else
				//	scanf("%c",&T);
				//T = getchar();
				T = buf[j];
				//printf("%2c",T);
				if ( T == '0' )
					map[i][j] = 0;
				else if ( T == '1' )
					map[i][j] = 1;
				else if ( T == ' ' )
					map[i][j] = 2;
				//printf("%2d",map[i][j]);
			}
			//getchar();
			//scanf("\n");
			//printf("\n");
		}
		//printf("\n");

		// start BFS
		esp = 0;
		ebp = 0;
		push(0);
		counter = 0;

		while ( ebp != esp ){
			counter++;
			ptr = pop();
			for ( i = 0 ; i < 5; i++ )
				for ( j= 0 ; j < 5; j++ )
					Mtmp[i][j] = queue[ptr].map[i][j];
			depth = queue[ptr].depth+1;
			if ( depth > 6 )
				continue;
			//printf("depth %d way\n",depth);
			// move eight way
			for ( i = -2 ; i <= 2 ; i++ ){
				if ( i == 0 )
					continue;
				for ( j = -1 ; j <= 1 ; j++ ){
					if ( j == 0 )
						continue;
					// copy from map
					for ( t = 0 ; t < 5 ; t++ ){
						for ( k = 0 ; k < 5; k++ ){
							map[t][k] = Mtmp[t][k];
							if ( Mtmp[t][k] == 2 ){
								x = k;
								y = t;
							}
						}
					}

					if ( i == 1 || i == -1 )
						t = j*2;
					else 
						t = j;
					// move eight ways
					if ( y+i >= 0 && y+i < 5 ){
						if ( x+t >= 0 && x+t < 5 ){
							k = map[y][x];
							map[y][x] = Mtmp[y+i][x+t];
							map[y+i][x+t] = k;
							flag = push(depth);
						} else {
							continue;
						}
					}else{
						continue;
					}

					
					for ( t = 0 ; t < 5 ; t++ ){
						for ( k = 0 ; k < 5; k++ ){
						//	printf("%2d",map[t][k]);
						}
						//printf("\n");
					}
					//printf("\n");

				}
			}
		}
		//printf("%d\n",counter);
		esp_q1 = esp;
		
		// second BFS
		esp = 0;
		ebp = 0;
		for ( i = 0 ; i < 5; i++ )
			for ( j = 0 ; j < 5 ; j++ )
				map[i][j] = gold[i][j];

		push_2(0);
		//printf("esp:%d\n",esp);

		while ( ebp != esp ){
			ptr = pop();
			for ( i = 0 ; i < 5; i++ )
				for ( j= 0 ; j < 5; j++ )
					Mtmp[i][j] = queue2[ptr].map[i][j];
			depth = queue2[ptr].depth+1;
			if ( depth > 6 )
				continue;
			// move eight way
			for ( i = -2 ; i <= 2 ; i++ ){
				if ( i == 0 )
					continue;
				for ( j = -1 ; j <= 1 ; j++ ){
					if ( j == 0 )
						continue;
					// copy from map
					for ( t = 0 ; t < 5 ; t++ ){
						for ( k = 0 ; k < 5; k++ ){
							map[t][k] = Mtmp[t][k];
							if ( Mtmp[t][k] == 2 ){
								x = k;
								y = t;
							}
						}
					}
					if ( i == 1 || i == -1 )
						t = j*2;
					else 
						t = j;
					// move eight ways
					if ( y+i >= 0 && y+i < 5 ){
						if ( x+t >= 0 && x+t < 5 ){
							k = map[y][x];
							map[y][x] = Mtmp[y+i][x+t];
							map[y+i][x+t] = k;
							flag = push_2(depth);
						} else {
							continue;
						}
					}else{
						continue;
					}
				}
			}
		}
		esp_q2 = esp;

		min_way = 12;
		for ( i = 0 ; i < esp_q1 ; i++ ){
			for ( j = 0 ; j < esp_q2 ; j++ ){
				flag = false;
				for ( t = 0 ; t < 5 ; t++ ){
					for ( k = 0 ; k < 5 ; k++ ){
						if ( queue[i].map[t][k] != queue2[j].map[t][k] ){
							flag = true;
							break;
						}
					}
					if ( flag == true ){
						break;
					}
				} 

				if ( flag == false ){
					//printf("Q1:%d , Q2:%d\n",queue[i].depth , queue2[j].depth);
					break;
				}
			}
			if ( flag == false && min_way > queue[i].depth + queue2[j].depth ){
				//printf("esp: %d %d \n",esp_q1 , esp_q2);
				min_way = queue[i].depth + queue2[j].depth;
			}
		}
		if ( min_way < 11 )
			printf("Solvable in %d move(s).\n",min_way);
		else
			printf("Unsolvable in less than 11 move(s).\n");
	}
}
