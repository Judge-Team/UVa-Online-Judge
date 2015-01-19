#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define BUF_SIZE        2000000
#define AGE_LIMIT       100


void sort_by_counting(int cnt_people, char *age_in, char *age_out, int *cnt_freq)
{
    int i, dummy;
    for (i = 0 ; i < AGE_LIMIT ; i++)
        cnt_freq[i] = 0;

    for (i = 0 ; i < cnt_people ; i++) {
        dummy = scanf("%d", &(age_in[i]));
        cnt_freq[age_in[i]]++;
    }

    for (i = 1 ; i < AGE_LIMIT ; i++)
        cnt_freq[i] += cnt_freq[i - 1];

    for (i = 0 ; i < cnt_people ; i++) {
        age_out[cnt_freq[age_in[i]] - 1] = age_in[i];
        cnt_freq[age_in[i]]--;
    }

    return;
}


int main()
{
    int cnt_people;
    char *age_in = (char*)malloc(sizeof(char) * BUF_SIZE);
    char *age_out = (char*)malloc(sizeof(char) * BUF_SIZE);
    int *cnt_freq = (int*)malloc(sizeof(int) * AGE_LIMIT);

    while (scanf("%d", &cnt_people) != EOF) {
        if (cnt_people == 0)
            break;
        sort_by_counting(cnt_people, age_in, age_out, cnt_freq);
        int i;
        for (i = 0 ; i < (cnt_people - 1) ; i++)
            printf("%d ", age_out[i]);
        printf("%d\n", age_out[cnt_people - 1]);
    }

    free(age_in);
    free(age_out);
    free(cnt_freq);
    return 0;
}
