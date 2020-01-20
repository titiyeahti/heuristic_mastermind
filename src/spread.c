/*
 * =====================================================================================
 *
 *       Filename:  spread.c
 *
 *    Description:  collecting data about the spreading of convergence
 *
 *        Version:  1.0
 *        Created:  04/12/2019 17:52:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  MPRI
 *
 * =====================================================================================
 */
#include	<stdlib.h>
#include  <stdio.h>
#include 	<time.h>
#include "mastermind.h"
#include "metaheuristic.h"
#include "neighbourg.h"
#include "proba.h"

#define LINE printf("%d, %s\n", __LINE__, __FILE__)

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
				int
main ( int argc, char *argv[] )
{
				srand(time(NULL));
				
				uint n, k;
				if (argc == 3)
				{
								n = strtoul(argv[1], NULL, 10);
								k = strtoul(argv[2], NULL, 10);
				}
				else 
				{
								n = 30;
								k = 20;
				}
				
				uint i, j;
				Result *one;
				Result *rls;
				
				one = (Result*) malloc(sizeof(Result)*k);
				rls = (Result*) malloc(sizeof(Result)*k);

				for(i=0; i<k; i++)
				{
								Instance a = rand_instance(n, n);
								one[i] = one_plus_one(a, 1/(float)n);
								rls[i] = randomized_local_search(a);

								free_instance(a);
								printf(".\n");
				}

				FILE *fp, *fq;

				fp = fopen("../data/One_spread", "w");
				fq = fopen("../data/RLS_spread", "w");

				uint min_one, min_rls,
								max_one, max_rls;
				float mean_one, mean_rls;

				for(i=0; i<n; i++)
				{
								min_one = one[0].value[i];
								max_one = one[0].value[i];
								min_rls = rls[0].value[i];
								max_rls = rls[0].value[i];

								mean_one = 0;
								mean_rls = 0;

								for(j=0; j<k; j++)
								{
												fprintf(fp, "%d ", rls[j].value[i]);
												fprintf(fq, "%d ", one[j].value[i]);
												
												max_one = MAX(max_one, one[j].value[i]);
												min_one = MIN(min_one, one[j].value[i]);
												max_rls = MAX(max_rls, rls[j].value[i]);
												min_rls = MIN(min_rls, rls[j].value[i]);

												mean_one += one[j].value[i] / (float) k;
												mean_rls += rls[j].value[i] / (float) k;
								}
								fprintf(fp, "%d %d %f\n", min_rls, max_rls, mean_rls);
								fprintf(fq, "%d %d %f\n", min_one, max_one, mean_one);
				}

				for(j=0; j<k; j++)
				{
								free(one[j].value);
								free(rls[j].value);
				}

				free(one);
				free(rls);

				fclose(fp);
				fclose(fq);

				return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
