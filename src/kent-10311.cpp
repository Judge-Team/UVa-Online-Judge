#include<cstdio>
#include<cmath>
#include<vector>
using namespace std;

#define prime_range 	10000
#define prime_num  	10000

char is_prime[prime_range+1];
int  prime_list[prime_num + 1];
int  prime_number;

void sieve_method()
{
	memset( is_prime , 1 , prime_range+1 );
	int i , k , m;
	m = (int) ( sqrt(prime_range) + 0.001 );
	for ( i = 2 ; i < m ; i++ ){
		if ( is_prime[i] == 1 ){
			if ( i != 2 && i%2 == 0 )
				continue;
			for ( k = i*i ; k <= prime_range ; k = k+i ){
				is_prime[k] = 0;
			}
		}
 	}
}

int binary_search( int upper_bound , int lower_bound , int target_num )
{
	int check;
	int max_index = upper_bound;
	int answer = 0;
	int tmp;
	int mid;
	while ( upper_bound > lower_bound ){
		mid = (upper_bound + lower_bound)/2;
		tmp = prime_list[mid] + prime_list[max_index];
		if( tmp > target_num )
		{
			upper_bound = mid;
		} else {
			if ( tmp == target_num)
				return mid;
			lower_bound = mid + 1;

		}
	}
	return upper_bound;
}

int is_prime_big( int target ){
	int i;
	if ( target <= 1 )
		return 0;
	if ( target%2 == 0 )
		return 0;

	for ( i = 0 ; i < prime_number && prime_list[i]*prime_list[i] <= target ; i++ )
	{
		if ( target%prime_list[i] == 0 )
			return 0;
	}
	return 1;
}


int main()
{
	int target_num;
	int i , j;
	//int max_index , min_index;
	//int max_prime , min_prime;
	//int upper_bound , lower_bound;
	int tmp;
	//int mid;
	int have_answer;
	int counter;
	sieve_method();
	is_prime[0] = 0;
	is_prime[1] = 0;
	counter = 0;
	prime_list[0] = 2;
	for ( i = 2 ; i <= prime_range ; i++ ){
		if ( is_prime[i] == 1 ){
			prime_list[counter] = i;
			counter++;
		}
	}
	prime_number = counter;
	while ( scanf( "%d",&target_num) != EOF ){
		if ( target_num%2 == 1 || target_num == 2 ){

			tmp = target_num - 2;
			if ( (tmp < prime_range && is_prime[tmp] == 1) 
			  || (tmp >= prime_range && is_prime_big(tmp) == 1) ){
				printf("%d is the sum of 2 and %d.\n",target_num,tmp);
			} else {
				printf("%d is not the sum of two primes!\n",target_num);
			}

		} else {

			have_answer = 0;
			i = target_num/2;
			if ( i%2 == 0 )
				i++;
			for ( ; i >= 3 ; i-- ) {

				//j = binary_search(i , min_index ,target_num);
				tmp = target_num - i;
				if ( tmp - i <= 0 )
					continue;
				if ( tmp < prime_range ){
					if ( is_prime[tmp] == 0 )
						continue;
				} else {
					if ( is_prime_big(tmp) == 0)
						continue;
				}
				if ( i < prime_range ){
					if ( is_prime[i] == 0)
						continue;	
				} else {
					if ( is_prime_big(i) == 0)
						continue;
				}
				printf("%d is the sum of %d and %d.\n",target_num,i,tmp);
				have_answer = 1;
				break;
			}

			if ( have_answer == 0 ){
				printf("%d is not the sum of two primes!\n",target_num);
			}
		}
	}
}
