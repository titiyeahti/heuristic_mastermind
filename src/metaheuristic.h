/*
 * =====================================================================================
 *
 *       Filename:  metaheuristic.h
 *
 *    Description:  Some metaheuristics applied to the mastermind game
 *
 *        Version:  1.0
 *        Created:  11/12/2019 21:21:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  MPRI
 *
 * =====================================================================================
 */

#ifndef  metaheuristic_INC
#define  metaheuristic_INC

#include <string.h>
#include "mastermind.h"


struct result {
				uint i, score;
				uint* value;
};				/* ----------  end of struct result  ---------- */

typedef struct result Result;

void print_result(Result res, uint n);

Result one_plus_one(Instance a, float p);

Result randomized_local_search(Instance a);


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  genetic_algo
 *  Description:  a should be an instance of mastermind, lamba is the number of newborns
 *  							at each generation, mu is the size of the generations,
 *  							mutation(uint* dest, uint* src, uint k, uint n),
 *  							crossover(uint* son, uint* father, uint* mother, uint n).
 *  							TODO
 * =====================================================================================
 */

/* the new generation is calculated directly in the table then all the new scores
 * are computed and finally the table is sorted*/
Result genetic_algo(Instance a, uint lambda, uint mu,
								void (* mutation)(uint*, uint*, uint, uint),
								void (* crossover)(uint*, uint*, uint*, uint))
/* simulated annealing */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  sim_annealing
 *  Description:  uint * neighbourg(uint n, uint k, uint score, uint* prop) 
 *  								computes a good enougth neighbourg of prop
 *  							
 *  							float temperature(t_k, param)
 *  								computes the temperature from the former one and a param
 *  							
 *  							float proba(uint s, uint ns, float t)
 *  								computes a proba from the score, the candidate, and the temperature
 *
 *  							This function applies the simulated annealing method to the 
 *  							mastermind instance a with the choosen functions and parameters.
 *
 *  							It returns the number of steps spent, the best solution met and its 
 *  							score.
 * =====================================================================================
 */

Result sim_annealing(Instance a, 
								uint* (*neighbourg) (uint, uint, uint, uint*),
/* 								float (*temperature) (float, float),
 */
								float (*proba) (uint, uint, float),
								uint max_steps,
								float t0,
								float param);

#endif   /* ----- #ifndef metaheuristic_INC  ----- */

