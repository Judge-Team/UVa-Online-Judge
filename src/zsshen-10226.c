#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define NAME_LENGTH             100
#define CHARACTER_SET           256
#define CHARACTER_BASE_NUMBER   1
#define CHARACTER_BASE_UPPER    11
#define CHARACTER_BASE_LOWER    37


typedef struct _Node {
    struct _Node *branch[CHARACTER_SET];
    int frequency;
} Node;


int transform_char_to_index(char ch) {

    if (ch == ' ') {
        return 0;
    } else if ((ch >= '0') && (ch <= '9')) {
        return CHARACTER_BASE_NUMBER + (ch - '0'); 
    } else if ((ch >= 'A') && (ch <= 'Z')) {
        return CHARACTER_BASE_UPPER + (ch - 'A');
    } else if ((ch >= 'a') && (ch <= 'z')) {
        return CHARACTER_BASE_LOWER + (ch - 'a');
    }
}


char transform_index_to_char(int idx) {

    if (idx == 0) {
        return ' ';
    } else if ((idx >= CHARACTER_BASE_NUMBER) && (idx < CHARACTER_BASE_UPPER)) {
        return (idx - CHARACTER_BASE_NUMBER) + '0';
    } else if ((idx >= CHARACTER_BASE_UPPER) && (idx < CHARACTER_BASE_LOWER)) {
        return (idx - CHARACTER_BASE_UPPER) + 'A';
    } else if (idx >= CHARACTER_BASE_LOWER) {
        return (idx - CHARACTER_BASE_LOWER) + 'a';
    }
}


void trie_traverse(Node *curr, char *prefix, int idx, int count_str) {
    int i;

    if (curr != NULL) {
        if (curr->frequency > 0) {
            prefix[idx] = 0;
            printf("%s %.4lf\n", prefix, ((double)curr->frequency / count_str) * 100);
        }
        for (i = 0 ; i < CHARACTER_SET ; i++) {
            if (curr->branch[i] != NULL) {
                prefix[idx] = i;    
                trie_traverse(curr->branch[i], prefix, idx + 1, count_str);
            }
        }
    }

    return;
}


void trie_new_node(Node **p_new) {
    int i;

    (*p_new) = (Node*)malloc(sizeof(Node));
    for (i = 0 ; i < CHARACTER_SET ; i++) {
        (*p_new)->branch[i] = NULL;
    }
    (*p_new)->frequency = 0;

    return;
}


void trie_delete_all(Node *curr) {
    int i;

    if (curr != NULL) {
        for (i = 0 ; i < CHARACTER_SET ; i++) {
            if (curr->branch[i] != NULL) {
                trie_delete_all(curr->branch[i]);
            }
        }
        free(curr);
    }
    
    return;
}


int main() {
    int  i, rc, idx_test, count_test, len_name, count_str, idx_branch;
    char absorb;
    char *ret;
    Node *root, *curr, *pred;
    char name[NAME_LENGTH + 1];

    rc = scanf("%d%c", &count_test, &absorb);
    ret = fgets(name, (NAME_LENGTH + 1), stdin);
    idx_test = 0;
    while (idx_test < count_test) {
        
        /* Initialize the trie. */
        trie_new_node(&root);
        count_str = 0;

        while (true) {
            memset(name, 0, sizeof(char) * (NAME_LENGTH + 1));
            ret = fgets(name, (NAME_LENGTH + 1), stdin);
            if (ret == NULL) {
                break;
            }
            len_name = strlen(name);
            if (len_name == 1) {
                break;
            }

            /* Create the relevant trie nodes for this string. */
            curr = root;
            for (i = 0 ; i < (len_name - 1) ; i++) {
                idx_branch = name[i];
                pred = curr;
                curr = curr->branch[idx_branch];
                if (curr == NULL) {
                    trie_new_node(&curr);
                    pred->branch[idx_branch] = curr;
                }
            }
            curr->frequency++;

            count_str++;
        }

        /* Traverse the trie and print the answer. */
        trie_traverse(root, name, 0, count_str);

        /* Deinitialize the trie. */
        trie_delete_all(root);

        idx_test++;
        if (idx_test != count_test) {
            printf("\n");
        }
    }

    return 0;
}
