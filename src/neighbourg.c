/*
 * =====================================================================================
 *
 *       Filename:  neighbourg.c
 *
 *    Description:  implementation of neighbourg.h
 *
 *        Version:  1.0
 *        Created:  12/12/2019 10:47:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  MPRI
 *
 * =====================================================================================
 */

#include "neighbourg.h"

uint* neigh_v1(uint n, uint k, uint score, uint* prop)
{
				uint i;
				uint* res;
				uint spot;
				uint val;

				res	= copy_prop(prop, n);

				for (i=0; i < n-score; i++)
				{
								spot = random(n);
								val = random(k);
								res[spot] = val;
				}
				return res;
}
