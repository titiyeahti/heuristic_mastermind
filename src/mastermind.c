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
				uint i;
				Instance a;
				a.n = n;
				a.k = k;

				if (k >= 256) {
								fprintf (stderr, "\nnew_instance : k is too_big (max value is 255)");
								exit(EXIT_FAILURE);
				}
				a.soluce	= malloc (sizeof(uint)*n);
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

uint random(uint k)
{
				return (uint)(rand()/(double)RAND_MAX * (k));
}


uint* rand_prop(uint n, uint k)
{
				uint* prop	= malloc (sizeof(uint)*n);
				if ( prop==NULL ) {
								fprintf ( stderr, "\ndynamic memory allocation failed\n" );
								exit (EXIT_FAILURE);
				}

				uint i;
				for (i=0; i<n; i++)
				{
								prop[i] = (uint) random(k);
				}

				return prop; 
}

uint* copy_prop(uint* prop, uint n)
{
				uint* res;

				res	= malloc(sizeof(uint)*n);
				if ( res==NULL ) {
								fprintf ( stderr, "\ndynamic memory allocation failed\n" );
								exit (EXIT_FAILURE);
				}

				return memcpy(res, prop, n*sizeof(uint));
}

Instance rand_instance(uint n, uint k)
{
				Instance a;
				a.n = n;
				a.k = k;

				a.soluce = rand_prop(n, k);
				return a;
}

void free_instance(Instance a)
{
				free(a.soluce);
				a.soluce = NULL;
}

int is_correct(Instance a, uint* p)
{
				uint i;

				for (i=0; i<a.n; i++)
				{
								if (p[i] >= a.k)
												return 0;
				}
				return 1;
}

uint score(Instance a, uint* p)
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

void print_prop(uint* p, uint n)
{
				uint i;
				for (i=0; i<n; i++)
				{
								printf("%d\t", p[i]);
				}
				printf("\n");
}

void print_instance(Instance a)
{
				printf("Instance (%d,%d) :\n", a.n, a.k);
				print_prop(a.soluce, a.n);
}
