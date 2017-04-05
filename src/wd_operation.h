#ifndef _WD_OPERATION_H_
#define _WD_OPERATION_H_

#include "config.h"

// Define Function 
void UNWORD_Mul(UNWORD *r, const UNWORD a, const UNWORD b);
void UNWORD_2_Mul(UNWORD *r, const UNWORD a, const UNWORD b);
void UNWORD_Sqr(UNWORD *r, const UNWORD a);
void BN_UNWORD_Mul(BIGNUM *R, const BIGNUM *A, const UNWORD b);


#else
#endif
