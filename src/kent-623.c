#include <stdio.h>

struct Big_num{
	char	value[3000];
	int	length;
};

struct Big_num answer[1001];

void Multiplication( struct Big_num *target , int num )
{
	struct Big_num *temp;
	temp = calloc( 1 , sizeof(struct Big_num) );
	int i , j , k ;
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
		/*if( k + target->length > temp->length )*/
		temp->length++;
		k++;
		num = num/10;
	}while (num != 0);
	target->length = temp->length;
	for ( i = temp->length-1 ; i >= 0 ; i-- ){
		target->value[i] = temp->value[i];		
	}
	free(temp);

}

int main()
{
	FILE *in , *out;
	int num;
	int i , j;
	int check;
	in = stdin;/*fopen("623.in","r");*/
	
	answer[0].value[0] = 1;
	answer[0].length = 1;
	
	for ( i = 0 ; i < 1000 ; i++ ){
		Multiplication( &answer[i] , i+1 );
		
		memcpy( &(answer[i+1]) , &(answer[i]) , sizeof(struct Big_num) );
	}

	while ( fscanf(in , "%d" , &num) != EOF ){

		printf("%d!\n",num);
		if ( num == 0 ){
			printf("1\n");
			continue;
		}
		check = 0;
		for ( i = answer[num-1].length-1 ; i >= 0 ; i-- ){
			if ( answer[num-1].value[i] != 0 && check == 0 )
				check = 1;
			if ( check == 0 )
				continue;
			printf("%d",answer[num-1].value[i]);
		}
		printf("\n");
	}
}
