#include <stdlib.h>
#include <stdio.h>
#include <cstdio>
#include <string.h>
#include <map>
#include <algorithm>
using namespace std;


/*#include <stdio.h>
#include <stdlib.h>*/
/* d = a + b + c -> a + b = c - d*/
struct LIST {
	int value;
	int	a;
	int	b;
	int index;
};

int 	List[1001];
struct	LIST Z[2004002];
int	list_num;


void swap(struct LIST *a , struct LIST *b)
{
	struct LIST temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int compare(const void * a, const void * b)
{
	struct LIST c , d;
	c = *(struct LIST*)a;
	d = *(struct LIST*)b;
	if ( c.value > d.value ){
		return 1;
	} else if (c.value < d.value){
		return -1;
	} else {
		return (c.index - d.index);
	}
}


int main( int argc , char *argv[] )
{
	FILE 	*in;
	int 	i , j , k;
	int	max_number;
	int	tmp;


	in = stdin;



	while ( fscanf(in , "%d" , &list_num) , list_num ){
		max_number = -9999999;

		for (i = 0 ; i < list_num ; i++){
			fscanf( in , "%d" , &List[i] );
		}


		for (i = 0 , k = 0 ; i < list_num ; i++){
			for (j = 0 ; j < list_num ; j++){
				if( i == j )
					continue;
				Z[k].value = List[i] + List[j];
				Z[k].a = i;
				Z[k].b = j;
				k++;
			}
		}
		for (i = 0 ; i < list_num ; i++){
			for (j = 0 ; j < list_num ; j++){
				if( i == j )
					continue;

				Z[k].value = List[i] - List[j];
				Z[k].a = i;
				Z[k].b = j;
				k++;
			}
		}
		qsort( Z , k , sizeof(Z[0]) , compare );

		for ( i = 0 ; i < k - 1 ; i++ ){
			j = 0;
			while( Z[i+j].value == Z[i+j+1].value ){
				if( Z[i].a != Z[i+1].a &&
				    Z[i].b != Z[i+1].b &&
				    Z[i].a != Z[i+1].b &&
				    Z[i].b != Z[i+1].a ){

					if( List[Z[i].a] + List[Z[i].b]
					  + List[Z[i+1].b] == List[Z[i+1].a] ){
						tmp = Z[i+1].a;
						max_number = ( List[tmp] > max_number )
						             ?List[tmp]:max_number;
					}
				}
				j++;
			}

		}
		if( max_number > -9999999)
			printf("%d\n",max_number);
		else
			printf("no solution\n");
	}


}
