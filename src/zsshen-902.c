#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/*
Do not pass OJ for the first time. List down the bugs:
    1. The buffer size for input message is too small (Set for 4096 bytes).
    2. The off-by-one issue:
       previous loop: i = 0 ; i <  len_msg - len_pswd ; i++.
       correct  loop: i = 0 ; i <= len_msg - len_pswd ; i++
*/


#define BUF_SIZE_LARGE  1000000
#define BUF_SIZE_SMALL  10
#define BRANCH_DEGREE   26


typedef struct _TrieNode {
    struct _TrieNode *branch[BRANCH_DEGREE];
    int freq;
} TrieNode;


void find_pswd(int, char*);

void trie_create_node(TrieNode **);

void trie_delete(TrieNode *);


int main() {
    int  rc, len_pswd;    
    char msg[BUF_SIZE_LARGE + 1];
    
    while (true) {
        memset(msg, 0, sizeof(char) * (BUF_SIZE_LARGE + 1));
        rc = scanf("%d%s", &len_pswd, msg);            
        if (rc != 2) {
            break;
        }
        
        find_pswd(len_pswd, msg);
    }

    return 0;
}


void find_pswd(int len_pswd, char *msg) {
    int i, j, len_msg, idx_branch, max_freq;    
    TrieNode *root, *curr, *pred;
    char pswd[BUF_SIZE_SMALL + 1];

    /* Initialize the trie. */
    trie_create_node(&root);

    len_msg = strlen(msg);
    max_freq = 0;
    for (i = 0 ; i <= len_msg - len_pswd ; i++) {
        curr = root;        

        /* Traverse the trie and create the nodes if necessary. */
        for (j = i ; j < i + len_pswd ; j++) {
            idx_branch =  msg[j] - 'a';
            pred = curr;
            curr = pred->branch[idx_branch];
            if (curr == NULL) {
                trie_create_node(&curr);
                pred->branch[idx_branch] = curr;
            }
        }
        curr->freq++;

        /* If the frequency of the current substring is larger than the one of
           temporary password, it should be the new password candidate. */
        if (max_freq <= curr->freq) {
            max_freq = curr->freq;
            memset(pswd, 0, sizeof(char) * (BUF_SIZE_SMALL + 1));
            strncpy(pswd, msg + i, len_pswd);
        }
    }

    if (max_freq > 0) {
        printf("%s\n", pswd);
    }

    /* Deinitialize the trie. */
    trie_delete(root);
    return;
}


void trie_create_node(TrieNode **p_new) {
    int i;

    *p_new = (TrieNode*)malloc(sizeof(TrieNode));
    for (i = 0 ; i < BRANCH_DEGREE ; i++) {
        (*p_new)->branch[i] = NULL;
    }    
    (*p_new)->freq = 0;

    return;
}


void trie_delete(TrieNode *curr) {
    int i;

    if (curr != NULL) {
        for (i = 0 ; i < BRANCH_DEGREE ; i++) {
            trie_delete(curr->branch[i]);
        }
        free(curr);
    }

    return;
}


