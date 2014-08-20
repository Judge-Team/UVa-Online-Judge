#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    MAX_LINE = 200,
    ALPHABET_SIZE = 26 * 2,
};

struct Anagram {
    int data_size;
    int cnt;
    struct {
        char c;
        int cnt;
    } data[ALPHABET_SIZE];
};

int compare(const void *ptr_x, const void *ptr_y)
{
    char x;
    char y;
    char low_x;
    char low_y;

    x = *(const char *) ptr_x;
    y = *(const char *) ptr_y;
    low_x = x | 0x20;
    low_y = y | 0x20;

    if (low_x == low_y) {
        return x - y;
    }

    return low_x - low_y;
}

static void update_anagram(char c, struct Anagram *anagram)
{
    int i;

    ++anagram->cnt;

    for (i = 0; i < anagram->data_size; ++i) {
        if (anagram->data[i].c == c) {
            ++anagram->data[i].cnt;
            return;
        }
    }

    assert(anagram->data_size < ALPHABET_SIZE);

    anagram->data[anagram->data_size].c = c;
    anagram->data[anagram->data_size].cnt = 1;
    ++anagram->data_size;
}

static void read_anagram(struct Anagram *anagram, char *line, size_t line_size)
{
    char *ptr;

    fgets(line, line_size, stdin);

    anagram->cnt = 0;
    anagram->data_size = 0;

    for (ptr = line; *ptr != '\n'; ++ptr) {
        update_anagram(*ptr, anagram);
    }

    qsort(anagram->data, anagram->data_size, sizeof(anagram->data[0]), compare);
}

static void print_anagram(struct Anagram *anagram, int pos, char *line, size_t line_size)
{
    int i;

    assert(pos < line_size);

    if (anagram->cnt == 0) {
        line[pos] = 0;
        printf("%s\n", line);
        return;
    }

    for (i = 0; i < anagram->data_size; ++i) {
        if (anagram->data[i].cnt == 0) {
            continue;
        }

        --anagram->cnt;
        --anagram->data[i].cnt;

        line[pos] = anagram->data[i].c;
        print_anagram(anagram, pos+1, line, line_size);

        ++anagram->data[i].cnt;
        ++anagram->cnt;
    }
}

int main()
{
    int cases;
    char line[MAX_LINE];

#if DEBUG
    int i;
#endif

    struct Anagram anagram;

    scanf("%d\n", &cases);
    for (; cases > 0; --cases) {
        read_anagram(&anagram, line, sizeof(line));

#if DEBUG
        printf("data_size = %d, cnt = %d\n", anagram.data_size, anagram.cnt);
        for (i = 0; i < anagram.cnt; ++i) {
            printf("(%c, %d) ", anagram.data[i].c, anagram.data[i].cnt);
        }
        printf("\n");
#endif

        assert(anagram.cnt < sizeof(line) - 1);

        print_anagram(&anagram, 0, line, sizeof(line));
    }

    return 0;
}
