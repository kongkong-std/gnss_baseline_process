#include "../include/main.h"

int main(int argc, char **argv)
{
    double pos_base[3] = {-2843601.5546, 4805439.1946, 3073086.1153};
    double **pos_rover = NULL;

    char *file_pos = argv[1];
    FILE *fp_pos = NULL;

    if ((fp_pos = fopen(file_pos, "rb")) == NULL)
    {
        fprintf(stderr, "Cannot open file!\n");
        exit(EXIT_FAILURE);
    }

    int cnt = 0;
    while (!feof(fp_pos))
    {
        char buffer[1024];
        fgets(buffer, 1024, fp_pos);
        ++cnt;
    }
    printf("cnt = %d\n", cnt);
    printf("base station position:\n");
    for (int index = 0; index < 3; ++index)
    {
        printf("%.4lf\n", pos_base[index]);
    }

    pos_rover = (double **)malloc(cnt * sizeof(double *));
    for (int index = 0; index < cnt; ++index)
    {
        *(pos_rover + index) = (double *)malloc(9 * sizeof(double));
    }

    fclose(fp_pos);

    if ((fp_pos = fopen(file_pos, "rb")) == NULL)
    {
        fprintf(stderr, "Cannot open file!\n");
        exit(EXIT_FAILURE);
    }

    for (int index = 0; index < cnt; ++index)
    {
        for (int index_i = 0; index_i < 9; ++index_i)
        {
            fscanf(fp_pos, "%lf", *(pos_rover + index) + index_i);
        }
    }

    fclose(fp_pos);

#if 0
    for (int index_i = 0; index_i < cnt - 1; ++index_i)
    {
        for (int index_j = 0; index_j < 9; ++index_j)
        {
            printf("%.4lf\t", pos_rover[index_i][index_j]);
        }
        putchar('\n');
    }
#endif

    // updating baseline data
    for (int index_i = 0; index_i < cnt; ++index_i)
    {
        for (int index_j = 0; index_j < 3; ++index_j)
        {
            pos_rover[index_i][index_j] -= pos_base[index_j];
        }
    }

#if 0 // print baseline
    for (int index_i = 0; index_i < cnt; ++index_i)
    {
        for (int index_j = 0; index_j < 3; ++index_j)
        {
            printf("%.4lf\t", pos_rover[index_i][index_j]);
        }
        putchar('\n');
    }
#endif

    BaseLineProcess(pos_rover, cnt - 1, 3);

    // free memory
    for (int index = 0; index < cnt; ++index)
    {
        free(*(pos_rover + index));
    }
    free(pos_rover);

    return 0;
}