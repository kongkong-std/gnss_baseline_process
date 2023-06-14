#ifndef MAIN_H_
#define MAIN_H_

// header file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "linked_list.h"

// function prototype
/*
 * source data file process
 *     1. source data file path
 *     2. base station position, size of base station array is 3
 *     3. add to linked list
 */
void SourceDataProcess(char *, double *, List_LinkedList *);

/*
 * baseline process with rre
 *     1. source data linked list
 *     2. base station position
 *     3. solution and size is 3
 */
void BaseLineRREImpl(const List_LinkedList *, const double *, double *);

#endif