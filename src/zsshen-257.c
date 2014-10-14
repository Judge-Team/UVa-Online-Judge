#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define WORD_SIZE            256
#define MIN_PALINDROME_SIZE  3
#define PALINWORD_THRESHOLD  2


bool check_palinword(char*);
bool check_palindrome(char*, int, int, char**);


int main() {
    bool is_palinword;
    char word[WORD_SIZE];

    while (true) {
        memset(word, 0, sizeof(char) * WORD_SIZE);
        if (scanf("%s", word) == EOF) {
            break;
        }
        is_palinword = check_palinword(word);
        if (is_palinword == true) {
            printf("%s\n", word);
        }
    }

    return 0;
}


bool check_palinword(char *word) {
    int  idx_bgn, idx_end, len_word, range, count_palindrome;
    bool is_palinword;
    char *palindrome;

    is_palinword = false;
    count_palindrome = 0;
    palindrome = NULL;
    len_word = strlen(word);
    range = MIN_PALINDROME_SIZE;
    
    /* Enumerate all substrings whose length is at least 3. */
    while (range <= len_word) {
        for (idx_bgn = 0 ; idx_bgn <= len_word - range ; idx_bgn++) {
            idx_end = idx_bgn + range - 1;
            count_palindrome += check_palindrome(word, idx_bgn, idx_end, &palindrome);
            if (count_palindrome == PALINWORD_THRESHOLD) {
                is_palinword = true;
                break;
            }
        }
        range++;
    }

    if (palindrome != NULL) {
        free(palindrome);
    }
        
    return is_palinword;
}


bool check_palindrome(char *word, int idx_bgn, int idx_end, char **p_palindrome) {
    int  i, len;
    bool good_palindrome;
    char *ret;
    char candidate[WORD_SIZE];

    good_palindrome = true;

    /* Check if the substring is a palindrome. */
    len = idx_end - idx_bgn + 1;
    for (i = 0 ; i < len / 2 ; i++) {
        if (word[idx_bgn + i] != word[idx_end - i]) {
            good_palindrome = false;
            break;
        }
    }

    /* Check if the new palindrome contradicts with the recorded one. */
    if (good_palindrome == true) {
        if (*p_palindrome == NULL) {
            *p_palindrome = (char*)malloc(sizeof(char) * WORD_SIZE);
            memset(*p_palindrome, 0, sizeof(char) * WORD_SIZE);
            strncpy(*p_palindrome, word + idx_bgn, len);
        } else {
            memset(candidate, 0, sizeof(char) * WORD_SIZE);
            strncpy(candidate, word + idx_bgn, len);
            ret = strstr(candidate, *p_palindrome);
            if (ret != NULL) {
                good_palindrome = false;
            }
        }
    }

    return good_palindrome;
}
