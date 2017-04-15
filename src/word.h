#ifndef _WD_OPERATION_H_
#define _WD_OPERATION_H_

#include "config.h"

// Define Function 
void UW_Mul(UNWORD *r, const UNWORD a, const UNWORD b);
void UW_Mul2(UNWORD *r, const UNWORD a, const UNWORD b);
void UW_Sqr(UNWORD *r, const UNWORD a);
//void BN_UW_Mul(BIGNUM *R, BIGNUM *A, const UNWORD b);

UNWORD UW_Div(const UNWORD a, const UNWORD wlen);
UNWORD UW_Mod(const UNWORD a, const UNWORD wlen);
#else
#endif
