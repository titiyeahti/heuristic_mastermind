/*
 * =====================================================================================
 *
 *       Filename:  metaheuristic.c
 *
 *    Description:  implementation of metaheuristic.h
 *
 *        Version:  1.0
 *        Created:  11/12/2019 22:51:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  MPRI
 *
 * =====================================================================================
 */

#include "metaheuristic.h"

float uniform(float a, float b)
{
				return (rand()/(double) RAND_MAX)*(b-a);
}

void print_result(Result res, uint n)
{
				printf("Nb it : %d \tScore : %d\n", res.i, res.score);
				print_prop(res.value, n);
}

Result sim_annealing(Instance a, 
								uint* (*neighbourg) (uint, uint, uint, uint*),
								float (*temperature) (float, float),
								float (*proba) (uint, uint, float),
								uint max_steps,
								float t0, 
								float param)
{
				uint i;
				uint* state = rand_prop(a.n, a.k);
				uint* gstate;

				gstate = malloc(sizeof(uint)*a.n);
				if ( gstate==NULL ) {
								fprintf ( stderr, "\ndynamic memory allocation failed\n" );
								exit (EXIT_FAILURE);
				}

				memcpy(gstate, state, a.n*sizeof(uint));

				uint* nstate;
				uint s = score(a, state);
				uint gs = s;

				uint ns;
				float t = t0;
				for(i=0; i<max_steps; i++)
				{
								if (s == a.n)
								{
												break;
								}
								t = temperature(t, param);
								nstate = neighbourg(a.n, a.k, s, state);
								ns = score(a, nstate);
								if (ns > s || uniform(.0,.1) < proba(s, ns, t))
								{
												memcpy(state, nstate, a.n*sizeof(uint));
												s = ns;
												if (s > gs)
												{
																gs = s;
																memcpy(gstate, state, a.n*sizeof(uint));
												}
								}
								free(nstate);
				}

				Result res;
				res.i = i;
				res.score = gs;
				res.value = gstate;

				return res;
};

