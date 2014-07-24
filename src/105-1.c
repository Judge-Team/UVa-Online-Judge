#include <stdio.h>

enum {
    MAX_BUILD = 5000,
    MAX_COORDINATE = 10000,
};

struct Build {
    int left;
    int height;
    int right;
};

struct Data {
    int research_start;
    int next_skyline_cand;
    int current_skyline;
    int pos;
    struct Build build[MAX_BUILD];
    int build_count;
};

int find_next_skyline_in_research(struct Data *data)
{
    int i;
    int new_current_skyline = -1;

    for (i = data->research_start; i < data->next_skyline_cand; ++i) {
        if (data->build[i].right <= data->pos) {
            if (i == data->research_start) {
                ++data->research_start;
            }

            continue;
        }

        if (new_current_skyline == -1 ||
            data->build[new_current_skyline].height < data->build[i].height) {
            new_current_skyline = i;
        }
    }

    return new_current_skyline;
}

int handle_skyline_end_with_next(struct Data *data)
{
    int i;
    int new_current_skyline = -1;

    new_current_skyline = find_next_skyline_in_research(data);

    if (data->pos < data->build[data->next_skyline_cand].left) {
        if (new_current_skyline == -1) {
            printf(" %d %d", data->pos, 0);
            data->current_skyline = data->next_skyline_cand;
            ++data->next_skyline_cand;
            printf(" %d %d", data->build[data->current_skyline].left, data->build[data->current_skyline].height);
            data->pos = data->build[data->current_skyline].left + 1;
        } else {
            if (data->build[new_current_skyline].height != data->build[data->current_skyline].height) {
                printf(" %d %d", data->pos, data->build[new_current_skyline].height);
            }
            data->current_skyline = new_current_skyline;
        }
    } else {
        if (new_current_skyline == -1) {
            new_current_skyline = data->next_skyline_cand;
            if (data->build[new_current_skyline].height != data->build[data->current_skyline].height) {
                printf(" %d %d", data->build[new_current_skyline].left, data->build[new_current_skyline].height);
            }
            data->current_skyline = data->next_skyline_cand;
            ++data->next_skyline_cand;
            printf(" %d %d", data->build[data->current_skyline].left, data->build[data->current_skyline].height);
            data->pos = data->build[data->current_skyline].left + 1;
        } else {
            if (data->build[new_current_skyline].height < data->build[data->next_skyline_cand].height) {
                new_current_skyline = data->next_skyline_cand;
                ++data->next_skyline_cand;
            }
            if (data->build[new_current_skyline].height != data->build[data->current_skyline].height) {
                printf(" %d %d", data->build[new_current_skyline].left, data->build[new_current_skyline].height);
            }
            data->current_skyline = new_current_skyline;
            data->pos = data->build[new_current_skyline].left + 1;
        }
    }
}

void handle_skyline_end(struct Data *data)
{
    int new_current_skyline = -1;

    new_current_skyline = find_next_skyline_in_research(data);

    if (new_current_skyline != -1) {
        if (data->build[new_current_skyline].height != data->build[data->current_skyline].height) {
            printf(" %d %d", data->build[new_current_skyline].left, data->build[new_current_skyline].height);
        }
        data->current_skyline = new_current_skyline;
    }

    return;
}

int main(int argc, char *argv[])
{
    struct Data data;

    data.build_count = 0;
    while (scanf("%d %d %d", &data.build[data.build_count].left, &data.build[data.build_count].height, &data.build[data.build_count].right) == 3) {
        if (data.build[data.build_count].left < data.build[data.build_count].right) {
            ++data.build_count;
        }
    }

    data.current_skyline = 0;
    data.next_skyline_cand = 1;
    data.research_start = 0;
    data.pos = data.build[0].left + 1;
    printf("%d %d", data.build[data.current_skyline].left, data.build[data.current_skyline].height);

    while (data.next_skyline_cand < data.build_count) {
        if (data.build[data.current_skyline].right < data.build[data.next_skyline_cand].left) {
            data.pos = data.build[data.current_skyline].right;
            handle_skyline_end_with_next(&data);
            continue;
        }

        if (data.build[data.next_skyline_cand].height <= data.build[data.current_skyline].height) {
            ++data.next_skyline_cand;
            continue;
        }

        /* overwrite current skyline by new building. */
        data.current_skyline = data.next_skyline_cand;
        ++data.next_skyline_cand;
        printf(" %d %d", data.build[data.current_skyline].left, data.build[data.current_skyline].height);
        data.pos = data.build[data.current_skyline].left + 1;
    }

    /* no new build available, we need to finish the remain building. */
    while (data.research_start < data.build_count) {
        data.pos = data.build[data.current_skyline].right;
        handle_skyline_end(&data);
    }

    printf(" %d %d\n", data.build[data.current_skyline].right, 0);

    return 0;
}
