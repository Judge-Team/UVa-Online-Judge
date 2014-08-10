#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    WORD_SIZE = 16,
    DICT_SIZE = 25000,
    ALPHABET_SIZE = 26,
};

struct TrieNode {
    int exist;
    struct TrieNode *children[ALPHABET_SIZE];
};

struct EditStep {
    int step;
    int word_len;
    char word[WORD_SIZE+1];
};

static int char_to_index(char x)
{
    return x - 'a';
}

static void insert_trie(struct TrieNode *trie, const char *str)
{
#if DEBUG
    printf("[trie] %s\n", str);
#endif

    while (*str) {
        if (trie->children[char_to_index(*str)] == NULL) {
            trie->children[char_to_index(*str)] = malloc(sizeof(*trie->children[0]));

            if (trie->children[char_to_index(*str)] ==NULL) {
                exit(-1);
            }

            memset(trie->children[char_to_index(*str)], 0, sizeof(*trie->children[0]));
        }
        trie = trie->children[char_to_index(*str)];
        ++str;
    }
    trie->exist = 1;
}

struct TrieNode *create_trie(const char *str)
{
    struct TrieNode *trie;
    int c;
    int pos;
    char word[WORD_SIZE+1+1];
    int len;

    trie = malloc(sizeof(*trie));
    if (trie == NULL) {
        exit(-1);
    }
    memset(trie, 0, sizeof(*trie));

    len = strlen(str);

#if DEBUG
    printf("[trie] insert all string which has one edit step from %s\n", str);
#endif

    /* insert */
    for (pos = 0; pos <= len; ++pos) {
        memcpy(word, str, pos);
        memcpy(word+pos+1, str+pos, len-pos);
        word[len+1] = 0;

        for (c = 'a'; c <= 'z'; ++c) {
            word[pos] = c;
            insert_trie(trie, word);
        }
    }

    /* delete */
    for (pos = 0; pos < len; ++pos) {
        memcpy(word, str, pos);
        memcpy(word+pos, str+pos+1, len-pos-1);
        word[len-1] = 0;
        insert_trie(trie, word);
    }

    /* change */
    for (pos = 0; pos < len; ++pos) {
        strcpy(word, str);
        for (c = 'a'; c <= 'z'; ++c) {
            word[pos] = c;
            insert_trie(trie, word);
        }
    }

    return trie;
}

static void destroy_trie(struct TrieNode *trie)
{
    int i;

    for (i = 0; i < ALPHABET_SIZE; ++i) {
        if (trie->children[i] != NULL) {
            destroy_trie(trie->children[i]);
        }
    }
    free(trie);
}

static int is_in_trie(const struct TrieNode *trie, const char *str)
{
    struct TrieNode *next;

    while (*str) {
        next = trie->children[char_to_index(*str)];
        if (next == NULL) {
            return 0;
        }
        trie = next;
        str++;
    }

    return trie->exist;
}

static int max(int x, int y)
{
    return x > y ? x : y;
}

static void remove_tailing_newline(char *str)
{
    int len;

    len = strlen(str);

    if (str[len-1] == '\n') {
        str[len-1] = 0;
    }
}

static int load_word(struct EditStep *edit_step)
{
    char *ret;
    ret = fgets(edit_step->word, sizeof(edit_step->word), stdin);
    if (ret == NULL) {
        return -1;
    }

    remove_tailing_newline(edit_step->word);
    edit_step->word_len = strlen(edit_step->word);
    edit_step->step = 1;

    return 0;
}

int main()
{
    struct TrieNode *trie;

    struct EditStep edit_step[DICT_SIZE];
    int edit_step_count;

    int i;

    int ans;

    edit_step_count = 0;
    load_word(&edit_step[edit_step_count]);
    ans = 1;

    ++edit_step_count;

    while (load_word(&edit_step[edit_step_count]) == 0) {
        /*
         * step[i] = maximum the longest edit step end in i
         *
         * step[i] = max | step[j] + 1 if j -> i is one edit step.
         *               | 1
         */

#if DEBUG
        printf("[edit step] start processing %s\n", edit_step[edit_step_count].word);
#endif

        trie = create_trie(edit_step[edit_step_count].word);

        for (i = 0; i < edit_step_count; ++i) {
            if (abs(edit_step[i].word_len - edit_step[edit_step_count].word_len) <= 1 &&
                is_in_trie(trie, edit_step[i].word)) {
                edit_step[edit_step_count].step = max(
                    edit_step[edit_step_count].step,
                    edit_step[i].step+1);
#if DEBUG
                printf("[edit step] Found %s in trie %d, step[%d] = %d\n",word, i, i, edit_step[i].step);
                printf("[edit step] Set step[%d] = %d\n", edit_step_count, edit_step[edit_step_count].step);
#endif
                ans = max(ans, edit_step[edit_step_count].step);
            }
        }

        destroy_trie(trie);

        ++edit_step_count;
    }

    printf("%d\n", ans);

    return 0;
}
