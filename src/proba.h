/*
 * =====================================================================================
 *
 *       Filename:  proba.h
 *
 *    Description:  Some probabilities for the simulated annealing algorithm
 *
 *        Version:  1.0
 *        Created:  12/12/2019 12:43:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  MPRI
 *
 * =====================================================================================
 */

#ifndef  proba_INC
#define  proba_INC

#include "mastermind.h"
#include <math.h>

float exp_law(uint s, uint ns, float t);

float gaussian(uint s, uint ns, float t);


#endif   /* ----- #ifndef proba_INC  ----- */
