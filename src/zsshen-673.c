#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define SIZE_BUF    (256)


bool check_parentheses(char *sz_paren)
{
    bool b_legal = true;
    int len_sz = strlen(sz_paren) - 1;
    char *stack = (char*)malloc(sizeof(char) * len_sz);
    int idx_top, idx_sz;

    idx_top = 0;
    char ch_token;
    for (idx_sz = 0 ; idx_sz < len_sz ; idx_sz++) {
        ch_token = sz_paren[idx_sz];
        switch(ch_token) {
          case '(':
          case '[':
            stack[idx_top++] = ch_token;
            break;
          case ')':
            if (idx_top == 0)
                b_legal = false;
            else if (stack[idx_top - 1] == '(')
                idx_top--;
            break;
          case ']':
            if (idx_top == 0)
                b_legal = false;
            else if (stack[idx_top - 1] == '[')
                idx_top--;
            break;
        }

        if (!b_legal)
            break;
    }
    free(stack);

    if (b_legal)
        b_legal = (idx_top == 0)? true : false;
    return b_legal;
}


int main()
{
    char sz_paren[SIZE_BUF];
    char garbage;
    int cnt_case, idx_case, dummy;

    dummy = scanf("%d%c", &cnt_case, &garbage);
    for (idx_case = 0 ; idx_case < cnt_case ; idx_case++) {
        char *sz_dummy = fgets(sz_paren, SIZE_BUF, stdin);
        bool b_legal = check_parentheses(sz_paren);
        if (b_legal)
            printf("Yes\n");
        else
            printf("No\n");
    }

    return 0;
}
