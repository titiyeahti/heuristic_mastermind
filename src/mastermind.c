/*
 * =====================================================================================
 *
 *       Filename:  mastermind.c
 *
 *    Description:  Implementation of mastermind.h
 *
 *        Version:  1.0
 *        Created:  04/12/2019 16:59:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  MPRI
 *
 * =====================================================================================
 */
#include "mastermind.h"

Instance new_instance(uint n, uint k)
{
				int i;
				Instance a;
				a.n = n;
				a.k = k;

				if (k >= 256) {
								fprintf (stderr, "\nnew_instance : k is too_big (max value is 255)");
								exit(EXIT_FAILURE);
				}
				a.soluce	= malloc (sizeof(uchar)*n);
				if ( a.soluce==NULL ) {
								fprintf ( stderr, "\ndynamic memory allocation failed\n" );
								exit (EXIT_FAILURE);
				}
				
				for (i=0; i<n; i++)
				{
								a.soluce[i] = a.soluce[i] % k;
				}
				return a;
}

void free_instance(Instance a)
{
				free(a.soluce);
				a.soluce = NULL;
}

int is_correct(Instance a, uchar* p)
{
				int i;

				for (i=0; i<a.n; i++)
				{
								if (p[i] >= a.k)
												return 0;
				}
				return 1;
}

uint score(Instance a, uchar* p)
{
				if (is_correct(a, p))
				{
								uint s, i;
								s = 0;
								for (i = 0; i<a.n; i++)
								{
												if (a.soluce[i] == p[i]) s++;
								}
								return s;
				}
				exit(EXIT_FAILURE);
}

void print_instance(Instance a)
{
				int i;
				for (i=0; i<a.n; i++)
				{
								printf("%d\t", a.soluce[i]);
				}
				printf("\n");
}
