#include <stdio.h>
#include <string.h>

enum {
    MAX_DIM = 10,
    MAX_BOX = 30,
};

struct Box {
    int id;
    int dim[MAX_DIM];

    int next;
    int size;
};

int compare_dim(void *x, void *y)
{
    int *a = (int *) x;
    int *b = (int *) y;

    return *b - *a;
}

void sort_dim(struct Box *box)
{
    qsort(box->dim, MAX_DIM, sizeof(box->dim[0]), compare_dim);
}

int compare_size(void *x, void *y)
{
    int i;
    struct Box *a = (struct Box *) x;
    struct Box *b = (struct Box *) y;

    for (i = 0; i < MAX_DIM; ++i) {
        if (a->dim[i] != b->dim[i]) {
            return a->dim[i] - b->dim[i];
        }
    }

    return 0;
}

int is_stackable(struct Box *x, struct Box *y)
{
    int i;

    for (i = 0; i < MAX_DIM; ++i) {
        if (x->dim[i] > y->dim[i]) {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char *argv[])
{
    int dim;
    int box;
    struct Box data[MAX_BOX];

    while (scanf("%d %d", &box, &dim) == 2) {
        int i;
        int j;

        memset(data, 0, sizeof(data));
        for (i = 0; i < box; ++i) {
            data[i].id = i;
            for (j = 0; j < dim; ++j) {
                scanf("%d", &data[i].dim[j]);
            }
            sort_dim(&data[i]);
        }

        qsort(&data, box, sizeof(data[0]), compare_size);

        for (i = 0; i < box; ++i) {
            ++data[i].id;
            data[i].next = data[i].id;
            data[i].size = 0;
        }

        for (i = 1; i < box; ++i) {
            for (j = i - 1; j >= 0; --j) {
                if (is_stackable(&data[j], &data[i])) {
                    if (data[j].size >= data[i].size) {
                        data[i].size = data[j].size + 1;
                        data[i].next = data[j].id;
                    }
                }
            }
        }

        for (i = 0; i < box; ++i) {
            printf("id = %d, next = %d, size = %d, ", data[i].id, data[i].next, data[i].size);
            for (j = 0; j < dim; ++j) {
                printf("%d ", data[i].dim[j]);
            }
            printf("\n");
        }

    }

    return 0;
}
