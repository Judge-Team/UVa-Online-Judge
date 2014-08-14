#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

enum {
    WORD_SIZE = 16,
    DICT_SIZE = 25000,
};

struct EditStep {
    int step;
    int word_len;
    int next;
    char word[WORD_SIZE+2];
};

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
    edit_step->next = -1;

    return 0;
}

static void insert_list(struct EditStep *edit_step, int idx, int *len_list)
{
    edit_step->next = len_list[edit_step->word_len];
    len_list[edit_step->word_len] = idx;
}

static void swap(struct EditStep **x, struct EditStep **y)
{
    struct EditStep *tmp;

    tmp = *x;
    *x = *y;
    *y = tmp;
}

static int is_one_step(struct EditStep *x, struct EditStep *y)
{
    char *ptr_x;
    char *ptr_y;
    int step;

    if (x->word_len < y->word_len) {
        swap(&x, &y);
    }

    step = 0;
    ptr_x = x->word;
    ptr_y = y->word;

    if (x->word_len == y->word_len) {
        while (*ptr_x) {
            if (*ptr_x != *ptr_y) {
                ++step;
                if (step > 1) {
                    return 0;
                }
            }
            ++ptr_x;
            ++ptr_y;
        }
    } else {
        /* x->word_len > y->word_len */
        while (*ptr_y) {
            if (*ptr_x != *ptr_y) {
                ++step;
                if (step > 1) {
                    return 0;
                }
                --ptr_y;
            }
            ++ptr_x;
            ++ptr_y;
        }
    }

    return 1;
}

int main()
{
    struct EditStep edit_step[DICT_SIZE];
    int len_list[WORD_SIZE+2];
    int edit_step_count;

    int i;
    int idx;

    int ans;

    for (i = 0; i < ARRAY_SIZE(len_list); ++i) {
        len_list[i] = -1;
    }

    edit_step_count = 0;
    load_word(&edit_step[edit_step_count]);
    insert_list(&edit_step[edit_step_count], edit_step_count, len_list);
    ans = 1;

    ++edit_step_count;

    while (load_word(&edit_step[edit_step_count]) == 0) {
        /*
         * step[i] = maximum the longest edit step end in i
         *
         * step[i] = max | step[j] + 1 if j -> i is one edit step.
         *               | 1
         *
         * To find a suitable j, we can use the balanced binary search tree. The
         * balanced B.S.T uses { length, step } as key. The suitable j will be:
         *
         *     max step in | { strlen(i)-1, step }
         *                 | { strlen(i),   step }
         *                 | { strlen(i)+1, step }
         *
         * We can use an array of list to store all previous words that have
         * particular length.
         *
         */

#if DEBUG
        printf("[edit step] start processing %s\n", edit_step[edit_step_count].word);
#endif

        for (i = edit_step[edit_step_count].word_len-1; i <= edit_step[edit_step_count].word_len+1; ++i) {
            idx = len_list[i];
            while (idx != -1) {
                if (is_one_step(&edit_step[idx], &edit_step[edit_step_count])) {
                    edit_step[edit_step_count].step = max(
                        edit_step[edit_step_count].step,
                        edit_step[idx].step+1);
#if DEBUG
                    printf("[edit step] Found %s in step[%d] = %d\n", edit_step[idx].word, idx, edit_step[idx].step);
                    printf("[edit step] Set step[%d] = %d\n", edit_step_count, edit_step[edit_step_count].step);
#endif
                    ans = max(ans, edit_step[edit_step_count].step);
                }
                idx = edit_step[idx].next;
            }
        }

        insert_list(&edit_step[edit_step_count], edit_step_count, len_list);
        ++edit_step_count;
    }

    printf("%d\n", ans);

    return 0;
}
