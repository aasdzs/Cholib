/**
 * @file word.c
 * @brief WORD 단위 연산
 * @details 
 * - Addition
 * - Square
 * - Multiplication
 * - Modular
 * - inversion
 * 자세한 설명
 * @date 2017. 03 ~ 07.
 * @author YoungJin CHO
 * @version 1.00
 */

#include "config.h"
#include "bignum.h"
#include "word.h"

/**
 * @brief Search for MSB (Most Significant Bit)
 * @details
 * - UNWORD a 에서 최상위 비트 위치 r 리턴 ()
 * @param[in] UNWORD *a
 * @return UNWORD msb
 * @date 2017. 03. 28. v1.00 \n
 * @todo 미완
 */
UNWORD UNWORD_MSB(const UNWORD a)
{	
	UNWORD msb;
}

/**
 * @brief Multiply UNWORD A from UNWORD B
 * @details
 * - UNWORD A 에서 UNWORD B 를 곱해서 UNWORD *R 출력 (최대 2 WORD 크기)
 * - UNWORD 곱셈 -> R = A * B
 * @param[out] UNWORD *R
 * @param[in] UNWORD A (const)
 * @param[in] UNWORD B (const)
 * @date 2017. 03. 28. v1.00 \n
 */

void UNWORD_Mul(UNWORD *r, const UNWORD a, const UNWORD b)
{	
	UNWORD half_len = BIT_LEN / 2;
	
	UNWORD a_H = (a >> half_len); // WORD 상위 절반 bit
	UNWORD a_L = (a & WORD_MASK_L); // WORD 하위 절반 bit
	UNWORD b_H = (b >> half_len);
	UNWORD b_L = (b & WORD_MASK_L);
	
	UNWORD aH_bL = (a_H * b_L);
	UNWORD aL_bH = (a_L * b_H);

	r[1] = (a_H * b_H); 
	r[0] = (a_L * b_L); 
	
	r[1] += (aH_bL >> half_len);
	r[0] += (aH_bL << half_len);
	if(r[0] < (aH_bL << half_len)) // carry
		r[1] += 1;
	
	r[1] += (aL_bH >> half_len);
	r[0] += (aL_bH << half_len);
	if(r[0] < (aL_bH << half_len)) // carry
		r[1] += 1;
}

/**
 * @brief Multiply BIGNUM A from UNWORD b
 * @details
 * - BIGNUM A 에서 UNWORD B 를 곱해서 BIGNUM *R 출력 (최대 2 WORD 크기)
 * - BIGNUM * UNWORD 연산 -> R = A * b
 * @param[out] BIGNUM *R
 * @param[in] BIGNUM A (const)
 * @param[in] UNWORD b (const)
 * @date 2017. 03. 28. v1.00 \n
 */
/*
void BN_UNWORD_Mul(BIGNUM *R, BIGNUM *A, const UNWORD b)
{	
	UNWORD i, n;
	UNWORD carry = 0;
	UNWORD tmp[2];
		
	if((A->Length == 0) || (b == 0)) // BIGNUM *A or UNWORD b 가 0 인 경우
		BN_Zeroize(R); 
	else if(b == 1) // UNWORD b == 1 인 경우
		BN_Copy(R, A);
	else if((A->Length == 1) && (A->Num[0] == 1)) // B = 1 or -1 인 경우 
		R->Num[0] = b;
	else // 실제 곱셈 연산
	{
		for(i = 0 ; i < A->Length ; i++)
		{
			// WORD * WORD 곱셈 , tmp[1]|tmp[0] 출력
			UNWORD_Mul(tmp, A->Num[i], b);
			
			// 결과 배열에 tmp[0] 추가
			R->Num[i] += tmp[0];
			carry = (R->Num[i] < tmp[0]); // carry 
			tmp[1] = (tmp[1] + carry);
			
			// carry 고려한 덧셈
			carry = (tmp[1] < carry); // tmp[1] + c < c 인 경우 carry 
			R->Num[i + 1] += tmp[1];
			carry += (R->Num[i + 1] < tmp[1]); // A + B + c < A + c 인 경우 carry 발생
			
			// 이후 상위 배열에 대한 carry 고려, 최대 배열 : R->Num[A->Length + B->Length - 1]
			if((carry == 1) && ((i + 1) < (A->Length)))
			{
				n = (i + 1);
				while (carry) // 상위 배열로 올라가면서 carry 계산
				{
					n++;
					R->Num[n] += carry;
					carry = (R->Num[n] < carry);
				}
			}
		}
	}
	
	// 부호 결정
	R->Sign = A->Sign;

	// BIGNUM 최적화
	BN_Optimize_Out(R);		
}
*/
/**
 * @brief Multiply UNWORD A and B and 2
 * @details
 * - UNWORD A * B * 2 => UNWORD *R 출력 (최대 3 WORD 크기)
 * - UNWORD 곱셈 -> R = 2 * (A * B)
 * @param[out] UNWORD *R
 * @param[in] UNWORD A (const)
 * @param[in] UNWORD B (const)
 * @date 2017. 03. 28. v1.00 \n
 */
void UNWORD_2_Mul(UNWORD *r, const UNWORD a, const UNWORD b)
{	
	UNWORD tmp_h, tmp_l;
	
	// WORD 단위 곱셈
	UNWORD_Mul(r, a, b);

	tmp_h = (r[1] << 1); // r[1] * 2
	tmp_l = (r[0] << 1); // r[0] * 2
	
	r[2] = (tmp_h < r[1]); // carry of r[1] (1 or 0)
	r[1] = tmp_h + (tmp_l < r[0]); // r[1] + carry of r[0]
	r[0] = tmp_l;
}

/**
 * @brief Square UNWORD A
 * @details
 * - UNWORD A 를 제곱해서 UNWORD *R 출력 (최대 2 WORD 크기)
 * - UNWORD 제곱 -> R = (A)^2
 * - 다른 방법들이랑 속도 차이 거의 없음..
 * @param[out] UNWORD *R
 * @param[in] UNWORD A (const)
 * @date 2017. 03. 28. v1.00 \n
 */
void UNWORD_Sqr(UNWORD *r, const UNWORD a)
{	
	UNWORD half_len = BIT_LEN / 2;
	
	UNWORD a_H = (a >> half_len);	// WORD 상위 절반 bit
	UNWORD a_L = (a & WORD_MASK_L); // WORD 하위 절반 bit
	
	UNWORD aH_bL = (a_H * a_L);
	
	r[1] = (a_H * a_H); 
	r[0] = (a_L * a_L); 
		
	// 2번 반복
	r[1] += (aH_bL >> half_len);
	r[0] += (aH_bL << half_len);
	if(r[0] < (aH_bL << half_len)) // carry 
		r[1] += 1;

	r[1] += (aH_bL >> half_len);
	r[0] += (aH_bL << half_len);
	if(r[0] < (aH_bL << half_len)) // carry 
		r[1] += 1;
}
