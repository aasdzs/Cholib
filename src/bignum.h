#ifndef _BIGNUM_H_
#define _BIGNUM_H_

#include "config.h"

// STRUCT
typedef struct _BIGNUM
{
    UNWORD	*Num;
	UNWORD	Length;
	SNWORD	Sign; 
	SNWORD	Flag; // Optimization Option (default = 0)
}BIGNUM;

// Define Function 
void BN_Init(BIGNUM *A, const UNWORD len, const SNWORD sign, const SNWORD flag);
void BN_Init_Zero(BIGNUM *A);
void BN_Init_One(BIGNUM *A);
void BN_Init_Rand(BIGNUM *A, const UNWORD maxsize);
void BN_Init_Copy(BIGNUM *R, const BIGNUM *A);
void BN_Zeroize(BIGNUM *A);
void BN_Randomize(BIGNUM *A);
void BN_Free(BIGNUM *A);
void BN_Zero_Free(BIGNUM *A);
void BN_Realloc_Mem(BIGNUM *A, const UNWORD size);
void BN_Zero_Realloc_Mem(BIGNUM *A, const UNWORD size);
void BN_Optimize_Out(BIGNUM *A);
void BN_Copy(BIGNUM *R, const BIGNUM *A);
SNWORD BN_Abs_Cmp(const BIGNUM *A, const BIGNUM *B);
SNWORD BN_Cmp(const BIGNUM *A, const BIGNUM *B);
void BN_RShift_Bit(BIGNUM *R, const BIGNUM *A, const UNWORD s_bit);
void BN_LShift_Bit(BIGNUM *R, const BIGNUM *A, const UNWORD s_bit);


//void BN_Bin_GCD(BIGNUM *R, const BIGNUM *A, const BIGNUM *B);
//void BN_Ext_Bin_GCD(BIGNUM *U, BIGNUM *V, BIGNUM *D, const BIGNUM *X, const BIGNUM *N);


#else
#endif
