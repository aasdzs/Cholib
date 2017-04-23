#ifndef _GF2N_H_
#define _GF2N_H_

#include "config.h"

// STRUCT
typedef struct _GF2N
{
    UNWORD	*Num;		// BIGNUM Value
	UNWORD	Top;		// Allocated Array Size (1 ~ )
	UNWORD	Length;		// Value Size (0 ~ )
	UNWORD	Sign;		// Sign (PLUS, ZERO) 
	SNWORD	Flag;		// Option (DEFAULT, OPTIMIZE)

}GF2N;

//////////////////////////

void GF2N_Init(GF2N *A, const UNWORD len, const SNWORD flag);						// done
void GF2N_Init_Zero(GF2N *A);														// done
void GF2N_Init_One(GF2N *A);
void GF2N_Init_Rand(GF2N *A, const UNWORD maxsize);									// done
void GF2N_Init_Copy(GF2N *R, const GF2N *A);										// done

void GF2N_Randomize(GF2N *A);														// done
void GF2N_Zero(GF2N *A);
void GF2N_Zeroize(GF2N *A);															// done
void GF2N_Copy(GF2N *R, const GF2N *A);												// done

void GF2N_Realloc_Mem(GF2N *A, const UNWORD size);									// done
void GF2N_Zero_Realloc_Mem(GF2N *A, const UNWORD size);								// done
void GF2N_Top_Check(GF2N *A);
void GF2N_Result_Size(GF2N *A, const UNWORD size);
void GF2N_Optimize(GF2N *A);													// done

void GF2N_Free(GF2N *A);															// done
void GF2N_Zero_Free(GF2N *A);														// done

void GF2N_RShift_Bit(GF2N *R, GF2N *A, const UNWORD s_bit);					// done
void GF2N_LShift_Bit(GF2N *R, GF2N *A, const UNWORD s_bit);					// done

SNWORD GF2N_IsZero(const GF2N *A);
UNWORD GF2N_Deg(const GF2N *A);														// done
SNWORD GF2N_Cmp(GF2N *A, GF2N *B);

// Print Function
void GF2N_Print_bin(const GF2N *A);													// done
void GF2N_FPrint_bin(FILE *fp, const GF2N *A);										// done
void GF2N_Print_poly(const GF2N *A);												// done
void GF2N_FPrint_poly(FILE *fp, const GF2N *A);										// done

// Define Function 

void GF2N_Div(GF2N *Q, GF2N *R, GF2N *A, GF2N *IRR);
void GF2N_Redc(GF2N *R, GF2N *A, GF2N *IRR);


void GF2N_Mul(GF2N *Out, GF2N *In1, GF2N *In2, GF2N *Irr);

#else
#endif
