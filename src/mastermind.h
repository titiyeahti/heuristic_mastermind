/*
 * =====================================================================================
 *
 *       Filename:  mastermind.h
 *
 *    Description:  header file for basic functions to implement mastermind
 *
 *        Version:  1.0
 *        Created:  04/12/2019 16:28:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  MPRI
 *
 * =====================================================================================
 */

#ifndef  mastermind_INC
#define  mastermind_INC


#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;
typedef unsigned char uchar;

struct instance {
				uint n,k;
				uchar* soluce;
};				/* ----------  end of struct instance  ---------- */

typedef struct instance Instance;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  new_instance
 *  Description:  
 * =====================================================================================
 */
Instance new_instance(uint n, uint k);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  free_instance
 *  Description:  free the memory used by the instance a.
 * =====================================================================================
 */
void free_instance (Instance a);


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  is_correct
 *  Description:  returns 1 if the proposal p is coherent with the instance a
 * =====================================================================================
 */
int is_correct (Instance a, uchar* p);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  score
 *  Description:  return the number of good bits in the proposal p wrt the instance a,
 *  							the proposal must be valid and coherent with a.
 * =====================================================================================
 */
uint score (Instance a, uchar* p);


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  print_instance
 *  Description:  prints the instance a.
 * =====================================================================================
 */
void print_instance (Instance a);

#endif   /* ----- #ifndef mastermind_INC  ----- */
