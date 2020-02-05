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

void copy_to_prop(uint* src, uint* target, uint n)
{
				memcpy(target, src, n*sizeof(uint));
}

Instance rand_instance(uint n, uint k)
{
				Instance a;
				a.n = n;
				a.k = k;

				a.soluce = rand_prop(n, k);
				return a;
}


/*-----------------------------------------------------------------------------
 *  MUTATIONS
 *-----------------------------------------------------------------------------*/

float uniform(float a, float b)
{
				return a + (rand()/(double) RAND_MAX)*(b-a);
}

float uniform01(void)
{
				return (rand()/(double) RAND_MAX);
}

uint rand_with_forb(uint k, uint forb)
{
				uint res = random(k-1);
				if (res >= forb)
								res ++;
				return res;
}

void binom_mutation(uint* src, uint* dest, float p, uint k, uint n)
{
				uint j;
				copy_to_prop(src, dest, n);
				for(j=0; j < n; j++)
				{
								if(uniform01()<=p)
												dest[j] = rand_with_forb(k, src[j]);
				}

}

void flip_one_slot(uint* src, uint* dest, uint spot, uint k, uint n)
{
				copy_to_prop(src, dest, n);
				dest[spot] = rand_with_forb(k, src[spot]);
}

void flip_many_slots(uint* src, uint* dest, uint many, uint k, uint n)
{
				copy_to_prop(src, dest, n);
				uint spot;
				uint i;
				for(i=0; i<many; i++)
				{
								spot = random(n);
								dest[spot] = rand_with_forb(k, src[spot]);
				}
							
}


/*-----------------------------------------------------------------------------
 *  Crossovers
 *-----------------------------------------------------------------------------*/
Prop_score_p* gen_init(Instance a, uint size)
{
				Prop_score_p* gen;
				uint i;
				
				gen = malloc(sizeof(Prop_score_p)*size);
				for(i = 0; i < size; i++)
				{
								gen[i] = malloc(sizeof(Prop_score));
				}
				
				for(i = 0; i < size; i++)
				{
								gen[i]->prop = rand_prop(a.n, a.k);
								gen[i]->score = score(a, gen[i]->prop);
				}

				return gen;
}

void gen_free(Prop_score_p* gen, uint size)
{
				uint i;
				for (i=0; i<size; i++)
				{
								free(gen[i]);
				}

				free(gen);

}

void print_gen(Prop_score_p* pop, uint size)
{
				uint i;
				for (i=0; i<size; i++)
				{
								printf("%d ", pop[i]->score);
				}
				printf("\n");
}

/* decreasing */
void quicksort(Prop_score_p* population, uint size)
{
				if (size > 0)
				{
								/* partitionning */
								uint i;
								uint j;
								uint sp, s;
								Prop_score_p temp;

								sp = population[size-1]->score;
								j=0;

								for (i=0; i<size-1; i++)
								{
												s = population[i]->score;
												if (s > sp)
												{				
																temp = population[j];
																population[j] = population[i];
																population[i] = temp;
																j++;
												}
								}
								/* at least as big as te pivot */
								/*replacing the pivot */
								temp = population[j];
								population[j] = population[size-1];
								population[size-1] = temp;

								quicksort(population, j);
								quicksort(population+j+1, size-j-1);
				}
}

void fixpoint_crossover(uint* son, uint* father, uint* mother, uint spot, uint n)
{
				copy_to_prop(father, son, spot);
				copy_to_prop(mother + spot, son + spot,
												n-spot);
}

void random_crossover(uint* son, uint* father, uint* mother, float p, uint n)
{
				uint i;
				for(i=0; i<n; i++)
				{
								float f = uniform01();
								if (f<p)
								{
												son[i] = father[i];
								}
								else 
								{
												son[i] = mother[i];
								}
				}
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
				printf("\n\n");
}

void print_instance(Instance a)
{
				printf("Instance (%d,%d) :\n", a.n, a.k);
				print_prop(a.soluce, a.n);
}
