#include "../include/linsys_solver_direct.h"

void GaussElimination(double **mat, double *rhs, double *sol, int n)
{
#if 0 // input check
for( int index_i = 0; index_i < n; ++index_i )
{
    for( int index_j = 0; index_j < n; ++index_j )
    {
        printf( "%.4lf\t", mat[index_i][index_j] );
    }
    printf( "%.4lf", rhs[index_i] );
    putchar('\n');
}
#endif

    // note
    /*
     * size mat = n x n
     * size rhs = n x 1
     * size sol = n x 1
     *
     * gaussian elimination
     *     1. maximum element in every column, norm of element
     *     2. row transformation
     */
    double value_tmp = 0.;
    for (int index_j = 0; index_j < n; ++index_j)
    {
        // get maximum element of index_j column
        for (int index_i = index_j + 1; index_i < n; ++index_i)
        {
            if (fabs(mat[index_i][index_j]) > fabs(mat[index_j][index_j]))
            {
                // swap index_i row and index_j row
                /*
                 * mat[ index_i ][ index_k ] <-> mat[ index_j ][ index_k ],
                 *     index_k = index_j, ..., n
                 */
                for (int index_k = index_j; index_k < n; ++index_k)
                {
                    value_tmp = mat[index_i][index_k];
                    mat[index_i][index_k] = mat[index_j][index_k];
                    mat[index_j][index_k] = value_tmp;
                }

                /*
                 * rhs[ index_i ] <-> rhs[ index_j ]
                 */
                value_tmp = rhs[index_i];
                rhs[index_i] = rhs[index_j];
                rhs[index_j] = value_tmp;
            }
        }

        // elimination of column
        for (int index_i = index_j + 1; index_i < n; ++index_i)
        {
            /*
             * mat( index_i, index_j : n ) -= mat[index_i][index_j]/mat[index_j][index_j] mat( index_j, index_j : n )
             */
            value_tmp = -mat[index_i][index_j] / mat[index_j][index_j];
            for (int index_k = index_j; index_k < n; ++index_k)
            {
                mat[index_i][index_k] += value_tmp * mat[index_j][index_k];
            }

            /*
             * rhs[ index_i ] -= mat[index_i][index_j]/mat[index_j][index_j] rhs[index_j]
             */
            rhs[index_i] += value_tmp * rhs[index_j];
        }
    }
#if 0 // check linear system
    puts(">>>> gaussian elimination >>>>");
    for (int index_i = 0; index_i < n; ++index_i)
    {
        for (int index_j = 0; index_j < n; ++index_j)
        {
            printf("%.4lf\t", mat[index_i][index_j]);
        }
        printf("%.4lf", rhs[index_i]);
        putchar('\n');
    }
#endif

    // solving up-triangular linear system
    /*
     * a_kk x_k + a_k,k+1 x_k+1 + ... + a_kn x_n = b_k
     * a_kk x_k = b_k - \sum _ {i = k + 1} ^ n a_ki x_i, k < n
     */
    for (int index = n - 1; index >= 0; --index)
    {
        double tmp_sum = 0.;
        for (int index_k = n - 1; index_k > index; --index_k)
        {
            tmp_sum += mat[index][index_k] * sol[index_k];
        }
        sol[index] = (rhs[index] - tmp_sum) / mat[index][index];
    }
#if 0 // check solution
    puts("==== solution ====");
    for (int index = 0; index < n; ++index)
    {
        printf("%.4lf\n", sol[index]);
    }
#endif
}

void MatTranspose(double **mat, double **trans_mat, int size_row, int size_column)
{
    // trans_mat( i, j ) = mat( j, i )
    /*
     * size mat = size_row x size_column
     * size trans_mat = size_column x size_row
     */
    for (int index_i = 0; index_i < size_column; ++index_i)
    {
        for (int index_j = 0; index_j < size_row; ++index_j)
        {
            trans_mat[index_i][index_j] = mat[index_j][index_i];
        }
    }
}

void MatMatProduct(double **mat_1, double **mat_2, double **mat, int size_row, int size_column, int size_column_2)
{
    // mat = mat_1 x mat_2
    /*
     * size mat_1 = size_row x size_column
     * size mat_2 = size_column x size_column_2
     * size_mat = size_row x size_column_2
     *
     * mat( i, j ) = \sum_{ k = 1 } ^ size_column mat_1( i, k ) * mat_2( k, j )
     */

    for (int index_i = 0; index_i < size_row; ++index_i)
    {
        for (int index_j = 0; index_j < size_column_2; ++index_j)
        {
            double tmp = 0.;
            for (int index_k = 0; index_k < size_column; ++index_k)
            {
                tmp += mat_1[index_i][index_k] * mat_2[index_k][index_j];
            }
            mat[index_i][index_j] = tmp;
        }
    }
}

void MatVecProduct(double **mat, double *vec, double *sol, int m, int n)
{
    // note
    /*
     * size mat = m x n
     * size vec = n x 1
     * size sol = m x 1
     *
     * sol = mat * vec
     * sol(i) = \sum k = 1 ^ n mat(i, k) vec(k)
     */
    for (int index_i = 0; index_i < m; ++index_i)
    {
        double tmp_sum = 0.;
        for (int index_k = 0; index_k < n; ++index_k)
        {
            tmp_sum += mat[index_i][index_k] * vec[index_k];
        }
        sol[index_i] = tmp_sum;
    }
}
