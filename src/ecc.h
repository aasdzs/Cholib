#ifndef _ECC_H_
#define _ECC_H_

#include "config.h"

// Prime Field (BIGNUM) ECC Points Structure
typedef struct ec_bn_point 
{
	BIGNUM X;
	BIGNUM Y;
	BIGNUM Z; 
   
} EC_BN_PNT;

// Binary Field (GF2N) ECC Points Structure
typedef struct ec_gf2n_point 
{
	GF2N X;
	GF2N Y;
	GF2N Z; 
   
} EC_GF2N_PNT;

#else
#endif
