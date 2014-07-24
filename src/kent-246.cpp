#include<cstdio>
#include<cmath>
#include<vector>
using namespace std;

struct CARD {
	int card[52];
	int num;
	int top;
	int buttom;
};


struct Trace {
	int round;
	struct CARD *Pile[7];
	struct CARD *Deck;
	struct Trace *next;
	struct Trace *end;
};


struct CARD pile[7];
struct CARD deck;
struct Trace *trace[999999];
int duplicate;

void dealt_card_to_top( struct CARD *dst , struct CARD *src )
{
	if ( dst->card[dst->top] != 0 )
		dst->top = (52 + dst->top - 1)%52;
	dst->card[dst->top] = src->card[src->top];
	src->top = (src->top+1)%52;
	dst->num++;
	src->num--;
	
}

void dealt_card_to_buttom( struct CARD *dst , struct CARD *src )
{
	dst->buttom = (dst->buttom + 1)%52;
	dst->card[dst->buttom] = src->card[src->top];
	src->top = (src->top+1)%52;	
	dst->num++;
	src->num--;
}

void insert_card_to_top( struct CARD *dst , struct CARD *src )
{
	dst->top = (52 + dst->top - 1)%52;
	dst->card[dst->top] = src->card[src->buttom];
	src->buttom = (52 + src->buttom - 1)%52;
	dst->num++;
	src->num--;	
}

void insert_card_to_buttom( struct CARD *dst , struct CARD *src )
{
	dst->buttom = (dst->buttom + 1)%52;
	dst->card[dst->buttom] = src->card[src->buttom];
	src->buttom = (52 + src->buttom - 1)%52;	
	dst->num++;
	src->num--;
}

int hash_of_trace()
{
	int Hash = 0;
	int i,j;
	for ( i = 0 ; i < 7 ; i++ ){
		for ( j = 0 ; j < pile[i].num ; j++ ){
			Hash += pile[i].card[ (pile[i].top+j)%52 ];
		}
		Hash *= 10;
	}
	for (j = 0 ; j < deck.num ; j++)
		Hash += deck.card[(deck.top+j)%52];
	if ( Hash < 0 )
		Hash = Hash*-1;
	return Hash%999999;
}

bool check_duplicate()
{
	int i,j;
	int Hash;
	int check;
	struct Trace *T_ptr;
	Hash = hash_of_trace();
	T_ptr = trace[Hash];

	for ( ; T_ptr != NULL ; T_ptr = T_ptr->next ){
		check = 0;
		for ( i = 0 ; i < 7 ; i++ ) {
			for ( j = 0 ; j < pile[i].num && pile[i].num == T_ptr->Pile[i]->num ; j++ ){
				if ( pile[i].card[(pile[i].top+j)%52] != T_ptr->Pile[i]->card[(T_ptr->Pile[i]->top+j)%52] ){
					check = 1;
					break;
				}
			}
			if( pile[i].num != T_ptr->Pile[i]->num )
				check = 1;
			if ( check == 1 )
				break;
		}

		for ( j = 0 ; j < deck.num && deck.num == T_ptr->Deck->num ; j++ ){
			if( deck.card[(deck.top+j)%52] != T_ptr->Deck->card[(T_ptr->Deck->top+j)%52] ){
				check = 1;
				break;
			}
			if ( check == 1 )
				break;
		}

		if ( deck.num != T_ptr->Deck->num )
			check = 1;
		if ( check == 0 ){
			duplicate = T_ptr->round;
			return true;
		}
	}
	return false;
}

void add_trace_data( int round )
{
	int i;
	int hash;
	struct CARD *P[7] , *D;
	struct Trace *T_ptr , *create; 


	for ( i = 0 ; i < 7 ; i++ ){
		P[i] = (struct CARD*)malloc(sizeof(struct CARD));	
		memcpy( P[i] , &pile[i] , sizeof(struct CARD) );
	}
	D = (struct CARD*)malloc(sizeof(struct CARD));
	memcpy( D , &deck , sizeof(struct CARD) );

	hash = hash_of_trace();
	create = (struct Trace*)malloc(sizeof(struct Trace));
	create->round = round;
	create->Deck = D;
	for ( i = 0 ; i < 7 ; i++ )
		create->Pile[i] = P[i];
	create->next = NULL;
	create->end = NULL;
	T_ptr = trace[hash];
	if ( trace[hash] == NULL ){
		trace[hash] = create;
		trace[hash]->end = create;
	} else {
		trace[hash]->end->next = create;
		trace[hash]->end = trace[hash]->end->next;
	}
}

void free_trace_data()
{
	struct Trace *tmp , *T_ptr;
	int k;
	int i,j;
	for ( i = 0 ; i < 999999 ; i++ ){
		if ( trace[i] == NULL )
			continue;
		T_ptr = trace[i];
		
		while ( trace[i] != NULL ){
			T_ptr = trace[i];
			trace[i] = trace[i]->next;
			free( T_ptr->Deck );
			for ( j = 0 ; j < 7 ; j++ )
				free( T_ptr->Pile[j] );
			free( T_ptr );
		}
		free(trace[i]);
		trace[i] = NULL;
	}
}

int check_over()
{
	if ( deck.num == 0 ){
		return 1;
	} else if ( deck.num == 52 ){
		return 2;
	} else if ( duplicate != 0 ){
		return 3;
	}
	
	return 0;
}

int main()
{
	int i , j , k;
	int first , second , last , last_2 , last_3 ;
	int tmp;
	int counter;
	int round;
	int check_num;
	FILE *in;
	in = stdin;//fopen("246.in","r");

	while ( fscanf(in,"%d",&tmp) != EOF){
		duplicate = 0;
		//memset( pile , 0 , sizeof(struct CARD)*7 );
		//memset( &deck , 0 , sizeof(struct CARD) );

		deck.num = 0;
		deck.top = 0;
		deck.buttom = 0;
		for ( i = 0 ; i < 52 ; i++ ){
			deck.card[i] = 0;
		}

		for ( i = 0 ; i < 7 ; i++ ){
			pile[i].num = 0;
			pile[i].top = 0;
			pile[i].buttom = 0;
			for ( j = 0 ; j < 52 ; j++ ){
				pile[i].card[j] = 0;
			}
		}

		for ( i = 0 ; i < 999999 ; i++ )
			trace[i] = NULL;

		if ( tmp == 0 )
			break;
		i = 0;
		deck.card[i] = tmp;
		for ( i = 1 ; i < 52 ; i++ ){ 
			fscanf(in,"%d",&tmp);
			deck.card[i] = tmp;
		}
		// init
		deck.top = 0;
		deck.buttom = 51;
		deck.num = 52;
		// first two card in each pile 
		for ( i = 0 ; i < 14 ; i++ ){
			dealt_card_to_top( &(pile[i%7]) , &deck );
		}
		round = 14;
		check_num = 16;
		
		while ( !check_over() ){
			for ( i = 0 ; i < 7 && !check_over() ; i++ ){

				if( pile[i].num != 0){
					dealt_card_to_top( &pile[i] , &deck );
					round++;
				}
				while ( pile[i].num >= 3 ){
					
					first = pile[i].buttom;
					second = (pile[i].buttom-1+52)%52;
					last = pile[i].top;
					last_2 = (pile[i].top+1)%52;
					last_3 = (pile[i].top+2)%52;

					if ( (pile[i].card[first]+pile[i].card[second]
								+pile[i].card[last])%10 == 0 ){

						insert_card_to_buttom(&deck,&(pile[i])); //first
						insert_card_to_buttom(&deck,&(pile[i])); //second
						dealt_card_to_buttom(&deck,&(pile[i]));  //last	

					}else if ( (pile[i].card[first]+pile[i].card[last]
								+pile[i].card[last_2])%10 == 0 ){
						
						insert_card_to_buttom(&deck,&(pile[i])); //first
						dealt_card_to_buttom(&deck,&(pile[i]));	 //last
						dealt_card_to_buttom(&deck,&(pile[i]));  //last2
						tmp = deck.card[ (52+deck.buttom-1)%52 ];
						deck.card[ (52+deck.buttom-1)%52 ] = deck.card[deck.buttom];
						deck.card[deck.buttom] = tmp;

					}else if ( (pile[i].card[last]+pile[i].card[last_2]
								+pile[i].card[last_3])%10 == 0 ){

						dealt_card_to_buttom(&deck,&(pile[i]));  //last
						dealt_card_to_buttom(&deck,&(pile[i]));	 //last2
						dealt_card_to_buttom(&deck,&(pile[i]));	 //last3

						tmp = deck.card[ (52+deck.buttom-2)%52 ];
						deck.card[ (52+deck.buttom-2)%52 ] = deck.card[deck.buttom];
						deck.card[deck.buttom] = tmp;

					}else{
						break;
					}
				}

				if (pile[i].num != 0){
					if ( check_duplicate() == true ){
						//	printf("duplicate!\n");
						break;
					}				
					//if ( check_num == round || round < 16 ){
						add_trace_data( round );
					//	if ( check_num == round )
					//		check_num = check_num*2;
					//}
				}
			}
			if ( duplicate != 0 )
				break;
		}

		tmp = check_over();
		switch (tmp){
			case 1:
				printf("Loss: %d\n",round);	
				break;
			case 2:
				printf("Win : %d\n",round);
				break;
			case 3:
				printf("Draw: %d\n",round);
		}
		free_trace_data();
	}
}

