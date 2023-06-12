#include "../include/main.h"

void BaseLineProcess(double **pos_baseline, int size_row, int size_column)
{
    puts("============ baseline processing ============");

    FILE *fp_baseline = NULL;
#if 0 // test successive error
    if ((fp_baseline = fopen("baseline_error.txt", "wb")) == NULL)
    {
        fprintf(stderr, "Cannot open file!\n");
        exit(EXIT_FAILURE);
    }
    for (int index_i = 0; index_i < size_row - 1; ++index_i)
    {
        for (int index_j = 0; index_j < 3; ++index_j)
        {
            fprintf(fp_baseline, "%.4lf\t", pos_baseline[index_i + 1][index_j] - pos_baseline[index_i][index_j]);
        }
        fprintf(fp_baseline, "\n");
    }
    fclose(fp_baseline);
#endif

    // rre
    /*
     * window size: l + 1
     * U _ { l + 1 } = []
     * alpha _ { l + 1 }
     */
    int rre_size = 0;
    printf("input window size of rre: ");
    scanf("%d", &rre_size);

    int rre_cnt_time = size_row / rre_size;
    int rre_cnt_time_res = size_row % rre_size;
    double **pos_baseline_rre = NULL;
    pos_baseline_rre = (double **)malloc((rre_cnt_time + 1) * sizeof(double *));
    for (int index = 0; index < rre_cnt_time + 1; ++index)
    {
        *(pos_baseline_rre + index) = (double *)malloc(3 * sizeof(pos_baseline_rre));
    }

    int index_rre = 0;
    for (index_rre = 0; index_rre < rre_cnt_time; ++index_rre)
    {
        printf("index_rre = %d !!!!\n", index_rre);
        rre_implementation(pos_baseline + index_rre * rre_size, rre_size, size_column, pos_baseline_rre, index_rre);
    }

    printf("====index_rre = %d !!!!\n", index_rre);
    rre_implementation(pos_baseline + index_rre * rre_size, rre_cnt_time_res, size_column, pos_baseline_rre, index_rre);

    // free memory
    for (int index = 0; index < rre_cnt_time + 1; ++index)
    {
        free(*(pos_baseline_rre + index));
    }
    free(pos_baseline_rre);
}