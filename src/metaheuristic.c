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

Result res_init(uint count, uint score, uint n)
{
				Result res;
				uint j;
				res.value = (uint*) malloc(n*sizeof(uint));
				for(j=0; j<score; j++)
								res.value[j] = count;
				res.score = score;

				return res;
}

void res_update(Result* res, uint count, uint score)
{
				uint j;
				if (score > res->score)
				{
								for (j=res->score; j<score; j++)
								{
												res->value[j] = count;
								}

								res->score = score;
								res->i = count;
				}
}

/* CHECK MEMORY HERE WARNING */
Result genetic_algo(Instance a, uint lambda, uint mu, float c,
								void (* mutation)(uint*, uint*, uint, uint),
								void (* crossover)(uint*, uint*, uint*, uint))
{
				Prop_score_p* gen;
				Result res;
				uint i, count;
				uint p, m;
				float test;
				count = 0;
				
				gen = gen_init(a, lambda + mu);	
				quicksort(gen, mu);

				res = res_init(count, gen[0]->score, a.n);

				while (gen[0]->score < a.n)
				{
								for(i=mu; i<mu+lambda; i++)
								{
												test = uniform01();
												if (test < c)
												{
																p = random(mu);
																m = rand_with_forb(mu, p);
																crossover(gen[i]->prop, gen[p]->prop, 
																								gen[m]->prop, a.n);
												}
												else
												{
																p = random(mu);
																mutation(gen[p]->prop, gen[i]->prop, a.k, a.n);
																gen[i] -> score = score(a, gen[i]->prop);
												}
												count++;
								}
								quicksort(gen, lambda + mu);
								res_update(&res, count, gen[0]->score);
				}

				gen_free(gen, lambda + mu);
				return res;
}


