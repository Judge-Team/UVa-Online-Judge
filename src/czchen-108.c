#include <limits.h>
#include <stdio.h>
#include <string.h>

enum {
    MAX_DIM = 100,
};

int max(int x, int y)
{
    return x > y ? x : y;
}

int main(int argc, char *argv[])
{
    int dim;

    while (scanf("%d", &dim) == 1) {
        int matrix[MAX_DIM+1][MAX_DIM];
        int i;
        int j;
        int k;
        int result;

        memset(matrix, 0, sizeof(matrix));

        for (i = 1; i < dim + 1; ++i) {
            for (j = 0; j < dim; ++j) {
                scanf("%d", &matrix[i][j]);
            }
        }

        /* Initial max to first element of matrix. */
        result = matrix[1][0];

#if DEBUG
        printf("original matrix:\n");
        for (i = 0; i < dim + 1; ++i) {
            for (j = 0; j < dim + 1; ++j) {
                printf("%d\t", matrix[i][j]);
            }
            printf("\n");
        }
#endif

        /*
         * convert to column accumulation matrix.
         */
        for (i = 1; i < dim + 1; ++i) {
            for (j = 0; j < dim; ++j) {
                 matrix[i][j] += matrix[i-1][j];
            }
        }

#if DEBUG
        printf("accumulation matrix:\n");
        for (i = 0; i < dim + 1; ++i) {
            for (j = 0; j < dim + 1; ++j) {
                printf("%d\t", matrix[i][j]);
            }
            printf("\n");
        }
#endif

        /*
         * i, j here is row number.
         */
        for (i = 0; i < dim; ++i) {
            for (j = j + 1; j < dim + 1; ++j) {
                /* Kadane's Algorithm */

                int current_max = matrix[j][0] - matrix[i][0];
                int right_max = current_max;

                for (k = 1; k < dim; ++k) {
                    int item = matrix[j][k] - matrix[i][k];
                    if (right_max < 0) {
                        right_max = item;
                    } else {
                        right_max += item;
                    }
                    current_max = max(current_max, right_max);
#if DEBUG
                    printf("(%d, %d, %d) item = %d\n", i, j, k, matrix[j][k] - matrix[i][k]);
#endif
                }
                result = max(result, current_max);
#if DEBUG
                printf("(%d, %d) = %d\n", i, j, current_max);
#endif
            }
        }

        printf("%d\n", result);
    }

    return 0;
}
