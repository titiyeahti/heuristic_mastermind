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

 /* simulated annealing */

Result sim_annealing(Instance a, 
								uint* (*neighbourg) (uint, uint, uint, uint*),
								float (*temperature) (float, float),
								float (*proba) (uint, uint, float),
								uint max_steps,
								float t0,
								float param);

#endif   /* ----- #ifndef metaheuristic_INC  ----- */

