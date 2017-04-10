#ifndef _GF2N_H_
#define _GF2N_H_

#include "config.h"

// STRUCT
typedef struct _GF2N
{
    UNWORD	*Num;
	UNWORD	Length;
	SNWORD	Flag; // Optimization Option (default = 0)
}GF2N;

// Define Function 
void GF2N_Init(GF2N *A, const UNWORD len, const SNWORD flag);
void GF2N_Init_Zero(GF2N *A);
void GF2N_Init_Copy(GF2N *R, const GF2N *A);
UNWORD GF2N_Deg(const GF2N *A);
void GF2N_Zeroize(GF2N *A);
void GF2N_Free(GF2N *A);
void GF2N_Zero_Free(GF2N *A);
void GF2N_Realloc_Mem(GF2N *A, const UNWORD size);
void GF2N_Zero_Realloc_Mem(GF2N *A, const UNWORD size);
void GF2N_Optimize_Out(GF2N *A);
void GF2N_Copy(GF2N *R, const GF2N *A);
void GF2N_LShift_Bit(GF2N *R, const GF2N *A, const UNWORD s_bit);


UNWORD GF2N_Deg(const GF2N *A);

#else
#endif
