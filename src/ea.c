/*
 * =====================================================================================
 *
 *       Filename:  ea.c
 *
 *    Description:  Implementation of evolutionary algorithms with differents 
 *    							parameters.
 *
 *        Version:  1.0
 *        Created:  05/02/2020 16:38:36
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
#define LOW 20
#define HI 81
#define STEP 30

#include <math.h>
#include "metaheuristic.h"

void mutation1(uint* src, uint* dest, uint score, uint k, uint n)
{
				float prob  = (float) score;
				prob = 1./n;
				binom_mutation(src, dest, prob, k, n);
}

void mutation2(uint* src, uint* dest, uint score, uint k, uint n)
{
				float prob  = (float) score;
				prob = 2./n;
				binom_mutation(src, dest, prob, k, n);
}

void mutation3(uint* src, uint* dest, uint score, uint k, uint n)
{
				float prob  = (float) score;
				prob = 3./n;
				binom_mutation(src, dest, prob, k, n);
}

Result ea(Instance a, uint lambda, uint mu, 
								void (*mutation)(uint*, uint*, uint, uint, uint))
{
				return genetic_algo(a, lambda, mu, 0, mutation, NULL);
}

int main(void)
{
				srand(time(NULL));
				setbuf(stdout, NULL);
				
				FILE* muta;
				FILE* lambda;
				uint i;
				uint j;

				/*-----------------------------------------------------------------------------
				 *  mutations
				 *-----------------------------------------------------------------------------*/
				/*  mean, var */
				Result r1[N];
				Result r2[N];
				Result r3[N];

				float mean_1, mean_2, mean_3;

				printf("Mutations :\n");
				for(j=0; j<N; j++)
				{
								Instance a = rand_instance(PROG, PROG);
								
								r1[j] = ea(a, 1, 4, mutation1);
								printf("+");
								r2[j] = ea(a, 1, 4, mutation2);
								printf("-");
								r3[j] = ea(a, 1, 4, mutation3);
								printf("*");

								free_instance(a);
				}
				printf("\n\n");

				muta = fopen("../data/ea_muta", "w");
				fprintf(muta, "#N=%d, n=%d\n#score p=1/n p=2/n p=3/n",
												N, PROG);

				for(i=0; i<PROG; i++)
				{
								mean_1 = 0;
								mean_2 = 0;
								mean_3 = 0;
								for(j=0; j<N; j++)
								{
												mean_1 += (float) r1[j].value[i];
												mean_2 += (float) r2[j].value[i];

												mean_3 += (float) r3[j].value[i];
								}
								mean_1 = mean_1/N;
								mean_2 = mean_2/N;
								mean_3 = mean_3/N;

								fprintf(muta, "%d %f %f %f\n", i, mean_1, mean_2, mean_3);
				}

				for(j=0; j<N; j++)
				{
								free(r1[j].value);
								free(r2[j].value);
								free(r3[j].value);
				}

				fclose(muta);


				/*-----------------------------------------------------------------------------
				 *  Lamda + Mu
				 *-----------------------------------------------------------------------------*/

				Result res1, res2, res3;
				float m_11, m_14, m_44;

				lambda = fopen("../data/ea_lambda", "w");

				fprintf(lambda, "#N=%d\n# n=%d 11 14 44, n=%d 11 14 44, n=%d 11 14 44\n",
												N, LOW, LOW+STEP, LOW+2*STEP);

				for(i=LOW; i<HI; i+=STEP)
				{
								m_11=0;
								m_14=0;
								m_44=0;

								for(j=0; j<N; j++)
								{
												Instance a = rand_instance(i, i);
												
												res1 = ea(a, 1, 1, mutation1);
												printf("+");
												res2 = ea(a, 1, 4, mutation1);
												printf("-");
												res3 = ea(a, 4, 4, mutation1);
												printf("*");

												m_11 += (float)res1.i;
												m_14 += (float)res2.i;
												m_44 += (float)res3.i;
												
												free(res1.value);
												free(res2.value);
												free(res3.value);

												free_instance(a);
								}

								m_11 = m_11/N;
								m_14 = m_14/N;
								m_44 = m_44/N;

								fprintf(lambda, "%f %f %f \n", m_11, m_14, m_44);
				}
				printf("\n\n");

				fclose(lambda);


				return EXIT_SUCCESS;
}
