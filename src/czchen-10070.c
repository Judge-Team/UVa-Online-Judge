#include <stdio.h>

int is_leap_year(int year)
{
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                return 1;
            }
            return 0;
        }
        return 1;
    }
    return 0;
}

int is_huluculu_festival(int year)
{
    return year % 15 == 0;
}

int is_bulukulu_festival(int year, int is_leap_year)
{
    return is_leap_year && year % 55 == 0;
}

int main()
{
    int year;
    int i;

    for (i = 0; scanf("%d", &year) == 1; ++i) {
        int leap_year;
        int huluculu_festival;
        int bulukulu_festival;

        if (i) {
            printf("\n");
        }

        leap_year = is_leap_year(year);
        huluculu_festival = is_huluculu_festival(year);
        bulukulu_festival = is_bulukulu_festival(year, leap_year);

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
