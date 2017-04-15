#ifndef _GF2N_H_
#define _GF2N_H_

#include "config.h"

// STRUCT
typedef struct _GF2N
{
    UNWORD	*Num;
	UNWORD	Length;
	UNWORD	Sign;
	SNWORD	Flag; // Optimization Option (default = 0)
}GF2N;

// Define Function 















void GF2N_Redc(GF2N *R, const GF2N *A, const GF2N *IRR);



//////////////////////////

void GF2N_Init(GF2N *A, const UNWORD len, const UNWORD sign, const SNWORD flag);	// done
void GF2N_Init_Rand(GF2N *A, const UNWORD maxsize, const UNWORD flag);				// done
void GF2N_Init_Zero(GF2N *A);														// done
void GF2N_Init_One(GF2N *A);
void GF2N_Init_Copy(GF2N *R, const GF2N *A);										// done

void GF2N_Randomize(GF2N *A);														// done
void GF2N_Zero(GF2N *A);
void GF2N_Zeroize(GF2N *A);															// done
void GF2N_Copy(GF2N *R, const GF2N *A);												// done

void GF2N_Realloc_Mem(GF2N *A, const UNWORD size);									// done
void GF2N_Zero_Realloc_Mem(GF2N *A, const UNWORD size);								// done
void GF2N_Optimize_In(GF2N *A, const UNWORD size);
void GF2N_Optimize_Out(GF2N *A);													// done

void GF2N_Free(GF2N *A);															// done
void GF2N_Zero_Free(GF2N *A);														// done

void GF2N_LShift_Bit(GF2N *R, const GF2N *A, const UNWORD s_bit);					// done
void GF2N_RShift_Bit(GF2N *R, const GF2N *A, const UNWORD s_bit);					// done

UNWORD GF2N_Deg(const GF2N *A);														// done

// Print Function
void GF2N_Print_bin(char *filename, const GF2N *A);									// done
void GF2N_Print_poly(char *filename, const GF2N *A);								// done




#else
#endif
