#include <stdio.h>
#include <string.h>

enum {
    MAX_LINE_LENGTH = 1000000,
};

int is_divisible_by_4(const char *year, size_t len)
{

    int x = (year[len-2] - '0') * 10 + (year[len-1] - '0');

    return x % 4 == 0;
}

int is_divisible_by_100(const char *year, size_t len)
{
    int x = (year[len-2] - '0') * 10 + (year[len-1] - '0');

    return x == 0;
}

int is_divisible_by_400(const char *year, size_t len)
{
    return is_divisible_by_100(year, len) && is_divisible_by_4(year, len-2);
}

int is_divisible_by_5(const char *year, size_t len)
{
    int x = year[len-1] - '0';
    return x == 0 || x == 5;
}

int is_divisible_by_3(const char *year, size_t len)
{
    int i;
    int x;

    for (i = 0, x = 0; i < len; ++i) {
        x += year[i] - '0';
        x %= 3;
    }

    return x == 0;
}

int is_divisible_by_11(const char *year, size_t len)
{
    int i;
    int x;

    for (i = 0, x = 0; i < len; ++i) {
        if (i % 2) {
            x += (year[i] - '0');
        } else {
            x -= (year[i] - '0');
        }
    }

    return x % 11 == 0;
}

int is_leap_year(const char *year, size_t len)
{
    if (is_divisible_by_4(year, len)) {
        if (is_divisible_by_100(year, len)) {
            if (is_divisible_by_400(year, len)) {
                return 1;
            }
            return 0;
        }
        return 1;
    }
    return 0;
}


int is_huluculu_festival(const char *year, size_t len)
{
    return is_divisible_by_3(year, len) && is_divisible_by_5(year, len);
}

int is_bulukulu_festival(const char *year, size_t len, int leap_year)
{
    return leap_year && is_divisible_by_5(year, len) && is_divisible_by_11(year, len);
}

void strip(char *year)
{
    for (; year[0] != '\0'; ++year) {
        if (!('0' <= year[0] && year[0] <= '9')) {
            year[0] = 0;
            break;
        }
    }
}

int main()
{
    char year[MAX_LINE_LENGTH];
    int i;

    for (i = 0; fgets(year, sizeof(year), stdin); ++i) {
        int leap_year;
        int huluculu_festival;
        int bulukulu_festival;
        int len;

        if (i) {
            printf("\n");
        }

        strip(year);
        len = strlen(year);

        leap_year = is_leap_year(year, len);
        huluculu_festival = is_huluculu_festival(year, len);
        bulukulu_festival = is_bulukulu_festival(year, len, leap_year);

        if (leap_year) {
            printf("This is leap year.\n");
        }

        if (huluculu_festival) {
            printf("This is huluculu festival year.\n");
        }

        if (bulukulu_festival) {
            printf("This is bulukulu festival year.\n");
        }

        if (!(leap_year || huluculu_festival || bulukulu_festival)) {
            printf("This is an ordinary year.\n");
        }
    }
    return 0;
}
