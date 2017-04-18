#ifndef _BIGNUM_H_
#define _BIGNUM_H_

#include "config.h"

// STRUCT
typedef struct _BIGNUM
{
    UNWORD	*Num;		// BIGNUM Value
	UNWORD 	Top;		// Allocated array Size (1 ~ )
	UNWORD	Length;		// Value Size (0 ~ )
	SNWORD	Sign; 		// Sign (PLUS, ZERO, MINUS)
	SNWORD	Flag;		// Option (DEFAULT, OPTIMIZE)
}BIGNUM;

// Define Function 
void BN_Init(BIGNUM *A, const UNWORD len, const SNWORD sign, const SNWORD flag);	// done
void BN_Init_Zero(BIGNUM *A);														// done	
void BN_Init_One(BIGNUM *A);														// done
void BN_Init_Rand(BIGNUM *A, const UNWORD maxsize);									// done
void BN_Init_Copy(BIGNUM *R, const BIGNUM *A);										// done

void BN_Randomize(BIGNUM *A);														// done
void BN_Zero(BIGNUM *A);															// done
void BN_Zeroize(BIGNUM *A);															// done
void BN_Copy(BIGNUM *R, const BIGNUM *A);											// done

void BN_Realloc_Mem(BIGNUM *A, const UNWORD size);									// done
void BN_Zero_Realloc_Mem(BIGNUM *A, const UNWORD size);								// done
void BN_Top_Check(BIGNUM *A);														// 
void BN_Optimize(BIGNUM *A);														// done

void BN_Free(BIGNUM *A);															// done
void BN_Zero_Free(BIGNUM *A);														// done

void BN_RShift_Bit(BIGNUM *R, BIGNUM *A, const UNWORD s_bit);
void BN_LShift_Bit(BIGNUM *R, const BIGNUM *A, const UNWORD s_bit);


SNWORD BN_Abs_Cmp(const BIGNUM *A, const BIGNUM *B);
SNWORD BN_Cmp(const BIGNUM *A, const BIGNUM *B);

// Print Function
void BN_Print_hex(const BIGNUM *A);									
void BN_FPrint_hex(FILE *fp, const BIGNUM *A);									




//void BN_Bin_GCD(BIGNUM *R, const BIGNUM *A, const BIGNUM *B);
//void BN_Ext_Bin_GCD(BIGNUM *U, BIGNUM *V, BIGNUM *D, const BIGNUM *X, const BIGNUM *N);


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
