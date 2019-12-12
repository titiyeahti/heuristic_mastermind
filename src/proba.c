/*
 * =====================================================================================
 *
 *       Filename:  proba.c
 *
 *    Description:  Implementation of proba.h
 *
 *        Version:  1.0
 *        Created:  12/12/2019 12:47:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  ENSIIE - SUAI
 *
 * =====================================================================================
 */

#define M_PI 3.1415926
#include "proba.h"


float exp_law(uint s, uint ns, float t)
{
				return exp((ns-s)/t);
}

float gaussian(uint s, uint ns, float t)
{
				return exp(-((ns-s)/t)*(((ns-s)/t))/2)/sqrt(2*M_PI*t);
}

