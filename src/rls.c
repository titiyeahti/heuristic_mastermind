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

#include "metaheuristic.h"

void mutation(uint* src, uint* dest, uint k, uint n)
{
				uint spot = random(n);
				flip_one_slot(src, dest, spot, k, n);
}

Result rls(Instance a)
{
				return genetic_algo(a, 1, 1, 0, mutation, NULL);
}

int main(void)
{
				srand(time(NULL));
				uint n = 10;
				Instance a = rand_instance(n, n);

				Result res = rls(a);

				print_result(res, n);

				free(res.value);

				return EXIT_SUCCESS;
}
