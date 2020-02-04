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


#define MAX(a,b) ((a)>(b) ? (a) : (b))
#define MIN(a,b) ((a)>(b) ? (b) : (a))

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



/*-----------------------------------------------------------------------------
 *  Mutations
 *-----------------------------------------------------------------------------*/

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  binom_mutation
 *  Description:  each case has a proba p to be replaced by a random number in [0,k[ 
 *  							different from the precedent one.
 * =====================================================================================
 */
void binom_mutation(uint* src, uint* dest, float p, uint k, uint n);


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  flip_one_slot
 *  Description:  The target contain gloally the same thing as the src execpting for one
 *  							slot.
 * =====================================================================================
 */
void flip_one_slot(uint* src, uint* dest, uint spot, uint k, uint n);


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  flip_many_slots
 *  Description:  similar to flip_one_slot but for many ones.
 * =====================================================================================
 */
void flip_many_slots(uint* src, uint* dest, uint many, uint k, uint n);



/*-----------------------------------------------------------------------------
 *  Crossovers
 *-----------------------------------------------------------------------------*/


struct prop_score {
				uint* prop;
				uint score;
};				/* ----------  end of struct prop_score  ---------- */

typedef struct prop_score Prop_score;

typedef Prop_score* Prop_score_p;

/* TODO */
void quicksort(Prop_score_p* population, uint size);



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  fixpoint_crossover
 *  Description:  take points from father until spot, then points from mother.
 *  							TODO
 * =====================================================================================
 */
void fixpoint_crossover(uint* son, uint* father, uint* mother, uint spot, uint n);


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  random_crossover
 *  Description:  each point of the son have a proba b to come from the father.
 *  							TODO
 * =====================================================================================
 */
void random_crossover(uint* son, uint* father, uint* mother, float p, uint n);


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
