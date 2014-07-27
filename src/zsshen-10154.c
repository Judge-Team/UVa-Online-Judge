#include <stdio.h>
#include <stdlib.h>


#define MAX_OBJECT      5608
#define Min(a,b)        ((a) < (b) ? (a) : (b))


typedef struct _Turtle {
    int m_weight;
    int m_strength;
    int m_power;
} Turtle;


int compare(const void *p_src, const void *p_tge) {
    
    if (((Turtle*)p_src)->m_power == ((Turtle*)p_tge)->m_power)
        return 0;
    else {
        if (((Turtle*)p_src)->m_power > ((Turtle*)p_tge)->m_power)
            return 1;
        else
            return -1;
    }
}


int main() {
    int i, j, idx, weight, power;
    int length, new_load;
    int load[MAX_OBJECT];
    Turtle turtle[MAX_OBJECT];
    
    idx = 1;
    while(scanf("%d%d", &weight, &power) != EOF) {
        turtle[idx].m_weight = weight;
        turtle[idx].m_strength = power - weight;
        turtle[idx].m_power = power;
        idx++;
    }  
    idx--;

    /* Sort the turtles by their original strength. */
    qsort(turtle + 1, idx, sizeof(Turtle), compare);

    /**
     * Let dp[len] denote the "minimum total weight" of tower with length "len".
     *
     * Given a turtle with index i:
     *      1. Update the length of tower, if s[i] >= dp[len]:
     *             len++;
     *             dp[len] = dp[len - 1] + w[i].
     *
     *      2. And then maintain the optimal substructure.          
     *             dp[j] = Min{dp[j], dp[j-1] + w[i]}, for 1 <= j <= len.  
     *
     */

    /* Initial step. */    
    load[0] = 0;
    load[1] = turtle[1].m_weight;
    length = 1;    

    /* Deduction step. */
    for (i = 2 ; i <= idx ; i++) {
        for (j = length ; j >= 0 ; j--) {
            if (turtle[i].m_strength >= load[j]) {
                if ((j + 1) > length) {
                    load[j + 1] = load[j] + turtle[i].m_weight;
                    length = j + 1;
                } else {
                    load[j + 1] = Min(load[j + 1], load[j] + turtle[i].m_weight);
                }
            }            
        }
    }

    printf("%d\n", length);

    return 0;
}
