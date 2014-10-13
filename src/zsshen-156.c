#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define WORD_SIZE       20
#define BUF_SIZE        80
#define LETTER_COUNT    26


typedef struct _Dict {
    char freq[LETTER_COUNT];
    char orig_str[WORD_SIZE + 1];
    int  count_rep;
    struct _Dict *next;
} Dict;


typedef struct _Index {
    Dict *dict_head;
    Dict *dict_tail;
} Index;


void check_ananagram(Index*, int*, char*);
void generate_answer(Index*);
void delete_dictionary(Index*);
int sort_word(const void*, const void*);


int main() {
    int  len_str, size_dict;
    char *word;
    Index idx_dict;
    char buf[BUF_SIZE + 1];

    size_dict = 0;
    idx_dict.dict_head = NULL;
    idx_dict.dict_tail = NULL;
    while (true) {
        memset(buf, 0, sizeof(char) * (BUF_SIZE + 1));
        if (fgets(buf, (BUF_SIZE + 1), stdin) == NULL) {
            break;
        }
        len_str = strlen(buf);
        buf[--len_str] = 0;

        /* Check for the process termination. */
        if (strcmp(buf, "#") == 0) {
            break;
        }
    
        /* Split the input line into several words for processing. */
        word = strtok(buf, " ");
        while (word != NULL) {
            check_ananagram(&idx_dict, &size_dict, word);
            word = strtok(NULL, " ");
        }
    }

    /* Sort and output the answer words. */
    generate_answer(&idx_dict);

    /* Release the allocated resource. */
    delete_dictionary(&idx_dict);

    return 0;
}


void check_ananagram(Index *p_idx_dict, int *p_size_dict, char *word) {
    int  i, rc, len_word;
    bool is_ananagram;
    Dict *curr;
    char new_freq[LETTER_COUNT];

    /* printf("debug %d %s\n", strlen(word), word); */

    /* Profile the character frequency of the input word. */
    memset(new_freq, 0, sizeof(char) * LETTER_COUNT);
    len_word = strlen(word);
    for (i = 0 ; i < len_word ; i++) {
        /* Check if the character is upper case. */
        if ((word[i] >= 'A') && (word[i] <= 'Z')) {
            new_freq[word[i] - 'A']++;
        }
        /* Check if the character is lower case. */
        else if ((word[i] >= 'a') && (word[i] <= 'z')) {
            new_freq[word[i] - 'a']++;
        }
    }

    is_ananagram = true;
    curr = p_idx_dict->dict_head;
    while (curr != NULL) {
        rc = memcmp(curr->freq, new_freq, sizeof(char) * LETTER_COUNT);    
        if (rc == 0) {
            is_ananagram = false;
            curr->count_rep++;
            break;
        }
        curr = curr->next;
    }

    if (is_ananagram == true) {
        curr = (Dict*)malloc(sizeof(Dict));
        curr->next = NULL;
        /* Record the character frequency data. */
        memcpy(curr->freq, new_freq, sizeof(char) * LETTER_COUNT);
        /* Record the original word. */
        memset(curr->orig_str, 0, sizeof(char) * (WORD_SIZE + 1));
        strcpy(curr->orig_str, word);
        /* Initialize the repeat count. */
        curr->count_rep = 1;

        if (p_idx_dict->dict_head == NULL) {
            p_idx_dict->dict_head = curr;
            p_idx_dict->dict_tail = curr;
        } else {
            p_idx_dict->dict_tail->next = curr;
            p_idx_dict->dict_tail = curr;
        }
        (*p_size_dict)++;
    }

    return;
}


void generate_answer(Index *p_idx_dict) {
    int  idx, size_real;
    Dict *curr;
    char **list_word;

    /* Count the number of ananagrams. */
    size_real = 0;
    curr = p_idx_dict->dict_head;
    while (curr != NULL) {
        if (curr->count_rep == 1) {
            size_real++;
        }
        curr = curr->next;
    }

    /* Collect the ananagrams for sorting. */
    list_word = (char**)malloc(sizeof(char*) * size_real);
    idx = 0;
    curr = p_idx_dict->dict_head;
    while (curr != NULL) {
        if (curr->count_rep == 1) {
            list_word[idx++] = curr->orig_str;
        }
        curr = curr->next;
    }

    /* Sort the ananagrams with lexicographical order. */
    qsort(list_word, size_real, sizeof(char*), sort_word);

    /* Print the answer. */
    for (idx = 0 ; idx < size_real ; idx++) {
        printf("%s\n", list_word[idx]);
    }
    free(list_word);

    return;
}


int sort_word(const void *ptr_src, const void *ptr_tge) {
    const char **word_src, **word_tge;

    word_src = (const char**)ptr_src;
    word_tge = (const char**)ptr_tge;
    
    return strcmp(*word_src, *word_tge);
}


void delete_dictionary(Index *p_idx_dict) {
    Dict *curr, *pred;

    curr = p_idx_dict->dict_head;
    while (curr != NULL) {
        pred = curr;
        curr = curr->next;
        free(pred);
    }
    return;
}

