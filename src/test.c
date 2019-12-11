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
#include "mastermind.h"
#include	<stdlib.h>
#include 	<time.h>

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
								n = 16;
								k = 10;
				}

				Instance a = rand_instance(n, k);
				uchar* p = rand_prop(n, k);

				print_instance(a);

				print_prop(p, n);

				printf("score : %d\n", score(a, p));

				free_instance(a);
				free(p);
				
				return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
