/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  test for mutations and crossover functions
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

				int
main ( int argc, char *argv[] )
{
				uint *p1, *p2, *p3;

				uint n = 10;
				p1 = rand_prop(n, n);
				p2 = rand_prop(n, n);
				p3 = rand_prop(n, n);
				print_prop(p1, n);

				binom_mutation(p1, p2, 1./n, n, n);
				print_prop(p2, n);

				flip_one_slot(p1, p2, 1, n, n);
				print_prop(p2, n);

				flip_many_slots(p1, p2, 4, n, n);
				print_prop(p2, n);

				printf("Mutations\n\n");

				p2 = rand_prop(n, n);
				
				print_prop(p1, n);
				print_prop(p2, n);

				printf("p1 to 3 then p2\n");

				fixpoint_crossover(p3, p1, p2, 3, n);
				print_prop(p3, n);

				random_crossover(p3, p1, p2, 0., n);
				print_prop(p3, n);

				random_crossover(p3, p1, p2, 1., n);
				print_prop(p3, n);

				return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
