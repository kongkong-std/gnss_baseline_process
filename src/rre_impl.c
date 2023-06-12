#include "../include/rre_impl.h"

void rre_implementation(double **src_data, int size_row, int size_column, double **rre_data, int rre_index)
{
    int rre_l = size_row - 1; // rre window size in implementation
    double *rre_alpha = NULL; // parameter alpha

    rre_alpha = (double *)malloc(rre_l * sizeof(double));

    double **rre_mat = NULL; // src_data[k + 1][] - src_data[k][]
    rre_mat = (double **)malloc(rre_l * sizeof(double *));
    for (int index = 0; index < rre_l; ++index)
    {
        *(rre_mat + index) = (double *)malloc(size_column * sizeof(double));
    }

    for (int index_i = 0; index_i < rre_l; ++index_i)
    {
        for (int index_j = 0; index_j < size_column; ++index_j)
        {
            rre_mat[index_i][index_j] = src_data[index_i + 1][index_j] - src_data[index_i][index_j];
        }
    }

#if 0 // file io check
    FILE *fp = NULL;
    if ((fp = fopen("succesive_error_test.txt", "a+b")) == NULL)
    {
        fprintf(stderr, "Cannot open file!\n");
        exit(EXIT_FAILURE);
    }

    for (int index_i = 0; index_i < rre_l; ++index_i)
    {
        for (int index_j = 0; index_j < size_column; ++index_j)
        {
            fprintf(fp, "%.4lf\t", rre_mat[index_i][index_j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
#endif

    double **trans_rre_mat = NULL; // size trans_rre_mat = size_column x rre_l
    trans_rre_mat = (double **)malloc(size_column * sizeof(double *));
    for (int index = 0; index < size_column; ++index)
    {
        *(trans_rre_mat + index) = (double *)malloc(rre_l * sizeof(double));
    }

    // trans_rre_mat[ i ][ j ] = rre_mat[ j ][ i ]
    for (int index_i = 0; index_i < size_column; ++index_i)
    {
        for (int index_j = 0; index_j < rre_l; ++index_j)
        {
            trans_rre_mat[index_i][index_j] = rre_mat[index_j][index_i];
        }
    }

    rre_lse_solver(trans_rre_mat, size_column, rre_l, rre_alpha);    // computing parameter alpha

    // free memory
    for (int index = 0; index < size_column; ++index)
    {
        free(*(trans_rre_mat + index));
    }
    free(trans_rre_mat);
    for (int index = 0; index < rre_l; ++index)
    {
        free(*(rre_mat + index));
    }
    free(rre_mat);
    free(rre_alpha);
}

void rre_lse_solver(double **mat, int size_row, int size_column, double *sol)
{
    double **mat_q = NULL, **mat_r = NULL; // qr decomposition

    // mat = mat_q * mat_r
    /*
     * size mat_q = size_row x size_column, unitary matrix
     * size mat_r = size_column x size_column, uptriangular matrix
     */
    mat_q = (double **)malloc(size_row * sizeof(double *));
    for (int index = 0; index < size_row; ++index)
    {
        *(mat_q + index) = (double *)malloc(size_column * sizeof(double));
    }

    // initialize mat_q = 0
    for (int index_i = 0; index_i < size_row; ++index_i)
    {
        for (int index_j = 0; index_j < size_column; ++index_j)
        {
            mat_q[index_i][index_j] = 0.;
        }
    }

    mat_r = (double **)malloc(size_column * sizeof(double *));
    for (int index = 0; index < size_column; ++index)
    {
        *(mat_r + index) = (double *)malloc(size_column * sizeof(double));
    }

    // initialize mat_r = 0
    for (int index_i = 0; index_i < size_column; ++index_i)
    {
        for (int index_j = 0; index_j < size_column; ++index_j)
        {
            mat_r[index_i][index_j] = 0.;
        }
    }

    qr_deco(mat, size_row, size_column, mat_q, mat_r);

    // free memory
    for (int index = 0; index < size_column; ++index)
    {
        free(*(mat_r + index));
    }
    free(mat_r);
    for (int index = 0; index < size_row; ++index)
    {
        free(*(mat_q + index));
    }
    free(mat_q);
}

void qr_deco(double **mat, int size_row, int size_column, double **mat_q, double **mat_r)
{
    // modified gram-schmidt orthonormalization
}
