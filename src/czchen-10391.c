#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

enum {
    MAX_WORD_LEN = 1000,
    MAX_CHILDREN_COUNT = 26,
};

struct Node {
    unsigned int is_end_:1;
    struct Node *children_[MAX_CHILDREN_COUNT];
};

struct DFSBuffer {
    char char_;
    unsigned int is_end_:1;
};

void print_word(struct DFSBuffer *buf, size_t buf_len)
{
    int idx;

    for (idx = 0; idx < buf_len; ++idx) {
        printf("%c", buf[idx].char_);
    }
    printf("\n");
}

int has_word(struct Node *ptr, struct DFSBuffer *buf, size_t buf_len)
{
    int idx;

#if DEBUG
    printf("has_word = ");
    print_word(buf, buf_len);
#endif

    for (idx = 0; idx < buf_len; ++idx) {
        if (!ptr->children_[buf[idx].char_ - 'a']) {
            return 0;
        }
        ptr = ptr->children_[buf[idx].char_ - 'a'];
    }

    return ptr->is_end_;
}

void search(struct Node *trie, struct DFSBuffer *buf, size_t buf_len, struct Node *ptr)
{
    int idx;

    if (ptr->is_end_) {
        /*
         * Search for possible compound word.
         */

#if DEBUG
        printf("len = %zu, word: ", buf_len);
        print_word(buf, buf_len);
#endif

        for (idx = 0; idx < buf_len - 1; ++idx) {
            if (buf[idx].is_end_ && has_word(trie, buf + idx + 1, buf_len - idx - 1)) {
                print_word(buf, buf_len);
                break;
            }
         }
    }

    for (idx = 0; idx < MAX_CHILDREN_COUNT; ++idx) {
        if (ptr->children_[idx]) {

            buf[buf_len].char_ = idx + 'a';
            buf[buf_len].is_end_ = ptr->children_[idx]->is_end_;

            search(trie, buf, buf_len+1, ptr->children_[idx]);
        }
    }
}

int main()
{
    char buf[MAX_WORD_LEN];

    struct Node trie = { 0 };
    struct Node *ptr;

    char *c;
    size_t idx;

    struct DFSBuffer dfs_buf[MAX_WORD_LEN];

    /*
     * Build a trie and do depth-first search.
     */

    while (scanf("%s", buf) == 1) {
        for (c = buf, ptr = &trie; *c; ++c) {
            idx = *c - 'a';
            if (!ptr->children_[idx]) {
                ptr->children_[idx] = calloc(1, sizeof(*ptr->children_[idx]));
                if (!ptr->children_[idx]) {
                    exit(-1);
                }
            }
            ptr = ptr->children_[idx];
        }

        ptr->is_end_ = 1;
    }

    search(&trie, dfs_buf, 0, &trie);

    return 0;
}
