#include <stdio.h>
#include <stdlib.h>


#define MAX_INT_COUNT   10000
#define Min(a, b)       (((a) < (b)) ? (a) : (b))
#define Max(a, b)       (((a) > (b)) ? (a) : (b))

typedef struct _Record {
    int     val_min;
    short   first_idx;
} Record;


int main() {
    int i, j, k, count, max_from_left, max_from_right, len_left, len_right, len_max;
    int     input[MAX_INT_COUNT + 1];
    Record  record_left[MAX_INT_COUNT + 1], record_right[MAX_INT_COUNT + 2];    

    while (scanf("%d", &count) != EOF) {
        for (i = 1 ; i <= count ; i++)
            scanf("%d", &input[i]);

        max_from_left = 0;
        max_from_right = 0;
        record_left[0].val_min = -1;
        record_left[0].first_idx = 0;
        record_right[0].val_min = -1;
        record_right[0].first_idx = count + 1;
                
        for (i = 1, k = count; i <= count ; i++, k--) {

            /* Deal with the LIS starting from left end. */
            if (input[i] > record_left[max_from_left].val_min) {
                record_left[++max_from_left].val_min = input[i];
                record_left[max_from_left].first_idx = i;
            } else {
                for (j = max_from_left - 1 ; j >= 0 ; j--) {
                    if ((input[i] > record_left[j].val_min) && 
                        (input[i] < record_left[j + 1].val_min)) {
                        record_left[j + 1].val_min = input[i];
                    }   
                }
            }

            /* Deal with the LIS starting from right end. */
            if (input[k] > record_right[max_from_right].val_min) {
                record_right[++max_from_right].val_min = input[k];
                record_right[max_from_right].first_idx = k;
            } else {
                for (j = max_from_right - 1 ; j >= 0 ; j--) {
                    if ((input[k] > record_right[j].val_min) && 
                        (input[k] < record_right[j + 1].val_min)) {
                        record_right[j + 1].val_min = input[k];
                    }   
                }
            }
        }

        /* Check the Wavio sequence from left end. */
        len_left = Min(max_from_left, max_from_right);
        len_right = len_left;        
        while (len_left >= 1) {
            if (record_left[len_left].first_idx <= record_right[len_left].first_idx)
                break;
            len_left--;
        }

        /* Check the Wavio sequence from right end. */
        while (len_right >= 1) {
            if (record_right[len_right].first_idx >= record_left[len_right].first_idx)
                break;
            len_right--;
        }

        len_max = Max(len_left, len_right);
        printf("%d\n", 2 * len_max - 1);
    }

    return 0;
}
