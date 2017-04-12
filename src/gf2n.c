/**
 * @file galoisfield.c
 * @brief 
 * @details 
 * - Initialize
 * - degree
 * - Zeroize
 * - Randomize
 * - Free
 * - Reaalocation
 * - Compare
 * - Copy
 * - Addition
 * - Multiplication
 * - Modular
 * - inversion
 * @date 2017. 04. 05.
 * @author YoungJin CHO
 * @version 1.00
 */

#include "config.h"
#include "gf2n.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Initialize to Random GF2N
 * @details
 * - 메모리 함수 내부에서 할당 \n
 * - 랜덤 GF2N 생성 \n
 * - Num, Length => 모두 랜덤 \n
 * - 단순 TEST용, 난수성 보장 X \n
 * @param[in,out] GF2N *A 
 * @param UNWORD maxsize (const)
 * @date 2017. 03. 28. v1.00 \n
 */
void GF2N_Init_Rand(GF2N *A, const UNWORD maxsize, const UNWORD flag)
{
	UNWORD rlen;
	rlen = (rand() % maxsize) + 1; // 길이 0 없음
	GF2N_Init(A, rlen, flag); 
	GF2N_Randomize(A);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Initialize to Zero GF2N
 * @details
 * - 메모리 함수 내부에서 할당 \n
 * - Generate Zero GF2N \n
 * - Length = 1, Flag = DEFAULT \n
 * @param[in,out] GF2N *A  
 * @date 2017. 04. 07. v1.00 \n
 */
void GF2N_Init_Zero(GF2N *A)
{	
    A->Num = (UNWORD *)calloc(1, sizeof(UNWORD));
	A->Length = 1; 
	A->Flag = DEFAULT;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Initialize and Copy GF2N *A to *R
 * @details
 * - 메모리 함수 내부에서 할당 \n
 * - GF2N 생성해서 (R <- A) COPY \n
 * @param[in,out] GF2N *R
 * @param[in] GF2N *A
 * @date 2017. 04. 07. v1.00 \n
 */
void GF2N_Init_Copy(GF2N *R, const GF2N *A)
{
	// A 와 크기 같은 BIGNUM 생성
	GF2N_Init(R, A->Length, A->Flag);
	GF2N_Copy(R, A); // 값 복사
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Randomize GF2N
 * @details
 * - 기존에 생성된 GF2N 에 랜덤 값 입력 \n
 * - Length 변경 X \n
 * - 단순 TEST용, 난수성 보장 X \n
 * @param[in,out] GF2N *A 
 * @date 2017. 04. 12. v1.00 \n
 * @todo 수정 요망
 */
void GF2N_Randomize(GF2N *A)
{
	UNWORD i, j;	 
	for(i = 0 ; i < A->Length ; i++)
	{
		for(j = 0 ; j < BIT_LEN ; j++)
		{
			A->Num[i] <<= 8;
			A->Num[i] ^= rand() ;
		}		
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Zeroize GF2N
 * @details 
 * - GF2N 값을 ZERO 로 변경 \n
 * - flag(Optimize) : 메모리 재할당 (크기 변경), Length = 1 \n
 * - flag(Dafault) : 값만 0 으로 변경 (크기 변경 X) \n 
 * @param[in,out] GF2N *A 
 * @date 2017. 04. 07. v1.00 \n
 */
void GF2N_Zeroize(GF2N *A)
{	
	UNWORD i;

	for(i = 0 ; i < A->Length ; i++)
			A->Num[i] = 0;

	// 크기도 재할당 (최적화)
	if(A->Flag == OPTIMIZE)
	{
		A->Num = (UNWORD *)realloc(A->Num, sizeof(UNWORD));
    	A->Length = 1;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief GF2N Copy A to R
 * @details
 * - GF2N *A 값을 GF2N *R 로 복사 (*A 와 동일 크기 *R 출력) \n
 * - 내부에서 GF2N *A 와 동일한 크기 GF2N *R 재할당 \n
 * @param[in,out] GF2N *R
 * @param[in] GF2N *A (const)
 * @date 2017. 04. 06. v1.00 \n
 */
void GF2N_Copy(GF2N *R, const GF2N *A)
{
	SNWORD i;
		
	// *R 크기와 *A 가 다르면 동일한 크기인 0 배열로 재할당
	if(R->Length != A->Length)
		GF2N_Zero_Realloc_Mem(R, A->Length);
	
	R->Flag = A->Flag;

	for(i = R->Length - 1 ; i >= 0 ; i--) 
		R->Num[i] = A->Num[i];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Memory Reallocate GF2N *A
 * @details
 * - 입력 받은 사이즈 이상의 값은 0 초기화 \n
 * - 나머지 값은 기존의 값 유지 \n
 * - GF2N *A 메모리를 입력받은 크기와 동일하게 재할당 \n
 * @param[out] GF2N *A
 * @param[in] UNWORD size (const)
 * @date 2017. 04. 05. v1.00 \n
 */
void GF2N_Realloc_Mem(GF2N *A, const UNWORD size)
{	
	if(A->Length > size)
	{
		// 입력받은 size 크기 보다 큰 값 0 으로 세팅 후
		while(A->Length > size)
		{
			A->Num[(A->Length - 1)] = 0;
			A->Length--;
		}
		// 메모리 재할당
		A->Num = (UNWORD *)realloc(A->Num, A->Length * sizeof(UNWORD));
	}
	else if(A->Length < size)
	{
		// 메모리만 재할당
		A->Num = (UNWORD *)realloc(A->Num, size * sizeof(UNWORD));
		A->Length = size;
	}	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Zero Data and Memory Reallocate GF2N *A
 * @details
 * - 모든 값을 0 으로 변경 후 \n
 * - GF2N *A 메모리를 입력받은 크기와 동일하게 재할당 \n
 * @param[out] GF2N *A
 * @param[in] UNWORD size (const)
 * @date 2017. 04. 05. v1.00 \n
 */
void GF2N_Zero_Realloc_Mem(GF2N *A, const UNWORD size)
{	
	// 입력 받은 크기 만큼 메모리 재할당
	GF2N_Realloc_Mem(A, size);
	// 재할당된 부분 0 으로 초기화
	GF2N_Zeroize(A);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Optimize Output of GF2N *A
 * @details
 * - GF2N *A 값의 크기 최적화 출력 (Memory, Length)
 * - 최상위 Num WORD 부터 값이 0 인지 체크
 * @param[in, out] GF2N *A
 * @date 2017. 04. 12. v1.00 \n
 */
void GF2N_Optimize_Out(GF2N *A)
{
	// Length가 1 이상이고, 최상위 WORD 값이 0 인 경우만 재할당
	if((A->Length > 1) && (A->Num[A->Length - 1] == 0))
	{
		//  최소 A->Length 값 : 1
		while((A->Length > 1) && (A->Num[A->Length - 1] == 0))
			A->Length--;
			
		A->Num = (UNWORD *)realloc(A->Num, A->Length * sizeof(UNWORD));
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Free GF2N Memory
 * @details
 * - GF2N Num WORD 동적할당 해제 \n
 * - 0 초기화 없이 단순 메모리 할당 해제 \n
 * - GF2N 이 Free 된 상태 => Length = 0, Flag = DEFAULT \n
 * @param[in,out] GF2N *A 
 * @date 2017. 04. 07. v1.00 \n
 */
void GF2N_Free(GF2N *A)
{
	free(A->Num);
	A->Length = ZERO;
	A->Flag = DEFAULT;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Zero Free GF2N Memory
 * @details
 * - GF2N Num WORD 동적할당 해제 \n
 * - 값을 0 으로 초기화 한 후 메모리 할당 해제 \n
 * - GF2N 이 Free 된 상태 => Length = 0, Flag = DEFAULT \n
 * @param[in,out] GF2N *A 
 * @date 2017. 04. 07. v1.00 \n
 */
void GF2N_Zero_Free(GF2N *A)
{
	while(A->Length > 0)
	{
		A->Num[(A->Length - 1)] = 0;
		A->Length--;
	}
	free(A->Num);
	A->Flag = DEFAULT;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Search for degree of GF2N *A
 * @details 
 * - 다항식의 차수인 최상위 bit 출력 \n
 * @param[in] GF2N *A (const)
 * @date 2017. 04. 05. v1.00 \n
 */
UNWORD GF2N_Deg(const GF2N *A)
{
	UNWORD degree;
	UNWORD mask;

	// A->Length 가 0 이면 degree 0 리턴
	if(!A->Length)
	{
		degree = 0;
		return degree;
	}
	// 최상위 - 1 배열만큼은 degree 보장
	degree = (A->Length - 1) * BIT_LEN;
	
	// 최상위 배열의 1 위치 판단
	mask = A->Num[A->Length - 1]; 
	while(mask)
	{
		mask = (mask >> 1); // 하위 bit 부터 탐색
		degree++;
	}
	if(degree)
		return (degree - 1);
	else // A->Length 는 1 이지만 degree 는 0 인 경우 
		return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief GF2N n-bit Right Shift  
 * @details
 * - GF2N *A 오른쪽으로 n 비트 시프트 \n
 * - GF2N_RShift_Bit(R, R, s_bit) 문제 없음 (하위 bit 부터 순차적 저장)\n
 * @param[out] GF2N *R 
 * @param[in] GF2N *A (const)
 * @param[in] s_bit (const)
 * @date 2017. 04. 08. v1.00 \n
 * @todo test 필요
 */
void GF2N_RShift_Bit(GF2N *R, const GF2N *A, const UNWORD s_bit)
{
	UNWORD i;
	UNWORD tmp_word = s_bit / BIT_LEN;
	UNWORD tmp_bit = s_bit % BIT_LEN;

	if(s_bit < BIT_LEN)	
	{
		for(i = 0 ; i < (A->Length - 1) ; i++)
			R->Num[i] = (A->Num[i + 1] << (BIT_LEN - s_bit)) ^ (A->Num[i] >> s_bit);
		// 최상위 WORD 처리
		R->Num[i] = (A->Num[i] >> s_bit);
	}
	else // s_bit >= BIT_LEN (워드 이동)
	{
		for(i = 0 ; (i + tmp_word) < A->Length ; i++)
			R->Num[i] = A->Num[i + tmp_word];
		
		for( ; i < (A->Length - 1) ; i++)
			R->Num[i] = 0;
				
		for(i = 0 ; i < ((A->Length - tmp_word) - 1) ; i++)
			R->Num[i] = (A->Num[i + 1] << (BIT_LEN - s_bit)) ^ (A->Num[i] >> s_bit);
		// 최상위 WORD 처리
		R->Num[i] = (A->Num[i] >> s_bit);
	}

	if(A->Flag == OPTIMIZE)
		GF2N_Optimize_Out(R);
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Print GF2N Binary Form
 * @details
 * - GF2N *A 를 (파일 & 콘솔창) 출력
 * - "0b101101...1001" -> Binary form
 * @param[in] SCHAR *filename
 * @param[in] CF2N *A (const)
 * @date 2017. 04. 12. v1.00 \n
 */
void GF2N_Print_bin(SCHAR *filename, const GF2N *A)
{
	SNWORD i, j;
	UNWORD mask;
	FILE *fp;
	
	fopen_s(&fp, filename, "at");   
	fprintf(fp, "0b");
	printf("0b");
	for(i = A->Length - 1 ; i >= 0 ; i--)
	{
		// 최상위 비트부터 >> 하면서 1 인 값 출력
		mask = WORD_MASK_MSB;
		j = 0;
		while(mask)
		{			
			if(A->Num[i] & mask)
			{
				fprintf(fp, "1");
				printf("1");
			}
			else
			{
				fprintf(fp, "0");
				printf("0");
			}
			mask >>= 1;
			j++;
		}
	}
	fprintf(fp, "\n");
	printf("\n");
	fclose(fp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Print GF2N Polynimial Form
 * @details
 * - GF2N *A 를 (파일 & 콘솔창) 출력
 * - "x^n + ... + x^0" -> Polynomial form
 * @param[in] SCHAR *filename
 * @param[in] CF2N *A (const)
 * @date 2017. 04. 12. v1.00 \n
 */
void GF2N_Print_poly(SCHAR *filename, const GF2N *A)
{
	SNWORD i, j;
	SNWORD n = 0;
	UNWORD mask;
	FILE *fp;
	
	fopen_s(&fp, filename, "at");  
	for(i = A->Length - 1 ; i >= 0 ; i--)
	{
		// 최상위 비트부터 >> 하면서 1 인 값 출력
		mask = WORD_MASK_MSB;
		j = BIT_LEN - 1;
		while(mask)
		{			
			if(A->Num[i] & mask)
			{
				if(n != 0) // 맨 처음 다항식 앞엔 + 안붙음
				{
					fprintf(fp, "+");
					printf("+");
				}
				// 다항식 차수 계산
				fprintf(fp, "x^%d", (BIT_LEN * i) + j); 
				printf("x^%d", (BIT_LEN * i) + j);
				n = 1;
			}	
			mask >>= 1;
			j--;
		}
	}
	fprintf(fp, "\n");
	printf("\n");
	fclose(fp);
}












































/**
 * @brief GF2N n-bit Left Shift  
 * @details
 * - GF2N *A 왼쪽으로 n 비트 시프트 \n
 * - BN_RShift_Bit(R, R, s_bit) 여도 문제 없음 (하위 부터 순차적 저장)\n
 * @param[out] GF2N *R 
 * @param[in] GF2N *A (const)
 * @param[in] s_bit (const)
 * @date 2017. 04. 07. v1.00 \n
 * @todo test 필요
 */
void GF2N_LShift_Bit(GF2N *R, GF2N *A, const UNWORD s_bit)
{
	SNWORD i;
	//UNWORD bit_cnt;
		
	UNWORD tmp_word;
	UNWORD tmp_bit;
	UNWORD word_len = A->Length - 1;
	UNWORD zero_cnt = 0;

	for(i = BIT_LEN - 1 ; i >= 0 ; i--)
	{
		// 상위 WORD 부터 0 인 bit 체크
		if((A->Num[word_len] >> i) == 0)
			zero_cnt++;
		else
			break;
		
		// 상위 한 WORD 전체가 0 이면 A 길이 조정 & for 문 다시 실행
		if((i == 0) && ((A->Num[word_len] >> i) == 0))
		{
			word_len--;
			i = (BIT_LEN - 1);
		}
	}

	// zero_cnt >= s_bit 이면 배열 단위 복사 고려할 필요 X
	if(zero_cnt < s_bit)
	{
		tmp_word = (s_bit - zero_cnt) / BIT_LEN;
		tmp_bit = (s_bit - zero_cnt) % BIT_LEN;
		GF2N_Realloc_Mem(A, (A->Length + tmp_word));
		
		for(i = (A->Length - 1) ; (i - tmp_word) >= 0 ; i--)
			R->Num[i] = A->Num[i - tmp_word];
		
		for( ; i < (A->Length - 1) ; i++)
			R->Num[i] = 0;
				
		for(i = 0 ; i < ((A->Length - tmp_word) - 1) ; i++)
			R->Num[i] = (A->Num[i] << s_bit) ^ (A->Num[i - 1] >> (BIT_LEN - s_bit));
		// 최상위 WORD 처리
		R->Num[i] = (A->Num[i] << s_bit);
	}

	if(A->Flag == OPTIMIZE)
		GF2N_Optimize_Out(R);
	
}










////////////////////////////////////////////////////////////////////////////////////////////////////






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