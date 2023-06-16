#ifndef LINSYS_SOLVER_DIRECT_H_
#define LINSYS_SOLVER_DIRECT_H_

// header file
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// function prototype
/*
 * gaussian elimination to solve linear system
 *     1. covariant matrix
 *     2. rhs vector
 *     3. solution
 *     4. size
 */
void GaussElimination(double **, double *, double *, int);

/*
 * transpose of matrix
 *     1. mat
 *     2. transpose of mat
 *     3. size
 */
void MatTranspose(double **, double **, int, int);

/*
 * matrix by matrix product
 *     1. mat_1
 *     2. mat_2
 *     3. mat = mat_1 x mat_2
 *     4. size
 */
void MatMatProduct(double **, double **, double **, int, int, int);

/*
 * matrix by vector product
 *     1. mat
 *     2. vec_1
 *     3. vec = mat * vec_1
 *     4. size
 */
void MatVecProduct(double **, double *, double *, int, int);

#endif