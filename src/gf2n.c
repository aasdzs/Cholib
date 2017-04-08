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
	GF2N_Init(R, A->Length, A->Sign, A->Flag);
	// 값 복사
	GF2N_Copy(R, A);
}


/**
 * @brief Search for degree of GF2N *A
 * @details 
 * - 메모리 함수 내부에서 할당 \n
 * - Get GF2N struct (Num, Length, Flag) -> Generate GF2N \n
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

	// 크기도 재할당
	if(A->Flag == OPTIMIZE)
	{
		A->Num = (UNWORD *)realloc(A->Num, sizeof(UNWORD));
    	A->Length = 1;
	}
}


/**
 * @brief Free GF2N Memory
 * @details
 * - GF2N Num WORD 동적할당 해제
 * - 0 초기화 없이 단순 메모리 할당 해제
 * - GF2N 이 Free 된 상태 => Length = 0, Flag = 0
 * @param[in,out] GF2N *A 
 * @date 2017. 04. 07. v1.00 \n
 */
void GF2N_Free(GF2N *A)
{
	free(A->Num);
	A->Length = ZERO;
	A->Flag = DEFAULT;
}

/**
 * @brief Zero Free GF2N Memory
 * @details
 * - GF2N Num WORD 동적할당 해제
 * - 값을 0 으로 초기화 한 후 메모리 할당 해제
 * - GF2N 이 Free 된 상태 => Length = 0 , Sign = 0, Flag = 0
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

/**
 * @brief Zero Data and Memory Reallocate GF2N *A
 * @details
 * - 모든 값을 0 으로 변경 후 
 * - GF2N *A 메모리를 입력받은 크기와 동일하게 재할당
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

/**
 * @brief Optimize Output of GF2N *A
 * @details
 * - GF2N *A 값의 크기 최적화 출력 (Memory, Length)
 * - 최상위 Num WORD 부터 값이 0 인지 체크
 * @param[in, out] GF2N *A
 * @date 2017. 03. 28. v1.00 \n
 * @date 2017. 04. 04. v1.01 \n
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


/**
 * @brief GF2N n-bit Right Shift  
 * @details
 * - GF2N *A 오른쪽으로 n 비트 시프트 \n
 * - GF2N_RShift_Bit(R, R, s_bit) 여도 문제 없음 (하위 부터 순차적 저장)\n
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
		BN_Optimize_Out(R);
	
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
void GF2N_LShift_Bit(GF2N *R, const GF2N *A, const UNWORD s_bit)
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
		BN_Realloc_Mem(&A, (A->Length + tmp_word));
		
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
		BN_Optimize_Out(R);
	
}
