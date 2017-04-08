/**
 * @file bn_operation.c
 * @brief BIGNUM 이용한 연산
 * @details 
 * - Addition
 * - Subtraction
 * - Multiplication
 * - Modular
 * - inversion
 * 자세한 설명
 * @date 2017. 03. ~ 
 * @author YoungJin CHO
 * @version 1.00
 */

#include "config.h"
#include "bignum.h"
#include "bn_operation.h"
#include "wd_operation.h"

/**
 * @brief Absolute Add BIGNUM *A and BIGNUM *B
 * @details
 * - BIGNUM *A 와 BIGNUM *B 를 더해서 BIGNUM *R 출력
 * - BN_Abs_Add() 함수 조건(Length) : A >= B  
 * - Sign 구분 없이 WORD 덧셈 -> R = |A| + |B|
 * - *R 의 최대 크기 : A.Length + 1
 * @param[out] BIGNUM *R
 * @param[in] BIGNUM *A (const)
 * @param[in] BIGNUM *B (const)
 * @date 2017. 03. 28. v1.00 \n
 */
void BN_Abs_Add(BIGNUM *R, const BIGNUM *A, const BIGNUM *B)
{	
	UNWORD i;
	UNWORD carry = 0;		// 초기 Carry = 0
	UNWORD tmp1, tmp2;
	
	//// R 크기가 |A| + |B| 결과보다 작으면 재할당 
	//if(R->Length < (A->Length + 1))
	//	BN_Realloc_Mem(R, (A->Length + 1));	

	for(i = 0 ; i < B->Length ; i++) 
	{
		tmp1 = (A->Num[i] + carry) & WORD_MASK;
		carry = (tmp1 < carry); // A + c < c 인 경우 carry 발생 
		tmp2 = (tmp1 + B->Num[i]) & WORD_MASK;
		carry += (tmp2 < tmp1); // A + B + c < A + c 인 경우 carry 발생
		R->Num[i] = tmp2;					
	}

	// A > B 인 경우 나머지 A 부분 연산
	if(carry)
	{
		for( ; i < A->Length ; i++)
		{
			tmp1 = (A->Num[i] + carry) & WORD_MASK;
			carry = (tmp1 < carry);
			R->Num[i] = tmp1;
		}

		if(carry)
		{
			R->Num[i] = carry;
			R->Length = A->Length + 1;
		}
	}
	else // carry = 0 이면 나머지 부분 그냥 덧셈
		for( ; i < A->Length ; i++)
			R->Num[i] = A->Num[i];
	
	R->Sign = PLUS;
	//// BIGNUM 최적화
	//BN_Optimize_Out(R);	
}

/**
 * @brief Absolute Subtract BIGNUM *B from BIGNUM *A
 * @details
 * - BIGNUM *A 에서 BIGNUM *B 를 빼서 BIGNUM *R 출력
 * - BN_Abs_Sub() 함수 조건(Length) : A > B  
 * - Sign 구분 없이 WORD 덧셈 -> R = |A| - |B|
 * - *R 의 최대 크기 : A.Length
 * @param[out] BIGNUM *R
 * @param[in] BIGNUM *A (const)
 * @param[in] BIGNUM *B (const)
 * @date 2017. 03. 28. v1.00 \n
 */
void BN_Abs_Sub(BIGNUM *R, const BIGNUM *A, const BIGNUM *B)
{	
	UNWORD i;
	UNWORD borrow = 0;	// 초기 borrow = 0
	UNWORD tmp1, tmp2;	
	
	//// R 크기가 |A| - |B| 결과보다 작으면 재할당
	//if(R->Length < A->Length)
	//	BN_Realloc_Mem(R, (A->Length));	

	for(i = 0 ; i < B->Length ; i++) 
	{
		tmp1 = (A->Num[i] - borrow) & WORD_MASK;
		borrow = (tmp1 > A->Num[i]); // A - b > A 인 경우 borrow 발생
		tmp2 = (tmp1 - B->Num[i]) & WORD_MASK;
		borrow += (tmp1 < B->Num[i]); // A - b < B 인 경우 borrow 발생
		R->Num[i] = tmp2;					
	}
	// A > B 인 경우 나머지 A 부분 연산
	if(borrow)
	{
		for( ; i < A->Length ; i++)
		{
			tmp1 = (A->Num[i] - borrow) & WORD_MASK;
			if(A->Num[i] > 0) // A->Num[i] > 0 이면 이후 borrow 발생 X
				borrow = 0;
			
			R->Num[i] = tmp1;	
		}
	}
	else // borrow = 0 이면 나머지 부분 그냥 
		for( ; i < A->Length ; i++)
			R->Num[i] = A->Num[i];	

	R->Sign = PLUS;
	// BIGNUM 최적화
	BN_Optimize_Out(R);	
}

/**
 * @brief Add BIGNUM *A and BIGNUM *B
 * @details
 * - BIGNUM *A 와 BIGNUM *B 를 더해서 BIGNUM *R 출력
 * - 부호 구분 가능
 * - WORD 덧셈 -> R = A + B
 * @param[out] BIGNUM *R
 * @param[in] BIGNUM *A (const)
 * @param[in] BIGNUM *B (const)
 * @date 2017. 03. 28. v1.00 \n
 */
void BN_Add(BIGNUM *R, const BIGNUM *A, const BIGNUM *B)
{		
	// A or B 가 0 인 경우 단순 배열 복사
	if(A->Length == 0)
		BN_Copy(R, B);
	else if(B->Length == 0)
		BN_Copy(R, A);
	else // A, B 모두 0 이 아닌 경우
	{
		if(A->Sign == B->Sign) 
		{
			//  a +  b =  (a + b)
			// -a + -b = -(a + b)
			R->Sign = A->Sign; // 결과 값 R 부호는 A, B 부호와 동일

			if(A->Length >= B->Length)
				BN_Abs_Add(R, A, B);
			else // (A->Length < B->Length)
				BN_Abs_Add(R, B, A);
		}
		else // A->Sign != B->Sign 인 경우
		{
			if(BN_Abs_Cmp(A, B) == LARGE) // A > B 인 경우
			{
				//  a + -b =  (a - b)
				BN_Abs_Sub(R, A, B);
				R->Sign = A->Sign; // 결과가 더 큰 수 부호 따라감
			}
			else // // A <= B 인 경우 
			{
				// -a +  b =  (b - a)
				BN_Abs_Sub(R, B, A);
				R->Sign = B->Sign; // 결과가 더 큰 수 부호 따라감
			}
		}		
	}
}

/**
 * @brief Subtract BIGNUM *B from BIGNUM *A
 * @details
 * - BIGNUM *A 에서 BIGNUM *B 를 빼서 BIGNUM *R 출력
 * - 부호 구분 가능
 * - WORD 뺄셈 -> R = A - B
 * @param[out] BIGNUM *R
 * @param[in] BIGNUM *A (const)
 * @param[in] BIGNUM *B (const)
 * @date 2017. 03. 28. v1.00 \n
 */
void BN_Sub(BIGNUM *R, const BIGNUM *A, const BIGNUM *B)
{	
	if(A->Sign != B->Sign) 
	{	
		if(BN_Abs_Cmp(A, B) == LARGE) // A > B 인 경우
			BN_Abs_Add(R, A, B);
		else // // A <= B 인 경우 
			BN_Abs_Add(R, B, A);
	
		// ( a) - (-b) =  (a + b)
		// (-a) - ( b) = -(a + b)
		R->Sign = A->Sign; // 결과가 크기 상관 없이 A 부호 따라감
	}
	else // A->Sign == B->Sign 인 경우
	{
		// ( a) - ( b) =  a - b)
		// (-a) - (-b) = -a + b)
		if(BN_Abs_Cmp(A, B) == LARGE)
		{
			BN_Abs_Sub(R, A, B);
			R->Sign = A->Sign; // 결과가 더 큰 수 부호 따라감
		}
		else // (A->Length < B->Length)
		{
			BN_Abs_Sub(R, B, A);
			R->Sign = -(B->Sign); // - 때문에 결과가 더 큰 수 반대 부호 따라감
		}
	}	
}

/**
 * @brief Multiply BIGNUM *A and BIGNUM *B
 * @details
 * - BIGNUM *A 와 BIGNUM *B 를 곱한 결과 BIGNUM *R 출력
 * - 기본 곱셈 방법 적용
 * - 부호 구분 가능
 * - WORD 곱셈 -> R = A * B
 * @param[out] BIGNUM *R
 * @param[in] BIGNUM *A (const)
 * @param[in] BIGNUM *B (const)
 * @date 2017. 03. 28. v1.00 \n
 */
void BN_Basic_Mul(BIGNUM *R, const BIGNUM *A, const BIGNUM *B)
{	
	UNWORD i, j, n;
	UNWORD carry = 0;
	UNWORD tmp[2];
		
	if((A->Length == 0) || (B->Length == 0)) // A or B 가 0 인 경우
		BN_Zeroize(R); 
	else if((A->Length == 1) && (A->Num[0] == 1)) // A = 1 or -1 인 경우
		BN_Copy(R, B);
	else if((B->Length == 1) && (B->Num[0] == 1)) // B = 1 or -1 인 경우 
		BN_Copy(R, A);
	else // 실제 곱셈 연산
	{
		for(i = 0 ; i < A->Length ; i++)
		{
			for(j = 0 ; j < B->Length ; j++)
			{
				// WORD * WORD 곱셈 , tmp[1]|tmp[0] 출력
				UNWORD_Mul(tmp, A->Num[i], B->Num[j]);
				
				// 결과 배열에 tmp[0] 추가
				R->Num[i + j] += tmp[0];
				carry = (R->Num[i + j] < tmp[0]); // carry 
				tmp[1] = (tmp[1] + carry);
				
				// carry 고려한 덧셈
				carry = (tmp[1] < carry); // tmp[1] + c < c 인 경우 carry 
				R->Num[i + j + 1] += tmp[1];
				carry += (R->Num[i + j + 1] < tmp[1]); // A + B + c < A + c 인 경우 carry 발생
				
				// 이후 상위 배열에 대한 carry 고려, 최대 배열 : R->Num[A->Length + B->Length - 1]
				if((carry == 1) && ((i + j + 1) < (A->Length + B->Length)))
				{
					n = (i + j + 1);
					while (carry) // 상위 배열로 올라가면서 carry 계산
					{
						n++;
						R->Num[n] += carry;
						carry = (R->Num[n] < carry);
					}
				}
			}
		}
	}
	
	// 부호 결정
	R->Sign = (A->Sign * B->Sign);

	// BIGNUM 최적화
	BN_Optimize_Out(R);			
}

/**
 * @brief Multiply BIGNUM *A and BIGNUM *B by Karatsuba Multiplication
 * @details
 * - BIGNUM *A 와 BIGNUM *B 를 곱한 결과 BIGNUM *R 출력
 * - 기본 곱셈 방법 적용
 * - 부호 구분 가능
 * - WORD 곱셈 -> R = A * B
 * @param[out] BIGNUM *R
 * @param[in] BIGNUM *A (const)
 * @param[in] BIGNUM *B (const)
 * @date 2017. 03. 28. v1.00 \n
 */
void BN_Kara_Mul(BIGNUM *R, const BIGNUM *A, const BIGNUM *B)
{
	BIGNUM u0, v0, u1, v1;			 // 구조체만 이용 (A 의 Num 사용)
	BIGNUM us, vs, u0v0, u1v1, usvs, tmp; // BIGNUM 생성해서 이용
	
	UNWORD d, q, p;
	UNWORD d0 = 1;
	
	// d = max(a,b) 
	d = (A->Length > B->Length) ? A->Length : B->Length;
	// Floor, Ceil 과정 (p <= q)
	// d = p + q
	p = (d >> 1);
	q = (d & 1) ? (p + 1) : (p);	
		
	if(p > d0) // d > KARA_THRESHOLD(d0) 인 경우 카라츄바 곱셈 
	{		
		// u0, u1, v0, v1 설정
		u0.Num = A->Num;		// u0 = (q-1, q-2, ..., 0)		// u0.Length = q
		u1.Num = A->Num + q;	// u1 = (p+q-1, p+q-2, ..., q)	// u1.Length = p = (A->Length - q)
		v0.Num = B->Num;		// v0 = (q-1, q-2, ..., 0)		// v0.Length = q
		v1.Num = B->Num + q;	// v1 = (p+q-1, p+q-2, ..., q)	// v1.Length = p = (B->Length - q)
				
		// Positive Multiprecision Integers
		u0.Sign = u1.Sign = PLUS;
		v0.Sign = v1.Sign = PLUS;
				
		// p, q 범위 정하기 (중요)
		if(q > A->Length) // u1.Length = (A->Length - q) < 0
		{
			u0.Length = A->Length;
			u1.Length = 0;
		}
		else
		{
			u0.Length = q;
			u1.Length = (p > A->Length - q) ? (A->Length - q) : p;
		}
		if(q > B->Length)
		{
			v0.Length = B->Length;
			v1.Length = 0;
		}
		else
		{
			v0.Length = q;
			v1.Length = (p > B->Length - q) ? (B->Length - q) : p;
		}
		// 연산 결과 BIGNUM 생성
		BN_Init(&us, (u0.Length + 1), PLUS, DEFAULT);
		BN_Init(&vs, (v0.Length + 1), PLUS, DEFAULT);
		BN_Init(&u0v0, (u0.Length + v0.Length), PLUS, DEFAULT);
		BN_Init(&u1v1, (u1.Length + v1.Length), PLUS, DEFAULT);
		BN_Init(&usvs, (us.Length + vs.Length), PLUS, DEFAULT);
		BN_Init(&tmp, (us.Length + vs.Length), PLUS, DEFAULT);
		
		// u0 + u1
		BN_Abs_Add(&us, &u0, &u1);
		// v0 + v1
		BN_Abs_Add(&vs, &v0, &v1);
		// u0v0
		BN_Kara_Mul(&u0v0, &u0, &v0);
		// u1v1
		BN_Kara_Mul(&u1v1, &u1, &v1);
		// ((usvs - u1v1) - u0v0) = usvs > 0
		BN_Kara_Mul(&usvs, &us, &vs);
		BN_Abs_Sub(&tmp, &usvs, &u1v1);
		BN_Zeroize(&usvs);
		BN_Abs_Sub(&usvs, &tmp, &u0v0);

		// R = (u1v1)^2q + (usvs)^q + u0v0
		// R += u0v0
		R->Length = u0v0.Length + 1; // carry 고려하여 길이 + 1
		BN_Abs_Add(R, R, &u0v0);
		// R += (usvs)^q
		R->Num += q;
		R->Length = usvs.Length + 1; 
		BN_Abs_Add(R, R, &usvs);
		// R += (u1v1)^2q
		R->Num += q;
		R->Length = u1v1.Length + 1; 
		BN_Abs_Add(R, R, &u1v1);
		
		// R 길이 수정
		R->Length = A->Length + B->Length; 
		R->Num -= (q << 1);

		// BIGNUM 할당 해제 
		BN_Zero_Free(&us);
		BN_Zero_Free(&vs);
		BN_Zero_Free(&u0v0);
		BN_Zero_Free(&u1v1);
		BN_Zero_Free(&usvs);
		BN_Zero_Free(&tmp);

	}
	else // d <= KARA_THRESHOLD(d0) 인 경우 기본 Mul 수행
		BN_Basic_Mul(R, A, B);
		
}

/**
 * @brief Multiplication (Basic or Karatsuba)
 * @details
 * - BIGNUM *A 와 BIGNUM *B 를 곱한 결과 BIGNUM *R 출력
 * - 기본 곱셈 방법 적용
 * - 부호 구분 가능
 * - WORD 곱셈 -> R = A * B
 * @param[out] BIGNUM *R
 * @param[in] BIGNUM *A (const)
 * @param[in] BIGNUM *B (const)
 * @date 2017. 03. 28. v1.00 \n
 */
void BN_Mul(BIGNUM *R, const BIGNUM *A, const BIGNUM *B)
{
	BN_Kara_Mul(R, A, B);
	//BN_Basic_Mul(R, A, B);
}

/**
 * @brief Square BIGNUM *A 
 * @details
 * - BIGNUM *A 의 제곱 결과 BIGNUM *R 출력
 * - 곱셈 보다 UNWORD 곱의 수 적음
 * - 부호 구분 가능
 * - WORD 곱셈 -> R = (A)^2
 * @param[out] BIGNUM *R
 * @param[in] BIGNUM *A (const)
 * @date 2017. 03. 28. v1.00 \n
 */
void BN_Sqr(BIGNUM *R, const BIGNUM *A)
{
	UNWORD i, j, n;
	UNWORD carry = 0;
	UNWORD tmp[3];
	UNWORD m0, m1;
			
	if(A->Length == 0) // A 가 0 인 경우
		BN_Zeroize(R); 
	else if((A->Length == 1) && (A->Num[0] == 1)) // A = 1 or -1 인 경우
		BN_Copy(R, A);
	else // 실제 제곱 연산
	{
		for(i = 0 ; i < A->Length ; i++)
		{
			m0 = i << 1; // (2 * i)
			m1 = m0 + 1; // (2 * i) + 1

			// (WORD)^2 제곱 , tmp[1]|tmp[0] 출력
			UNWORD_Sqr(tmp, A->Num[i]);

			// 결과 배열에 tmp[0] 추가
			R->Num[m0] += tmp[0];
			carry = (R->Num[m0] < tmp[0]); // carry 

			// carry 고려한 덧셈
			tmp[1] = (tmp[1] + carry);
			carry = (tmp[1] < carry); // tmp[1] + c < c 인 경우 carry 
			R->Num[m1] += tmp[1];
			if(R->Num[m1] < tmp[1]) // A + B + c < A + c 인 경우 carry 발생
				carry += 1;
						
			// 이후 상위 배열에 대한 carry 고려, 최대 배열 : R->Num[(2 * A->Length) - 1]
			if((carry == 1) && (m1 < (A->Length << 1)))
			{
				while (carry) // 상위 배열로 올라가면서 carry 계산
				{
					m1++;
					R->Num[m1] += carry;
					carry = (R->Num[m1] < carry);
				}
			}
			
			for(j = i + 1 ; j < A->Length ; j++)
			{
				// (WORD * WORD) * 2 , tmp[2]|tmp[1]|tmp[0] 출력 (최대 3 배열)
				UNWORD_2_Mul(tmp, A->Num[i], A->Num[j]);
				
				// 결과 배열에 tmp[0] 추가
				R->Num[i + j] += tmp[0];
				carry = (R->Num[i + j] < tmp[0]); // carry 
				tmp[1] = (tmp[1] + carry);
				carry = (tmp[1] < carry); // tmp[1] + c < c 인 경우 carry 
				R->Num[i + j + 1] += tmp[1];
				carry += (R->Num[i + j + 1] < tmp[1]) + tmp[2]; // A + B + c < A + c 인 경우 carry 발생
				
				// 이후 상위 배열에 대한 carry 고려, 최대 배열 : (2 * R->Num[A->Length]) - 1]
				if((carry > 0) && ((i + j + 1) < (A->Length << 1)))
				{
					n = (i + j + 1);
					while (carry) // 상위 배열로 올라가면서 carry 계산
					{
						n++;
						R->Num[n] += carry;
						carry = (R->Num[n] < carry);
					}
				}
			}
		}
	}
	
	// 부호 무조건 양수
	R->Sign = PLUS;
	
	// BIGNUM 최적화
	BN_Optimize_Out(R);	
}

/**
 * @brief Barret Reduction of BIGNUM (Modulus)
 * @details
 * - 
 * - Guide to ECC p.36 참고 \n
 * @param[out] BIGNUM *R 
 * @param[in] BIGNUM *Z (const)
 * @param[in] BIGNUM *P (const)
 * @param[in] BIGNUM *MU (const)
 * @date 2017. 03. 29. v1.00 \n
 * @todo 아직 미완성
 */
void BN_Bar_Redc(BIGNUM *R, const BIGNUM *Z, const BIGNUM *P, const BIGNUM *MU)
{	
	BIGNUM qh, qh_p, s_tmp;	// BN_Init() 필요 
	BIGNUM tmp;				// BIGNUM 주소만 활용
	UNWORD k;
	
	// 확인사항
	// Input 조건 따져줘야 하나 ? -> P >= 3 
	// Z == P 인 경우는 ??
	// Reduction 결과 최적화 문제 ?

	// BIGNUM 연산 최대 크기 고려
	BN_Init(&qh, 0, ZERO); // 크기 수정
	BN_Init(&qh_p, 0, ZERO);
	

	// Z < P 인 경우 -> Reduction 필요 X
	if(BN_Abs_Cmp(Z, P) == SMALL)
		BN_Copy(R, Z); 
	else // Z > P 인 경우 Reduction 수행
	{
		// b = 2^(L), L : WORD 크기 or 프로세서 단위
		k = P->Length;	// k = Ceil(log_b(P)) + 1 
		
		// Ceil(Z / b^(k-1)) 계산 (워드 단위 >> 연산)
		tmp.Num = Z->Num + k - 1; // 기준 포인터 위치 변경
		tmp.Length = Z->Length - k + 1; 
		tmp.Sign = Z->Sign; // 항상 Z > 0
				
		BN_Mul(&qh, &tmp, MU);
		// Ceil(qh / b^(k+1)) 계산 (워드 단위 >> 연산)
		qh.Num += (k + 1); 
		qh.Length -= (k + 1);

		// Z mod b^(k+1) -> k + 1 보다 작은 배열만 살림
		tmp.Num = Z->Num;
		tmp.Length = k;
		
		// (qh * P) mod b^(k+1)
		BN_Mul(&qh_p, &qh, P);
		if(qh_p.Length > k)  
			qh_p.Length = k;

		// Z mod b^(k+1) - (qh * P) mod b^(k+1)
		BN_Sub(R, &tmp, &qh_p);
		
		// R 이 음수 -> R = R + b^(k+1)
		if(R->Sign == MINUS)
		{
			BN_Init(&s_tmp, k + 1, ZERO, DEFAULT); // (k+1) 개 s_tmp.Num 배열 -> 0 초기화
			s_tmp.Num[k + 1] = 1;	// b^(k+1) ex) 0x10..0
			s_tmp.Sign = PLUS;

			BN_Add(R, &s_tmp, R);
		}
		// R >= p 이면 -> R - p 반복
		while(BN_Abs_Cmp(R, P) != MINUS)
			BN_Sub(R, R, P);		
	}

	// BN_Free() or BN_Zero_Free() ? 
	BN_Zero_Free(&qh);
	BN_Zero_Free(&qh_p);		
}

/**
 * @brief Montgomery Reduction of BIGNUM (Modulus)
 * @details
 * - 
 * - Handbook of E&HC p.181 참고 \n
 * @param[out] BIGNUM *T 
 * @param[in] BIGNUM *N (const)
 * @param[in] BIGNUM *R (const)
 * @param[in] UNWORD Np (const)
 * @param[in] BIGNUM *U (const)
 * @date 2017. 03. 29. v1.00 \n
 * @todo 아직 미완성
 */
void BN_Mont_Redc(BIGNUM *T, const BIGNUM *N, const BIGNUM *R, const UNWORD Np, const BIGNUM *U)
{	
	/*
	BIGNUM t, knb;
	UNWORD i, k;
	UNWORD tmp[2];
		
	BN_Init_Copy(&t, U);
	BN_Init(knb, N->Length + 1, PLUS, DEFAULT);

	for(i = 0 ; i < N->Length ; i++)	
	{
		UNWORD_Mul(tmp, t.Num[i], Np);
		k = tmp[0]; // k = (ti * Np) mod b
		BN_UNWORD_Mul(knb, N, k);

		// 연산하기 위한 위치로 이동
		t.Num += i;
		t.Length -= i;

		BN_ADD(&t, &t, knb);
		
		// 기존 위치로 복귀
		t.Num -= i;
		t.Length += i;
	}
	
	// t = t/R
	t.Num += N->Length;
	t.Length -= N->Length;
	
	if(BN_Abs_Cmp(t, N) != SMALL) // => if(t >= N)
		BN_Abs_Sub(t, t, N);

	BN_COPY(T, &t);

	BN_Zero_Free(t);
	BN_Zero_Free(knb);
	*/
}