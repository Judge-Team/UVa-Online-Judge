#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


#define WORD_WIDTH      1000
#define BRANCH_DEGREE   26


typedef struct _NODE {
    bool is_word;
    struct _NODE* branch[BRANCH_DEGREE];
} NODE;


void create_node(NODE **new)
{
    int br_idx;
    *new = (NODE*)malloc(sizeof(NODE));
    for (br_idx = 0 ; br_idx < BRANCH_DEGREE ; br_idx++)
        (*new)->branch[br_idx] = NULL;
    (*new)->is_word = false;

    return;
}


void delete_tree(NODE *curr)
{
    int br_idx;
    for (br_idx = 0 ; br_idx < BRANCH_DEGREE ; br_idx++) {
        if (curr->branch[br_idx])
            delete_tree(curr->branch[br_idx]);
    }

    free(curr);

    return;
}


void update_tree(NODE *root, char *sz_word)
{
    int ofst = 0;
    char ch;
    NODE *curr = root, *pred;
    while (ch = sz_word[ofst]) {
        if (isalpha(ch)) {
            int br_idx;
            if (isupper(ch))
                br_idx = ch - 'A';
            else
                br_idx = ch - 'a';
            pred = curr;
            curr = curr->branch[br_idx];
            if (!curr) {
                create_node(&curr);
                pred->branch[br_idx] = curr;
            }
        }
        ofst++;
    }
    if (curr)
        curr->is_word = true;

    return;
}


void traverse_tree(NODE *curr, char *stack, int top)
{
    int br_idx;
    for (br_idx = 0 ; br_idx < BRANCH_DEGREE ; br_idx++) {
        if (curr->branch[br_idx]) {
            stack[top] = br_idx + 'a';
            if (curr->branch[br_idx]->is_word)
                printf("%s\n", stack);
            traverse_tree(curr->branch[br_idx], stack, top + 1);
            stack[top] = 0;
        }
    }

    return;
}


int main()
{
    char sz_word[WORD_WIDTH];
    NODE *root;
    
    create_node(&root);
    while (scanf("%s", sz_word) != EOF) {
        int ofst;
        int len_word = strlen(sz_word);
        int base = 0;
        for (ofst = 0 ; ofst < len_word ; ofst++) {
            if ((!isalpha(sz_word[ofst])) && (ofst != base)) {
                sz_word[ofst] = 0;
                update_tree(root, sz_word + base);
                base = ofst + 1;
            }
        }
        if (ofst != base) {
            sz_word[ofst] = 0;
            update_tree(root, sz_word + base);
        }
    }

    char stack[WORD_WIDTH];
    memset(stack, 0, sizeof(char) * WORD_WIDTH);
    traverse_tree(root, stack, 0);

    delete_tree(root);

    return 0;
}
