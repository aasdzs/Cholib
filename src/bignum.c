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
 * @date 2017. 04. 04.
 * @author YoungJin CHO
 * @version 1.01
 */

#include "config.h"
#include "bignum.h"
#include "bn_operation.h"
#include "wd_operation.h"

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

/**
 * @brief Initialize to Zero BIGNUM
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

	if((rlen == 1) && (A->Num[0] == 0))
		A->Sign = ZERO; 
	else if(rlen & 1)
		A->Sign = MINUS;
	else
        A->Sign = PLUS;
}

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
	// 값 복사
	BN_Copy(R, A);
}

/**
 * @brief Zeroize BIGNUM
 * @details 
 * - BIGNUM 값을 ZERO 로 변경 \n
 * - flag(Optimize) : 메모리 재할당 (크기 변경), Length = 1 \n
 * - flag(Dafault) : 값만 0 으로 변경 (크기 변경 X) \n 
 * @param[in,out] BIGNUM *A 

 * @date 2017. 03. 28. v1.00 \n
 * @date 2017. 03. 29. v1.01 (Flag) \n 
 */
void BN_Zeroize(BIGNUM *A)
{	
	UNWORD i;

	for(i = 0 ; i < A->Length ; i++)
			A->Num[i] = 0;
	A->Sign = ZERO;			

	// 크기도 재할당
	if(A->Flag == OPTIMIZE)
	{
		A->Num = (UNWORD *)realloc(A->Num, sizeof(UNWORD));
    	A->Length = 1;
	}
}

/**
 * @brief Randomize BIGNUM
 * @details
 * - 기존에 생성된 BIGNUM 에 랜덤 값 입력 \n
 * - Length 변경 X \n
 * - 단순 TEST용, 난수성 보장 X \n
 * - flag(Optimize) : 부호 랜덤 \n
 * - flag(Dafault) : 값만 랜덤 으로 변경 (크기 변경 X) \n 
 * @param[in,out] BIGNUM *A 
 * @date 2017. 03. 28. v1.00 \n
 * @date 2017. 03. 30. v1.01 (Flag) \n
 * @todo 수정 요망
 */
void BN_Randomize(BIGNUM *A)
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
	
	// Flag(Optimize) : 부호 랜덤
	if(A->Flag == OPTIMIZE)
	{
		if((A->Length == 1) && (A->Num[0] == 0))
			A->Sign = ZERO; // 만약 랜덤 생성 값이 0 이면 Sign = ZERO
		else if(A->Num[0] & 1)
			A->Sign = MINUS;
		else
        	A->Sign = PLUS;
	}
}

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
	A->Sign = ZERO;
	A->Flag = DEFAULT;
}

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
 */
void BN_Realloc_Mem(BIGNUM *A, const UNWORD size)
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
	BN_Realloc_Mem(A, size);
	// 재할당된 부분 0 으로 초기화
	BN_Zeroize(A);	
}

/**
 * @brief Optimize Output of BIGNUM *A
 * @details
 * - BIGNUM *A 값의 크기 최적화 출력 (Memory, Length)
 * - BIGNUM *A 가 0 인 경우 *A 의 Sign = ZERO
 * - 최상위 Num WORD 부터 값이 0 인지 체크
 * @param[in, out] BIGNUM *A
 * @date 2017. 03. 28. v1.00 \n
 * @date 2017. 04. 04. v1.01 \n
 */
void BN_Optimize_Out(BIGNUM *A)
{
	// Length가 1 이상이고, 최상위 WORD 값이 0 인 경우만 재할당
	if((A->Length > 1) && (A->Num[A->Length - 1] == 0))
	{
		//  최소 A->Length 값 : 1
		while((A->Length > 1) && (A->Num[A->Length - 1] == 0))
			A->Length--;
			
		A->Num = (UNWORD *)realloc(A->Num, A->Length * sizeof(UNWORD));
	}
	
	// A->Length = 1 , A-Num[0] = 0 인 경우 Sign = ZERO 변경
	if((A->Length == 1) && (A->Num[0] == 0))
		A->Sign = ZERO; 
}

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
		
	// *R 크기와 *A 가 다르면 동일한 크기인 0 배열로 재할당
	if(R->Length != A->Length)
		BN_Zero_Realloc_Mem(R, A->Length);
	
	R->Sign = A->Sign;
	R->Flag = A->Flag;

	for(i = R->Length - 1 ; i >= 0 ; i--) 
		R->Num[i] = A->Num[i];
}

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

/**
 * @brief BIGNUM n-bit Right Shift  
 * @details
 * - BIGNUM *A 오른쪽으로 n 비트 시프트 \n
 * - BN_RShift_Bit(R, R, s_bit) 여도 문제 없음 (하위 부터 순차적 저장)\n
 * @param[out] BIGNUM *R 
 * @param[in] BIGNUM *A (const)
 * @param[in] s_bit (const)
 * @date 2017. 03. 29. v1.00 \n
 * @todo test 필요
 */
void BN_RShift_Bit(BIGNUM *R, const BIGNUM *A, const UNWORD s_bit)
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
 * @brief BIGNUM n-bit Left Shift  
 * @details
 * - BIGNUM *A 왼쪽으로 n 비트 시프트 \n
 * - BN_RShift_Bit(R, R, s_bit) 여도 문제 없음 (하위 부터 순차적 저장)\n
 * @param[out] BIGNUM *R 
 * @param[in] BIGNUM *A (const)
 * @param[in] s_bit (const)
 * @date 2017. 03. 29. v1.00 \n
 * @todo test 필요
 */
void BN_LShift_Bit(BIGNUM *R, BIGNUM *A, const UNWORD s_bit)
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
		BN_Realloc_Mem(A, (A->Length + tmp_word));
		
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

	
	BN_UNWORD_Mul(R, v, e);

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