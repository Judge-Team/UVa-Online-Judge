#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/*
Do not pass OJ for the first time. List down the bugs:
    1. Early break is not necessary. We should scan all the previously
       recorded string to check if they can be dominated by the new string.
*/


#define STRING_SIZE     10
#define CHARACTER_SET   26


typedef struct _Record {
    char str[STRING_SIZE + 1];
    char char_set[CHARACTER_SET];
    bool is_dominant;
    struct _Record *next;
} Record;


int comp_string(const void*, const void*);


int main() {
    int  i, len_str, size_ans;
    char idx_ch;
    bool is_new_dom;
    char **list_ans;
    Record *list_record, *pred, *curr, *trav;
    char buf[STRING_SIZE + 1];

    list_record = NULL;    
    while (true) {
        memset(buf, 0, sizeof(char) * (STRING_SIZE + 1));
        if (scanf("%s", buf) == EOF) {
            break;
        }

        if (list_record == NULL) {
            list_record = (Record*)malloc(sizeof(Record));
            list_record->next = NULL;
            curr = list_record;
        } else {
            curr = (Record*)malloc(sizeof(Record));
            curr->next = NULL;
            pred->next = curr;
        }

        for (i = 0 ; i < CHARACTER_SET ; i++) {
            curr->char_set[i] = 0;
        }
        len_str = strlen(buf);
        for (i = 0 ; i < len_str ; i++) {
            idx_ch = buf[i] - 'a';        
            curr->char_set[idx_ch]++;
        }
        memset(curr->str, 0, sizeof(char) * (STRING_SIZE + 1));
        strncpy(curr->str, buf, len_str);
        curr->is_dominant = true;

        /* Two-way checking: 
            1. The new string is dominated by some previously recorded ones.
            2. The new string dominates some previously recorded ones.
        */
        trav = list_record;
        is_new_dom = false;
        while (trav != curr) {
            /* Check condition 1. */
            if (is_new_dom == false) {
                for (i = 0 ; i < CHARACTER_SET ; i++) {
                    if (trav->char_set[i] < curr->char_set[i]) {
                        break;
                    }                              
                }
                if (i == CHARACTER_SET) {
                    is_new_dom = true;
                    curr->is_dominant = false;
                }
            }
            /* Check condition 2. */
            for (i = 0 ; i < CHARACTER_SET ; i++) {
                if (curr->char_set[i] < trav->char_set[i]) {
                    break;
                }
            }
            if (i == CHARACTER_SET) {
                trav->is_dominant = false;
            }
            trav = trav->next;
        }         

        /* Foward the linked list pointers. */
        pred = curr;
        curr = curr->next;
    }

    /* Calculate the number of dominant string. */
    size_ans = 0;
    curr = list_record;
    while (curr != NULL) {
        if (curr->is_dominant == true) {
            size_ans++;
        }
        curr = curr->next;
    }

    /* Generate the answer list. */
    if (size_ans > 0) {
        list_ans = (char**)malloc(sizeof(char*) * size_ans);
        i = 0;
        curr = list_record;
        while (curr != NULL) {
            if (curr->is_dominant == true) {
                list_ans[i++] = curr->str;
            }
            curr = curr->next;
        }
        qsort(list_ans, size_ans, sizeof(char*), comp_string);
        for (i = 0 ; i < size_ans ; i++) {
            printf("%s\n", list_ans[i]);
        }
    }

    /* Release the record list and answer list. */
    curr = list_record;
    while (curr != NULL) {
        pred = curr;
        curr = curr->next;
        free(pred);
    }
    if (size_ans > 0) {
        free(list_ans);
    }

    return 0;
}


int comp_string(const void *ptr_src, const void *ptr_dst) {

    return strcmp(*(char**)ptr_src, *(char**)ptr_dst);
}
