/**
 * @file gf_operation.c
 * @brief Galois Field 이용한 연산
 * @details 
 * - Addition
 * - Multiplication
 * - Modular
 * - inversion
 * 자세한 설명
 * @date 2017. 03. ~ 
 * @author YoungJin CHO
 * @version 1.00
 */

#include "config.h"
#include "galoisfield.h"
#include "gf_operation.h"


/**
 * @brief Add GF2N *A and GF2N *B
 * @details
 * - GF2N *A 와 GF2N *B 를 더해서 GF2N *R 출력
 * - GF(2) 에서는 +, - 동일 연산, Sign 구분 X
 * - *R 의 최대 크기 = A.Length or B.Length
 * @param[out] GF2N *R
 * @param[in] GF2N *A (const)
 * @param[in] GF2N *B (const)
 * @date 2017. 03. 28. v1.00 \n
 */
void GF2N_Add(GF2N *R, GF2N *A, GF2N *B)
{
	UNWORD i, tmp_len;

    // 더 큰 수 기준으로 덧셈
	if(A->Length > B->Length)
	{
		tmp_len = A->Length;

		for(i = 0 ; i < B->Length ; i++)
			R->Num[i] = A->Num[i] ^ B->Num[i];

		for( ; i < A->Length ; i++)
			R->Num[i] = A->Num[i];
	}
	else
	{
		tmp_len = B->Length;

		for(i = 0 ; i < A->Length ; i++)
			R->Num[i] = A->Num[i] ^ B->Num[i];

		for( ; i < B->Length ; i++)
			R->Num[i] = B->Num[i];
	}

    // carry 없음
	R->Length = tmp_len;

    // Optimize 문제 

}


/**
 * @brief Multiply GF2N *A and GF2N *B
 * @details
 * - GF2N *A 와 GF2N *B 를 곱한 결과 GF2N *R 출력
 * - 기본 곱셈 방법 적용
 * - 부호 구분 가능
 * - WORD 곱셈 -> R = A * B
 * @param[out] BIGNUM *R
 * @param[in] BIGNUM *A (const)
 * @param[in] BIGNUM *B (const)
 * @date 2017. 03. 28. v1.00 \n
 */
void GF2N_Mul(GF2N *R, GF2N *A, GF2N *B, GF2N *IRR)
{
	GF2N T1, T2, tmpOut;
	UNWORD Mask;
	int i=0, j=0;

	if((!In1->length) && (!In1->num[0]))
	{
		for(i=0; i<Out->length; i++)
			Out->num[i] = 0;
		Out->length = 0;
		return KM_OK;
	}

	if((!In2->length) && (!In2->num[0]))
	{
		for(i=0; i<Out->length; i++)
			Out->num[i] = 0;
		Out->length = 0;
		return KM_OK;
	}

	if((In1->length == 1) && (In1->num[0] == 1))
	{
		KMU_Copy_GF2N(Out, In2);
		return KM_OK;
	}

	if((In2->length == 1) && (In2->num[0] == 1))
	{
		KMU_Copy_GF2N(Out, In1);
		return 0;
	}

	KMU_Init_GF2N(&T1, In1->length+In2->length);
	KMU_Init_GF2N(&T2, In1->length+In2->length);
	KMU_Init_GF2N(&tmpOut, In1->length+In2->length);

	KMU_Copy_GF2N(&T1, In2);

	Mask = In1->num[0];

	if(Mask & 1)
		KMU_Copy_GF2N(&tmpOut, In2);

	i = 0;
	while(i < In1->length)
	{
		Mask = (i)?		(In1->num[i]) : (In1->num[i] >> 1);
		j    = (i)?		(0)           : (1);

		while((Mask) || (i < In1->length-1))
		{
			KMU_LShift1_GF2N(&T2, &T1);
			KMU_Binary_Red(&T1, &T2, Irr);

			if(Mask & 1)
				KMU_Binary_Add(&tmpOut, &tmpOut, &T1);

			Mask = (Mask >> 1);

			if(++j == 32)
				break;
		}

		i++;
	}

	KMU_Binary_Red(Out, &tmpOut, Irr);

	return KM_OK;
}