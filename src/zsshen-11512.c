#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define BRANCH_DEGREE   4
#define BUF_SIZE        1000
#define CHAR_TO_BRANCH_INDEX(ch)    switch(ch) {            \
                                        case 'A': {         \
                                            ch = 0;         \
                                            break;          \
                                        }                   \
                                        case 'C': {         \
                                            ch = 1;         \
                                            break;          \
                                        }                   \
                                        case 'G': {         \
                                            ch = 2;         \
                                            break;          \
                                        }                   \
                                        case 'T': {         \
                                            ch = 3;         \
                                        }                   \
                                    }


#define BRANCH_INDEX_TO_CHAR(idx)    switch(idx) {          \
                                        case 0: {           \
                                            idx = 'A';      \
                                            break;          \
                                        }                   \
                                        case 1: {           \
                                            idx = 'C';      \
                                            break;          \
                                        }                   \
                                        case 2: {           \
                                            idx = 'G';      \
                                            break;          \
                                        }                   \
                                        case 3: {           \
                                            idx = 'T';      \
                                        }                   \
                                    }


typedef struct _Node {
    struct _Node *branch[BRANCH_DEGREE];
    int frequency;
} Node;


typedef struct _Record {
    char prefix[BUF_SIZE + 1];
    int  length, frequency;
} Record;


void trie_new_node(Node **p_new) {
    int i;
    
    (*p_new) = (Node*)malloc(sizeof(Node));
    (*p_new)->frequency = 0;
    for (i = 0 ; i < BRANCH_DEGREE ; i++) {
        (*p_new)->branch[i] = NULL;
    }

    return;
}


void trie_traverse(Node *curr, char *prefix, int idx_prefix, Record *record) {
    int  i, len_prefix;
    char ch;

    if (curr != NULL) {
        if (curr->frequency > 0) {
            prefix[idx_prefix] = 0;
            if ((idx_prefix > record->length) && (curr->frequency > 1)) {
                record->length = idx_prefix;
                record->frequency = curr->frequency;
                strncpy(record->prefix, prefix, (idx_prefix + 1));
            }
        }
        for (i = 0 ; i < BRANCH_DEGREE ; i++) {
            if (curr->branch[i] != NULL) {
                ch = i;
                BRANCH_INDEX_TO_CHAR(ch);
                prefix[idx_prefix] = ch;
                trie_traverse(curr->branch[i], prefix, idx_prefix + 1, record);    
            }
        }
    }

    return;
}


void trie_delete_all(Node *curr) {
    int i;

    if (curr != NULL) {
        for (i = 0 ; i < BRANCH_DEGREE ; i++) {
            if (curr->branch[i] != NULL) {
                trie_delete_all(curr->branch[i]);
            }
        }
        free(curr);
    }

    return;
}


int main() {
    int  i, j, rc, count_case, idx_case, len_sequence;
    char idx_branch;
    Node *root, *curr, *pred;
    Record *record;
    char sequence[BUF_SIZE + 1];

    rc = scanf("%d", &count_case);
    idx_case = 0;
    while (idx_case < count_case) {
        rc = scanf("%s", sequence);
        len_sequence = strlen(sequence);
        
        /* Initialize the trie. */
        trie_new_node(&root);

        /* Collect all the prefix combinations and create the relevant trie nodes. */
        for (i = 0 ; i < len_sequence ; i++) {
            curr = root;
            for (j = i ; j < len_sequence ; j++) {
                idx_branch = sequence[j];
                CHAR_TO_BRANCH_INDEX(idx_branch);
                pred = curr;
                curr = curr->branch[idx_branch];
                if (curr == NULL) {
                    trie_new_node(&curr);
                    pred->branch[idx_branch] = curr;
                }
                curr->frequency++;
            }
        }

        record = (Record*)malloc(sizeof(Record));
        record->length = 0;
        record->frequency = 1;
        trie_traverse(root, sequence, 0, record);
        if (record->frequency > 1) {
            printf("%s %d\n", record->prefix, record->frequency);
        } else {
            printf("No repetitions found!\n");
        }

        /* Deinitialize the trie. */
        trie_delete_all(root);
        free(record);
        idx_case++;
    }

    return 0;
}
