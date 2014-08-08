#include <stdio.h>
#include <stdlib.h>
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

int compare_dim(const void *x, const void *y)
{
    const int *a = (const int *) x;
    const int *b = (const int *) y;

    return *b - *a;
}

void sort_dim(struct Box *box)
{
    qsort(box->dim, MAX_DIM, sizeof(box->dim[0]), compare_dim);
}

int compare_size(const void *x, const void *y)
{
    int i;
    const struct Box *a = (const struct Box *) x;
    const struct Box *b = (const struct Box *) y;

    for (i = 0; i < MAX_DIM; ++i) {
        if (a->dim[i] != b->dim[i]) {
            return a->dim[i] - b->dim[i];
        }
    }

    return 0;
}

int compare_id(const void *x, const void *y)
{
    const struct Box *a = (const struct Box *) x;
    const struct Box *b = (const struct Box *) y;

    return a->id - b->id;
}

int is_stackable(struct Box *x, struct Box *y, int dim)
{
    int i;

    for (i = 0; i < dim; ++i) {
        if (x->dim[i] >= y->dim[i]) {
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
        int sol_size;
        int sol_base;

        memset(data, 0, sizeof(data));
        for (i = 0; i < box; ++i) {
            data[i].id = i;
            for (j = 0; j < dim; ++j) {
                scanf("%d", &data[i].dim[j]);
            }
            /* Sort by dimension */
            sort_dim(&data[i]);
        }

        /* Topological sort */
        qsort(&data, box, sizeof(data[0]), compare_size);

        for (i = 0; i < box; ++i) {
            data[i].next = data[i].id;
            data[i].size = 1;
        }

        sol_base = 1;
        sol_size = 1;

        /*
         * The DP formula:
         *
         * Stack[i, j] = maximum stack from i to j
         *
         * Stack[i, j] = max | 1 + Stack[i + 1, j] if is_stackable(i, head of Stack[i + 1, j])
         *                   | Stack[i + 1, j] otherwise
         */
        for (i = box - 2; i >= 0; --i) {
            for (j = i + 1; j < box; ++j) {
                if (is_stackable(&data[i], &data[j], dim)) {
                    if (data[i].size <= data[j].size) {
                        data[i].size = data[j].size + 1;
                        data[i].next = data[j].id;
                    }
                }

                if (data[i].size > sol_size) {
                    sol_size = data[i].size;
                    sol_base = data[i].id;
                }
            }
        }

        qsort(&data, box, sizeof(data[0]), compare_id);

        printf("%d\n", sol_size);

        while (data[sol_base].next != sol_base) {
            printf("%d ", sol_base + 1);
            sol_base = data[sol_base].next;
        }
        printf("%d\n", sol_base + 1);

#if 0
        printf("sol_size = %d, sol_base = %d\n", sol_size, sol_base);
        for (i = 0; i < box; ++i) {
            printf("id = %d, next = %d, size = %d, ", data[i].id, data[i].next, data[i].size);
            for (j = 0; j < dim; ++j) {
                printf("%d ", data[i].dim[j]);
            }
            printf("\n");
        }
#endif
    }
    return 0;
}
