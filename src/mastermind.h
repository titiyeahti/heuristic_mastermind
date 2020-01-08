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
#include <string.h>

typedef unsigned int uint;

struct instance {
				uint n,k;
				uint* soluce;
};				/* ----------  end of struct instance  ---------- */

typedef struct instance Instance;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  new_instance
 *  Description:  
 * =====================================================================================
 */
Instance new_instance(uint n, uint k);

uint random(uint k);

uint* rand_prop (uint n, uint k);

uint* copy_prop (uint* prop, uint n);

void copy_to_prop(uint* src, uint* target, uint n);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  rand_instance
 *  Description:  return a randomized instance given the size (n) and the number of 
 *  							colors (k).
 * =====================================================================================
 */
Instance rand_instance (uint n, uint k);

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
int is_correct (Instance a, uint* p);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  score
 *  Description:  return the number of good bits in the proposal p wrt the instance a,
 *  							the proposal must be valid and coherent with a.
 * =====================================================================================
 */
uint score(Instance a, uint* p);

void print_prop(uint* p, uint n);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  print_instance
 *  Description:  prints the instance a.
 * =====================================================================================
 */
void print_instance (Instance a);

#endif   /* ----- #ifndef mastermind_INC  ----- */
