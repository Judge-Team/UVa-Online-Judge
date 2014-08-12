#include <stdio.h>
#include <string.h>

enum {
    MAX_CITY = 50,
    MAX_SPEECH = 20,
};

static unsigned long long next_cities(
        unsigned long long *city,
        int city_cnt,
        unsigned long long curr_cities
)
{
    int i;
    unsigned long long next_cities;

    next_cities = 0;
    for (i = 0; i < city_cnt; ++i) {
        if (curr_cities & (0x1 << i)) {
            next_cities |= city[i];
        }
    }

    return next_cities;
}

int main()
{
    int city_cnt;
    int road_cnt;
    int speech_cnt;
    int step_cnt;

    int from;
    int to;

    int i;

    unsigned long long city[MAX_CITY];
    unsigned long long curr_cities;
    int step;

    while (scanf("%d%d%d", &city_cnt, &road_cnt, &speech_cnt) == 3) {
        if (city_cnt == 0 && road_cnt == 0 && speech_cnt == 0) {
            break;
        }
        /*
         * We use bitmask to store road. city[0] = 0x2 means city 0 has a road
         * to city 1 (2 = 0x1 << 1).
         */
        memset(city, 0, sizeof(city));

        for (i = 0; i < road_cnt; ++i) {
            scanf("%d%d", &from, &to);
            if (from != to) {
                city[from] |= (0x1 << to);
            }
        }

#if DEBUG
        for (i = 0; i < city_cnt; ++i) {
            printf("[%d] = %#llx\n", i, city[i]);
        }
#endif

        curr_cities = 0x1;
        /*
         * step_cnt = speech_cnt - 1 because politician needs to speech in
         * hometown and the capital city.
         *
         * Now using Bellman-Ford algorithm to find if we can reach capital in
         * k ~ (MAX_SPEECH-1) steps.
         */
        step_cnt = speech_cnt - 1;

        for (step = 1; step < step_cnt; ++step) {
            curr_cities = next_cities(city, city_cnt, curr_cities);
#if DEBUG
            printf("step = %d, curr_cities = %#llx\n", step, curr_cities);
#endif
        }

        for (; step < MAX_SPEECH; ++step) {
            curr_cities = next_cities(city, city_cnt, curr_cities);
#if DEBUG
            printf("step = %d, curr_cities = %#llx\n", step, curr_cities);
#endif
            if (curr_cities & (0x1 << (city_cnt - 1))) {
                    break;
            }
        }

        if (step < MAX_SPEECH) {
            printf("%d\n", step+1);
        } else {
            printf("LOSER\n");
        }
    }

    return 0;
}
