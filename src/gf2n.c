/**
 * @file galoisfield.c
 * @brief 
 * @details 
 * - Initialize
 * - degree
 * - Zeroize
 * - Randomize
 * - Free
 * - Reallocation
 * - Compare
 * - Copy
 * - Addition
 * - Multiplication
 * - Modular
 * - inversion
 * @date 2017. 04. 20.
 * @author YoungJin CHO
 * @version 1.00
 */
#include "gf2n.h"
#include "word.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Initialize to GF(2^n)
 * @details 
 * - 메모리 함수 내부에서 할당 \n
 * - Get GF2N struct (Num, Length, Flag) -> Generate GF2N \n
 * @param[in,out] GF2N *A 
 * @param[in] UNWORD len (const) 길이
 * @param[in] SNWORD flag (const) 최적화 옵션
 * @date 2017. 04. 20. \n
 */
void GF2N_Init(GF2N *A, const UNWORD len, const SNWORD flag)
{
	A->Num = (UNWORD *)calloc(len, sizeof(UNWORD)); 
	A->Top = A->Length = len; 
	A->Sign = PLUS;	// Default (PLUS)
	A->Flag = flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Initialize to Zero GF2N
 * @details
 * - 메모리 함수 내부에서 할당 \n
 * - Generate Zero GF2N \n
 * - Length = 1, Sign = ZERO, Flag = DEFAULT \n
 * @param[in,out] GF2N *A  
 * @date 2017. 04. 20. \n
 */
void GF2N_Init_Zero(GF2N *A)
{	
    A->Num = (UNWORD *)calloc(1, sizeof(UNWORD));
	A->Top = 1;			// 실제 할당된 배열 크기
	A->Length = 0; 		// 값이 들어있는 배열 크기
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
 * @date 2017. 04. 20. \n
 */
void GF2N_Init_One(GF2N *A)
{	
	A->Num = (UNWORD *)calloc(1, sizeof(UNWORD));
	A->Num[0] = 1;
	A->Top = A->Length = 1; 
	A->Sign = PLUS;
	A->Flag = DEFAULT;
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
 * @date 2017. 04. 20. \n
 */
void GF2N_Init_Rand(GF2N *A, const UNWORD maxsize)
{
	UNWORD rlen = (rand() % maxsize) + 1; 
	GF2N_Init(A, rlen, DEFAULT); 
	GF2N_Randomize(A);
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
 * @date 2017. 04. 20. \n
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
	GF2N_Optimize(A);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Zero GF2N
 * @details 
 * - GF2N *A 를 ZERO 로 변경 \n
 * - 메모리 재할당 (크기 변경), Length = 1 \n
 * @param[in,out] GF2N *A 
 * @date 2017. 04. 20. \n
 */
void GF2N_Zero(GF2N *A)
{	
	GF2N_Zeroize(A);
	A->Num = (UNWORD *)realloc(A->Num, sizeof(UNWORD)); 
    A->Top = 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Zeroize GF2N
 * @details 
 * - GF2N 값만 0 으로 변경 (Top, Flag 변경 X) \n
 * @param[in,out] GF2N *A 
 * @date 2017. 04. 20. \n
 */
void GF2N_Zeroize(GF2N *A)
{	
	UNWORD i;
	for(i = 0 ; i < A->Top ; i++)
		A->Num[i] = 0;	
	A->Length = 0;
	A->Sign = ZERO;
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
	if(R->Top != A->Top)
		GF2N_Zero_Realloc_Mem(R, A->Length);
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
 * @brief Memory Reallocate GF2N *A
 * @details
 * - 입력 받은 사이즈 이상의 값은 0 초기화 \n
 * - 나머지 값은 기존의 값 유지 \n
 * - GF2N *A 메모리를 입력받은 크기와 동일하게 재할당 \n
 * @param[out] GF2N *A
 * @param[in] UNWORD size (const)
 * @date 2017. 04. 20. v1.00 \n
 */
void GF2N_Realloc_Mem(GF2N *A, const UNWORD size)
{	
	UNWORD i;	
	if(size == 0)
		GF2N_Zero(A);
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
 * @brief Zero Data and Memory Reallocate GF2N *A
 * @details
 * - GF2N *A 메모리를 입력받은 크기와 동일하게 재할당 \n
 * - 모든 값을 0 으로 변경 \n
 * - 크기가 같아도 값 0 으로 변경
 * @param[out] GF2N *A
 * @param[in] UNWORD size (const)
 * @date 2017. 04. 20. \n
 */
void GF2N_Zero_Realloc_Mem(GF2N *A, const UNWORD size)
{	
	// 입력 받은 크기 만큼 메모리 재할당
	if(A->Top != size)
		GF2N_Realloc_Mem(A, size);
	// 재할당된 메모리 0 으로 초기화
	GF2N_Zeroize(A);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Top Check of GF2N *A
 * @details
 * - GF2N *A 입력 값의 배열 크기 최적화 \n
 * - A->Top != A->Length 인 경우 메모리 재할당 (A->Top == A->Length) \n
 * - BIGNUM *A 가 빈 배열이면 메모리 할당 \n
 * @param[in, out] GF2N *A
 * @date 2017. 04. 20. \n
 * @todo 경우 더 생각해보기
 */
void GF2N_Top_Check(GF2N *A)
{
	// TODO 

	// BIGNUM *A 의 메모리가 할당되지 않은 경우
	if(A->Top == 0)
		GF2N_Init_Zero(A);
	
	// 실제 할당된 배열 크기와 값이 들어있는 배열 크기 다르면 재할당
	if((A->Top != A->Length) && (A->Length != 0))
		GF2N_Realloc_Mem(A, A->Length);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Result size check of GF2N *A
 * @details
 * - 연산의 결과 값의 배열 크기 체크 \n
 * - A->Top 크기가 입력된 연산의 출력 크기 보다 작으면 메모리 재할당 \n
 * - GF2N *A 가 빈 배열이면 메모리 할당
 * @param[in, out] GF2N *A
 * @date 2017. 04. 20. \n
 * @todo 경우 더 생각해보기
 */
void GF2N_Result_Size(GF2N *A, const UNWORD size)
{	
	// TODO 

	// GF2N *A 의 메모리가 할당되지 않은 경우
	if(A->Top == 0)
		GF2N_Init_Zero(A);
	else if(A->Top < size) // (A->Top >= size) 인 경우 재할당 X
		GF2N_Realloc_Mem(A, size); // 
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Optimize Output of GF2N *A
 * @details
 * - GF2N *A 값의 크기 최적화 출력 (Memory, Length)
 * - GF2N *A 가 0 인 경우 *A 의 Sign = ZERO
 * - 최상위 WORD 부터 값이 0 인지 체크
 * @param[in, out] GF2N *A
 * @date 2017. 04. 20. \n
 */
void GF2N_Optimize(GF2N *A)
{
	// TODO
	
	// 빈 배열 체크
	while(A->Num[A->Length - 1] == 0)
		A->Length--;

	// 실제 할당된 배열 크기와 값이 들어있는 배열 크기 다르면 재할당
	if((A->Top != A->Length) && (A->Top != 0))
		GF2N_Realloc_Mem(A, A->Length); // A->Top = A->Length 세팅
	
	//실제 *A 에 저장된 값이 0 인 경우  
	if((A->Length == 1) && (A->Num[0] == 0))
	{	
		A->Length = 0;
		A->Sign = ZERO; 
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Free GF2N Memory
 * @details
 * - GF2N Num WORD 동적할당 해제 \n
 * - 0 초기화 없이 단순 메모리 할당 해제 \n
 * - GF2N 이 Free 된 상태 => Num = NULL, Top = 0, Length = 0, Flag = DEFAULT \n
 * @param[in,out] GF2N *A 
 * @date 2017. 04. 20. \n
 */
void GF2N_Free(GF2N *A)
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
 * @brief Zero Free GF2N Memory
 * @details
 * - GF2N Num WORD 동적할당 해제 \n
 * - 값을 0 으로 초기화 한 후 메모리 할당 해제 \n
 * - GF2N 이 Free 된 상태 => NUM = NULL, Top = 0, Length = 0, Flag = DEFAULT \n
 * @param[in,out] GF2N *A 
 * @date 2017. 04. 20. \n
 */
void GF2N_Zero_Free(GF2N *A)
{
	while(A->Top > 0)
	{
		A->Num[(A->Top - 1)] = 0;
		A->Top--;
	}	
	free(A->Num);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief GF2N n-bit Right Shift  
 * @details
 * - GF2N *A 오른쪽으로 n 비트 시프트 \n
 * - 외부에서 결과 값 저장 할 GF2N *R 생성해서 입력 \n
 * - GF2N_RShift_Bit(R, R, s_bit) 가능
 * @param[out] GF2N *R 
 * @param[in] GF2N *A 
 * @param[in] s_bit (const) // shift bit
 * @date 2017. 04. 13. v1.00 \n
 */
void GF2N_RShift_Bit(GF2N *R, GF2N *A, const UNWORD s_bit)
{
	UNWORD i;
	UNWORD tmp_word;
	UNWORD tmp_bit = s_bit;

	GF2N_Top_Check(A);
	// R = A 인 경우 재할당 X , Ex) GF2N_RShift_Bit(R, R, shift);
	GF2N_Result_Size(R, A->Top);
	
	// Right Shift 값이 현재 할당된 배열 보다 크면 결과는 0
	if(s_bit > (A->Length * BIT_LEN))
		GF2N_Zero(R);
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
	GF2N_Optimize(R);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief GF2N n-bit Light Shift  
 * @details
 * - GF2N *A 왼쪽으로 n 비트 시프트 \n
 * - 외부에서 결과 값 저장 할 GF2N *R 생성해서 입력 \n
 * @param[out] GF2N *R 
 * @param[in] GF2N *A 
 * @param[in] s_bit (const) // shift bit
 * @date 2017. 04. 20. \n
 */
void GF2N_LShift_Bit(GF2N *R, GF2N *A, const UNWORD s_bit)
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
		GF2N_Result_Size(R, (A->Length + tmp_word + 1));		
		R->Num[R->Length - 1] = 0;					  // 최상위 배열 빈 상태 유지 (Shift carry 고려)
		for(i = R->Length - 1 ; i > tmp_word ; i--)
			R->Num[i - 1] = A->Num[i - 1 - tmp_word]; // Range : [(R->Length - 2), tmp_word]
		for( ; i > 0 ; i--)							  
			R->Num[i - 1] = 0;						  // Range : [(tmp_word - 1), 0]
	}
	else // zero_cnt >= tmp_bit(조정)
	{
		GF2N_Result_Size(R, (A->Length + tmp_word));		
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
	GF2N_Optimize(R);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief GF2N *A is Zero ?
 * @details 
 * - GF2N *A 가 Zero 인지 아닌지 판단 \n
 * @param[in] GF2N *A (const)
 * @return SNWORD TRUE/FALSE
 * @date 2017. 04. 17. \n
 */
SNWORD GF2N_IsZero(const GF2N *A)
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
 * @brief Compare GF2N *A to BIGNUM *B
 * @details
 * - GF2N *A 값과 GF2N *B 값 크기 비교 (Length, WORD Num 값) \n
 * - GF2N *A 기준으로 A > B -> return LARGE(1) \n
 * - GF2N 에서는 부호 구분 X \n
 * - 1) Length 비교 후 \n
 * - 2) 최상위 Num WORD부터 값 비교 \n
 * @param[in] GF2N *A (const)
 * @param[in] GF2N *B (const)
 * @return LARGE(1), EQUAL(0), SMALL(-1)
 * @date 2017. 04. 15. v1.00 \n
 */
SNWORD GF2N_Cmp(GF2N *A, GF2N *B)
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
 * @param[in] CF2N *A (const)
 * @date 2017. 04. 12. v1.00 \n
 */
void GF2N_Print_bin(const GF2N *A)
{
	SNWORD i, j;
	UNWORD mask;
	   
	printf("0b");
	for(i = A->Length ; i > 0 ; i--)
	{
		// 최상위 비트부터 >> 하면서 1 인 값 출력
		mask = WORD_MASK_MSB;
		j = 0;
		while(mask)
		{			
			if(A->Num[i - 1] & mask)
				printf("1");
			else
				printf("0");
			mask >>= 1;
			j++;
		}
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/**	
 * @brief File Print GF2N Binary Form
 * @details
 * - GF2N *A 를 (파일 & 콘솔창) 출력
 * - "0b101101...1001" -> Binary form
 * @param[in] FILE *fp
 * @param[in] CF2N *A (const)
 * @date 2017. 04. 12. v1.00 \n
 */
void GF2N_FPrint_bin(FILE *fp, const GF2N *A)
{
	SNWORD i, j;
	UNWORD mask;
	   
	fprintf(fp, "0b");
	for(i = A->Length ; i > 0 ; i--)
	{
		// 최상위 비트부터 >> 하면서 1 인 값 출력
		mask = WORD_MASK_MSB;
		j = 0;
		while(mask)
		{			
			if(A->Num[i - 1] & mask)
				fprintf(fp, "1");
			else
				fprintf(fp, "0");
			mask >>= 1;
			j++;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Print GF2N Polynimial Form
 * @details
 * - GF2N *A 를 (파일 & 콘솔창) 출력
 * - "x^n + ... + x^0" -> Polynomial form
 * @param[in] CF2N *A (const)
 * @date 2017. 04. 12. v1.00 \n
 */
void GF2N_Print_poly(const GF2N *A)
{
	SNWORD i, j;
	SNWORD n = 0;
	UNWORD mask;
	
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
					printf("+");
				// 다항식 차수 계산
				printf("x^%d", (BIT_LEN * i) + j);
				n = 1;
			}	
			mask >>= 1;
			j--;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief File Print GF2N Polynimial Form
 * @details
 * - GF2N *A 를 (파일 & 콘솔창) 출력
 * - "x^n + ... + x^0" -> Polynomial form
 * @param[in] File *fp
 * @param[in] CF2N *A (const)
 * @date 2017. 04. 12. v1.00 \n
 */
void GF2N_FPrint_poly(FILE *fp, const GF2N *A)
{
	SNWORD i, j;
	SNWORD n = 0;
	UNWORD mask;
	
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
					fprintf(fp, "+");
				// 다항식 차수 계산
				fprintf(fp, "x^%d", (BIT_LEN * i) + j); 
				n = 1;
			}	
			mask >>= 1;
			j--;
		}
	}
}



////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Add GF2N *A and GF2N *B
 * @details
 * - GF2N *A 와 GF2N *B 를 더해서 GF2N *R 출력
 * - GF(2) 에서는 +, - 동일 연산 부호 구분 X
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
 * @brief Divide GF2N *A by GF2N *IRR (Division)
 * @details
 * - GF2N *A 를 *IRR 로 나눈 몫과 나머지
 * - *R 의 최대 크기 = IRR 길이
 * - Lecture Note 참고
 * @param[out] GF2N *R
 * @param[in] GF2N *A 
 * @param[in] GF2N *IRR (const)
 * @date 2017. 04. 06. v1.00 \n

 */
void GF2N_Div(GF2N *Q, GF2N *R, GF2N *A, GF2N *IRR)
{
	UNWORD deg_m, deg_r;
	GF2N ft, deg_tmp;
	
	GF2N_Result_Size(Q, A->Top);
	GF2N_Result_Size(R, A->Top);
	
	GF2N_Init_One(&deg_tmp);		// 임시 deg 저장
	GF2N_Init(&ft, IRR->Length, DEFAULT);	// 임시 GF2N
	GF2N_Copy(R, A);
	
	deg_m = GF2N_Deg(IRR);	// 기약 다항식(IRR) 최고차항 m (고정)
	deg_r = GF2N_Deg(R);	// 초기 Deg(R(x))
	while(deg_r >= deg_m)
	{			
		deg_tmp.Num[0] = (deg_r - deg_m);

		GF2N_Mul(&ft, IRR, &deg_tmp, IRR);
		GF2N_Add(R, R, &ft);
		GF2N_Add(Q, Q, &deg_tmp);
		
		deg_r = GF2N_Deg(R);		
	}

	GF2N_Zero_Free(&ft);
	GF2N_Zero_Free(&deg_tmp);
	
	GF2N_Optimize(R);
	GF2N_Optimize(Q);
}
/**
 * @brief GF2N *A Modulus GF2N *IRR (Reduction)
 * @details
 * - GF2N *A 를 *IRR 로 나눈 나머지
 * - *R 의 최대 크기 = IRR 길이
 * @param[out] GF2N *R
 * @param[in] GF2N *A (const)
 * @param[in] GF2N *IRR (const)
 * @date 2017. 04. 16. \n
 */
void GF2N_Redc(GF2N *Out, GF2N *In, GF2N *Irr)
{
	SNWORD i, j;
	UNWORD m1, m2, m, n, CurPos, msb=0, msbMASK=1, msbIn=0, msbIrr=0;
	GF2N tmp, r[32];

	if(In->Length == Irr->Length)
	{
		UW_BitSearch(&msbIn,  In->Num[In->Length-1]);
		UW_BitSearch(&msbIrr, Irr->Num[Irr->Length-1]);

		if(msbIn < msbIrr)
		{
			GF2N_Copy(Out, In);
		}
	}

	// 입력값 복사
	GF2N_Init(&tmp, In->Length, DEFAULT);
	GF2N_Copy(&tmp, In);

	// 중간값 배열 할당
	for(i=0; i<32; i++)
		GF2N_Init(&r[i], Irr->Length+1, DEFAULT);

	// 기약다항식 복사
	GF2N_Copy(&r[0], Irr);

	// 기약다항식의 최상위 비트 위치 계산
	UW_BitSearch(&msb, Irr->Num[Irr->Length-1]);
	m2 = msb + ((Irr->Length-1) * 32);	
	
	// 최고차항을 제거
	msbMASK = msbMASK << msb;
	r[0].Num[Irr->Length-1] ^= msbMASK;

	while(!r[0].Num[r[0].Length-1])
		r[0].Length--;
	
	// 32개의 중간값 생성
	for(i=1; i<32; i++)
		GF2N_LShift_Bit(&r[i], &r[i-1], 1);

	// 입력의 최상위 비트 위치 계산
	msb = 0;
	UW_BitSearch(&msb, In->Num[In->Length-1]);
	m1 = msb + ((In->Length-1) * 32);
		
	// 최초 소거 위치 계산
	CurPos = (UNWORD)1 << msb;

	// 계산
	for(i=(SNWORD)m1; i>=(SNWORD)m2; i--)
	{
		if(tmp.Num[i>>5] & CurPos)
		{
			tmp.Num[i>>5] ^= CurPos;

			n = (i-m2) / 32;
			m = (i-m2) & 31;

			for(j=0; j<r[m].Length; j++)
				tmp.Num[n+j] ^= r[m].Num[j];
		}

		CurPos = CurPos >> 1;

		if(!CurPos)
			CurPos = 0x80000000;
	}

	GF2N_Copy(Out, &tmp);

	while(!Out->Num[Out->Length-1])
		Out->Length--;

	if(Out->Length == -1)
		Out->Length = 0;

	free(tmp.Num);

	for(i=0; i<32; i++)
		free(r[i].Num);
}

/**
 * @brief Multiply GF2N *A and GF2N *B (Shift-and-add)
 * @details
 * - GF2N *A 와 GF2N *B 를 곱한 결과 GF2N *R 출력
 * - Right-to-left : Shift-and-add \n
 * - Lecture Note 참고
 * - WORD 곱셈 -> R = A * B
 * @param[out] BIGNUM *R
 * @param[in] BIGNUM *A (const)
 * @param[in] BIGNUM *B (const)
 * @date 2017. 04. 07. v1.00 \n
 */
void GF2N_Mul(GF2N *Out, GF2N *In1, GF2N *In2, GF2N *Irr)
{
	GF2N T1, T2, tmpOut;
	UNWORD Mask;
	int i=0, j=0;

	if((!In1->Length) && (!In1->Num[0]))
	{
		for(i=0; i<Out->Length; i++)
			Out->Num[i] = 0;
		Out->Length = 0;
	}
	else if((!In2->Length) && (!In2->Num[0]))
	{
		for(i=0; i<Out->Length; i++)
			Out->Num[i] = 0;
		Out->Length = 0;
	}
	else if((In1->Length == 1) && (In1->Num[0] == 1))
	{
		GF2N_Copy(Out, In2);
	}
	else if((In2->Length == 1) && (In2->Num[0] == 1))
	{
		GF2N_Copy(Out, In1);
	}
	else
	{
		GF2N_Init(&T1, In1->Length+In2->Length, DEFAULT);
		GF2N_Init(&T2, In1->Length+In2->Length, DEFAULT);
		GF2N_Init(&tmpOut, In1->Length+In2->Length, DEFAULT);

		GF2N_Copy(&T1, In2);

		Mask = In1->Num[0];

		if(Mask & 1)
			GF2N_Copy(&tmpOut, In2);

		i = 0;
		while(i < In1->Length)
		{
			Mask = (i)?		(In1->Num[i]) : (In1->Num[i] >> 1);
			j    = (i)?		(0)           : (1);

			while((Mask) || (i < In1->Length-1))
			{
				GF2N_LShift_Bit(&T2, &T1, 1);
				GF2N_Redc(&T1, &T2, Irr);
				
				if(Mask & 1)
					GF2N_Add(&tmpOut, &tmpOut, &T1);

				Mask = (Mask >> 1);

				if(++j == 32)
					break;
			}

			i++;
		}

		GF2N_Redc(Out, &tmpOut, Irr);
	}
	
	GF2N_Optimize(Out);
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
 /*
void GF2N_Sqr(GF2N *R, const GF2N *A, const GF2N *IRR)
{
	
}
*/