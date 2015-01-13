#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define STRAND_BASE_TYPE    (4)
#define STRING_LENGTH       (512)
#define FLAG_FIRST          (0)
#define FLAG_SECOND         (1)


#define GET_BASE(ch, base)          switch(ch) {                \
                                      case 'a':                 \
                                        base = 0;               \
                                        break;                  \
                                      case 'c':                 \
                                        base = 1;               \
                                        break;                  \
                                      case 'g':                 \
                                        base = 2;               \
                                        break;                  \
                                      case 't':                 \
                                        base = 3;               \
                                    }

#define GET_CHAR(base, ch)          switch(base) {              \
                                      case 0:                   \
                                        ch = 'a';               \
                                        break;                  \
                                      case 1:                   \
                                        ch = 'c';               \
                                        break;                  \
                                      case 2:                   \
                                        ch = 'g';               \
                                        break;                  \
                                      case 3:                   \
                                        ch = 't';               \
                                    }

#define SET_FLAG(flag, ptr)         switch(flag) {              \
                                      case FLAG_FIRST:          \
                                        ptr->b_fst = true;      \
                                        break;                  \
                                      case FLAG_SECOND:         \
                                        ptr->b_snd = true;      \
                                    }


typedef struct TRIE_NODE_T {
    struct TRIE_NODE_T *branch[STRAND_BASE_TYPE];
    bool b_fst, b_snd;
} TRIE_NODE;


void create_tree_node(TRIE_NODE** new);
void update_suffix_tree(TRIE_NODE* root, char* sz_suffix, int flag_sz, int* len_lcp);
void find_lcp_from_tree(TRIE_NODE* root, char* sz_prefix, int depth, int len_lcp);
void destroy_suffix_tree(TRIE_NODE* curr);


int main() 
{
    bool fst_case, more_case;
    char sz_fst[STRING_LENGTH + 1];
    char sz_snd[STRING_LENGTH + 1];
    char sz_prefix[STRING_LENGTH + 1];
    int len_fst, len_snd;

    fst_case = true;
    more_case = false;
    while (true) {
        TRIE_NODE *root;
        bool last_case = false;
        while (true) {
            if (fgets(sz_fst, STRING_LENGTH, stdin) == NULL) {
                last_case = true;
                break;
            }
            len_fst = strlen(sz_fst);
            if (len_fst > 1) {
                sz_fst[len_fst - 1] = 0;
                len_fst--;
                break;
            }
            if (!fst_case)
                more_case = true;
        }
        if (last_case)
            break;

        int dummy = scanf("%s", sz_snd);
        len_snd = strlen(sz_snd);

        if (more_case)
            printf("\n");

        /* Create the root of suffix tree. */
        create_tree_node(&root);

        /* Generate all suffixes of the given strings. */
        int i, len_lcp = 0;
        for (i = 0 ; i < len_fst ; i++)
            update_suffix_tree(root, sz_fst + i, FLAG_FIRST, &len_lcp);
        for (i = 0 ; i < len_snd ; i++)
            update_suffix_tree(root, sz_snd + i, FLAG_SECOND, &len_lcp);

        if (len_lcp > 0) {
            memset(sz_prefix, 0, sizeof(char) * (STRING_LENGTH + 1));
            find_lcp_from_tree(root, sz_prefix, 0, len_lcp);
        } else
            printf("No common sequence.\n");

        fst_case = false;
        destroy_suffix_tree(root);
    }

    return 0;
}


void create_tree_node(TRIE_NODE** new)
{
    int i;
    *new = (TRIE_NODE*)malloc(sizeof(TRIE_NODE));
    for (i = 0 ; i < STRAND_BASE_TYPE ; i++)
        (*new)->branch[i] = NULL;
    (*new)->b_fst = (*new)->b_snd = false;

    return;
}


void update_suffix_tree(TRIE_NODE* root, char* sz_suffix, int flag_sz, int* len_lcp)
{
    TRIE_NODE *pred = root, *curr;
    char ch, base;
    int depth = 0;
    while ((ch = *sz_suffix++)) {
        GET_BASE(ch, base);
        curr = pred->branch[base];
        if (!curr) {
            create_tree_node(&curr);
            pred->branch[base] = curr;
        }
        pred = curr;
        depth++;

        SET_FLAG(flag_sz, pred);
        if (pred->b_fst & pred->b_snd) {
            if (depth > *len_lcp)
                *len_lcp = depth;
        }
    }    

    return;
}


void find_lcp_from_tree(TRIE_NODE* curr, char* sz_prefix, int depth, int len_lcp)
{
    int i;
    for (i = 0 ; i < STRAND_BASE_TYPE ; i++) {
        if (curr->branch[i]) {
            char ch;
            GET_CHAR(i, ch);
            sz_prefix[depth] = ch;
            find_lcp_from_tree(curr->branch[i], sz_prefix, depth + 1, len_lcp);
            sz_prefix[depth] = 0;
        }
    }

    if ((depth == len_lcp) && (curr->b_fst & curr->b_snd))
        printf("%s\n", sz_prefix);
    
    return;
}


void destroy_suffix_tree(TRIE_NODE* curr)
{
    int i;
    for (i = 0 ; i < STRAND_BASE_TYPE ; i++) {
        if (curr->branch[i])
            destroy_suffix_tree(curr->branch[i]);
    }
    free(curr);

    return;
}
