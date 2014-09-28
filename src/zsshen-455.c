#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define MAX_INPUT_SIZE 80


/* Main routine to find the periodic string. */
int calculate_periodic(const char*);


int main() {
    int rc, count_case, periodic;
    char str_input[MAX_INPUT_SIZE + 1];
    
    rc = scanf("%d", &count_case);
    while (count_case > 0) {
        memset(str_input, 0, sizeof(char) * (MAX_INPUT_SIZE + 1));
        rc = scanf("%s", str_input);
        periodic = calculate_periodic(str_input);
        printf("%d\n", periodic);
        count_case--;
        if (count_case > 0) {
            printf("\n");
        }
    }

    return 0;
}


int calculate_periodic(const char *str_orig) {
    int len_orig, pivot_orig, pivot_key, periodic;
    bool not_match, found_periodic;
    char str_key[MAX_INPUT_SIZE + 1];

    len_orig = strlen(str_orig);
    
    /* Check for the early return. */
    /*
    if ((len_orig % 2) != 0) {
        return len_orig;
    }
    */

    found_periodic = false;
    for (periodic = 1 ; periodic <= len_orig / 2 ; periodic++) {
        strncpy(str_key, str_orig, periodic);
        
        pivot_orig = pivot_key = 0;
        not_match = false;
        while (pivot_orig < len_orig) {
            while (pivot_key < periodic) {
                if (str_orig[pivot_orig] != str_key[pivot_key]) {
                    not_match = true;
                    break;
                }
                pivot_orig++;
                pivot_key++;
            }
            if (not_match == true) {
                break;
            }
            pivot_key = 0;
        }

        if ((pivot_orig == len_orig) && (pivot_key == 0)) {
            found_periodic = true;
            break;
        }
    }

    if (found_periodic == false) {
        periodic = len_orig;
    }

    return periodic;
}



