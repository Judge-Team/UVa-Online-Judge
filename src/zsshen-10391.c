#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define WORD_SIZE       10000
#define CHAR_SET        26
#define WORD_COUNT      120000
#define PHASE_FIRST     0
#define PHASE_SECOND    1


typedef struct _Node {
    struct _Node *branch[CHAR_SET];
    bool   bkey;
} Node;


typedef struct _Word {
    int  len;
    char *body;
} Word;


void trie_create_node(Node **p_new) {
    int i;

    *p_new = (Node*)malloc(sizeof(Node));
    (*p_new)->bkey = false;
    for (i = 0 ; i < CHAR_SET ; i++) {
        (*p_new)->branch[i] = NULL;
    }

    return;
}


void trie_delete_all(Node *curr) {
    int i;

    if (curr != NULL) {
        for (i = 0 ; i < CHAR_SET ; i++) {
            if (curr->branch[i] != NULL) {
                trie_delete_all(curr->branch[i]);
            }
        }
        free(curr);
    }

    return;
}


bool check_compound_word(char *word, int bgn, int end, Node *root, bool phase) {
    int  i, idx_branch;
    bool rc;    
    Node *curr;

    curr = root;
    for (i = bgn ; (i < end) && (curr != NULL)  ; i++) {
        if ((curr->bkey == true) && (phase == PHASE_FIRST)) {
            rc = check_compound_word(word, i, end, root, PHASE_SECOND);
            if (rc == true) {
                return true;
            }    
        }
        idx_branch = word[i] - 'a';
        curr = curr->branch[idx_branch];
    }

    if ((curr != NULL) && (curr->bkey == true) &&
        (i == end) && (phase == PHASE_SECOND)) {
        return true;
    }

    return false;
}



int main() {
    int  i, len_word, count_word, idx_branch;
    bool rc;
    Node *root, *curr, *pred;
    char buf[WORD_SIZE];
    Word **list_word;    

    /* Initialization. */
    trie_create_node(&root);
    list_word = (Word**)malloc(sizeof(Word*) * WORD_COUNT);
    
    count_word = 0;    
    while (scanf("%s", buf) != EOF) {

        /* Store this word into word list. */        
        len_word = strlen(buf);          
        list_word[count_word] = (Word*)malloc(sizeof(Word));      
        list_word[count_word]->body = (char*)malloc(sizeof(char) * (len_word + 1));
        memset(list_word[count_word]->body, 0, sizeof(char) * (len_word + 1));
        strncpy(list_word[count_word]->body, buf, len_word);
        list_word[count_word]->len = len_word;
        count_word++;

        /* Create the relevant trie nodes for this word. */
        curr = root;
        for (i = 0 ; i < len_word ; i++) {
            pred = curr;
            idx_branch = buf[i] - 'a';
            curr = curr->branch[idx_branch];
            if (curr == NULL) {
                trie_create_node(&curr);
                pred->branch[idx_branch] = curr;
            }
        }
        curr->bkey = true;
    }

    /* Check for compond words. */
    list_word = (Word**)realloc(list_word, sizeof(Word*) * count_word);
    for (i = 0 ; i < count_word ; i++) {
        rc = check_compound_word(list_word[i]->body, 0, list_word[i]->len, root, PHASE_FIRST);
        if (rc == true) {
            printf("%s\n", list_word[i]->body);
        }
    }    

    /* Deinitialization. */
    trie_delete_all(root);
    for (i = 0 ; i < count_word ; i++) {
        free(list_word[i]->body);
        free(list_word[i]);
    }
    free(list_word);

    return 0;
}
