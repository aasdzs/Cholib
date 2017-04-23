/**
 * @file bignum.c
 * @brief 
 * @details 
 * - Initialize
 * - Zeroize
 * - Randomize
 * - Free
 * - Reallocation
 * - Compare
 * - Copy
 * - Addition
 * - Subtraction
 * - Multiplication
 * - Modular
 * - inversion
 * @date 2017. 
 * @author YoungJin CHO
 * @version 1.00
 */

#include "config.h"
#include "bignum.h"
#include "word.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Initialize to BIGNUM
 * @details 
 * - 메모리 함수 내부에서 할당 \n
 * - Get BIGNUM struct parameter (Num, Length, Sign, Flag) -> Generate BIGNUM \n
 * @param[in,out] BIGNUM *A 
 * @param[in] UNWORD len (const) 
 * @param[in] SNWORD sign (const) 
 * @param[in] SNWORD flag (const) 
 * @date 2017. 04. 17. v1.00 \n
 */
void BN_Init(BIGNUM *A, const UNWORD len, const SNWORD sign, const SNWORD flag)
{
	A->Num = (UNWORD *)calloc(len, sizeof(UNWORD)); 
	A->Top = A->Length = len; 
	A->Sign = sign;
	A->Flag = flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Initialize to Zero BIGNUM
 * @details
 * - 메모리 함수 내부에서 할당 \n
 * - Generate Zero BIGNUM \n
 * - 값이 0 인 BIGNUM 은 Length 를 0 으로 정의
 * - Top = 1, Length = 0, Sign = ZERO, Flag = DEFAULT \n
 * @param[in,out] BIGNUM *A  
 * @date 2017. 04. 17. \n
 */
void BN_Init_Zero(BIGNUM *A)
{	
	A->Num = (UNWORD *)calloc(1, sizeof(UNWORD));
	A->Top = 1;			// 실제 할당된 배열 크기
	A->Length = 0; 		// 값이 들어있는 배열 크기
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
 * @date 2017. 04. 17. \n
 */
void BN_Init_One(BIGNUM *A)
{	
	A->Num = (UNWORD *)calloc(1, sizeof(UNWORD));
	A->Num[0] = 1;
	A->Top = A->Length = 1;
	A->Sign	= PLUS;
	A->Flag	= DEFAULT;	
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
 * @date 2017. 04. 17. v1.00 \n
 */
void BN_Init_Rand(BIGNUM *A, const UNWORD maxsize)
{
	UNWORD rlen = (rand() % maxsize) + 1;
	BN_Init(A, rlen, ZERO, DEFAULT); 
	BN_Randomize(A);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Initialize and Copy BIGNUM *A to *R
 * @details
 * - 메모리 함수 내부에서 할당 \n
 * - BIGNUM 생성해서 (R <- A) COPY \n
 * @param[in,out] BIGNUM *R
 * @param[in] BIGNUM *A
 * @date 2017. 04. 17. \n
 */
void BN_Init_Copy(BIGNUM *R, const BIGNUM *A)
{
	// A 와 배열 크기 같은 BIGNUM 생성
	BN_Init(R, A->Top, A->Sign, A->Flag);
	BN_Copy(R, A); // 값 복사
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Randomize BIGNUM
 * @details
 * - 기존에 생성된 BIGNUM 에 랜덤 값 입력 \n
 * - Length 변경 X \n
 * - 단순 TEST 용, 난수성 보장 X \n
 * @param[in,out] BIGNUM *A 
 * @date 2017. 04. 17. \n
 */
void BN_Randomize(BIGNUM *A)
{
	UNWORD i, j;	 
	for(i = 0 ; i < A->Top ; i++)
		for(j = 0 ; j < BIT_LEN ; j++)
		{
			A->Num[i] <<= 8;
			A->Num[i] ^= rand() ;
		}		
	A->Sign = (rand() & 1) ? PLUS : MINUS;
	BN_Optimize(A);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Zero BIGNUM
 * @details 
 * - BIGNUM *A 를 0 으로 변경 \n
 * - 메모리 재할당 (크기, 부호 변경), Length = 1 \n
 * @param[in,out] BIGNUM *A 
 * @date 2017. 04. 17. \n
 */
void BN_Zero(BIGNUM *A)
{		
	BN_Zeroize(A);
	A->Num = (UNWORD *)realloc(A->Num, sizeof(UNWORD)); 
	A->Top = 1; // Top = 1, Length = 0
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Zeroize BIGNUM
 * @details 
 * - BIGNUM 값만 0 으로 변경 (Top, Flag 변경 X) \n
 * @param[in,out] BIGNUM *A 
 * @date 2017. 04. 17. \n
 */
void BN_Zeroize(BIGNUM *A)
{	
	UNWORD i;
	for(i = 0 ; i < A->Top ; i++)
		A->Num[i] = 0;
	A->Length = 0;	
	A->Sign = ZERO;	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief BIGNUM Copy A to R
 * @details
 * - BIGNUM *A 값을 BIGNUM *R 로 복사 (*A 와 동일 크기 *R 출력) \n
 * - 내부에서 BIGNUM *A 와 동일한 크기 BIGNUM *R 재할당 \n
 * @param[in,out] BIGNUM *R
 * @param[in] BIGNUM *A (const)
 * @date 2017. 04. 17. \n
 */
void BN_Copy(BIGNUM *R, const BIGNUM *A)
{
	UNWORD i;		
	// *R 배열 크기와 *A 배열 크기가 다르면 동일한 크기인 0 배열로 재할당
	if(R->Top != A->Top)
		BN_Zero_Realloc_Mem(R, A->Top);
	// 값 복사 (R->Top = A->Top 상태)
	for(i = R->Top ; i > 0 ; i--) 
		R->Num[i - 1] = A->Num[i - 1];
	// 나머지 복사
	R->Length = A->Length;
	R->Sign	= A->Sign;
	R->Flag	= A->Flag;	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Memory Reallocate BIGNUM *A
 * @details
 * - 입력 받은 사이즈 이상의 값은 0 초기화 \n
 * - 나머지 값은 기존의 값 유지 \n
 * - BIGNUM *A 메모리를 입력받은 크기와 동일하게 재할당 \n
 * @param[out] BIGNUM *A
 * @param[in] UNWORD size (const)
 * @date 2017. 04. 17. \n 
 */
void BN_Realloc_Mem(BIGNUM *A, const UNWORD size)
{	
	UNWORD i;	
	if(size == 0)
		BN_Zero(A);
	else if(A->Top > size)
	{
		// 입력받은 size 크기 보다 큰 값들을 0 으로 세팅 후
		for(i = A->Top ; i > size ; i--)
			A->Num[i - 1] = 0;
		A->Top = A->Length = size;
		A->Num = (UNWORD *)realloc(A->Num, (A->Top * sizeof(UNWORD)));
	}
	else if(A->Top < size)
	{
		// 메모리만 재할당 (항상 size > 0)
		A->Num = (UNWORD *)realloc(A->Num, (size * sizeof(UNWORD)));
		// 재할당 받은 배열 값 0 으로 세팅
		for(i = A->Top ; i < size ; i++)
			A->Num[i - 1] = 0;
		A->Top = size; // A->Length = 기존 값 유지
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
 * @date 2017. 04. 17. \n
 */
void BN_Zero_Realloc_Mem(BIGNUM *A, const UNWORD size)
{	
	// 입력 받은 크기 만큼 메모리 재할당
	if(A->Top != size)
		BN_Realloc_Mem(A, size);
	// 재할당된 부분 0 으로 초기화
	BN_Zeroize(A);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Top Check of BIGNUM *A
 * @details
 * - BIGNUM *A 입력 값의 배열 크기 최적화 \n
 * - A->Top != A->Length 인 경우 메모리 재할당 (A->Top == A->Length) \n
 * - BIGNUM *A 가 빈 배열이면 메모리 할당
 * @param[in, out] BIGNUM *A
 * @date 2017. 04. 17. \n
 * @todo 경우 더 생각해보기
 */
void BN_Top_Check(BIGNUM *A)
{	
	// TODO 

	// BIGNUM *A 의 메모리가 할당되지 않은 경우
	if(A->Top == 0)
		BN_Init_Zero(A);
	
	// 실제 할당된 배열 크기와 값이 들어있는 배열 크기 다르면 재할당
	if((A->Top != A->Length) && (A->Length != 0))
		BN_Realloc_Mem(A, A->Length);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Result size check of BIGNUM *A
 * @details
 * - 연산의 결과 값의 배열 크기 체크 \n
 * - A->Top 크기가 입력된 연산의 출력 크기 보다 작으면 메모리 재할당 \n
 * - BIGNUM *A 가 빈 배열이면 메모리 할당
 * @param[in, out] BIGNUM *A
 * @date 2017. 04. 17. \n
 * @todo 경우 더 생각해보기
 */
void BN_Result_Size(BIGNUM *A, const UNWORD size)
{	
	// TODO 

	// BIGNUM *A 의 메모리가 할당되지 않은 경우
	if(A->Top == 0)
		BN_Init_Zero(A);
	else if(A->Top < size) // (A->Top >= size) 인 경우 재할당 X
		BN_Realloc_Mem(A, size); // 
}

/**
 * @brief Optimize Output of BIGNUM *A
 * @details
 * - BIGNUM *A 값의 크기 최적화 출력 (Memory, Length)
 * - BIGNUM *A 가 0 인 경우 *A 의 Sign = ZERO
 * - 최상위 WORD 부터 값이 0 인지 체크
 * @param[in, out] BIGNUM *A
 * @date 2017. 04. 17. \n
 * @todo 경우 더 생각해보기
 */
void BN_Optimize(BIGNUM *A)
{
	// TODO
	
	// 빈 배열 체크
	while(A->Num[A->Length - 1] == 0)
		A->Length--;

	// 실제 할당된 배열 크기와 값이 들어있는 배열 크기 다르면 재할당
	if((A->Top != A->Length) && (A->Top != 0))
		BN_Realloc_Mem(A, A->Length); // A->Top = A->Length 세팅
	
	//실제 *A 에 저장된 값이 0 인 경우  
	if((A->Length == 1) && (A->Num[0] == 0))
	{	
		A->Length = 0;
		A->Sign = ZERO; 
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Free BIGNUM Memory
 * @details
 * - BIGNUM WORD 배열 동적할당 해제 \n
 * - 0 초기화 없이 단순 메모리 할당 해제 \n
 * - Num = NULL, Top = 0, Length = 0 , Sign = 0, Flag = DEFAULT \n
 * @param[in,out] BIGNUM *A 
 * @date 2017. 04. 17. \n
 */
void BN_Free(BIGNUM *A)
{
	free(A->Num);
	A->Num = NULL;
	A->Top = 0;
	A->Length = 0;
	A->Sign = ZERO;
	A->Flag = DEFAULT;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Zero Free BIGNUM Memory
 * @details
 * - BIGNUM WORD 배열 동적할당 해제 \n
 * - 값을 0 으로 초기화 한 후 메모리 할당 해제 \n
 * - Num = NULL, Top = 0, Length = 0 , Sign = 0, Flag = DEFAULT \n
 * @param[in,out] BIGNUM *A 
 * @date 2017. 04. 17. \n
 */
void BN_Zero_Free(BIGNUM *A)
{
	while(A->Top > 0)
	{
		A->Num[(A->Top - 1)] = 0;
		A->Top--;
	}
	BN_Free(A);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief BIGNUM n-bit Right Shift  
 * @details
 * - BIGNUM *A 오른쪽으로 n 비트 시프트 \n
 * - 외부에서 결과 값 저장 할 BIGNUM *R 생성해서 입력 \n
 * - BN_RShift_Bit(R, R, s_bit) 가능
 * @param[out] BIGNUM *R 
 * @param[in] BIGNUM *A 
 * @param[in] s_bit (const) // shift bit
 * @date 2017. 04. 17. \n
 * @todo sage 에서 음수 일 때 쉬프트 문제...
 */
void BN_RShift_Bit(BIGNUM *R, BIGNUM *A, const UNWORD s_bit)
{
	UNWORD i;
	UNWORD tmp_word;
	UNWORD tmp_bit = s_bit;

	BN_Top_Check(A);
	// R = A 인 경우 재할당 X , Ex) BN_RShift_Bit(R, R, shift);
	BN_Result_Size(R, A->Top);
	
	// Right Shift 값이 현재 할당된 배열 보다 크면 결과는 0
	if(s_bit > (A->Length * BIT_LEN))
		BN_Zero(R);
	else
	{
		if(s_bit >= BIT_LEN) // s_bit >= BIT_LEN (워드 이동)
		{
			tmp_word = UW_Div(s_bit, BIT_LEN);		// Move word
			tmp_bit = UW_Mod(s_bit, BIT_LEN);		// New shift bits
			// WORD 이동
			for(i = 0 ; i < A->Length - tmp_word ; i++)
				R->Num[i] = A->Num[i + tmp_word];
			// 이동된 나머지 WORD = 0 채우기
			for( ; i < A->Length ; i++)
				R->Num[i] = 0;
			// 연산 후 길이
			R->Length = A->Length - tmp_word;
		}
		else
		{
			for(i = 0 ; i < A->Length ; i++)
				R->Num[i] = A->Num[i];
			// 연산 후 길이
			R->Length = A->Length;
		}		
		if(tmp_bit != 0) // tmp_bit == 0 인 경우 WORD 이동만
		{
			// s_bit < BIT_LEN 인 상태 
			for(i = 0 ; i < (R->Length - 1) ; i++) 
				R->Num[i] = (R->Num[i + 1] << (BIT_LEN - tmp_bit)) ^ (R->Num[i] >> tmp_bit);
			// 최상위 WORD 처리 (i = A->Num[A->Top - 1] 일 때)
			R->Num[i] >>= tmp_bit;
		}
		R->Top = A->Top;
		R->Sign = A->Sign;
		R->Flag = A->Flag;
	}
	BN_Optimize(R);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief BIGNUM n-bit Light Shift  
 * @details
 * - BIGNUM *A 왼쪽으로 n 비트 시프트 \n
 * - 외부에서 결과 값 저장 할 BIGNUM *R 생성해서 입력 \n
 * @param[out] BIGNUM *R 
 * @param[in] BIGNUM *A 
 * @param[in] s_bit (const) // shift bit
 * @date 2017. 04. 13. v1.00 \n
 */
void BN_LShift_Bit(BIGNUM *R, BIGNUM *A, const UNWORD s_bit)
{
	SNWORD i;
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
		BN_Result_Size(R, (A->Length + tmp_word + 1));		
		R->Num[R->Length - 1] = 0;					  // 최상위 배열 빈 상태 유지 (Shift carry 고려)
		for(i = R->Length - 1 ; i > tmp_word ; i--)
			R->Num[i - 1] = A->Num[i - 1 - tmp_word]; // Range : [(R->Length - 2), tmp_word]
		for( ; i > 0 ; i--)							  
			R->Num[i - 1] = 0;						  // Range : [(tmp_word - 1), 0]
	}
	else // zero_cnt >= tmp_bit(조정)
	{
		BN_Result_Size(R, (A->Length + tmp_word));		
		for(i = R->Length ; i > tmp_word ; i--)
			R->Num[i - 1] = A->Num[i - 1 - tmp_word]; // Range : [(R->Length - 2), tmp_word]
		for( ; i > 0 ; i--)							  
			R->Num[i - 1] = 0;						  // Range : [(tmp_word - 1), 0]
	}

	if(tmp_bit != 0) // tmp_bit == 0 인 경우 WORD 이동만 필요
	{
		// s_bit < zero_cnt 인 상태 
		for(i = R->Length - 1 ; i > 0 ; i--) 
			R->Num[i] = (R->Num[i] << tmp_bit) ^ (R->Num[i - 1] >> (BIT_LEN - tmp_bit));
		// 최하위 WORD 처리 (i = A->Num[0] 일 때)
		R->Num[i] <<= tmp_bit;
	}
		
	// 연산 후 길이
	R->Length = R->Top;	
	// R 설정 동일하게
	R->Sign = A->Sign;
	R->Flag = A->Flag;
	BN_Optimize(R);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief BIGNUM *A is Zero ?
 * @details 
 * - BIGNUM *A 가 Zero 인지 아닌지 판단 \n
 * @param[in] BIGNUM *A (const)
 * @return SNWORD TRUE/FALSE
 * @date 2017. 04. 17. \n
 */
SNWORD BN_IsZero(const BIGNUM *A)
{	
	UNWORD tmp = A->Length;	
	while(tmp != 0)
	{
		if(A->Num[tmp - 1] == 0)
			tmp--;
		else
			break;
	}
	if(tmp == 0)
		return TRUE;
	else
		return FALSE;	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Absolute Value Compare BIGNUM *A to BIGNUM *B
 * @details
 * - Top 비교 하지 않고 Length 비교 (실제 값 크기)
 * - BIGNUM *A 값과 BIGNUM *B 값 절대값 크기 비교 (Length, WORD Num 값)\n
 * - BIGNUM *A 기준으로 A > B -> return LARGE(1) \n
 * - 1) Length 비교 후 \n
 * - 2) 최상위 Num WORD부터 값 비교 \n
 * @param[in] BIGNUM *A (const)
 * @param[in] BIGNUM *B (const)
 * @return LARGE(1), EQUAL(0), SMALL(-1)
 * @date 2017. 03. 28. v1.00 \n
 * @todo input optimize 문제 
 */
SNWORD BN_Abs_Cmp(const BIGNUM *A, const BIGNUM *B)
{
	SNWORD i;
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
SNWORD BN_Cmp(const BIGNUM *A, const BIGNUM *B)
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
	
	printf("%s0x", (A->Sign == -1) ? "-" : "+");
	for(i = A->Top ; i > 0 ; i--)
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
	fprintf(fp, "%s0x", (A->Sign == -1) ? "-" : "+");
	for(i = A->Top ; i > 0 ; i--)
		fprintf(fp, "%08X", A->Num[i - 1]);
}

/**
 * @brief Euclidean algorithm of BIGNUM (GCD)
 * @details
 * - BIGNUM *A, *B : Positive Integer
 * - BIGNUM *A 와 *B 의 최대공약수 BIGNUM *R 계산
 * - Lecture Note 참고
 * @param[in] BIGNUM *A (const)
 * @param[in] BIGNUM *B (const)
 * @param[out] BIGNUM *R 
 * @date 2017. 04. 17. \n
 * @todo 보류 (Division 필요)
 */
/*
void BN_Euclidean_GCD(BIGNUM *R, BIGNUM *A, BIGNUM *B)
{	
	// division 필요.. 추후 구현
}
*/
/**
 * @brief Extended Euclidean algorithm of BIGNUM (GCD)
 * @details
 * - Lecture Note 참고
 * @param[out] BIGNUM *R 
 * @param[out] BIGNUM *X 
 * @param[out] BIGNUM *Y 
 * @param[in] BIGNUM *A (const)
 * @param[in] BIGNUM *B (const)
 * @date 2017. 04. 17. \n
 * @todo 보류 (Division 필요)
 */
 /*
void BN_Ext_Euclidean_GCD(BIGNUM *R, BIGNUM *X, BIGNUM *Y, BIGNUM *A, BIGNUM *B)
{	
	// division 필요.. 추후 구현
}
*/
/**
 * @brief BIGNUM Binary GCD algorithm 
 * @details
 * - BIGNUM *A, *B : Positive Integer
 * - BIGNUM *A 와 *B 의 최대공약수 BIGNUM *R 계산
 * - Lecture Note 참고
 * @param[out] BIGNUM *R 
 * @param[in] BIGNUM *A (const)
 * @param[in] BIGNUM *B (const)
 * @date 2017. 04. 19. \n
 * @todo 검증 X
 */
void BN_Binary_GCD(BIGNUM *R, BIGNUM *A, BIGNUM *B)
{	
	BIGNUM t0, t1, t2;
	BN_Init_Copy(&t0, A);
	BN_Init_Copy(&t1, B);
	BN_Init_One(&t2);

	while(((t0.Num[0] & 1) == 0) && ((t1.Num[0] & 1) == 0))
	{
		BN_RShift_Bit(&t0, &t0, 1);
		BN_RShift_Bit(&t1, &t1, 1);
		BN_LShift_Bit(&t2, &t2, 1);
	}
	while(BN_IsZero(&t1) == FALSE)
	{
		while((t0.Num[0] & 1) == 0)
			BN_RShift_Bit(&t0, &t0, 1);
		while((t1.Num[0] & 1) == 0)
			BN_RShift_Bit(&t1, &t1, 1);
		if(!(BN_Cmp(&t1, &t0) == SMALL)) // (t1 >= t0) == !(t1 < t0) 
			BN_Abs_Sub(&t1, &t1, &t0);
		else // (t0 > t1)
			BN_Abs_Sub(&t0, &t0, &t1);
	}
	BN_Mul(R, &t0, &t2);

	BN_Zero_Free(&t0);
	BN_Zero_Free(&t1);
	BN_Zero_Free(&t2);
}

/**
 * @brief BIGNUM Extended Binary GCD algorithm 
 * @details
 * - BIGNUM *R = gcd(A, B), BIGNUM *X and *Y s.t. AX + BY = gcd(A, B) \n
 * - BIGNUM *A, *B : Positive Integer \n
 * - Lecture Note 참고 \n
 * @param[out] BIGNUM *R 
 * @param[out] BIGNUM *X 
 * @param[out] BIGNUM *Y 
 * @param[in] BIGNUM *A (const)
 * @param[in] BIGNUM *B (const)
 * @date 2017. 04. 19. \n
 * @todo 검증 X
 */
void BN_Ext_Binary_GCD(BIGNUM *R, BIGNUM *X, BIGNUM *Y, BIGNUM *A, BIGNUM *B)
{	
	BIGNUM t0, t1, t2;
	BIGNUM a, b, u0, u1, v0, v1;

	BN_Init_Copy(&t0, A);
	BN_Init_Copy(&t1, B);
	BN_Init_One(&t2);

	while(((t0.Num[0] & 1) == 0) && ((t1.Num[0] & 1) == 0))
	{
		BN_RShift_Bit(&t0, &t0, 1);
		BN_RShift_Bit(&t1, &t1, 1);
		BN_LShift_Bit(&t2, &t2, 1);
	}

	BN_Init_Copy(&a, &t0);
	BN_Init_Copy(&b, &t1);
	BN_Init_One(&u0);
	BN_Init_Zero(&v0);
	BN_Init_Zero(&u1);
	BN_Init_One(&v1);

	while(BN_IsZero(&t0) == FALSE)
	{
		while((t0.Num[0] & 1) == 0)
		{
			BN_RShift_Bit(&t0, &t0, 1);
			if(((u0.Num[0] & 1) == 0) && ((v0.Num[0] & 1) == 0))
			{
				BN_RShift_Bit(&u0, &u0, 1);
				BN_RShift_Bit(&v0, &v0, 1);
			}
			else
			{
				BN_Add(&u0, &u0, &b);
				BN_RShift_Bit(&u0, &u0, 1);
				BN_Sub(&v0, &v0, &a);
				BN_RShift_Bit(&v0, &v0, 1);
			}
		}
		while((t1.Num[0] & 1) == 0)
		{
			BN_RShift_Bit(&t1, &t1, 1);
			if(((u1.Num[0] & 1) == 0) && ((v1.Num[0] & 1) == 0))
			{
				BN_RShift_Bit(&u1, &u1, 1);
				BN_RShift_Bit(&v1, &v1, 1);
			}
			else
			{
				BN_Add(&u1, &u1, &b);
				BN_RShift_Bit(&u1, &u1, 1);
				BN_Sub(&v1, &v1, &a);
				BN_RShift_Bit(&v1, &v1, 1);
			}
		}
		if(!(BN_Cmp(&t0, &t1) == SMALL)) // (t0 >= t1) == !(t0 < t1) 
		{
			BN_Sub(&t0, &t0, &t1);
			BN_Sub(&u0, &u0, &u1);
			BN_Sub(&v0, &v0, &v1);
		}
		else // (t1 > t0)
		{
			BN_Sub(&t1, &t1, &t0);
			BN_Sub(&u1, &u1, &u0);
			BN_Sub(&v1, &v1, &v0);
		}
	}

	BN_Mul(R, &t1, &t2);
	BN_Copy(X, &u1);
	BN_Copy(Y, &v1);

	BN_Zero_Free(&t0);
	BN_Zero_Free(&t1);
	BN_Zero_Free(&t2);
	BN_Zero_Free(&a);
	BN_Zero_Free(&b);
	BN_Zero_Free(&u0);
	BN_Zero_Free(&v0);
	BN_Zero_Free(&u1);
	BN_Zero_Free(&v1);
}

/**
 * @brief A^(-1) by Extended Binary GCD algorithm 
 * @details
 * - BIGNUM *R = A^(-1) mod p \n
 * - BIGNUM *A : Positive Integer, *P : Prime \n
 * - Lecture Note(틀림?) & Guide to ECC p.41 참고 \n
 * @param[out] BIGNUM *R 
 * @param[in] BIGNUM *A (const)
 * @param[in] BIGNUM *P (const)
 * @date 2017. 04. 19. \n
 * @todo 검증 X
 */
void BN_Ext_Binary_Inv(BIGNUM *R, BIGNUM *A, BIGNUM *P)
{	
	BIGNUM t0, t1;
	BIGNUM u0, u1;

	BN_Init_Copy(&t0, A);
	BN_Init_Copy(&t1, P);
	BN_Init_One(&u0);
	BN_Init_Zero(&u1);

	while(BN_IsZero(&t0) == FALSE)
	{
		while((t0.Num[0] & 1) == 0)
		{
			BN_RShift_Bit(&t0, &t0, 1);
			if((u0.Num[0] & 1) == 0)
				BN_RShift_Bit(&u0, &u0, 1);
			else
			{
				BN_Add(&u0, &u0, P);
				BN_RShift_Bit(&u0, &u0, 1);
			}
		}
		while((t1.Num[0] & 1) == 0)
		{
			BN_RShift_Bit(&t1, &t1, 1);
			if((u1.Num[0] & 1) == 0)
				BN_RShift_Bit(&u1, &u1, 1);
			else
			{
				BN_Add(&u1, &u1, P);
				BN_RShift_Bit(&u1, &u1, 1);
			}
		}
		if(!(BN_Cmp(&t0, &t1) == SMALL)) // (t0 >= t1) == !(t0 < t1) 
		{
			BN_Sub(&t0, &t0, &t1);
			BN_Sub(&u0, &u0, &u1);
		}
		else // (t1 > t0)
		{
			BN_Sub(&t1, &t1, &t0);
			BN_Sub(&u1, &u1, &u0);
		}
	}
	
	BN_Copy(R, &u1);

	BN_Zero_Free(&t0);
	BN_Zero_Free(&t1);
	BN_Zero_Free(&u0);
	BN_Zero_Free(&u1);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Absolute Add BIGNUM *A and BIGNUM *B
 * @details
 * - BIGNUM *A 와 BIGNUM *B 를 더해서 BIGNUM *R 출력
 * - BN_Abs_Add() 함수 조건(Length) : A >= B  
 * - Sign 구분 없이 WORD 덧셈 -> R = |A| + |B|
 * - *R 의 최대 크기 : A.Length + 1
 * @param[out] BIGNUM *R
 * @param[in] BIGNUM *A 
 * @param[in] BIGNUM *B 
 * @date 2017. 04. 17. \n
 */
void BN_Abs_Add(BIGNUM *R, BIGNUM *A, BIGNUM *B)
{	
	UNWORD i;
	UNWORD carry = 0;		// 초기 Carry = 0
	UNWORD tmp1, tmp2;
		
	// R 크기가 |A| + |B| 결과보다 작으면 재할당 
	BN_Result_Size(R, A->Top + 1);
	
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
	// BIGNUM 최적화
	BN_Optimize(R);	
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
 * @param[in] BIGNUM *A 
 * @param[in] BIGNUM *B 
 * @date 2017. 04. 17. \n
 */
void BN_Abs_Sub(BIGNUM *R, BIGNUM *A, BIGNUM *B)
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
	BN_Optimize(R);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Add BIGNUM *A and BIGNUM *B
 * @details
 * - BIGNUM *A 와 BIGNUM *B 를 더해서 BIGNUM *R 출력
 * - 부호 구분 가능
 * - WORD 덧셈 -> R = A + B
 * @param[out] BIGNUM *R
 * @param[in] BIGNUM *A 
 * @param[in] BIGNUM *B 
 * @date 2017. 04. 17. \n
 */
void BN_Add(BIGNUM *R, BIGNUM *A, BIGNUM *B)
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

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Subtract BIGNUM *B from BIGNUM *A
 * @details
 * - BIGNUM *A 에서 BIGNUM *B 를 빼서 BIGNUM *R 출력
 * - 부호 구분 가능
 * - WORD 뺄셈 -> R = A - B
 * @param[out] BIGNUM *R
 * @param[in] BIGNUM *A 
 * @param[in] BIGNUM *B 
 * @date 2017. 04. 17. \n
 */
void BN_Sub(BIGNUM *R, BIGNUM *A, BIGNUM *B)
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

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Multiply BIGNUM *A and BIGNUM *B
 * @details
 * - BIGNUM *A 와 BIGNUM *B 를 곱한 결과 BIGNUM *R 출력
 * - 기본 곱셈 방법 적용
 * - 부호 구분 가능
 * - WORD 곱셈 -> R = A * B
 * @param[out] BIGNUM *R
 * @param[in] BIGNUM *A 
 * @param[in] BIGNUM *B 
 * @date 2017. 04. 17. \n
 */
void BN_Basic_Mul(BIGNUM *R, BIGNUM *A, BIGNUM *B)
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
	BN_Optimize(R);			
}

/**
 * @brief Multiply BIGNUM *A and BIGNUM *B by Karatsuba Multiplication
 * @details
 * - BIGNUM *A 와 BIGNUM *B 를 곱한 결과 BIGNUM *R 출력
 * - 기본 곱셈 방법 적용
 * - 부호 구분 가능
 * - WORD 곱셈 -> R = A * B
 * @param[out] BIGNUM *R
 * @param[in] BIGNUM *A 
 * @param[in] BIGNUM *B 
 * @date 2017. 04. 17. \n
 * @todo TEST Vector 맞춰야 함 / input optimize 조건
 */
void BN_Kara_Mul(BIGNUM *R, BIGNUM *A, BIGNUM *B)
{
	BIGNUM u0, v0, u1, v1;					// 구조체만 이용 (A 의 Num 사용)
	BIGNUM us, vs, u0v0, u1v1, usvs, tmp1, tmp2;	// BIGNUM 생성해서 이용
	
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
		BN_Init(&tmp1, (us.Length + vs.Length), PLUS, DEFAULT);
		
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
		BN_Abs_Sub(&tmp1, &usvs, &u1v1);
		BN_Zeroize(&usvs);
		BN_Abs_Sub(&usvs, &tmp1, &u0v0);

		// R = (u1v1)^2q + (usvs)^q + u0v0
		// R += u0v0
		BN_Zero_Realloc_Mem(&tmp1, u0v0.Length + 1);
		BN_Init_Zero(&tmp2); 
		R->Length = u0v0.Length + 1; // carry 고려하여 길이 + 1
		BN_Abs_Add(R, &tmp2, &u0v0);
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
		BN_Zero_Free(&tmp1);
		BN_Zero_Free(&tmp2);
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
 * @param[in] BIGNUM *A 
 * @param[in] BIGNUM *B 
 * @date 2017. 04. 17. \n
 * @todo 조건 필요
 */
void BN_Mul(BIGNUM *R, BIGNUM *A, BIGNUM *B)
{
	BN_Kara_Mul(R, A, B);
	//BN_Basic_Mul(R, A, B);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Square BIGNUM *A 
 * @details
 * - BIGNUM *A 의 제곱 결과 BIGNUM *R 출력
 * - 곱셈 보다 UNWORD 곱의 수 적음
 * - 부호 구분 가능
 * - WORD 곱셈 -> R = (A)^2
 * @param[out] BIGNUM *R
 * @param[in] BIGNUM *A 
 * @date 2017. 03. 28. v1.00 \n
 */
void BN_Sqr(BIGNUM *R, BIGNUM *A)
{
	UNWORD i, j, n;
	UNWORD carry = 0;
	UNWORD tmp[3];
	UNWORD m0, m1;
			
	if((A->Length == 1 && A->Num[0] == 0) || (A->Length == 0)) // A 가 0 인 경우
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
	BN_Optimize(R);	
}

/**
 * @brief Barret Reduction of BIGNUM (Modulus)
 * @details
 * - A mod N ,where 0 <= A < W^(2n), W^(n-1) <= N < W^n and T = Ceil((W^2n) / M) \n
 * - Lecture Note 참고 \n
 * @param[out] BIGNUM *R 
 * @param[in] BIGNUM *A (const)
 * @param[in] BIGNUM *N (const)
 * @param[in] BIGNUM *T (const & Precomputation)
 * @date 2017. 03. 29. v1.00 \n
 * @todo 아직 미완성
 */
void BN_Bar_Redc(BIGNUM *R, BIGNUM *A, BIGNUM *N, BIGNUM *T)
{	
	BIGNUM qh, qh_n;				
	BIGNUM tmp1, tmp2;				
	//UNWORD W = BIT_LEN;		// W = 2^(w), W : WORD 1개 크기 or 프로세서 단위 
	UNWORD n = N->Length;	// n = Ceil(log_W(N)) + 1
	
	// 확인사항
	// Input 조건 따져줘야 하나 ? -> P >= 3 
	// Z == P 인 경우는 ??
	// R 크기 문제
	// Reduction 결과 최적화 문제 ?

	// BIGNUM 연산 최대 크기 고려	
	
	// A < N 인 경우 -> Reduction 필요 X
	if(BN_Abs_Cmp(A, N) == SMALL)
		BN_Copy(R, A); 
	else // A > N 인 경우 Reduction 수행
	{	
		// tmp1 = Ceil(A / W^(n-1)) 계산 (워드 단위 >> 쉬프트 연산)
		tmp1.Num = A->Num + (n - 1); // 기준 포인터 위치 변경
		tmp1.Length = A->Length - (n - 1); 
		tmp1.Sign = PLUS; 
		
		// Ceil(A / W^(n-1)) * T
		BN_Init(&qh, (tmp1.Length + T->Length), PLUS, DEFAULT); 
		BN_Mul(&qh, &tmp1, T);

		// Ceil(qh / W^(n+1)) 계산 (워드 단위 >> 쉬프트 연산)
		qh.Num += (n + 1); 
		qh.Length -= (n + 1);

		// A mod W^(n+1) : n + 1 보다 작은 배열만 살림
		tmp1.Num = A->Num;
		tmp1.Length = n; // mod
		
		// (N * qh) mod W^(n+1)
		BN_Init(&qh_n, (qh.Length + N->Length), PLUS, DEFAULT);
		BN_Mul(&qh_n, &qh, N);
		if(qh_n.Length > n)  
			qh_n.Length = n; // mod

		// A mod W^(n+1) - (qh * N) mod W^(n+1)
		BN_Init(&tmp2, n, PLUS, DEFAULT);
		BN_Sub(&tmp2, &tmp1, &qh_n); // tmp2 = R
		
		BN_Init(&tmp1, n + 1, PLUS, DEFAULT);		// n 개 tmp1.Num 배열 -> 0 으로 초기화
		// R 이 음수 -> A += W^(n+1)
		if(tmp2.Sign == MINUS)
		{			
			tmp1.Num[n - 1] = 1;					// 최상위 워드 = 1 : W^(n+1) ex) 0x10..0 
			BN_Add(R, &tmp2, &tmp1);
			if(BN_Abs_Cmp(R, N) != MINUS) // 아래 while문 때문에 추가
				BN_Copy(&tmp2, R); 
		}
		// R >= N 이면 -> R - N 반복 (최대 2번)
		while(BN_Abs_Cmp(&tmp2, N) != MINUS)
		{
			BN_Sub(R, &tmp2, N);
			if(BN_Abs_Cmp(R, N) != MINUS) // 조건 만족하면 while문 한 번 더 반복
				BN_Copy(&tmp2, R);
		}
		
	}

	BN_Zero_Free(&qh);
	BN_Zero_Free(&qh_n);		
	BN_Zero_Free(&tmp1);
	BN_Zero_Free(&tmp2);

	// output optimize

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
 /*
void BN_Mont_Redc(BIGNUM *T, const BIGNUM *N, const BIGNUM *R, const UNWORD Np, const BIGNUM *U)
{	
	
}
*/