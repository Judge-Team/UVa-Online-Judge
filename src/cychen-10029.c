#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDLENMAX 17
static char *newline = "\n";
/*static char *spaces=" \r\n";*/
struct node {
    int count;
    char *word;
    struct node *pre;
};
 
static int editstepcmp(char *s1, char *s2) {
    int lens1, lens2, lentemp, diff, i;
    char *temp;
    lens1 = strlen(s1);
    lens2 = strlen(s2);
    if(lens1 < lens2) {
        temp = s1;
        s1 = s2;
        s2 = temp;
        lentemp = lens1;
        lens1 = lens2;
        lens2 = lentemp;
    }
    /*
    debug
    printf("%s %s\n", s1, s2);
    return 0;
    */

    diff = 0;

    if(lens1 == lens2) {
        for(i = 0; i < lens1; i++) {
            if(s1[i] != s2[i]) {
                diff++;
                if(diff > 1) return -1;
            }
        }
        if(diff == 0) return -1;
        else return 0;
    }
    else if((lens1 - lens2) == 1) {
        for(i = 0; i < lens1; i++) {
            temp = malloc(lens1);
            /*debug
            printf("before %s\n", s1);*/
            strncpy(temp, s1, i);
            strncpy(&temp[i], &s1[i+1], lens1 - i - 1);
            /*printf("after %s\n", temp);*/
            diff = strcmp(temp, s2);
            if(diff == 0) return 0;
            free(temp);
        }
        return -1;
    }
    else {
        return -1;
    }
}
 
int main(int argc, char **argv) {
    char word[WORDLENMAX];
    int max, maxstep = 0;
    struct node *last = NULL, *tmp;
    last = malloc(sizeof(struct node));
    last->pre = 0;
    
    /*while(getline(&line, &bufsize, stdin)) {*/
    while(fgets(word, WORDLENMAX, stdin) != NULL) {
        strtok(word, newline);
        /*word = strsep(&line, spaces);*/
        if (word[0] == '\0' || word[0] == '\r' || word[0] == '\n') {
            break;
        }
        max = 0;
        tmp = last;
        while(tmp->pre != NULL) {
            /*debug
            printf("%s, %d\n", tmp->word, tmp->count);*/
            if(editstepcmp(word, tmp->word) == 0) {
                if(tmp->count > max) {
                    max = tmp->count;
                }
            }
            tmp = tmp->pre;
            
        }
        struct node *newnode = NULL;
        newnode = malloc(sizeof(struct node));
        newnode->count = max + 1;
        /*Fucking Wrong
            newnode->word = word;
        */
        newnode->word = (char*)malloc(strlen(word));
        strcpy(newnode->word, word);
        newnode->pre = last;
        last = newnode;
        if(newnode->count > maxstep) maxstep = newnode->count;
    }
    printf("%d\n", maxstep);
    return 0;
}
