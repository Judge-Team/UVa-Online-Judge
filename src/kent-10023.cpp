#include <stdio.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

struct Big_num{
	char	value[1010];
	int	length;
};

struct Big_num source;

void add( struct Big_num *target , struct Big_num *src )
{
	int i , j ;
	for ( i = 0 ; i < src->length ; i++ ){
		target->value[i] += src->value[i];
		for ( j = i ; target->value[j] > 9 ; j++ ){
			target->value[j+1] += target->value[j]/10;
			target->value[j] = target->value[j]%10;
			if ( j+1 > target->length )
				target->length++;
		}
	}
}

void add_int( struct Big_num *target , int num )
{
	int j;
	target->value[0] += num;
	for ( j = 0 ; target->value[j] > 9 ; j++ ){
		target->value[j+1] += target->value[j]/10;
		target->value[j] = target->value[j]%10;
		if ( j+1 > target->length )
			target->length++;
	}
}
void cut( struct Big_num *target , struct Big_num *src )
{
	int i , j ;
	for ( i = 0 ; i < src->length ; i++ ){
		target->value[i] -= src->value[i];
		for ( j = i ; target->value[j] < 0 ; j++ ){
			target->value[j+1]--;
			target->value[j] += 10;
			if ( j+1 == target->length-1 && target->value[j+1] == 0 )
				target->length--;
		}
	}
}

void Multiplication( struct Big_num *target , int num )
{
	struct Big_num *temp;
	temp = (struct Big_num*)calloc( 1 , sizeof(struct Big_num) );
	int i , j , k ;
	int check;
	k = 0;
	temp->length = target->length;
	
	do{
		for ( i = 0 ; i < target->length ; i++ ){
			temp->value[i+k] += target->value[i]*(num%10);
			j = i+k;
			while ( temp->value[j] > 9 ){
				temp->value[j+1] += temp->value[j]/10;
				temp->value[j] = temp->value[j]%10;
				j++;
				if( j+1 > temp->length )
					temp->length++;
			}
		}
		temp->length++;
		k++;
		num = num/10;
	}while (num != 0);
	target->length = temp->length;
	check = 0;
	for ( i = temp->length-1 ; i >= 0 ; i-- ){
		if ( check == 0 && temp->value[i] == 0 ){
			target->length--;
		} else {
			check = 1;
		}
		target->value[i] = temp->value[i];		
	}
	if (target->length == 0)
		target->length++;
	free(temp);

}

int bigcmp( struct Big_num *A , struct Big_num *B )
{
	int i;
	if( A->length > B->length )
		return 1;
	else if ( A->length < B->length )
		return -1;
	else {
		for ( i = A->length ; i >= 0 ; i-- ){
			if ( A->value[i] > B->value[i] )
				return 1;
			else if ( A->value[i] < B->value[i] )
				return -1;
		}
		/* equal */
		return 0;
	}
}

void init( struct Big_num * A , struct Big_num * B )
{
	int i;
	for ( i = 0 ; i < 1010 ; i++ ){
		A->value[i] = 0;
		B->value[i] = 0;
		source.value[i] = 0;
	}
}

int main()
{
	FILE *in , *out;
	int num;
	int i , j , k , x , y , z;
	int check;
	int T;
	struct Big_num Reg , Ans , Tmp;
	char temp[1000];
	in = stdin;/*fopen("10023.in","r");*/
	fscanf( in , "%d" , &num );
	for ( i = 0 ; i < num ; i++ ){
		init( &Ans , &Reg );
		fscanf( in , "%s" , temp);
		source.length = strlen(temp);
		for ( j = 0 , k = source.length-1 ; j < source.length ; j++ , k-- ){
			source.value[k] = temp[j] - '0';
		}
		Reg.length = 2;
		Ans.length = 1;
		Ans.value[0] = 0;
		for ( j = source.length-1 ; j >= 0 ; j-=2 ){
			if ( j%2 == 0 ){
				j++;
				Reg.length--;
			}
			if ( Reg.length == 1 && source.value[j] > 0 ){
				Reg.length++;	
			}

			Reg.value[1] = source.value[j];
			Reg.value[0] = source.value[j-1];
			for ( x = 0 ; x <= 9 ; x++ ){
				memcpy( &Tmp , &Ans , sizeof(struct Big_num) );
				Multiplication( &Tmp , 20 );
				add_int( &Tmp , x );
				Multiplication( &Tmp , x );
				if ( bigcmp( &Tmp , &Reg ) == 1 )
					break;
			}
			memcpy( &Tmp , &Ans , sizeof(struct Big_num) );
			Multiplication( &Tmp , 20 );
			add_int( &Tmp , x-1 );
			Multiplication( &Tmp , x-1 );
			cut( &Reg , &Tmp );
			Multiplication( &Ans , 10 );
			Ans.value[0] = x-1;
				
			Multiplication( &Reg , 100 );
		}
		check = 0;
		for( x = Ans.length ; x >= 0 ; x-- )
		{
			if ( Ans.value[x] > 0 )
				check = 1;
			if ( check == 0 && Ans.value[x] == 0 )
				continue;

			printf("%d",Ans.value[x]);
		}
		if( Ans.length == 1 && Ans.value[0] == 0 )
			printf("0");
		printf("\n");
		if( i != num-1 )	
			printf("\n");
	}

}

