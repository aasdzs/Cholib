#ifndef _WORD_H_
#define _WORD_H_

#include "config.h"

// Define Function 
void UW_Mul(UNWORD *r, const UNWORD a, const UNWORD b);
void UW_Mul2(UNWORD *r, const UNWORD a, const UNWORD b);
void UW_Sqr(UNWORD *r, const UNWORD a);
void UW_BitSearch(UNWORD *msb_bit, const UNWORD A) ;

UNWORD UW_Div(const UNWORD a, const UNWORD wlen);
UNWORD UW_Mod(const UNWORD a, const UNWORD wlen);
#else
#endif
