#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double equation( int p , int q , int r , int s , int t , int u , float x ){
        return p*exp(-x) + q*sin(x) + r*cos(x) + s*tan(x) + t*x*x + u ;
}

int main( int argc ,char *argv[]){
        FILE *In , *Out;
        int p , q , r , s , t , u;
        double upper_bound , lower_bound;
        double ans , mid;
        double upper_ans , lower_ans;
        int no;

        In = stdin;
        Out = stdout;

        while( fscanf( In , "%d%d%d%d%d%d",&p,&q,&r,&s,&t,&u) != EOF ){
                upper_bound = 1;
                lower_bound = 0;
                no = 1;
                while(1){
                        upper_ans = equation(p,q,r,s,t,u,upper_bound);
                        lower_ans = equation(p,q,r,s,t,u,lower_bound);

                        if( ( upper_ans > 0 && lower_ans > 0 ) || ( upper_ans < 0 && lower_ans < 0 ))
                                break;

                        mid = (upper_bound+lower_bound)/2;
                        ans = equation(p,q,r,s,t,u,mid);
                        if( (int)(ans*200000) == 0 )
                        {
                                printf("%0.4lf\n",mid);
                                no = 0;
                                break;
                        }else if( ans > 0 ){
                                lower_bound = mid;
                                if( ans < 0.0000001 )
                                {
                                        printf("%0.4lf\n",mid );
                                        no = 0;
                                        break;
                                }
                        }else{
                                upper_bound = mid;
                                if(  ans > -0.0000001 ){
                                        printf("%0.4lf\n",mid);
                                        no = 0;
                                        break;
                                }
                        }
                }
                if( no == 1 )
                        printf("No solution\n");
        }
}

