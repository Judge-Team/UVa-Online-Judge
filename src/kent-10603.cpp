#include <stdio.h>
#include <stdlib.h>

#define MAX_QUE	8000000

int water_use[201][201][201];

int capacity[3];
int destion_water;


struct state {
	int water[3];
	int total;
};
struct state S;

struct state queue[MAX_QUE];
int Q_start;
int Q_end;

int min( int a , int b )
{
	if ( a > b )
		return b;
	else 
		return a;
}

void Q_push( struct state *Q ){

	queue[Q_end].water[0] = Q->water[0];  
	queue[Q_end].water[1] = Q->water[1];  
	queue[Q_end].water[2] = Q->water[2];  
	queue[Q_end].total = Q->total;
	Q_end = (Q_end+1)%MAX_QUE;
}

int Q_pop(){
	int ptr = Q_start;
	Q_start = (Q_start+1)%MAX_QUE;
	return ptr;
}

int pour( int src , int dst )
{

	int W=0;
	if ( src == dst )
		return 0;
	// water of src is more then the rest of dst capacity
	if ( S.water[src] > capacity[dst] - S.water[dst] ){
		S.water[src] = S.water[src] - (capacity[dst] - S.water[dst]);
		S.water[dst] = capacity[dst];	// full
		W = capacity[dst] - S.water[dst];
	} else { // water of src is less then the rest of dst capacity
		S.water[dst] = S.water[dst] + S.water[src];
		S.water[src] = 0;
		W = S.water[src];
	}
	S.total = W; 
}

int pour_v2( struct state *tmp , int src , int dst )
{
	if ( src != dst ){
		int w = min(tmp->water[src],capacity[dst] - tmp->water[dst]);
		tmp->water[src] -= w;
		tmp->water[dst] += w;
		tmp->total += w;
   	}
}

int main()
{
	struct state tmp;
	int i , j , k , t;
	int a, b ,c ,d;
	int case_num;
	int flag;
	int near , near_total;
	int q;

	scanf("%d",&case_num);

	for ( t = 0 ; t < case_num ; t++ ){
		flag = false;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		capacity[0] = a;
		capacity[1] = b;
		capacity[2] = c;
		destion_water = d;
		// init state
		S.water[0] = 0;
		S.water[1] = 0;
		S.water[2] = capacity[2];
		S.total = 0;
		Q_start = 0;
		Q_end = 0;
		near = MAX_QUE;
		near_total = 0;
		for ( i = 0 ; i < 201 ; i++ ){
			for ( j = 0 ; j < 201 ; j++ ){
				for (k = 0 ; k < 201 ; k++ ){
					water_use[i][j][k] = 0;
				}
			}
		}
		water_use[0][0][capacity[2]] = 1;
		// BFS
		Q_push(&S);

		while ( Q_start != Q_end ){
	
			q = Q_pop();
			S.water[0] = queue[q].water[0];
			S.water[1] = queue[q].water[1];
			S.water[2] = queue[q].water[2];
			S.total = queue[q].total;

			//
			for ( i = 0 ; i < 3 ; i++ ){
				if ( destion_water == S.water[i] ){
					flag = true;
					printf("%d %d\n",S.total,destion_water);
					break;
				}
			}
			if ( flag == true )
				break;

			// update the nearest value of D
			for ( i = 0 ; i < 3 ; i++ ){
				if ( destion_water - S.water[i] < near && destion_water - S.water[i] > 0 ){
					near = destion_water - S.water[i];
					near_total = S.total;
				}	
			}

			for ( i = 0 ; i < 3 ; i++ ){
				for ( j = 0 ; j < 3 ; j++ ){
					if ( i == j || S.water[i] == 0 )
						continue;
					tmp.water[0] = S.water[0];
					tmp.water[1] = S.water[1];
					tmp.water[2] = S.water[2];
					tmp.total = S.total;
					pour_v2( &tmp , i , j );

					if ( water_use[tmp.water[0]][tmp.water[1]][tmp.water[2]] == 1 )
						continue;
					else {
						water_use[tmp.water[0]][tmp.water[1]][tmp.water[2]] = 1;
						Q_push(&tmp);
					}				
				}
			}
		}
		if ( flag == false )
			printf("%d %d\n",near_total , destion_water - near );
	}
}
