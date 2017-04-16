/**
 * @file bignum.c
 * @brief 
 * @details 
 * - Initialize
 * - Zeroize
 * - Randomize
 * - Free
 * - Reaalocation
 * - Compare
 * - Copy
 * - Addition
 * - Subtraction
 * - Multiplication
 * - Modular
 * - inversion
 * @date 2017. 04. 04.
 * @author YoungJin CHO
 * @version 1.01
 */

#include "config.h"
#include "bignum.h"
#include "word.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Initialize to BIGNUM
 * @details 
 * - 메모리 함수 내부에서 할당 \n
 * - Get BIGNUM struct (Num, Length, Sign, Flag) -> Generate BIGNUM \n
 * @param[in,out] BIGNUM *A 
 * @param[in] UNWORD len (const) 길이
 * @param[in] SNWORD sign (const) 부호
 * @param[in] SNWORD flag (const) 최적화 옵션
 * @date 2017. 03. 28. v1.00 \n
 * @date 2017. 03. 30. v1.01 (Flag) \n
 */
void BN_Init(BIGNUM *A, const UNWORD len, const SNWORD sign, const SNWORD flag)
{
	A->Num = (UNWORD *)calloc(len, sizeof(UNWORD)); 
	A->Length = len; 
	A->Sign = sign;
	A->Flag = flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Initialize to Random BIGNUM
 * @details
 * - 메모리 함수 내부에서 할당 \n
 * - 랜덤 BIGNUM 생성 \n
 * - Num, Length, Sign => 모두 랜덤 \n
 * - 단순 TEST용, 난수성 보장 X \n
 * @param[in,out] BIGNUM *A 
 * @param UNWORD maxsize (const)
 * @date 2017. 03. 28. v1.00 \n
 */
void BN_Init_Rand(BIGNUM *A, const UNWORD maxsize)
{
	UNWORD rlen;
		
	rlen = (rand() % maxsize) + 1; // 길이 0 없음
	BN_Init(A, rlen, ZERO, DEFAULT); 
	BN_Randomize(A);
	
	A->Sign = rlen & 1 ? PLUS : MINUS;

	if((rlen == 1) && (A->Num[0] == 0))
		A->Sign = ZERO; 
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Initialize to Zero BIGNUM
 * @details
 * - 메모리 함수 내부에서 할당 \n
 * - Generate Zero BIGNUM \n
 * - Length = 1, Sign = ZERO, Flag = DEFAULT \n
 * @param[in,out] BIGNUM *A  
 * @date 2017. 03. 28. v1.00 \n
 * @date 2017. 03. 30. v1.01 (Flag) \n
 */
void BN_Init_Zero(BIGNUM *A)
{	
	A->Num = (UNWORD *)calloc(1, sizeof(UNWORD));
	A->Length = 1; 
	A->Sign = ZERO;
	A->Flag = DEFAULT;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Initialize to value 1 of BIGNUM
 * @details
 * - 메모리 함수 내부에서 할당 \n
 * - 값이 1인 BIGNUM 생성 \n
 * - Length = 1, Sign = PLUS, Flag = DEFAULT \n
 * @param[in,out] BIGNUM *A  
 * @date 2017. 04. 08. v1.00 \n
 */
void BN_Init_One(BIGNUM *A)
{	
	A->Num = (UNWORD *)calloc(1, sizeof(UNWORD));
	A->Num[0] = 1;
	A->Length = 1; 
	A->Sign = PLUS;
	A->Flag = DEFAULT;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Initialize and Copy BIGNUM *A to *R
 * @details
 * - 메모리 함수 내부에서 할당 \n
 * - BIGNUM 생성해서 (R <- A) COPY \n
 * @param[in,out] BIGNUM *R
 * @param[in] BIGNUM *A
 * @date 2017. 03. 30. v1.00 \n
 */
void BN_Init_Copy(BIGNUM *R, const BIGNUM *A)
{
	// A 와 크기 같은 BIGNUM 생성
	BN_Init(R, A->Length, A->Sign, A->Flag);
	BN_Copy(R, A); // 값 복사
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Randomize BIGNUM
 * @details
 * - 기존에 생성된 BIGNUM 에 랜덤 값 입력 \n
 * - Length 변경 X \n
 * - 단순 TEST용, 난수성 보장 X \n
 * @param[in,out] BIGNUM *A 
 * @date 2017. 03. 28. v1.00 \n
 * @date 2017. 03. 30. v1.01 (Flag) \n
 */
void BN_Randomize(BIGNUM *A)
{
	UNWORD i, j;	 
	for(i = 0 ; i < A->Length ; i++)
		for(j = 0 ; j < BIT_LEN ; j++)
		{
			A->Num[i] <<= 8;
			A->Num[i] ^= rand() ;
		}		
	A->Sign = (rand() & 1) ? PLUS : MINUS;
	// 만약 랜덤 생성 값이 0 이면 Sign = ZERO
	if((A->Length == 1) && (A->Num[0] == 0))
			A->Sign = ZERO; 
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Zero BIGNUM
 * @details 
 * - BIGNUM 값을 ZERO 로 변경 \n
 * - 메모리 재할당 (크기, 부호 변경), Length = 1 \n
 * @param[in,out] BIGNUM *A 
 * @date 2017. 03. 28. v1.00 \n
 * @date 2017. 03. 29. v1.01 (Flag) \n 
 */
void BN_Zero(BIGNUM *A)
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
 * @brief Zeroize BIGNUM
 * @details 
 * - BIGNUM 값만 ZERO 로 변경 (부호, 크기 변경 X) \n
 * @param[in,out] BIGNUM *A 
 * @date 2017. 03. 28. v1.00 \n
 * @date 2017. 03. 29. v1.01 (Flag) \n 
 */
void BN_Zeroize(BIGNUM *A)
{	
	UNWORD i;
	for(i = 0 ; i < A->Length ; i++)
		A->Num[i] = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief BIGNUM Copy A to R
 * @details
 * - BIGNUM *A 값을 BIGNUM *R 로 복사 (*A 와 동일 크기 *R 출력) \n
 * - 내부에서 BIGNUM *A 와 동일한 크기 BIGNUM *R 재할당 \n
 * @param[in,out] BIGNUM *R
 * @param[in] BIGNUM *A (const)
 * @date 2017. 03. 28. v1.00 \n
 */
void BN_Copy(BIGNUM *R, const BIGNUM *A)
{
	SNWORD i;
	R->Sign = A->Sign;
	R->Flag = A->Flag;		
	// *R 크기와 *A 가 다르면 동일한 크기인 0 배열로 재할당
	if(R->Length != A->Length)
		BN_Zero_Realloc_Mem(R, A->Length);
	// 값 복사
	for(i = R->Length ; i > 0 ; i--) 
		R->Num[i - 1] = A->Num[i - 1];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Memory Reallocate BIGNUM *A
 * @details
 * - 입력 받은 사이즈 이상의 값은 0 초기화
 * - 나머지 값은 기존의 값 유지
 * - BIGNUM *A 메모리를 입력받은 크기와 동일하게 재할당
 * @param[out] BIGNUM *A
 * @param[in] UNWORD size (const)
 * @date 2017. 03. 28. v1.00 \n
 * @date 2017. 04. 04. v1.01 \n
 * @date 2017. 04. 14. v1.02 \n
 */
void BN_Realloc_Mem(BIGNUM *A, const UNWORD size)
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
 * @brief Zero Data and Memory Reallocate BIGNUM *A
 * @details
 * - 모든 값을 0 으로 변경 후 
 * - BIGNUM *A 메모리를 입력받은 크기와 동일하게 재할당
 * @param[out] BIGNUM *A
 * @param[in] UNWORD size (const)
 * @date 2017. 03. 30. v1.00 \n
 */
void BN_Zero_Realloc_Mem(BIGNUM *A, const UNWORD size)
{	
	// 입력 받은 크기 만큼 메모리 재할당
	if(A->Length != size)		
		BN_Realloc_Mem(A, size);
	// 재할당된 부분 0 으로 초기화
	BN_Zeroize(A);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Optimize Input of BIGNUM *A
 * @details
 * - BIGNUM *A 값의 크기 최적화 입력 (Memory, Length) \n
 * - 예상 결과 크기와 메모리 크기가 다르면 메모리 재할당 \n
 * @param[in, out] BIGNUM *A
 * @param[in] UNWORD size (const)
 * @date 2017. 04. 14. v1.00 \n
 */
void BN_Optimize_In(BIGNUM *A, const UNWORD size)
{
	if(A->Length != size)
		BN_Zero_Realloc_Mem(A, size);
}

/**
 * @brief Optimize Output of BIGNUM *A
 * @details
 * - BIGNUM *A 값의 크기 최적화 출력 (Memory, Length)
 * - BIGNUM *A 가 0 인 경우 *A 의 Sign = ZERO
 * - 최상위 WORD 부터 값이 0 인지 체크
 * @param[in, out] BIGNUM *A
 * @date 2017. 03. 28. v1.00 \n
 * @date 2017. 04. 04. v1.01 \n
 */
void BN_Optimize_Out(BIGNUM *A)
{
	UNWORD tmp_len = A->Length;
	// Length가 1 이상이고, 최상위 WORD 값이 0 인 경우 재할당
	while(A->Num[tmp_len - 1] == 0)
	{
		if(tmp_len > 1) 
			tmp_len--;
		else // A->Length <= 1 일 때
			break;
	}
	if(A->Length != tmp_len)
		BN_Realloc_Mem(A, tmp_len);

	// 길이 0 존재 X
	if(A->Length == 0)
		A->Length = 1;

	// A->Length = 1 , A-Num[0] = 0 인 경우 Sign = ZERO 변경
	if((A->Length == 1) && (A->Num[0] == 0))
		A->Sign = ZERO; 
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Free BIGNUM Memory
 * @details
 * - BIGNUM Num WORD 동적할당 해제
 * - 0 초기화 없이 단순 메모리 할당 해제
 * - BIGNUM 이 Free 된 상태 => Length = 0 , Sign = 0, Flag = 0
 * @param[in,out] BIGNUM *A 
 * @date 2017. 03. 28. v1.00 \n
 * @date 2017. 03. 30. v1.01 (Flag) \n
 */
void BN_Free(BIGNUM *A)
{
	free(A->Num);
	A->Length = ZERO;
	A->Sign = ZERO;
	A->Flag = DEFAULT;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Zero Free BIGNUM Memory
 * @details
 * - BIGNUM Num WORD 동적할당 해제
 * - 값을 0 으로 초기화 한 후 메모리 할당 해제
 * - BIGNUM 이 Free 된 상태 => Length = 0 , Sign = 0, Flag = 0
 * @param[in,out] BIGNUM *A 
 * @date 2017. 03. 28. v1.00 \n
 * @date 2017. 03. 30. v1.01 (Flag) \n 
 */
void BN_Zero_Free(BIGNUM *A)
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
 * @brief BIGNUM n-bit Right Shift  
 * @details
 * - BIGNUM *A 오른쪽으로 n 비트 시프트 \n
 * - 외부에서 결과 값 저장 할 BIGNUM *R 생성해서 입력 \n
 * @param[out] BIGNUM *R 
 * @param[in] BIGNUM *A (const)
 * @param[in] s_bit (const) // shift bit
 * @date 2017. 04. 13. v1.00 \n
 * @todo sage 에서 음수 일 때 쉬프트 문제...
 */
void BN_RShift_Bit(BIGNUM *R, const BIGNUM *A, const UNWORD s_bit)
{
	UNWORD i;
	UNWORD tmp_word;
	UNWORD tmp_bit = s_bit;
		
	if(s_bit > (A->Length * BIT_LEN))
		BN_Zero(R);
	else
	{
		// R 길이 조정
		BN_Optimize_In(R, A->Length);
		R->Sign = A->Sign;
		R->Flag = A->Flag;

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
			BN_Optimize_Out(R);	
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief BIGNUM n-bit Light Shift  
 * @details
 * - BIGNUM *A 왼쪽으로 n 비트 시프트 \n
 * - 외부에서 결과 값 저장 할 BIGNUM *R 생성해서 입력 \n
 * @param[out] BIGNUM *R 
 * @param[in] BIGNUM *A (const)
 * @param[in] s_bit (const) // shift bit
 * @date 2017. 04. 13. v1.00 \n
 */
void BN_LShift_Bit(BIGNUM *R, const BIGNUM *A, const UNWORD s_bit)
{
	SNINT i;
	UNWORD tmp_word = UW_Div(s_bit, BIT_LEN);	// 실제 추가되는 WORD;
	UNWORD tmp_bit = UW_Mod(s_bit, BIT_LEN);	// 실제 Shift bit;
	UNWORD word_len = A->Length;
	UNWORD zero_cnt = 0;
	
	// R 설정 동일하게
	R->Sign = A->Sign;
	R->Flag = A->Flag;

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
		BN_Zero_Realloc_Mem(R, (A->Length + tmp_word + 1));
	
		for(i = 0 ; i < tmp_word ; i++)
			R->Num[i] = 0;
		for( ; i < R->Length - 1 ; i ++)
			R->Num[i] = A->Num[i - tmp_word];
	}
	else // zero_cnt >= tmp_bit(조정)
	{
		BN_Zero_Realloc_Mem(R, (A->Length + tmp_word));
	
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
		BN_Optimize_Out(R);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Absolute Value Compare BIGNUM *A to BIGNUM *B
 * @details
 * - BIGNUM *A 값과 BIGNUM *B 값 절대값 크기 비교 (Length, WORD Num 값)\n
 * - BIGNUM *A 기준으로 A > B -> return LARGE(1) \n
 * - 1) Length 비교 후 \n
 * - 2) 최상위 Num WORD부터 값 비교 \n
 * @param[in] BIGNUM *A (const)
 * @param[in] BIGNUM *B (const)
 * @return LARGE(1), EQUAL(0), SMALL(-1)
 * @date 2017. 03. 28. v1.00 \n
 */
SNWORD BN_Abs_Cmp(BIGNUM *A, BIGNUM *B)
{
	SNWORD i;

	// 빈 배열 체크 
	BN_Optimize_Out(A);
	BN_Optimize_Out(B);
	
	// 1) A 와 B 의 WORD Length(개수) 같을 때
	if(A->Length == B->Length)
	{	
		// 최상위 WORD 부터 크기 비교
		for(i = A->Length - 1 ; i >= 0 ; i--)
			if(A->Num[i] != B->Num[i]) // A == B 인 경우 Skip
				return (A->Num[i] > B->Num[i]) ? LARGE : SMALL;
		
		// 모든 WORD에 대해서 A == B 이면 두 BIGNUM 동일
		return EQUAL;
	}
	else // 2) A 와 B 의 WORD Length(개수) 다를 때
		return (A->Length > B->Length) ? LARGE : SMALL; // A > B 이면 LARGE 리턴
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Compare BIGNUM *A to BIGNUM *B
 * @details
 * - BIGNUM *A 값과 BIGNUM *B 값 크기 비교 (Sign, Length, WORD Num 값)
 * - BIGNUM *A 기준으로 A > B -> return LARGE(1) 
 * - Sign 비교 후 BN_Abs_Cmp() 비교
 * @param[in] BIGNUM *A (const)
 * @param[in] BIGNUM *B (const)
 * @return LARGE(1), EQUAL(0), SMALL(-1)
 * @date 2017. 03. 28. v1.00 \n
 */
SNWORD BN_Cmp(BIGNUM *A, BIGNUM *B)
{	
	// A, B Sign 다를 때
	if(A->Sign != B->Sign)
		return (A->Sign > B->Sign) ? LARGE : SMALL;
	else // A, B Sign 같을 때 BN_Abs_Cmp() 사용
	{
		if(A->Sign == PLUS)
			return BN_Abs_Cmp(A, B); // |A > B| => (A > B) : retun LARGE(1)
		else // 음수일 때는 절대 값 작은 수가 더 큼
			return BN_Abs_Cmp(B, A); // |A < B| => (-A > -B) : retun LARGE(1)
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/**	
 * @brief Print BIGNUM Hex form
 * @details
 * - BIGNUM *A 를 콘솔창 출력
 * - "0x1234...cdef" -> Hex form
 * @param[in] BIGNUM *A (const)
 * @date 2017. 04. 15. v1.00 \n
 */
void BN_Print_hex(const BIGNUM *A)
{
	SNWORD i;
	
	printf("%s0x", (A->Sign == -1) ? "-" : "");
	for(i = A->Length ; i > 0 ; i--)
		printf("%08X", A->Num[i - 1]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**	
 * @brief File Print BIGNUM Hex form
 * @details
 * - BIGNUM *A 를 파일 출력 \n
 * - "0x1234...cdef" -> Hex form \n
 * @param[in] FILE *fp
 * @param[in] BIGNUM *A (const)
 * @date 2017. 04. 15. v1.00 \n
 */
void BN_FPrint_hex(FILE *fp, const BIGNUM *A)
{
	SNWORD i;
	fprintf(fp, "%s0x", (A->Sign == -1) ? "-" : "");
	for(i = A->Length ; i > 0 ; i--)
		fprintf(fp, "%08X", A->Num[i - 1]);
}



/**
 * @brief BIGNUM Binary GCD algorithm 
 * @details
 * - BIGNUM *a, *b : Positive Integer
 * - BIGNUM *a 와 *b 의 최대공약수 BIGNUM *R 계산
 * - Guide to ECC p.41 참고
 * @param[in] BIGNUM *a (const)
 * @param[in] BIGNUM *b (const)
 * @param[out] BIGNUM *R 
 * @date 2017. 03. 28. v1.00 \n
 * @todo 검증 X
 */
void BN_Bin_GCD(BIGNUM *R, const BIGNUM *a, const BIGNUM *b)
{	
	/*
	BIGNUM u, v, e;

	BN_Init_Copy(&u, a);
	BN_Init_Copy(&v, b);
	BN_Init(&e, 1, PLUS, DEFAULT);
	e.Num[0] = 1;
	
	while(((u.Num[0] & 1) == 0) && ((v.Num[0] & 1) == 0)) // u[0] and v[0] 가 짝수이면 반복
	{
		BN_RShift_Bit(&u, &u, 1);	// u <- (u / 2)
		BN_RShift_Bit(&v, &v, 1);	// v <- (v / 2)
		BN_LShift_Bit(&e, &e, 1);	// e <- (2 * e)
	}

	while((u.Num[0] != 0) && (v.Length == 1)) // (u != 0)
	{
		while((u.Num[0] & 1) == 0)
			BN_RShift_Bit(&u, &u, 1); // u <- u/2		
		while((v.Num[0] & 1) == 0)		
			BN_RShift_Bit(&v, &v, 1); // v <- v/2	
		
		if(BN_Cmp(&u, &v))
			BN_Sub(&u, &u, &v);
		else
			BN_Sub(&v, &v, &u);

		BN_Optimize_Out(&u);
	}

	
	BN_UW_Mul(R, v, e);

	BN_Zero_Free(&u);
	BN_Zero_Free(&v);
	BN_Zero_Free(&e);
	*/
}

/**
 * @brief BIGNUM Extended Binary GCD algorithm 
 * @details
 * - BIGNUM *x, *y : Positive Integer
 * - BIGNUM *v = gcd(x, y), BIGNUM *a and *b s.t. ax + by = gcd(x, y) 
 * - Handbook of Applied Cryptography p.608 참고
 * @param[out] BIGNUM *v \n
 * @param[out] BIGNUM *a \n
 * @param[out] BIGNUM *b \n
 * @param[in] BIGNUM *x (const)
 * @param[in] BIGNUM *y (const)
 * @date 2017. 03. 28. v1.00 \n
 * @todo 아직 미완성
 */
void BN_Ext_Bin_GCD(BIGNUM *v, BIGNUM *a, BIGNUM *b, const BIGNUM *x, const BIGNUM *y)
{	
	/*
	BIGNUM g, u, v;
	BIGNUM A, B, C, D;

	BN_Init(&g, )

	// while x and y are both even
	while(((x->Num[0] & 1) == 0) && ((y->Num[0] & 1) == 0))
	{
		BN_RShift_Bit(x, x, 1);
		BN_RShift_Bit(y, y, 1);
		BN_LShift_Bit(g, g, 1);	
	}
	BN_Init_Copy(&u, x);
	BN_Init_Copy(&v, y);
	BN_Init_One(&A);
	BN_Init_Zero(&B);
	BN_Init_Zero(&C);
	BN_Init_One(&D);

	while((u.Num[0] & 1) == 0)
	{
		BN_RShift_Bit(&u, &u, 1);
		if()
	}

	while((v.Num[0] & 1) == 0)
	{
		BN_RShift_Bit(&v, &v, 1);
		if()
	}
	
	// if u < v
	if(BN_Abs_Cmp(&u, &v) == SMALL)
	{
		BN_Abs_Sub(&v, &v, &u);
		BN_Abs_Sub(&C, &C, &A);
		BN_Abs_Sub(&D, &D, &B);
	}
	else // if u >= v
	{
		BN_Abs_Sub(&u, &u, &v);
		BN_Abs_Sub(&A, &A, &C);
		BN_Abs_Sub(&B, &B, &D);		
	}

	if((u.Length == 0) &&(u.Num[0] == 0))
	{
		BN_Copy(a, &C);
		BN_Copy(b, &D);
	}
	else
	{

	}
	*/

}


/**
 * @brief BIGNUM a^(-1) by Extended Binary GCD algorithm 
 * @details
 * - 입력 a 의 역원 계산
 * - BIGNUM *x 출력 s.t. ax = 1 mod p 
 * - Lecture Note 참고
 * @param[out] BIGNUM *x \n
 * @param[in] BIGNUM *a (const)
 * @param[in] BIGNUM *p (const)
 * @date 2017. 04. 08. v1.00 \n
 * @todo 아직 미완성
 */
void BN_Ext_Inv(BIGNUM *x, const BIGNUM *a, const BIGNUM *p)
{	
	BIGNUM g, u, v;
	BIGNUM A, B, C, D;
	/*
	BN_Init(&g, )

	// while x and y are both even
	while(((x->Num[0] & 1) == 0) && ((y->Num[0] & 1) == 0))
	{
		BN_RShift_Bit(x, x, 1);
		BN_RShift_Bit(y, y, 1);
		BN_LShift_Bit(g, g, 1);	
	}
	BN_Init_Copy(&u, x);
	BN_Init_Copy(&v, y);
	BN_Init_One(&A);
	BN_Init_Zero(&B);
	BN_Init_Zero(&C);
	BN_Init_One(&D);

	while((u.Num[0] & 1) == 0)
	{
		BN_RShift_Bit(&u, &u, 1);
		if()
	}

	while((v.Num[0] & 1) == 0)
	{
		BN_RShift_Bit(&v, &v, 1);
		if()
	}
	
	// if u < v
	if(BN_Abs_Cmp(&u, &v) == SMALL)
	{
		BN_Abs_Sub(&v, &v, &u);
		BN_Abs_Sub(&C, &C, &A);
		BN_Abs_Sub(&D, &D, &B);
	}
	else // if u >= v
	{
		BN_Abs_Sub(&u, &u, &v);
		BN_Abs_Sub(&A, &A, &C);
		BN_Abs_Sub(&B, &B, &D);		
	}

	if((u.Length == 0) &&(u.Num[0] == 0))
	{
		BN_Copy(a, &C);
		BN_Copy(b, &D);
	}
	else
	{
		
	}
	*/

}

// Bignum Opertation

////////////////////////////////////////////////////////////////////////////////////////////////////
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
 * @todo A>=B 가 아닐 때 예외 처리
 */
void BN_Abs_Add(BIGNUM *R, const BIGNUM *A, const BIGNUM *B)
{	
	UNWORD i;
	UNWORD carry = 0;		// 초기 Carry = 0
	UNWORD tmp1, tmp2;
	
	// 연산 결과 최대값 설정	
	if(A->Length > B->Length)
		BN_Optimize_In(R, A->Length + 1);
	else
		BN_Optimize_In(R, B->Length + 1);
	
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
	
	R->Sign = A->Sign;
	//// BIGNUM 최적화
	BN_Optimize_Out(R);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
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
 * @todo 입력 조건 완성 필요... if(A<B) 이면 ..?
 */
void BN_Abs_Sub(BIGNUM *R, const BIGNUM *A, const BIGNUM *B)
{	
	UNWORD i;
	UNWORD borrow = 0;	// 초기 borrow = 0
	UNWORD tmp1, tmp2;	
	
	/*
	// 연산 결과 최대값 설정	
	if(A->Length > B->Length)
		BN_Optimize_In(R, A->Length + 1);
	else
		BN_Optimize_In(R, B->Length + 1);	
	*/
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

	R->Sign = A->Sign;
	// BIGNUM 최적화
	BN_Optimize_Out(R);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
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
	if(((A->Length == 1) && (A->Num[0] == 0)) || (B->Length == 0))
		BN_Copy(R, B);
	else if(((B->Length == 1) && (B->Num[0] == 0)) || (B->Length == 0))
		BN_Copy(R, A);
	else // A, B 모두 0 이 아닌 경우
	{
		if(A->Sign == B->Sign) 
		{
			//  a +  b =  (a + b)
			// -a + -b = -(a + b)
			if(A->Length >= B->Length)
				BN_Abs_Add(R, A, B);
			else // (A->Length < B->Length)
				BN_Abs_Add(R, B, A);
			R->Sign = A->Sign; // 결과 값 R 부호는 A, B 부호와 동일
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

////////////////////////////////////////////////////////////////////////////////////////////////////
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
 * @date 2017. 04. 15. v1.01 (Optimize input)\n
 */
void BN_Basic_Mul(BIGNUM *R, const BIGNUM *A, const BIGNUM *B)
{	
	UNWORD i, j, n;
	UNWORD carry = 0;
	UNWORD tmp[2];

	if(R->Length < (A->Length + B->Length))
		BN_Optimize_In(R, A->Length + B->Length);
		
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
				UW_Mul(tmp, A->Num[i], B->Num[j]);
				
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
			UW_Sqr(tmp, A->Num[i]);

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
				UW_Mul2(tmp, A->Num[i], A->Num[j]);
				
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
	BN_Init(&qh, 0, ZERO, DEFAULT); // 크기 수정
	BN_Init(&qh_p, 0, ZERO, DEFAULT);
	

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
		UW_Mul(tmp, t.Num[i], Np);
		k = tmp[0]; // k = (ti * Np) mod b
		BN_UW_Mul(knb, N, k);

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