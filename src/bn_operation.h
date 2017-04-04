#ifndef _BN_OPERATION_H_
#define _BN_OPERATION_H_

#include "bignum.h"

// Define Function 

void BN_Abs_Add(BIGNUM *R, const BIGNUM *A, const BIGNUM *B);
void BN_Abs_Sub(BIGNUM *R, const BIGNUM *A, const BIGNUM *B);
void BN_Add(BIGNUM *R, const BIGNUM *A, const BIGNUM *B);
void BN_Sub(BIGNUM *R, const BIGNUM *A, const BIGNUM *B);

void BN_Basic_Mul(BIGNUM *R, const BIGNUM *A, const BIGNUM *B);
void BN_Kara_Mul(BIGNUM *R, const BIGNUM *A, const BIGNUM *B);
void BN_Mul(BIGNUM *R, const BIGNUM *A, const BIGNUM *B);
void BN_Sqr(BIGNUM *R, const BIGNUM *A);

#else
#endif
