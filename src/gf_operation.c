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
#include "gf2n.h"
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
 * @brief GF2N *A Modulus GF2N *IRR (Reduction)
 * @details
 * - GF2N *A 를 *IRR 로 나눈 나머지
 * - *R 의 최대 크기 = IRR 길이
 * - Lecture Note 참고
 * @param[out] GF2N *R
 * @param[in] GF2N *A (const)
 * @param[in] GF2N *IRR (const)
 * @date 2017. 04. 06. v1.00 \n
 */
void GF2N_Redc(GF2N *R, const GF2N *A, const GF2N *IRR)
{
	UNWORD deg_m, deg_r;
	UNWORD tmp_sft;
	GF2N t;

	GF2N_Init(&t, A->Length, DEFAULT);
	GF2N_Copy(R, A);
	// 기약 다항식 최고차항 m
	deg_m = GF2N_Deg(IRR);

	deg_r = GF2N_Deg(R);
	while(deg_r >= deg_m)
	{	
		tmp_sft = (deg_r - deg_m);
		GF2N_LShift_Bit(&t, IRR, tmp_sft);
		GF2N_Add(R, R, &t);
		deg_r = GF2N_Deg(R);
		
	}
}


/**
 * @brief Divide GF2N *A by GF2N *IRR (Division)
 * @details
 * - GF2N *A 를 *IRR 로 나눈 몫과 나머지
 * - *R 의 최대 크기 = IRR 길이
 * - Lecture Note 참고
 * @param[out] GF2N *R
 * @param[out] GF2N *R
 * @param[in] GF2N *A (const)
 * @param[in] GF2N *IRR (const)
 * @date 2017. 04. 06. v1.00 \n

 */
void GF2N_Div(GF2N *Q, GF2N *R, const GF2N *A, const GF2N *IRR)
{
	UNWORD deg_m, deg_r;
	UNWORD tmp_sft;
	GF2N t, q;
	/*
	// 기약 다항식 최고차항 m
	deg_m = GF2N_Deg(IRR);

	GF2N_Init(&t, A->Length, DEFAULT);
	GF2N_Init(&q, (A->Length - IRR->Length), DEFAULT);
	GF2N_Copy(R, A);
	

	deg_r = GF2N_Deg(R);
	while(deg_r >= deg_m)
	{	
		tmp_sft = (deg_r - deg_m);
		GF2N_LShift_Bit(&t, IRR, tmp_sft);
		GF2N_Add(R, R, &t);
		deg_r = GF2N_Deg(R);
		
	}
	*/
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
 * @date 2017. 04. 07. v1.00 \n
 */
void GF2N_Mul(GF2N *R, const GF2N *A, const GF2N *B, const GF2N *IRR)
{
	

}

/**
 * @brief Square GF2N *A 
 * @details 
 * - GF2N *A 를 제곱한 결과 GF2N *R 출력
 * - WORD 제곱 -> R = (A)^2
 * @param[out] BIGNUM *R
 * @param[in] BIGNUM *A (const)
 * @date 2017. 04. 06. v1.00 \n
 */
void GF2N_Sqr(GF2N *R, const GF2N *A, const GF2N *IRR)
{
	
}