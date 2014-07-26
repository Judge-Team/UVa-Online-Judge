#include <stdio.h>
#include <stdlib.h>


#define MAX_STRENGTH    2147483647
#define MAX_OBJECT      5608
#define Min(a,b)        ((a) < (b) ? (a) : (b))


typedef struct _Turtle {
    int m_weight;
    int m_strength;
} Turtle;


int compare(const void *p_src, const void *p_tge) {
    
    if (((Turtle*)p_src)->m_strength == ((Turtle*)p_tge)->m_strength)
        return 0;
    else {
        if (((Turtle*)p_src)->m_strength < ((Turtle*)p_tge)->m_strength)
            return 1;
        else
            return -1;
    }
}


int main() {
    int i, j, idx, weight, power;
    int length, new_load;
    int min_load[MAX_OBJECT];
    Turtle list_turtle[MAX_OBJECT];
    
    idx = 1;
    while(scanf("%d%d", &weight, &power) != EOF) {
        list_turtle[idx].m_weight = weight;
        list_turtle[idx].m_strength = power - weight;
        idx++;
    }  
    idx--;

    /* Sort the turtles by their weights. */
    qsort(list_turtle + 1, idx, sizeof(Turtle), compare);

    /* Initial step. */    
    min_load[0] = MAX_STRENGTH;
    min_load[1] = list_turtle[1].m_strength;
    length = 1;    

    /* Deduction step. */
    for (i = 2 ; i <= idx ; i++) {
        if (list_turtle[i].m_weight <= min_load[length]) {
            new_load = Min(list_turtle[i].m_strength, min_load[length] - list_turtle[i].m_weight);
            min_load[++length] = new_load;
        } else {
            for (j = length - 1 ; j >= 0 ; j--) {
                if (list_turtle[i].m_weight <= min_load[j]) {
                    new_load = Min(list_turtle[i].m_strength, min_load[j] - list_turtle[i].m_weight);
                    if (new_load > min_load[j + 1])
                        min_load[j + 1] = new_load;
                }
            }
        }
    }

    printf("%d\n", length);

    return 0;
}
