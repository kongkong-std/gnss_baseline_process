#ifndef RRE_IMPL_H_
#define RRE_IMPL_H_

// header file
#include "main.h"

// function prototype
/*
 * RRE process
 *     1. vector sequential
 *     2. count of vector element in sequence
 *     3. size of vector element in sequence
 *     4. extrapolation result
 */
void RREProcess(double **, int, int, double *);

/*
 * unconstraint least-square equation
 *     1. second order difference
 *     2. rhs
 *     3. solution of gamma
 */
void RREUnconstraintLSE(double **, double **, int, int, double *);

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
* gaussian elimination to solve linear system
*     1. covariant matrix
*     2. rhs vector
*     3. solution
*     4. size
*/
void GaussElimination( double * *, double *, double *, int );

#endif