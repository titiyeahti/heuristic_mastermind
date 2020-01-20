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
				return a + (rand()/(double) RAND_MAX)*(b-a);
}

float uniform01(void)
{
				return (rand()/(double) RAND_MAX);
}

void free_result(Result res)
{
				free(res.value);
}

void print_result(Result res, uint n)
{
				printf("Nb it : %d \tScore : %d\n", res.i, res.score);
				print_prop(res.value, n);
				printf("\n");
}

uint rand_with_forb(uint k, uint forb)
{
				uint res = random(k-1);
				if (res >= forb)
								res ++;
				return res;
}

Result one_plus_one(Instance a, float p)
{
				uint i = 0;
				uint j;
				uint* best = rand_prop(a.n, a.k);
				uint s = score(a, best);

				Result res;
				res.value = (uint*) malloc(a.n*sizeof(uint));
				for(j=0; j<s; j++)
								res.value[s-1] = i;

				/* just allocating memory */
				uint* prop = rand_prop(a.n, a.k);
				uint ps;
				while(s<a.n)
				{
								memcpy(prop, best, a.n*sizeof(uint));
								for(j=0; j<a.n; j++)
								{
												if(uniform01()<=p)
																prop[j] = rand_with_forb(a.k, best[j]);
								}
								ps = score(a, prop);
								if (ps>s)
								{
												memcpy(best, prop, a.n*sizeof(uint));
												for(j=s-1; j<ps; j++)
																res.value[ps-1] = i;
												s = ps;
								}
								i++;
				}
				res.i = i;
				res.score = s;
				free(prop);
				free(best);

				return res;
}

Result randomized_local_search(Instance a)
{
				uint i = 0;
				uint j;
				uint* best = rand_prop(a.n, a.k);
				uint s = score(a, best);

				Result res;
				res.value = (uint*) malloc(a.n*sizeof(uint));
				
				for(j=0; j<s; j++)
								res.value[s-1] = i;
				
				/* just allocating memory */
				uint* prop = rand_prop(a.n, a.k);
				uint ps;
				while(s<a.n)
				{
								memcpy(prop, best, a.n*sizeof(uint));
								j = random(a.n);
								prop[j] = rand_with_forb(a.k, best[j]);
								ps = score(a, prop);
								if (ps>s)
								{
												memcpy(best, prop, a.n*sizeof(uint));
												for(j=s-1; j<ps; j++)
																res.value[ps-1] = i;
												s = ps;
								}
								i++;
				}
				res.i = i;
				res.score = s;
				free(prop);
				free(best);

				return res;
}

Result sim_annealing(Instance a, 
								uint* (*neighbourg) (uint, uint, uint, uint*),
/* 								float (*temperature) (float, float),
 */
								float (*proba) (uint, uint, float),
								uint max_steps,
								float t0, 
								float param)
{
				uint i;
				uint* state = rand_prop(a.n, a.k);
				uint* gstate;

				gstate = copy_prop(state, a.n);
				
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
/* 								t = (*temperature)(t, param);
 */
								t = t*param;
								nstate = (*neighbourg)(a.n, a.k, s, state);
								ns = score(a, nstate);
								if (ns > s || uniform(.0,.1) < (*proba)(s, ns, t))
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

