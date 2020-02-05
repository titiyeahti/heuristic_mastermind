/*
 * =====================================================================================
 *
 *       Filename:  ga.c
 *
 *    Description:  Data collecting for genetic algorithms.
 *
 *        Version:  1.0
 *        Created:  05/02/2020 21:51:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  ENSIIE - SUAI
 *
 * =====================================================================================
 */


#define	N 200 /* Number of loops */
#define PROG 51 
#define LOW 60
#define HI 76
#define STEP 5

#include <math.h>
#include "metaheuristic.h"

void mutation(uint* src, uint* dest, uint score, uint k, uint n)
{
				float prob  = (float) score;
				prob = 1./n;
				binom_mutation(src, dest, prob, k, n);
}

void cross1(uint* son, uint* father, uint* mother, uint n)
{
				uint spot = random(n);
				fixpoint_crossover(son, father, mother, spot, n);
}

void cross2(uint* son, uint* father, uint* mother, uint n)
{
				random_crossover(son, father, mother, 1./2, n);
}

Result ga(Instance a, uint lambda, uint mu, 
								void (*mutation)(uint*, uint*, uint, uint, uint))
{
				return genetic_algo(a, lambda, mu, 0, mutation, NULL);
}

int main(void)
{
				srand(time(NULL));
				setbuf(stdout, NULL);  
				
				FILE* cross;
				FILE* cross12;
				uint i;
				uint j;

				/*-----------------------------------------------------------------------------
				 * Proba cross 1/3 1/2 2/3 3/4
				 *-----------------------------------------------------------------------------*/
				/*  mean, var */
				Result r1[N];
				Result r2[N];
				Result r3[N];
				Result r4[N];

				float mean_1, mean_2, mean_3, mean_4;

				printf("Cross :\n");
				for(j=0; j<N; j++)
				{
								Instance a = rand_instance(PROG, PROG);
								
								r1[j] = genetic_algo(a, 10, 5, 1./3, mutation, cross2);
								printf("+");
								r2[j] = genetic_algo(a, 10, 5, 1./2, mutation, cross2);
								printf("-");
								r3[j] = genetic_algo(a, 10, 5, 1./5, mutation, cross2);
								printf("*");
								r4[j] = genetic_algo(a, 10, 5, 1./4, mutation, cross2);
								printf("=");



								free_instance(a);
				}
				printf("\n\n");

				cross = fopen("../data/ga_cross", "w");
				fprintf(cross, "#N=%d, n=%d\n#score 1/3 1/2 1/5 1/4",
												N, PROG);

				for(i=0; i<PROG; i++)
				{
								mean_1 = 0;
								mean_2 = 0;
								mean_3 = 0;
								mean_4 = 0;
								for(j=0; j<N; j++)
								{
												mean_1 += (float) r1[j].value[i];
												mean_2 += (float) r2[j].value[i];
												mean_3 += (float) r3[j].value[i];
												mean_4 += (float) r4[j].value[i];
								}
								mean_1 = mean_1/N;
								mean_2 = mean_2/N;
								mean_3 = mean_3/N;
								mean_4 = mean_4/N;

								fprintf(cross, "%d %f %f %f %f\n", i, 
																mean_1, mean_2, mean_3, mean_4);
				}

				for(j=0; j<N; j++)
				{
								free(r1[j].value);
								free(r2[j].value);
								free(r3[j].value);
								free(r4[j].value);
				}

				fclose(cross);


				/*-----------------------------------------------------------------------------
				 *  Different crossovers
				 *-----------------------------------------------------------------------------*/

				Result res1, res2;
				float m_11, m_14;

				cross12 = fopen("../data/ga_diffcross", "w");

				fprintf(cross12, "#N=%d, [%d:%d:%d]\n# cross1 cross2\n",
												N, LOW, HI, STEP);

				for(i=LOW; i<HI; i+=STEP)
				{
								m_11=0;
								m_14=0;

								for(j=0; j<N; j++)
								{
												Instance a = rand_instance(i, i);
												
												res1 = genetic_algo(a, 10, 5, 1./4, mutation, cross1);
												printf("+");
												res2 = genetic_algo(a, 10, 5, 1./4, mutation, cross2);
												printf("-");

												m_11 += (float)res1.i;
												m_14 += (float)res2.i;
												
												free(res1.value);
												free(res2.value);

												free_instance(a);
								}

								m_11 = m_11/N;
								m_14 = m_14/N;

								fprintf(cross12, "%f %f \n", m_11, m_14);
				}
				printf("\n\n");

				fclose(cross12);


				return EXIT_SUCCESS;
}
