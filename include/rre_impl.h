#ifndef RRE_IMPL_H_
#define RRE_IMPL_H_

// header file
#include "main.h"
#include "linsys_solver_direct.h"

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
 * updating rre solution
 */
void RREUpdateSolution(double **, double **, double *, double *, int, int);

#endif