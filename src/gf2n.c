/**
 * @file galoisfield.c
 * @brief 
 * @details 
 * - Initialize
 * - Zeroize
 * - Randomize
 * - Free
 * - Reaalocation
 * - Compare
 * - Copy
 * @date 2017. 04. 05.
 * @author YoungJin CHO
 * @version 1.00
 */

#include "config.h"
#include "gf2n.h"

/**
 * @brief Initialize to GF(2^n)
 * @details 
 * - 메모리 함수 내부에서 할당 \n
 * - Get GF2N struct (Num, Length, Flag) -> Generate GF2N \n
 * @param[in,out] GF2N *A 
 * @param[in] UNWORD len (const) 길이
 * @param[in] SNWORD flag (const) 최적화 옵션
 * @date 2017. 04. 05. v1.00 \n
 */
void GF2N_Init(GF2N *A, const UNWORD len, const SNWORD flag)
{
	A->Num = (UNWORD *)calloc(len, sizeof(UNWORD)); 
	A->Length = len; 
	A->Flag = flag;
}

