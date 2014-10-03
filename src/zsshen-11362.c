#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/*------------------------------------------------------------*/
/*                   Optimized version                        */
/*------------------------------------------------------------*/
#define COUNT_BRANCH    10
#define BUF_SIZE        10000
#define ASCII_BIAS      48


typedef struct _Node {
    struct _Node *succ[COUNT_BRANCH];
    bool   is_leaf;
} Node;


void init_trie(Node**);


void deinit_trie(Node*);


void construct_trie(Node*, int);


int main() {
    int  rc, count_case, size_book;
    Node *trie;

    rc = scanf("%d", &count_case);
    while (count_case) {
        rc = scanf("%d", &size_book);

        init_trie(&trie);        
        construct_trie(trie, size_book);
        deinit_trie(trie);

        count_case--;
    }

    return 0;
}


void init_trie(Node **p_trie) {
    int  i;
    Node *trie;

    *p_trie = (Node*)malloc(sizeof(Node));
    trie = *p_trie;    
    for (i = 0 ; i < COUNT_BRANCH ; i++) {
        trie->succ[i] = NULL;        
    }        
    trie->is_leaf = true;

    return;
}


void deinit_trie(Node *trie) {
    int i;

    if (trie != NULL) {    
        for (i = 0 ; i < COUNT_BRANCH ; i++) {
            if (trie->succ[i] != NULL) {
                deinit_trie(trie->succ[i]);
            }    
        }
        free(trie);
    }

    return;
}


void construct_trie(Node *trie, int size_book) {
    int  rc, i, idx_phone, len_phone, number;
    Node *curr, *succ;
    char buf[BUF_SIZE + 1];

    for (idx_phone = 0 ; idx_phone < size_book ; idx_phone++) {
        memset(buf, 0, sizeof(char) * (BUF_SIZE + 1));
        rc = scanf("%s", buf);
        len_phone = strlen(buf);

        curr = trie;
        for (i = 0 ; i < len_phone ; i++) {
            number = buf[i] - ASCII_BIAS;
            if (curr->succ[number] == NULL) {
                break;
            }
            curr = curr->succ[number];

            /* Some of the previously recorded string is the prefix of the current string. */
            if (curr->is_leaf == true) {
                printf("NO\n");
                return;
            }
        }

        /* The current string is the prefix of some previously recorded string. */
        if ((i == len_phone) && (curr->is_leaf == false)) {
            printf("NO\n");
            return;
        }

        for (; i < len_phone ; i++) {
            number = buf[i] - ASCII_BIAS;                
            init_trie(&succ);
            curr->succ[number] = succ;
            curr->is_leaf = false;
            curr = curr->succ[number];
        }
    }

    printf("YES\n");
    return;
}
/*------------------------------------------------------------*/
/*                    Brute force version                     */
/*------------------------------------------------------------*/
/*
#define BUF_SIZE 10000


typedef struct _Phone {
    int  len_phone;
    char *str_phone;
} Phone;


void init_phone_book(Phone**, int);


void deinit_phone_book(Phone*, int);


void scan_phone_book(Phone*, int);


int func_sort_phone_book(const void*, const void*);


int main() {
    int rc, count_case, size_book;
    Phone *phone_book;

    rc = scanf("%d", &count_case);
    while (count_case > 0) {
        rc = scanf("%d", &size_book);
        
        init_phone_book(&phone_book, size_book);
        scan_phone_book(phone_book, size_book);
        deinit_phone_book(phone_book, size_book);
    
        count_case--;
    }

    return 0;
}


void init_phone_book(Phone **p_phone_book, int size_book) {
    int  i, rc, len_phone;
    char buf[BUF_SIZE];
    Phone *phone_book;

    *p_phone_book = (Phone*)malloc(sizeof(Phone) * size_book);
    phone_book = *p_phone_book;

    for (i = 0 ; i < size_book ; i++) {
        memset(buf, 0, sizeof(char) * BUF_SIZE);
        rc = scanf("%s", buf);
        len_phone = strlen(buf);
        phone_book[i].len_phone = len_phone;
        phone_book[i].str_phone = (char*)malloc(sizeof(char) * (len_phone + 1));
        strcpy(phone_book[i].str_phone, buf);
    }

    return;
}


void deinit_phone_book(Phone *phone_book, int size_book) {
    int i;

    for (i = 0 ; i < size_book ; i++) {
        free(phone_book[i].str_phone);
    }
    free(phone_book);

    return;
}


void scan_phone_book(Phone *phone_book, int size_book) {
    int idx_pred, idx_curr, i;
    bool not_match;

    // First sort the phone book with the lengh of each phone string.
    qsort(phone_book, size_book, sizeof(Phone), func_sort_phone_book);

    // Apply backward comparsion to determine if there is string in the previous list
    // which is the prefix of the current string.
    for (idx_curr = 1 ; idx_curr < size_book ; idx_curr++) {
        for (idx_pred = idx_curr - 1 ; idx_pred >= 0 ; idx_pred--) {
            not_match = false;
            for (i = 0 ; i < phone_book[idx_pred].len_phone ; i++) {
                if (phone_book[idx_curr].str_phone[i] != 
                    phone_book[idx_pred].str_phone[i]) {
                    not_match = true;
                    break;
                }
            }
            if (not_match == false) {
                printf("NO\n");
                return;
            } 
        }
    }

    printf("YES\n");
    return;
}


int func_sort_phone_book(const void *src, const void *tge) {
    Phone *phone_src, *phone_tge;

    phone_src = (Phone*)src;
    phone_tge = (Phone*)tge;

    return phone_src->len_phone - phone_tge->len_phone;
}
*/
