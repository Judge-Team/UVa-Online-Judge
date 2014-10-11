#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define BUF_SIZE 1024


bool match_pattern(char*, int, int, char*, int, int);


int main() {
    int  len_pat, len_str;
    bool is_match, ever_hit, prev_status;
    char *ret;
    char pat[BUF_SIZE + 1], str[BUF_SIZE + 1];

    prev_status = false;
    while (true) {
        /* Read the pattern. */
        memset(pat, 0, sizeof(char) * (BUF_SIZE + 1));
        ret = fgets(pat, BUF_SIZE, stdin);
        if (ret == NULL) {
            break;
        }
        len_pat = strlen(pat);
        if (len_pat == 1) {
            break;
        }
        len_pat--;
        pat[len_pat] = 0;

        ever_hit = false;
        while (true) {
            /* Read the case list. */
            memset(str, 0, sizeof(char) * (BUF_SIZE + 1));
            ret = fgets(str, BUF_SIZE, stdin);
            if (ret == NULL) {
                break;
            }
            len_str = strlen(str);            
            if (len_str == 1) {
                break;
            }
            len_str--;
            str[len_str] = 0;

            /* Conduct the pattern match. */
            is_match = match_pattern(str, len_str, 0, pat, len_pat, 0);
            if (is_match == true) {
                if (ever_hit == false) {
                    if (prev_status == true) {
                        printf("\n");
                    }
                    printf("MATCHES FOR THE PATTERN: %s\n", pat);
                }
                ever_hit = true;
                printf("%s\n", str);                
            }
        }
        if (ever_hit == true) {
            prev_status = true;
        }
    }

    return 0;
}


bool match_pattern(char *str, int len_str, int bgn_str,
                   char *pat, int len_pat, int bgn_pat) {
    int  idx_str, idx_pat, nidx_str;
    bool is_match;

    is_match = false;
    idx_str = bgn_str;
    idx_pat = bgn_pat;
    while (true) {
        if (idx_pat == len_pat) {
            break;
        }
    
        if (pat[idx_pat] != '*') {
            if (idx_str == len_str) {
                break;
            }
            if (str[idx_str] != pat[idx_pat]) {
                break;
            }
            idx_str++;
            idx_pat++;
        } else {
            for (nidx_str = idx_str ; nidx_str <= len_str ; nidx_str++) {
                is_match = match_pattern(str, len_str, nidx_str, pat, len_pat, idx_pat + 1);
                if (is_match == true) {
                    break;
                }
            }
            break;
        }
    }

    if (is_match == false) {
        if ((idx_str == len_str) && (idx_pat == len_pat)) {
            is_match = true;
        }
    }

    return is_match;
}
