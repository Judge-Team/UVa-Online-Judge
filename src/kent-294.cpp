#include<cstdio>
#include<cmath>
#include<vector>
using namespace std;

#define prime_range 	31622

char is_prime[prime_range+1];

void sieve_method()
{
	memset( is_prime , 1 , prime_range+1 );
	int i , k , m;
	m = (int) ( sqrt(prime_range) + 0.001 );
	for ( i = 2 ; i <= m ; i++ ){
		if ( is_prime[i] == 1 ){
			for ( k = i*i ; k > i ; k = k-i ){
				is_prime[k] = 0;
			}
		}
	}
}


int main()
{
	FILE *in;
	int num;
	int num_counter;
	int L , U;
	int i , j , k , x , y;
	int m , g;
	int max_prime_num;
	int max_prime;
	int prime_tmp , prime_num_tmp , tmp ;



	sieve_method();
	max_prime_num = 0;

	scanf("%d",&num);
	for ( num_counter = 0 ; num_counter < num ; num_counter++ ){
		scanf("%d %d",&L,&U);
		max_prime = 0;
		max_prime_num = 0;
		for ( g = L ; g <= U ; g++ ){
			m = (int) (sqrt(g) + 0.001);
			prime_tmp = g;
			prime_num_tmp = 1;
			for ( i = 2 ; i <= m ; i++ ){
				tmp = 0;
				if ( (is_prime[i] == 1) && (prime_tmp%i == 0) ){
					
					while ( prime_tmp%i == 0 ){
						tmp++;
						prime_tmp = prime_tmp/i;
					}		
					prime_num_tmp = prime_num_tmp*(tmp+1);
				}
			}
			if ( prime_tmp > 1 ){
				prime_num_tmp = prime_num_tmp*2; 
			}

			if ( max_prime_num < prime_num_tmp ){
				max_prime_num = prime_num_tmp;
				max_prime = g;
			}
		}
		printf("Between %d and %d, %d has a maximum of %d divisors.\n",L,U,max_prime , max_prime_num );
	}

}
