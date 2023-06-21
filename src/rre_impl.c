/**
 * @file rre_impl.c
 * @author Zikang Qin
 * @brief reduced rank extrapolation implementation functions
 * @version 0.1
 * @date 2023-06-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../include/rre_impl.h"

/**
 * @callgraph
 * @brief baseline process RRE main implementation
 * 
 * @param [in] pList linked list
 * @param [in] base_station coordinate of base station
 * @param [in,out] solution solution to rre
 */
void BaseLineRREImpl(const List_LinkedList *pList, const double *base_station, double *solution)
{
    int base_line_size = pList->size;
    double **base_line_data = NULL; // size base_line_data = base_line_size x size

    base_line_data = (double **)malloc(base_line_size * sizeof(double *));
    for (int index = 0; index < base_line_size; ++index)
    {
        *(base_line_data + index) = (double *)malloc(3 * sizeof(double));
    }

    Node_LinkedList *pTmpNode = pList->head;
    int cnt_tmp = 0;
    while (pTmpNode != NULL && cnt_tmp < base_line_size)
    {
        base_line_data[cnt_tmp][0] = pTmpNode->item.x - base_station[0];
        base_line_data[cnt_tmp][1] = pTmpNode->item.y - base_station[1];
        base_line_data[cnt_tmp][2] = pTmpNode->item.z - base_station[2];
        pTmpNode = pTmpNode->next;
        ++cnt_tmp;
    }

#if 0 // check base line data
    printf("baseline data:\n");
    printf("cnt_tmp = %d, base_line_size = %d\n", cnt_tmp, base_line_size);
    for (int index_i = 0; index_i < cnt_tmp; ++index_i)
    {
        for (int index_j = 0; index_j < 3; ++index_j)
        {
            printf("%.4lf\t", base_line_data[index_i][index_j]);
        }
        putchar('\n');
    }
#endif

    RREProcess(base_line_data, base_line_size, 3, solution);

    // free memory
    for (int index = 0; index < base_line_size; ++index)
    {
        free(*(base_line_data + index));
    }
    free(base_line_data);
}

/**
 * @callgraph
 * @brief rre process
 * 
 * @param [in] vec_seq original vector sequence
 * @param [in] size_row row size of vector sequence 
 * @param [in] size_column column size of vector sequence
 * @param [in,out] trans_vec_seq solution to rre 
 */
void RREProcess(double **vec_seq, int size_row, int size_column, double *trans_vec_seq)
{
    double **diff_vec_seq = NULL; // size = size_column x ( size_row - 1 )
    diff_vec_seq = (double **)malloc(size_column * sizeof(double *));
    for (int index = 0; index < size_column; ++index)
    {
        *(diff_vec_seq + index) = (double *)malloc((size_row - 1) * sizeof(double));
    }

    // diff_vec_seq = [ dv_1, dv_2, ..., dv_n ]
    /*
     * dv_k = v_{ k + 1 } - v_k
     * vec_seq = [ v_1, v_2, ..., v_n, v_{n+1} ]'
     */
    for (int index_i = 0; index_i < size_column; ++index_i)
    {
        for (int index_j = 0; index_j < size_row - 1; ++index_j)
        {
            diff_vec_seq[index_i][index_j] = vec_seq[index_j + 1][index_i] - vec_seq[index_j][index_i];
        }
    }
#if 0 // check diff_vec_seq
for( int index = 0; index < size_column; ++index )
{
    printf( "%.4lf\n", diff_vec_seq[ index ][ size_row - 2 ]   );
}
puts( "==== ---- ====" );
for( int index = 0; index < size_column; ++index )
{
    printf( "%.4lf\n", diff_vec_seq[ index ][ size_row - 1 ]   );
}
#endif

    double **double_diff_vec_seq = NULL; // size = size_column x ( size_row - 2 )
    double_diff_vec_seq = (double **)malloc(size_column * sizeof(double *));
    for (int index = 0; index < size_column; ++index)
    {
        *(double_diff_vec_seq + index) = (double *)malloc((size_row - 2) * sizeof(double));
    }

    // double_diff_vec_seq = [ ddv_1, ddv_2, ..., ddv_{n-1} ]
    /*
     * ddv_k = dv_{ k + 1 } - dv_k
     */
    for (int index_i = 0; index_i < size_column; ++index_i)
    {
        for (int index_j = 0; index_j < size_row - 2; ++index_j)
        {
            double_diff_vec_seq[index_i][index_j] = diff_vec_seq[index_i][index_j + 1] - diff_vec_seq[index_i][index_j];
        }
    }

    double *rre_gamma = NULL; // size = size_row - 2 x 1
    rre_gamma = (double *)malloc((size_row - 2) * sizeof(double));

    // unconstraint least-square equation
    RREUnconstraintLSE(double_diff_vec_seq, diff_vec_seq, size_column, size_row - 2, rre_gamma);

    // computing result of rre
    /*
     * trans_vec_seq = vec_seq( size_row, : ) - diff_vec_seq( :, 2 : size_row - 1 ) * rre_gamma
     */
    RREUpdateSolution(vec_seq, diff_vec_seq, rre_gamma, trans_vec_seq, size_row, size_column);

    // free memory
    free(rre_gamma);
    for (int index = 0; index < size_column; ++index)
    {
        free(*(double_diff_vec_seq + index));
    }
    free(double_diff_vec_seq);
    for (int index = 0; index < size_column; ++index)
    {
        free(*(diff_vec_seq + index));
    }
    free(diff_vec_seq);
}

/**
 * @callgraph
 * @brief fusing valid data with linear combination coefficients
 * to update solution
 * 
 * @param [in] mat_1 original vector sequence
 * @param [in] mat_2 difference of original vector sequence
 * @param [in] gamma linear combination coefficients
 * @param [in,out] solution solution to rre
 * @param [in] m row size of vector sequence
 * @param [in] n column size of vector sequence
 */
void RREUpdateSolution(double **mat_1, double **mat_2, double *gamma, double *solution, int m, int n)
{
    // note
    /*
     * size mat_1 = m x n
     * size mat_2 = n x m - 1
     * size gamma = m - 2
     * size solution = n x 1
     *
     * solution = mat_1( m, : )' - mat_2( :, 2 : m - 1 ) gamma
     */
    for (int index_i = 0; index_i < n; ++index_i)
    {
        // solution = mat_1( m, : )' - mat_2( :, 2 : m - 1 ) gamma
        /*
         * solution(i) = mat_1( m, i ) - \sum _ { k = 1 : m - 2 } mat_2( i, k + 1 ) gamma(k)
         */
        double sum_tmp = 0.;
        for (int index_j = 0; index_j < m - 1; ++index_j)
        {
            sum_tmp += mat_2[index_i][index_j + 1] * gamma[index_j];
        }
        solution[index_i] = mat_1[m - 1][index_i] - sum_tmp;
    }
}

/**
 * @callgraph
 * @brief assemble unconstraint least-squares equation
 * 
 * @param [in] delta_mat_u difference of mat_u
 * @param [in] mat_u difference of original vector sequence
 * @param [in] size_row row size of delta_mat_u
 * @param [in] size_column column size of delta_mat_u
 * @param [in,out] gamma linear combination coefficients of rre
 */
void RREUnconstraintLSE(double **delta_mat_u, double **mat_u, int size_row, int size_column, double *gamma)
{
    // note
    /*
     * size delta_mat_u = size_row x size_column
     * size mat_u = size_row x ( size_column + 1 )
     * size gamma = size_column x 1
     * gamma = delta_mat_u' INV( delta_mat_u delta_mat_u' ) mat_u( :, size_column + 1 )
     */

    double **mat_tmp = NULL; // size = size_row x size_row
    mat_tmp = (double **)malloc(size_row * sizeof(double *));
    for (int index = 0; index < size_row; ++index)
    {
        *(mat_tmp + index) = (double *)malloc(size_row * sizeof(double));
    }

    double **trans_delta_mat_u = NULL; // transpose, size = size_column x size_row
    trans_delta_mat_u = (double **)malloc(size_column * sizeof(double *));
    for (int index = 0; index < size_column; ++index)
    {
        *(trans_delta_mat_u + index) = (double *)malloc(size_row * sizeof(double));
    }

    MatTranspose(delta_mat_u, trans_delta_mat_u, size_row, size_column);
    MatMatProduct(delta_mat_u, trans_delta_mat_u, mat_tmp, size_row, size_column, size_row);

#if 0 // check mat_tmp
    for (int index_i = 0; index_i < size_row; ++index_i)
    {
        for (int index_j = 0; index_j < size_row; ++index_j)
        {
            printf("%.6lf\t", mat_tmp[index_i][index_j]);
        }
        putchar('\n');
    }
#endif

    double *solution_tmp = NULL; // size = size_row x 1
    double *rhs_tmp = NULL;      // size = size_row x 1
    solution_tmp = (double *)malloc(size_row * sizeof(double));
    rhs_tmp = (double *)malloc(size_row * sizeof(double));

    // rhs_tmp = mat_u( :, size_column + 1 )
    for (int index = 0; index < size_row; ++index)
    {
        rhs_tmp[index] = mat_u[index][size_column];
    }

    // mat_tmp solution_tmp = rhs_tmp
    GaussElimination(mat_tmp, rhs_tmp, solution_tmp, size_row);

    // computing gamma
    /*
     * gamma = trans_delta_mat_u * solution_tmp
     */
    MatVecProduct(trans_delta_mat_u, solution_tmp, gamma, size_column, size_row);

    // free memory
    free(solution_tmp);
    for (int index = 0; index < size_column; ++index)
    {
        free(*(trans_delta_mat_u + index));
    }
    free(trans_delta_mat_u);
    for (int index = 0; index < size_row; ++index)
    {
        free(*(mat_tmp + index));
    }
    free(mat_tmp);
}
