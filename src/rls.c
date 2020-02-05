/*
 * =====================================================================================
 *
 *       Filename:  rls.c
 *
 *    Description:  Implementation of the randomized loca search for mastermind with 
 *    							n colors and n slots.
 *
 *        Version:  1.0
 *        Created:  05/02/2020 01:51:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  ENSIIE - SUAI
 *
 * =====================================================================================
 */

#define	N 100 /* Number of loops */
#define LOW 20
#define HIGH 400
#define STEP 10
#define PROG 100

#include <math.h>
#include "metaheuristic.h"

void mutation(uint* src, uint* dest, uint score, uint k, uint n)
{
				uint spot = score;
				spot = random(n);
				flip_one_slot(src, dest, spot, k, n);
}

Result rls(Instance a)
{
				return genetic_algo(a, 1, 1, 0, mutation, NULL);
}

int main(void)
{
				srand(time(NULL));
				setbuf(stdout, NULL);
				
				FILE* progress;
				FILE* compl;
				uint i;
				uint j;

				/*-----------------------------------------------------------------------------
				 *  PROGRESSION
				 *-----------------------------------------------------------------------------*/
				/*  mean, var */
				Result tab[N];
				float mean_prog, var_prog;

				printf("PROGRESS :\n");
				for(j=0; j<N; j++)
				{
								Instance a = rand_instance(PROG, PROG);
								
								tab[j] = rls(a);

								printf(".");
				}
				printf("\n\n");

				progress = fopen("../data/rls_progress", "w");

				for(i=0; i<PROG; i++)
				{
								mean_prog = 0;
								var_prog = 0;
								for(j=0; j<N; j++)
								{
												mean_prog += (float) tab[j].value[i];
												var_prog += (float) (tab[j].value[i]*tab[j].value[i]);
								}
								mean_prog = mean_prog/N;
								var_prog = sqrt((var_prog/N) - (mean_prog*mean_prog));

								fprintf(progress, "%d %f %f\n", i, mean_prog, var_prog);
				}

				for(j=0; j<N; j++)
								free(tab[j].value);

				fclose(progress);

				/*-----------------------------------------------------------------------------
				 *  BBCOMPL
				 *-----------------------------------------------------------------------------*/
				/*  mean, var */
				clock_t t1;
				float mean_bb, mean_t, var_bb, var_t;
				float val_bb, val_t;

				compl = fopen("../data/rls_compl", "w");
				fprintf(compl, "#N=%d\n#Columns n mean_bb var_bb mean_t var_t\n", N);
				
				printf("COMPL :\n");
				for (i=LOW; i<HIGH; i+=STEP)
				{
								mean_bb = 0;
								mean_t = 0;
								var_bb = 0;
								var_t = 0;

								Result res;

								printf("i=%d\n", i);
								for (j=0; j<N; j++)
								{
												Instance a = rand_instance(i, i);
												
												t1 = clock();
												res = rls(a);
												t1 = clock() - t1;

												val_t = (float) t1/(CLOCKS_PER_SEC);
												val_bb = (float) res.i;

												mean_bb += val_bb;
												var_bb += val_bb*val_bb;

												mean_t += val_t;
												var_t += val_t*val_t;

												free_instance(a);
												free(res.value);
												
												printf(".");
								}

								mean_bb = mean_bb/N;
								mean_t = mean_t/N;
								
								var_bb = sqrt(var_bb/N - (mean_bb*mean_bb));
								var_t = sqrt(var_t/N - (mean_t*mean_t));

								fprintf(compl,"%d %f %f %f %f\n", i, 
																mean_bb, var_bb, mean_t, var_t);

								printf("\n\n");
				}

				fclose(compl);

				return EXIT_SUCCESS;
}
