#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define BUF_SIZE        10000


#define PRIORITY_ADD    0
#define PRIORITY_SUB    0
#define PRIORITY_MUL    1
#define PRIORITY_DIV    1


/* The utility function to get the operator priority. */
char get_operator_priority(char);


int main() {
    int  round, length, top;
    char ch, garbage, priority_src, priority_tge;
    char stack[BUF_SIZE];

    garbage = scanf("%d%c%c", &round, &garbage, &garbage);
    
    do {
        top = -1;
        while (true) {
            
            garbage = scanf("%c", &ch);
            /* Check for the end of single test case. */
            if (ch == '\n') {
                break;
            }
            
            /* Check for the end of all test cases. */
            if (feof(stdin) > 0) {
                break;
            }
            garbage = scanf("%c", &garbage);

            /* The Polish transformation. */
            if ((ch >= '0') && (ch <= '9')) {
                printf("%c", ch);
            } else {   
                if ((top == -1) || (ch == '(')) {
                    stack[++top] = ch;
                } else if (ch == ')') {
                    while (stack[top] != '(') {
                        printf("%c", stack[top--]);
                    }
                    top--;
                } else {
                    while ((top >= 0) && (stack[top] != '(')) {
                        priority_src = get_operator_priority(stack[top]);
                        priority_tge = get_operator_priority(ch);
                        if (priority_src < priority_tge) {
                            break;
                        }
                        printf("%c", stack[top--]);
                    }
                    stack[++top] = ch;
                }
            }
        }
        while (top >= 0) {
            printf("%c", stack[top--]);
        }
        printf("\n");

        round--;
        if (round == 0)
            break;
        printf("\n");

    } while (true);
    
    return 0;
}


char get_operator_priority(char operator) {

    switch(operator) {
        case '+':
            return PRIORITY_ADD;
        case '-':
            return PRIORITY_SUB;
        case '*':
            return PRIORITY_MUL;
        case '/':
            return PRIORITY_DIV;
    }
}
