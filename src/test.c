/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  first test file for mastermind.c
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
								n = 10;
								k = 10;
				}

				Instance a = rand_instance(n, k);
				/* 				uint* p = rand_prop(n, k);
				 * 
				 * 				print_instance(a);
				 * 
				 * 				print_prop(p, n);
				 * 
				 * 				printf("score : %d\n", score(a, p));
				 * 
				 * 				free(p);
				 */

				print_instance(a);
				printf("\n");

				uint i;
				Result res;

				for(i=1; i<=n; i++)
				{
								res = sim_annealing(a, neigh_v1, exp_law, 1000*i, 
																(float) 10, 0.99);
								print_result(res, n);
								free(res.value);
				}


				free_instance(a);
				return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
