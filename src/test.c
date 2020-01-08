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

				clock_t t1, t2;

				float t_one = 0.;
			 	float t_rls = 0.;

				float m_one;
				float m_rls;

				uint n, k;
				if (argc == 3)
				{
								n = strtoul(argv[1], NULL, 10);
								k = strtoul(argv[2], NULL, 10);
				}
				else 
				{
								n = 5;
								k = 10;
				}

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

				uint i;
				Result res;

				for(i=1; i<=k; i++)
				{
/* 								res = sim_annealing(a, neigh_v1, exp_law, 1000*i, 
 * 																(float) 10, 0.99);
 */
/* 								printf("line : %d\n", __LINE__);
 */
								Instance a = rand_instance(n, n);

								t1 = clock();
								res = one_plus_one(a, 1/(float)n);
								t2 = clock();
								t_one += (t2 - t1)/(float)CLOCKS_PER_SEC;
								m_one += res.i/(float)k;

								if (i == 1)
								{
												print_instance(a);
												print_result(res, n);
								}
								free(res.value);

								t1 = clock();
								res = randomized_local_search(a);
								t2 = clock();
								t_rls += (t2 - t1)/(float)CLOCKS_PER_SEC;
								m_rls += res.i/(float)k;
								if (i == 1)
								{
												print_result(res,n);
								}

								free(res.value);
								free_instance(a);
				}

				printf("number of runs = %d, n = %d\n\n", k, n);
				printf("\tnumber of calls \t time \n");
				printf("rls\t%f \t\t\t %f\n", m_rls, t_rls);
				printf("one\t%f \t\t\t %f\n", m_one, t_one);


				return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
