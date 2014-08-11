#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>


#define MAX_WORD_LENGTH  18


typedef struct _Word {
    short step;
    char *str;
    struct _Word *next;
} Word;


/* Utility function to check the edit step for two strings with length differencing by one. */
bool check_edit_step_diff_length(const char*, int, const char*, int);


/* Utility function to check the edit step for two strings with equal length. */
bool check_edit_step_same_length(const char*, const char*, int);


int main() {
    int    i;
    short  len_word, global_max, local_max, step;
    bool   is_edit_step, is_linked;
    char   *str_src, *str_dst;
    Word   *word, *curr, *pred;
    char   input[MAX_WORD_LENGTH];
    Word   *book[MAX_WORD_LENGTH];

    for (i = 0 ; i < MAX_WORD_LENGTH ; i++)
        book[i] = NULL; 

    global_max = 0;
    do {
        memset(input, 0, sizeof(char) * MAX_WORD_LENGTH);
        if (scanf("%s", input + 1) == EOF)
            break;
                
        word = (Word*)malloc(sizeof(Word));
        len_word = strlen(input + 1);        
        str_src = (char*)malloc(sizeof(char) * (len_word + 2));
        memset(str_src, 0, sizeof(char) * (len_word + 2));
        strcpy(str_src + 1, input + 1);
        word->str = str_src;
        word->next = NULL;        

        local_max = 0;
        /* Check for the words with length equal to "len_word" - 1. */
        curr = book[len_word - 1];
        while (curr != NULL) {
            str_dst = curr->str;
            is_edit_step = check_edit_step_diff_length(str_src, len_word, str_dst, len_word - 1);
            if (is_edit_step == true) {
                step = curr->step;
                if (step > local_max)
                    local_max = step;
                break;
            }
            curr = curr->next;
        }

        /* Check for the words with length equal to "len_word". */
        curr = book[len_word];
        while (curr != NULL) {
            str_dst = curr->str;
            is_edit_step = check_edit_step_same_length(str_src, str_dst, len_word);
            if (is_edit_step == true) {
                step = curr->step;
                if (step > local_max)
                    local_max = step;
                break;
            }
            curr = curr->next;
        }

        /* Check for the words with length equal to "len_word" + 1. */
        curr = book[len_word + 1];
        while (curr != NULL) {
            str_dst = curr->str;
            is_edit_step = check_edit_step_diff_length(str_src, len_word, str_dst, len_word + 1);
            if (is_edit_step == true) {
                step = curr->step;
                if (step > local_max)
                    local_max = step;
                break;
            }
            curr = curr->next;
        }
        
        step = local_max + 1;
        word->step = step;
        if (step > global_max)
            global_max = step;

        /* Insert the new word to the appropriate position. */
        if (book[len_word] == NULL)
            book[len_word] = word;
        else {
            is_linked = false;
            curr = book[len_word];
            while (curr != NULL) {
                if (step > curr->step) {
                    if (curr == book[len_word]) {
                        word->next = curr;
                        book[len_word] = word;
                    } else {
                        word->next = curr;
                        pred->next = word;
                    }        
                    is_linked = true;            
                    break;
                }
                pred = curr;                
                curr = curr->next;
            }

            if (is_linked == false)
                pred->next = word;                
        }
    } while (true);
    
    printf("%d\n", global_max);

    /*
    for (i = 1 ; i < MAX_WORD_LENGTH ; i++) {
        if (book[i] != NULL) {
            printf("%3d -> ", i);
            curr = book[i];
            while (curr != NULL) {
                printf("(%s, %d) ", curr->str + 1, curr->step);
                curr = curr->next;
            }
            printf("\n");
        }
    }
    */

    for (i = 1 ; i < MAX_WORD_LENGTH ; i++) {
        if (book[i] != NULL) {
            curr = book[i];
            while (curr != NULL) {
                pred = curr;
                curr = curr->next;
                free(pred->str);
                free(pred);
            }
        }
    }

    return 0;
}

/*
bool check_edit_step_diff_length(const char *str_src, int len_src, const char *str_dst, int len_dst) {
    int i, j, min, sum;
    int edit[MAX_WORD_LENGTH][MAX_WORD_LENGTH];    

    for (i = 0 ; i <= len_src ; i++)
        edit[i][0] = 0;
    for (i = 0 ; i <= len_dst ; i++)
        edit[0][i] = 0;
    
    for (i = 1 ; i <= len_src ; i++) {
        for (j = 1 ; j <= len_dst ; j++) {
            if (str_src[i] == str_dst[j])
                edit[i][j] = edit[i - 1][j - 1];
            else {
                min = INT_MAX;
                sum = edit[i - 1][j - 1] + 1;
                if (sum < min)
                    min = sum;
                sum = edit[i][j - 1] + 1;
                if (sum < min)
                    min = sum;
                sum = edit[i - 1][j] + 1;
                if (sum < min)
                    min = sum;      
                edit[i][j] = min;                                  
            }                
        }
    }

    if (edit[len_src][len_dst] == 1)
        return true;
    else
        return false;
}
*/

bool check_edit_step_diff_length(const char *str_src, int len_src, const char *str_dst, int len_dst) {
    int i, j, len_short, len_long, count;
    const char *str_short, *str_long;
    
    if (len_src > len_dst) {
        len_long = len_src;
        str_long = str_src;
        len_short = len_dst;
        str_short = str_dst;
    } else {
        len_long = len_dst;
        str_long = str_dst;
        len_short = len_src;
        str_short = str_src;        
    }

    count = 0;
    for (i = 1, j = 1 ; (i <= len_long) && (j <= len_short); ) {
        if (str_long[i] == str_short[j]) {
            i++;        
            j++;
        }
        else {
            i++;
            count++;
            if (count > 1)
                return false;
        }
    }

    return true;
}


bool check_edit_step_same_length(const char *str_src, const char *str_dst, int len_str) {
    int i, diff_count;

    diff_count = 0;
    for (i = 1 ; i <= len_str ; i++) {
        if (str_src[i] != str_dst[i]) {
            diff_count++;
            if (diff_count > 1)
                return false;
        }
    }
   
    if (diff_count == 1)
        return true;
    else
        return false;
}
