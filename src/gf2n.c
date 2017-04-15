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
#include "word.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Initialize to GF(2^n)
 * @details 
 * - 메모리 함수 내부에서 할당 \n
 * - Get GF2N struct (Num, Length, Sign, Flag) -> Generate GF2N \n
 * @param[in,out] GF2N *A 
 * @param[in] UNWORD len (const) 길이
 * @param[in] UNWORD sign (const) 부호 PLUS or ZERO
 * @param[in] SNWORD flag (const) 최적화 옵션
 * @date 2017. 04. 05. v1.00 \n
 */
void GF2N_Init(GF2N *A, const UNWORD len, const UNWORD sign, const SNWORD flag)
{
	A->Num = (UNWORD *)calloc(len, sizeof(UNWORD)); 
	A->Length = len; 
	A->Sign = sign;
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
	GF2N_Init(A, rlen, PLUS, flag); 
	GF2N_Randomize(A);

	if((rlen == 1) && (A->Num[0] == 0))
		A->Sign = ZERO; 
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Initialize to Zero GF2N
 * @details
 * - 메모리 함수 내부에서 할당 \n
 * - Generate Zero GF2N \n
 * - Length = 1, Sign = PLUS, Flag = DEFAULT \n
 * @param[in,out] GF2N *A  
 * @date 2017. 04. 07. v1.00 \n
 */
void GF2N_Init_Zero(GF2N *A)
{	
    A->Num = (UNWORD *)calloc(1, sizeof(UNWORD));
	A->Length = 1; 
	A->Sign = ZERO;
	A->Flag = DEFAULT;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Initialize to value 1 of GF2N
 * @details
 * - 메모리 함수 내부에서 할당 \n
 * - 값이 1인 GF2N 생성 \n
 * - Length = 1, Sign = PLUS, Flag = DEFAULT \n
 * @param[in,out] GF2N *A  
 * @date 2017. 04. 08. v1.00 \n
 */
void GF2N_Init_One(GF2N *A)
{	
	A->Num = (UNWORD *)calloc(1, sizeof(UNWORD));
	A->Num[0] = 1;
	A->Length = 1; 
	A->Sign = PLUS;
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
	GF2N_Init(R, A->Length, PLUS, A->Flag);
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
		for(j = 0 ; j < BIT_LEN ; j++)
		{
			A->Num[i] <<= 8;
			A->Num[i] ^= rand() ;
		}
	// 만약 랜덤 생성 값이 0 이면 Sign = ZERO
	if((A->Length == 1) && (A->Num[0] == 0))
			A->Sign = ZERO; 
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Zero GF2N
 * @details 
 * - GF2N *A 를 ZERO 로 변경 \n
 * - 메모리 재할당 (크기, 부호 변경), Length = 1 \n
 * @param[in,out] GF2N *A 
 * @date 2017. 04. 07. v1.00 \n
 * @date 2017. 04. 14. v1.01 \n
 */
void GF2N_Zero(GF2N *A)
{	
	UNWORD i;
	for(i = 0 ; i < A->Length ; i++)
		A->Num[i] = 0;
	A->Num = (UNWORD *)realloc(A->Num, sizeof(UNWORD)); // size = 1
    A->Length = 1;
	A->Sign = ZERO;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Zeroize GF2N
 * @details 
 * - GF2N 값만 ZERO 로 변경 (부호, 크기 변경 X) \n
 * @param[in,out] GF2N *A 
 * @date 2017. 04. 07. v1.00 \n
 * @date 2017. 04. 14. v1.01 \n
 */
void GF2N_Zeroize(GF2N *A)
{	
	UNWORD i;
	for(i = 0 ; i < A->Length ; i++)
		A->Num[i] = 0;	
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
	R->Flag = A->Flag;
	// *R 크기와 *A 가 다르면 동일한 크기인 0 배열로 재할당
	if(R->Length != A->Length)
		GF2N_Zero_Realloc_Mem(R, A->Length);
	// 값 복사
	for(i = R->Length ; i > 0 ; i--) 
		R->Num[i - 1] = A->Num[i - 1];
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
 * @date 2017. 04. 14. v1.01 \n
 */
void GF2N_Realloc_Mem(GF2N *A, const UNWORD size)
{	
	SNWORD i;
	if(A->Length > size)
	{
		// 입력받은 size 크기 보다 큰 값 0 으로 세팅 후
		for(i = A->Length ; i > size ; i--)
			A->Num[i - 1] = 0;
		A->Length = size;
		// 메모리 재할당
		if(A->Length == 0) // Realloc 에 0 들어가면 안됨
			A->Length = 1;
		A->Num = (UNWORD *)realloc(A->Num, (A->Length * sizeof(UNWORD)));
	}
	else if(A->Length < size)
	{
		// 메모리만 재할당 (항상 size > 0)
		A->Num = (UNWORD *)realloc(A->Num, (size * sizeof(UNWORD)));
		// 재할당 받은 배열 값 0 으로 세팅
		for(i = size ; i > A->Length ; i--)
			A->Num[i - 1] = 0;
		A->Length = size;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Zero Data and Memory Reallocate GF2N *A
 * @details
 * - GF2N *A 메모리를 입력받은 크기와 동일하게 재할당 \n
 * - 모든 값을 0 으로 변경 \n
 * - 크기가 같아도 값 0 으로 변경
 * @param[out] GF2N *A
 * @param[in] UNWORD size (const)
 * @date 2017. 04. 05. v1.00 \n
 */
void GF2N_Zero_Realloc_Mem(GF2N *A, const UNWORD size)
{	
	// 입력 받은 크기 만큼 메모리 재할당
	if(A->Length != size)
		GF2N_Realloc_Mem(A, size);
	// 재할당된 메모리 0 으로 초기화
	GF2N_Zeroize(A);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Optimize Input of GF2N *A
 * @details
 * - GF2N *A 값의 크기 최적화 입력 (Memory, Length) \n
 * - 예상 결과 크기와 메모리 크기가 다르면 메모리 재할당 \n
 * @param[in, out] GF2N *A
 * @param[in] UNWORD size (const)
 * @date 2017. 04. 14. v1.00 \n
 */
void GF2N_Optimize_In(GF2N *A, const UNWORD size)
{
	if(A->Length != size)
		GF2N_Zero_Realloc_Mem(A, size);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Optimize Output of GF2N *A
 * @details
 * - GF2N *A 값의 크기 최적화 출력 (Memory, Length)
 * - 최상위 WORD 부터 값이 0 인지 체크
 * @param[in, out] GF2N *A
 * @date 2017. 04. 12. v1.00 \n
 */
void GF2N_Optimize_Out(GF2N *A)
{
	UNWORD tmp_len = A->Length;
	// Length가 1 이상이고, 최상위 WORD 값이 0 인 경우 재할당
	while(A->Num[tmp_len - 1] == 0)
	{
		if(tmp_len > 1) 
			tmp_len--;
		else // 실제 A->Length <= 1 일 때
			break;
	}
	if(A->Length != tmp_len)
		GF2N_Realloc_Mem(A, tmp_len);

	// 길이 0 존재 X
	if(A->Length == 0)
		A->Length = 1;

	// A->Length = 1 , A-Num[0] = 0 인 경우 Sign = ZERO 변경
	if((A->Length == 1) && (A->Num[0] == 0))
		A->Sign = ZERO; 
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
	A->Sign = ZERO;
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
	A->Length = ZERO;
	A->Sign = ZERO;
	A->Flag = DEFAULT;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief GF2N n-bit Right Shift  
 * @details
 * - GF2N *A 오른쪽으로 n 비트 시프트 \n
 * - 외부에서 결과 값 저장 할 GF2N *R 생성해서 입력 \n
 * @param[out] GF2N *R 
 * @param[in] GF2N *A (const)
 * @param[in] s_bit (const) // shift bit
 * @date 2017. 04. 13. v1.00 \n
 */
void GF2N_RShift_Bit(GF2N *R, const GF2N *A, const UNWORD s_bit)
{
	UNWORD i;
	UNWORD tmp_word;
	UNWORD tmp_bit = s_bit;
		
	if(s_bit > (A->Length * BIT_LEN))
		GF2N_Zero(R);
	else
	{
		// R 길이 조정
		GF2N_Optimize_In(R, A->Length);

		if(tmp_bit >= BIT_LEN) // s_bit >= BIT_LEN (워드 이동)
		{
			tmp_word = UW_Div(tmp_bit, BIT_LEN);	// Move word
			tmp_bit = UW_Mod(tmp_bit, BIT_LEN);		// New shift bits
			// WORD 이동
			for(i = 0 ; i < A->Length - tmp_word ; i++)
				R->Num[i] = A->Num[i + tmp_word];
			// 이동된 나머지 WORD = 0 채우기
			for( ; i < A->Length ; i++)
				R->Num[i] = 0;
		}
		else
		{
			for(i = 0 ; i < A->Length ; i++)
				R->Num[i] = A->Num[i];
		}
		
		if(tmp_bit != 0) // tmp_bit == 0 인 경우 WORD 이동만 필요
		{
			// s_bit < BIT_LEN 인 상태 
			for(i = 0 ; i < (R->Length - 1) ; i++) 
				R->Num[i] = (R->Num[i + 1] << (BIT_LEN - tmp_bit)) ^ (R->Num[i] >> tmp_bit);
			// 최상위 WORD 처리 (i = A->Num[A->Length - 1] 일 때)
			R->Num[i] >>= tmp_bit;
		}		
		
		if(A->Flag == OPTIMIZE)
			GF2N_Optimize_Out(R);	
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief GF2N n-bit Light Shift  
 * @details
 * - GF2N *A 왼쪽으로 n 비트 시프트 \n
 * - 외부에서 결과 값 저장 할 GF2N *R 생성해서 입력 \n
 * @param[out] GF2N *R 
 * @param[in] GF2N *A (const)
 * @param[in] s_bit (const) // shift bit
 * @date 2017. 04. 13. v1.00 \n
 */
void GF2N_LShift_Bit(GF2N *R, const GF2N *A, const UNWORD s_bit)
{
	SNINT i;
	UNWORD tmp_word = UW_Div(s_bit, BIT_LEN);	// 실제 추가되는 WORD;
	UNWORD tmp_bit = UW_Mod(s_bit, BIT_LEN);	// 실제 Shift bit;
	UNWORD word_len = A->Length;
	UNWORD zero_cnt = 0;
	
	for(i = BIT_LEN - 1 ; i >= 0 ; i--)
	{
		// 상위 WORD 부터 shift 하면서 0 인 bit 체크
		if((A->Num[word_len - 1] >> i) == 0)
			zero_cnt++;
		else
			break;		
	}	
	
	if(zero_cnt < tmp_bit) // 최상위 WORD 1개 추가
	{			
		GF2N_Zero_Realloc_Mem(R, (A->Length + tmp_word + 1));
	
		for(i = 0 ; i < tmp_word ; i++)
			R->Num[i] = 0;
		for( ; i < R->Length - 1 ; i ++)
			R->Num[i] = A->Num[i - tmp_word];
	}
	else // zero_cnt >= tmp_bit(조정)
	{
		GF2N_Zero_Realloc_Mem(R, (A->Length + tmp_word));
	
		for(i = 0 ; i < tmp_word ; i++)
			R->Num[i] = 0;
		for( ; i < R->Length ; i ++)
			R->Num[i] = A->Num[i - tmp_word];
	}

	if(tmp_bit != 0) // tmp_bit == 0 인 경우 WORD 이동만 필요
	{
		// s_bit < zero_cnt 인 상태 
		for(i = R->Length - 1 ; i > 0 ; i--) 
			R->Num[i] = (R->Num[i] << tmp_bit) ^ (R->Num[i - 1] >> (BIT_LEN - tmp_bit));
		// 최하위 WORD 처리 (i = A->Num[0] 일 때)
		R->Num[i] <<= tmp_bit;
	}
		
	if(A->Flag == OPTIMIZE)
		GF2N_Optimize_Out(R);

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
	for(i = A->Length ; i > 0 ; i--)
	{
		// 최상위 비트부터 >> 하면서 1 인 값 출력
		mask = WORD_MASK_MSB;
		j = 0;
		while(mask)
		{			
			if(A->Num[i - 1] & mask)
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
	//fprintf(fp, "\n");
	//printf("\n");
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
	//fprintf(fp, "\n");
	//printf("\n");
	fclose(fp);
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

	GF2N_Init(&t, A->Length, PLUS, DEFAULT);
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