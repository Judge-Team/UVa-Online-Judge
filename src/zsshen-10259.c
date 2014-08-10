#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_DIMENSION 100


typedef struct _Edge {
    short src;
    short dst;
    struct _Edge *next;
} Edge;


void build_graph(Edge**, Edge**, short, short);


int main() {
    int i, j, round, dim, hop, src, dst, sum, max;
    bool check;
    Edge *head, *tail;
    int input[MAX_DIMENSION * MAX_DIMENSION];
    int dp[MAX_DIMENSION * MAX_DIMENSION];

    scanf("%d", &round);
    while (round > 0) {
        scanf("%d%d", &dim, &hop);
        
        for (i = 0 ; i < dim * dim ; i++) {
            scanf("%d", &(input[i]));
            dp[i] = -1;        
        }
        dp[0] = input[0];

        /** 
         * For each vertex pair (src, dst), there will be a direct edge from "src" to "dst" if   
         * the value stored in "dst" is larger than "src" and the distance between them is equal 
         * or smaller than the designated hop counts.   
         */                                         
        head = tail = NULL;
        for (i = 0 ; i < dim * dim ; i++) {
            src = i;
            /* Down direction. */
            for (j = 1 ; j <= hop ; j++) {
                dst = src + j * dim;
                if (dst >= dim * dim)
                    break;
                if (input[dst] > input[src])
                    build_graph(&head, &tail, (short)src, (short)dst);
            }
            
            /* Up direction. */
            for (j = 1 ; j <= hop ; j++) {
                dst = src - j * dim;
                if (dst < 0)
                    break;
                if (input[dst] > input[src])
                    build_graph(&head, &tail, (short)src, (short)dst);
            }
            
            /* Left direction. */
            for (j = 1 ; j <= hop ; j++) {
                dst = src - j;
                if ((dst < 0) || (dst % dim) == (dim - 1))
                    break;
                if (input[dst] > input[src])
                    build_graph(&head, &tail, (short)src, (short)dst);
            }            

            /* Right direction. */
            for (j = 1 ; j <= hop ; j++) {
                dst = src + j;
                if ((dst >= dim * dim) || (dst % dim) == 0)
                    break;
                if (input[dst] > input[src])
                    build_graph(&head, &tail, (short)src, (short)dst);
            }     
        }

        /* Initialization with right direction. */        
        src = 0;        
        for (i = 1 ; i <= hop ; i++) {
            dst = src + i;
            if (dst >= dim)
                break;
            if (input[dst] > input[src])
                dp[dst] = dp[0] + input[dst];
        }

        /* Initialization with down direction. */
        src = 0;
        for (i = 1 ; i <= hop ; i++) {
            dst = src + i * dim;
            if (dst >= dim * dim)
                break;
            if (input[dst] > input[src])
                dp[dst] = dp[0] + input[dst];
        }

        /**
         * Recursive formula (Applying modified Bellman-Ford algorithm) :
         * 1. dp[v] : The maximum penny counts collected along the path from source vertex to vertex "v".
         * 2. dp[dst] = MAX{dp[dst], dst[src] + input[dst]}. 
         */
        max = dp[0];
        for (i = 2 ; i < dim * dim ; i++) {
            tail = head;
            check = false;

            /* Path relaxation for each pair of edges. */
            while (tail != NULL) {
                src = tail->src;
                dst = tail->dst;
                tail = tail->next;
    
                if ((dp[src] == -1) && (dp[dst] == -1))
                    continue;
    
                sum = dp[src] + input[dst];
                if (sum > dp[dst]) {
                    dp[dst] = sum;
                    check = true;                
                }

                if (dp[dst] > max)
                    max = dp[dst];
            }

            if (check == false)
                break;
        }

        /* Destruct the graph. */
        while (head != NULL) {
            tail = head;
            head = head->next;
            free(tail);
        }

        printf("%d\n", max);
        round--;
        if (round > 0)
            printf("\n");
    }

    return 0;
}


void build_graph(Edge **pHead, Edge **pTail, short src, short dst) {
    Edge *head, *new;

    if (*pHead == NULL) {
        *pHead = (Edge*)malloc(sizeof(Edge));
        head = *pHead;
        head->next = NULL;
        head->src = src;
        head->dst = dst;
        *pTail = head;
    } else {
        new = (Edge*)malloc(sizeof(Edge));
        new->next = NULL;
        new->src = src;
        new->dst = dst;
        (*pTail)->next = new;
        *pTail = new;
    }   

    return;
}
