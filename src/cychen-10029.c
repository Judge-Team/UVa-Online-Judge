#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDLENMAX 18
/*static char *newline = "\n";*/
struct node {
    int count;
    int length;
    char *word;
    struct node *pre;
};
 
static int editstepcmp(char *s1, int lens1, char *s2, int lens2) {
    int lentemp, diff, i, j;
    char *temp;
    if(lens1 < lens2) {
        temp = s1;
        s1 = s2;
        s2 = temp;
        lentemp = lens1;
        lens1 = lens2;
        lens2 = lentemp;
    }

#if DEBUG
    printf("Compare stings: %s, %s\n", s1, s2);
#endif

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
    /*else if((lens1 - lens2) == 1) {*/
    else {
        for(i = 0, j = 0; i < lens2;) {
/*
            temp = malloc(lens1);
#if DEBUG
            printf("before modify string: %s\n", s1);
#endif
            strncpy(temp, s1, i);
            strncpy(&temp[i], &s1[i+1], lens1 - i - 1);
#if DEBUG
            printf("after modify string: %s\n", temp);
#endif
            diff = strcmp(temp, s2);
*/          
            if(s2[i] == s1[j]) {
                i++;
                j++;
                continue;
            }
            else {
                j++;
                diff++; 
            }
            if(diff > 1) return -1;
        }
        return 0;
        /*free(temp);return -1;*/
    }
    /*else {
        return -1;
    }*/
}
 
int main(int argc, char **argv) {
    char word[WORDLENMAX];
    int i, strlength = 0, max, maxstep = 0;
    struct node *len[WORDLENMAX];
    struct node *tmp, *tmp1;

/*origin
    struct node *last = NULL, *tmp;
    last = malloc(sizeof(struct node));
    last->pre = 0;
*/
    
    for (i = 0 ; i < WORDLENMAX ; i++){
        len[i] = NULL;
        len[i] = malloc(sizeof(struct node));
        len[i]->pre = 0;
    }

    memset(word, 0 , sizeof(char) * WORDLENMAX);    
    while(scanf("%s", word) != EOF) {
        /*strtok(word, newline);
        word = strsep(&line, spaces);
        if (word[0] == '\0' || word[0] == '\r' || word[0] == '\n') {
            break;
        }*/
        strlength = strlen(word);
        max = 0;

/*origin
        tmp = last;
        while(tmp->pre != NULL) {
            if(editstepcmp(word, tmp->word) == 0) {
                if(tmp->count > max) {
                    max = tmp->count;
                }
            }
            tmp = tmp->pre;    
        }
*/
        for(i = -1; i <= 1; i++) {
            if((strlength + i - 1) < 0 || (strlength + i) > WORDLENMAX) continue;
            tmp = len[strlength + i - 1];
            while(tmp->pre != NULL) {
                /*printf("check 1: %x, %s, %d\n", tmp->pre, tmp->word, tmp->count);*/
                if(editstepcmp(word, strlength, tmp->word, tmp->length) == 0) {
                    if(tmp->count > max) {
                        max = tmp->count;
                    }
                }
                tmp = tmp->pre;
            }
        }

        struct node *newnode = NULL;
        newnode = malloc(sizeof(struct node));
        newnode->count = max + 1;
        newnode->length = strlength;
        /*Fucking Wrong
            newnode->word = word;
        */
        newnode->word = (char*)malloc(strlen(word));
        strcpy(newnode->word, word);
/*origin
        newnode->pre = last;
        last = newnode;
*/
        newnode->pre = len[strlength - 1];
        /*printf("check 2: %x, %s\n", newnode->pre, newnode->word);*/
        len[strlength - 1] = newnode;

        if(newnode->count > maxstep) maxstep = newnode->count;
    }

    /*free node*/
    for(i = 0; i < WORDLENMAX; i++) {
        if(len[i] != NULL) {
            tmp = len[i];
            while(tmp != NULL) {
                tmp1 = tmp;
                tmp = tmp->pre;                
                free(tmp1);
            }
        }
    }

    printf("%d\n", maxstep);
    return 0;
}
