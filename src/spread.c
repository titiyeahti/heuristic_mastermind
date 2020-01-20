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

				for(i=0; i<n; i++)
				{
								for(j=0; j<k; j++)
								{
												fprintf(fp, "%d ", rls[j].value[i]);
												fprintf(fq, "%d ", one[j].value[i]);
								}
								fprintf(fp, "\n");
								fprintf(fq, "\n");
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
