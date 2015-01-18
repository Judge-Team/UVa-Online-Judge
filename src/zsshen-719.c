#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define BUF_SIZE 10000


void get_minimum_expression(char *sz_word, int len_word, int *min_ofst)
{
    int idx_bgn = 0, idx_end = 1;
    while ((idx_end - idx_bgn) < len_word) {
        if (sz_word[idx_end] > sz_word[idx_bgn])
            idx_end++;
        else if (sz_word[idx_end] < sz_word[idx_bgn]) {
            idx_bgn = idx_end;
            idx_end = idx_bgn + 1;
        } else {
            bool should_replace = false;
            int ofst;
            for (ofst = 0 ; ofst < (idx_end - idx_bgn) ; ofst++) {
                if (sz_word[ofst + idx_end] != sz_word[ofst + idx_bgn]) {
                    if (sz_word[ofst + idx_end] < sz_word[ofst + idx_bgn])
                        should_replace = true;
                    break;
                } 
            }
            if (should_replace) {
                idx_bgn = idx_end;
                idx_end = idx_bgn + 1;
            } else
                idx_end++;
        }
    }
    *min_ofst = idx_bgn + 1;

    return;
}


int main() 
{
    int cnt_case, idx_case, dummy;
    char sz_word[2 * BUF_SIZE + 1];

    dummy = scanf("%d", &cnt_case);
    idx_case = 0;
    while (idx_case < cnt_case) {
        int min_ofst, len_word;
        
        dummy = scanf("%s", sz_word);
        len_word = strlen(sz_word);
        strncpy(sz_word + len_word, sz_word, len_word);
        get_minimum_expression(sz_word, len_word, &min_ofst);
 
        printf("%d\n", min_ofst);
        idx_case++;
    }

    return 0;
}
