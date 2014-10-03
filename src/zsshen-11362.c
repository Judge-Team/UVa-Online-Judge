#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


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

    /* First sort the phone book with the lengh of each phone string. */
    qsort(phone_book, size_book, sizeof(Phone), func_sort_phone_book);

    /* Apply backward comparsion to determine if there is string in the previous list
     * which is the prefix of the current string.  */
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

