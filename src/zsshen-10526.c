#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define BGN_TDP_CASE    "BEGIN TDP CODEBASE" 
#define END_TDP_CASE    "END TDP CODEBASE"
#define BGN_JCN_CASE    "BEGIN JCN CODEBASE"
#define END_JCN_CASE    "END JCN CODEBASE"
#define BUF_SIZE        50001


#define CHAR_SET        256
typedef struct TRIE_NODE_T {
    struct TRIE_NODE_T* branch[CHAR_SET];
} TRIE_NODE;

typedef struct RECORD_T {
    int pos;
    int len;
} RECORD;


bool check_hint_tokens(char *sz_src, int len_src, char *sz_tge, int len_tge)
{
    int idx_src = 0, idx_tge = 0;
    while ((idx_src < len_src) && (idx_tge < len_tge)) {
        if (sz_src[idx_src] != sz_tge[idx_tge])
            break;
        idx_src++;
        idx_tge++;
    }

    return (idx_tge == len_tge)? true : false;
}


void create_trie_node(TRIE_NODE **new)
{
    *new = (TRIE_NODE*)malloc(sizeof(TRIE_NODE));
    int i;
    for (i = 0 ; i < CHAR_SET ; i++)
        (*new)->branch[i] = NULL;

    return;
}


void update_suffix_trie(TRIE_NODE *root, char *sz_sfx)
{
    TRIE_NODE *pred, *curr = root;
    int idx_sfx = 0;
    char ch;
    while (ch = sz_sfx[idx_sfx++]) {
        pred = curr;
        if (!pred->branch[ch]) {
            create_trie_node(&curr);
            pred->branch[ch] = curr;
        }
        curr = pred->branch[ch];
    }    

    return;
}


void delete_suffix_trie(TRIE_NODE *curr)
{
    int i;
    for (i = 0 ; i < CHAR_SET ; i++) {
        if (curr->branch[i])
            delete_suffix_trie(curr->branch[i]);
    }
    free(curr);

    return;
}


void match_suffix_trie(TRIE_NODE *curr, char *sz_sub, int idx_bgn, int *idx_end)
{
    char ch;
    while (ch = sz_sub[idx_bgn]) {
        if (curr->branch[ch])
            curr = curr->branch[ch];
        else
            break;
        idx_bgn++;
    }

    *idx_end = idx_bgn;
    return;
}


bool check_empty_string(char *sz_mat, int idx_bgn, int idx_end)
{
    bool is_empty = true;
    while (idx_bgn < idx_end) {
        char ch = sz_mat[idx_bgn];
        if (!isspace(ch)) {
            is_empty = false;
            break;
        }
        idx_bgn++;
    }

    return is_empty;
}


int sort_record(const void *vp_src, const void *vp_tge)
{
    RECORD *rec_src = (RECORD*)vp_src;
    RECORD *rec_tge = (RECORD*)vp_tge;
    if (rec_src->len == rec_tge->len)
        return rec_tge->pos - rec_src->pos;
    return rec_tge->len - rec_src->len;
}


int main() 
{
    char sz_tdp[BUF_SIZE + 1];
    char sz_jcn[BUF_SIZE + 1];
    char sz_seg[BUF_SIZE + 1];
    int len_tdp, len_jcn;

    int len_tdp_bgn = strlen(BGN_TDP_CASE);
    int len_tdp_end = strlen(END_TDP_CASE);
    int len_jcn_bgn = strlen(BGN_JCN_CASE);
    int len_jcn_end = strlen(END_JCN_CASE);

    int cnt_case = 1;
    int cnt_expt;
    while (scanf("%d", &cnt_expt) != EOF) {
        if (cnt_expt == 0)
            break;
        if (cnt_case > 1)
            printf("\n");
        
        /* Get the TDP code base. */
        while (fgets(sz_seg, BUF_SIZE, stdin) != NULL) {
            int len_seg = strlen(sz_seg);
            bool is_bgn = check_hint_tokens(sz_seg, len_seg, BGN_TDP_CASE, len_tdp_bgn);
            if (is_bgn)
                break;
        }
        len_tdp = 0;
        while (fgets(sz_seg, BUF_SIZE, stdin) != NULL) {
            int len_seg = strlen(sz_seg);
            bool is_end = check_hint_tokens(sz_seg, len_seg, END_TDP_CASE, len_tdp_end);
            if (is_end)
                break;
            strncpy(sz_tdp + len_tdp, sz_seg, len_seg);
            len_tdp += len_seg;
            sz_tdp[len_tdp] = 0;
        }

        /* Get the JCN code base. */
        while (fgets(sz_seg, BUF_SIZE, stdin) != NULL) {
            int len_seg = strlen(sz_seg);
            bool is_bgn = check_hint_tokens(sz_seg, len_seg, BGN_JCN_CASE, len_jcn_bgn);
            if (is_bgn)
                break;
        }
        len_jcn = 0;
        while (fgets(sz_seg, BUF_SIZE, stdin) != NULL) {
            int len_seg = strlen(sz_seg);
            bool is_end = check_hint_tokens(sz_seg, len_seg, END_JCN_CASE, len_jcn_end);
            if (is_end)
                break;
            strncpy(sz_jcn + len_jcn, sz_seg, len_seg);
            len_jcn += len_seg;
            sz_jcn[len_jcn] = 0;
        }

        /* Construct the suffix trie with TDP code base. */
        TRIE_NODE *root;
        create_trie_node(&root);
        int i;
        for (i = 0 ; i < len_tdp ; i++)
            update_suffix_trie(root, sz_tdp + i);

        /* Compare the JCN substrings with the suffix trie. */
        RECORD *rec = NULL;
        int cnt_seg = 0;
        int idx_bgn = 0, idx_end, min_len = 1;
        while (idx_bgn < len_jcn) {
            match_suffix_trie(root, sz_jcn, idx_bgn, &idx_end);
            if ((idx_end - idx_bgn) < min_len) {
                if (min_len > 1)
                    min_len--;
            } else {
                bool is_empty = check_empty_string(sz_jcn, idx_bgn, idx_end);
                if (is_empty) {
                    if (min_len > 1)
                        min_len--;
                } else {
                    if (cnt_seg == 0) {
                        printf("CASE %d\n", cnt_case);
                        rec = (RECORD*)malloc(sizeof(RECORD) * BUF_SIZE);
                    }
                    min_len = idx_end - idx_bgn;
                    rec[cnt_seg].pos = idx_bgn;
                    rec[cnt_seg].len = min_len;
                    cnt_seg++;
                }
            }
            idx_bgn++;
        }

        /* Output the sorted answer. */
        if (rec) {
            qsort(rec, cnt_seg, sizeof(RECORD), sort_record);
            if (cnt_seg > cnt_expt)
                cnt_seg = cnt_expt;
            for (i = 0 ; i < cnt_seg ; i++) {
                idx_bgn = rec[i].pos;
                int len_seg = rec[i].len;
                int ofst_tail = idx_bgn + len_seg;
                char ch = sz_jcn[ofst_tail];
                sz_jcn[ofst_tail] = 0;
                printf("INFRINGING SEGMENT %d LENGTH %d POSITION %d\n%s\n",
                       (i + 1), len_seg, idx_bgn, sz_jcn + idx_bgn);    
                sz_jcn[ofst_tail] = ch;
            }
            free(rec);
        }
        delete_suffix_trie(root);
        cnt_case++;
    }

    return 0;
}
