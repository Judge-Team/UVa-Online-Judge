#include <stdio.h>
#include <string.h>

enum {
    MIN_AGE = 1,
    MAX_AGE = 99,
};

int main()
{
    int people;
    int count[MAX_AGE-MIN_AGE+1];
    int age;
    int i;

    while (scanf("%d", &people) == 1) {
        if (people == 0) {
            break;
        }

        memset(count, 0, sizeof(count));

        for (i = 0; i < people; ++i) {
            scanf("%d", &age);
            ++count[age-MIN_AGE];
        }

        for (age = 0; age < MAX_AGE-MIN_AGE+1; ++age) {
            if (count[age]) {
                printf("%d", age+MIN_AGE);
                --count[age];
                break;
            }
        }

        for (; age < MAX_AGE-MIN_AGE+1; ++age) {
            for (i = 0; i < count[age]; ++i) {
                printf(" %d", age+MIN_AGE);
            }
        }
        printf("\n");
    }

    return 0;
}
