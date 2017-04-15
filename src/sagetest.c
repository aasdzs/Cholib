///**
// * @file sagetest.c
// * @brief Sagemath Test Function
// * @details 
// * - 각 연산마다 함수로 정의
// * - ctrl + f 를 통해 testvector 검색 가능
// * - Sagemath input form 으로 .txt 파일 출력
// * - Test 위해서 #if 0 -> #if 1 로 변경
// * - http://cloud.sagemath.com
// * @date 2017. 04. 12.
// * @author YoungJin CHO
// * @version 1.00
// */
//
//#include "config.h"
//#include "bignum.h"
//#include "gf2n.h"
//#include "word.h"
//
#define TEST_NUM 200
//

#include"benchmark.h"
#include "config.h"
#include "word.h"
#include "bignum.h"
#include "gf2n.h"


void Sage_Test_GF2N()
{
#if 0
// void GF2N_Init(GF2N *A, const UNWORD len, const SNWORD flag);
	GF2N a;
	GF2N_Init(&a, 4, DEFAULT);
	GF2N_Print_bin("GF2N_Init_bin.txt", &a);
	GF2N_Print_poly("GF2N_Init_poly.txt", &a);
	GF2N_Zero_Free(&a);
#endif 
#if 0
//void GF2N_Init_Rand(GF2N *A, const UNWORD maxsize, const UNWORD flag);
	GF2N a;
	GF2N_Init_Rand(&a, 4, DEFAULT);
	GF2N_Print_bin("GF2N_GF2N_Init_Rand_bin.txt", &a);
	GF2N_Print_poly("GF2N_GF2N_Init_Rand_poly.txt", &a);
	GF2N_Zero_Free(&a);
#endif 
#if 0
//void GF2N_Init_Zero(GF2N *A, const UNWORD maxsize, const UNWORD flag);
	GF2N a;
	GF2N_Init_Zero(&a, 4, DEFAULT);
	GF2N_Print_bin("GF2N_Init_Zero_bin.txt", &a);
	GF2N_Print_poly("GF2N_Init_Zero_poly.txt", &a);
	GF2N_Zero_Free(&a);
#endif 
#if 0
// void GF2N_Init_Copy(GF2N *R, const GF2N *A);
	GF2N a, b;
	GF2N_Init_Rand(&a, 4, DEFAULT);
	GF2N_Init_Copy(&b, &a);
	GF2N_Print_poly("GF2N_Init_Copy_poly.txt", &a);
	GF2N_Print_poly("GF2N_Init_Copy_poly.txt", &b);
	GF2N_Zero_Free(&a);
	GF2N_Zero_Free(&b);
#endif 
#if 0
// void GF2N_Zeroize(GF2N *A);
	GF2N a;
	GF2N_Init_Rand(&a, 4, DEFAULT);
	GF2N_Print_bin("GF2N_Zeroize_bin.txt", &a);
	GF2N_Print_poly("GF2N_Zeroize_poly.txt", &a);
	GF2N_Zeroize(&a);
	GF2N_Print_bin("GF2N_Zeroize_bin.txt", &a);
	GF2N_Print_poly("GF2N_Zeroize_poly.txt", &a);
	GF2N_Zero_Free(&a);
	// Optimize
	GF2N_Init_Rand(&a, 4, OPTIMIZE);
	GF2N_Print_bin("GF2N_Zeroize_bin.txt", &a);
	GF2N_Print_poly("GF2N_Zeroize_poly.txt", &a);
	GF2N_Zeroize(&a);
	GF2N_Print_bin("GF2N_Zeroize_bin.txt", &a);
	GF2N_Print_poly("GF2N_Zeroize_poly.txt", &a);
	GF2N_Zero_Free(&a);
#endif 
#if 0
// void GF2N_Copy(GF2N *R, const GF2N *A);
	GF2N a, b;
	GF2N_Init_Rand(&a, 4, DEFAULT);
	GF2N_Init_Rand(&b, 4, DEFAULT);
	GF2N_Zeroize(&b);
	GF2N_Print_bin("GF2N_Copy_bin.txt", &a);
	GF2N_Print_bin("GF2N_Copy_bin.txt", &b);
	GF2N_Copy(&b, &a);
	GF2N_Print_bin("GF2N_Copy_bin.txt", &a);
	GF2N_Print_bin("GF2N_Copy_bin.txt", &b);
	GF2N_Zero_Free(&a);
	GF2N_Zero_Free(&b);
#endif 
#if 0
// void GF2N_Realloc_Mem(GF2N *A, const UNWORD size); void GF2N_Zero_Realloc_Mem(GF2N *A, const UNWORD size);
	GF2N a;
	// GF2N_Realloc_Mem
	GF2N_Init_Rand(&a, 4, DEFAULT);
	GF2N_Print_bin("GF2N_Realloc_Mem_bin.txt", &a);
	GF2N_Realloc_Mem(&a, 1);
	GF2N_Print_bin("GF2N_Realloc_Mem_bin.txt", &a);
	GF2N_Zero_Free(&a);
	// GF2N_Zero_Realloc_Mem
	GF2N_Init_Rand(&a, 4, OPTIMIZE);
	GF2N_Print_bin("GF2N_Zero_Realloc_Mem_bin.txt", &a);
	GF2N_Zero_Realloc_Mem(&a, 1);
	GF2N_Print_bin("GF2N_Zero_Realloc_Mem_bin.txt", &a);
	GF2N_Zero_Free(&a);
#endif 
#if 0
// void GF2N_Optimize_Out(GF2N *A);
	GF2N a;
	// GF2N_Realloc_Mem
	GF2N_Init(&a, 8, OPTIMIZE);
	GF2N_Randomize(&a);
	GF2N_Print_bin("GF2N_Optimize_Out_bin.txt", &a);
	a.Num[a.Length - 1] = 0;
	a.Num[a.Length - 2] = 0;
	GF2N_Print_bin("GF2N_Optimize_Out_bin.txt", &a);
	GF2N_Optimize_Out(&a);
	GF2N_Print_bin("GF2N_Optimize_Out_bin.txt", &a);
	GF2N_Zero_Free(&a);
#endif 
#if 0
// void GF2N_Free(GF2N *R, const GF2N *A); void GF2N_Zero_Free(GF2N *R, const GF2N *A);
	GF2N a;
	// GF2N_Free
	GF2N_Init_Rand(&a, 4, DEFAULT);
	GF2N_Print_bin("GF2N_Free_bin.txt", &a);
	GF2N_Print_poly("GF2N_Free_poly.txt", &a);
	GF2N_Free(&a);
	GF2N_Print_bin("GF2N_Free_bin.txt", &a);
	GF2N_Print_poly("GF2N_Free_poly.txt", &a);
	// GF2N_Zero_Free
	GF2N_Init_Rand(&a, 4, OPTIMIZE);
	GF2N_Print_bin("GF2N_Free_bin.txt", &a);
	GF2N_Print_poly("GF2N_Free_poly.txt", &a);
	GF2N_Zero_Free(&a);
	GF2N_Print_bin("GF2N_Free_bin.txt", &a);
	GF2N_Print_poly("GF2N_Free_poly.txt", &a);
#endif 
#if 0
// void GF2N_Deg(GF2N *R, const GF2N *A);
	GF2N a;
	FILE *fp;
	GF2N_Init_Rand(&a, 4, DEFAULT);
	GF2N_Print_poly("GF2N_Deg_poly.txt", &a);
	fopen_s(&fp, "GF2N_Deg_poly.txt", "at");
	printf("%d\n", GF2N_Deg(&a));
	fprintf(fp, "%d\n", GF2N_Deg(&a));
	fclose(fp);
	GF2N_Zero_Free(&a);
#endif 
#if 0
// void GF2N_LShift_Bit(GF2N *R, const GF2N *A, const UNWORD s_bit);
	GF2N a, r;
	UNWORD sft;
	FILE *fp;
	// DEFAULT
	if(rand() & 1)
	{
		GF2N_Init_Rand(&a, 4, DEFAULT);
		GF2N_Init_Rand(&r, 4, DEFAULT);
	}
	else
	{
		GF2N_Init_Rand(&a, 4, OPTIMIZE);
		GF2N_Init_Rand(&r, 4, OPTIMIZE);
	}
	fopen_s(&fp, "GF2N_LShift_Bit_bin.txt", "at");
	printf("bin(");
	fprintf(fp, "bin(");
	fclose(fp);
	GF2N_Print_bin("GF2N_LShift_Bit_bin.txt", &a);
	sft = rand() % 100;
	fopen_s(&fp, "GF2N_LShift_Bit_bin.txt", "at");
	printf(" << %d) == bin(", sft);
	fprintf(fp, " << %d) == bin(", sft);
	fclose(fp);
	GF2N_LShift_Bit(&r, &a, sft);
	GF2N_Print_bin("GF2N_LShift_Bit_bin.txt", &r);
	fopen_s(&fp, "GF2N_LShift_Bit_bin.txt", "at");
	printf(")\n", sft);
	fprintf(fp, ")\n", sft);
	fclose(fp);
	GF2N_Zero_Free(&a);
	GF2N_Zero_Free(&r);	
#endif 
#if 0
// void GF2N_RShift_Bit(GF2N *R, const GF2N *A, const UNWORD s_bit);
	GF2N a, r;
	UNWORD sft;
	FILE *fp;
	// DEFAULT
	if(rand() & 1)
	{
		GF2N_Init_Rand(&a, 4, DEFAULT);
		GF2N_Init_Rand(&r, 4, DEFAULT);
	}
	else
	{
		GF2N_Init_Rand(&a, 4, OPTIMIZE);
		GF2N_Init_Rand(&r, 4, OPTIMIZE);
	}
	fopen_s(&fp, "GF2N_RShift_Bit_bin.txt", "at");
	printf("bin(");
	fprintf(fp, "bin(");
	fclose(fp);
	GF2N_Print_bin("GF2N_RShift_Bit_bin.txt", &a);
	sft = rand() % 100;
	fopen_s(&fp, "GF2N_RShift_Bit_bin.txt", "at");
	printf(" >> %d) == bin(", sft);
	fprintf(fp, " >> %d) == bin(", sft);
	fclose(fp);
	GF2N_RShift_Bit(&r, &a, sft);
	GF2N_Print_bin("GF2N_RShift_Bit_bin.txt", &r);
	fopen_s(&fp, "GF2N_RShift_Bit_bin.txt", "at");
	printf(")\n", sft);
	fprintf(fp, ")\n", sft);
	fclose(fp);
	GF2N_Zero_Free(&a);
	GF2N_Zero_Free(&r);	
#endif 




}

void Sage_Test_BIGNUM()
{
#if 0
// void GF2N_Init(GF2N *A, const UNWORD len, const SNWORD flag);
	GF2N a;
	GF2N_Init(&a, 4, DEFAULT);
	GF2N_Print_bin("GF2N_Init_bin.txt", &a);
	GF2N_Print_poly("GF2N_Init_poly.txt", &a);
	GF2N_Zero_Free(&a);
#endif 
#if 0
//void GF2N_Init_Rand(GF2N *A, const UNWORD maxsize, const UNWORD flag);
	GF2N a;
	GF2N_Init_Rand(&a, 4, DEFAULT);
	GF2N_Print_bin("GF2N_GF2N_Init_Rand_bin.txt", &a);
	GF2N_Print_poly("GF2N_GF2N_Init_Rand_poly.txt", &a);
	GF2N_Zero_Free(&a);
#endif 
#if 0
//void GF2N_Init_Zero(GF2N *A, const UNWORD maxsize, const UNWORD flag);
	GF2N a;
	GF2N_Init_Zero(&a, 4, DEFAULT);
	GF2N_Print_bin("GF2N_Init_Zero_bin.txt", &a);
	GF2N_Print_poly("GF2N_Init_Zero_poly.txt", &a);
	GF2N_Zero_Free(&a);
#endif 
#if 0
// void GF2N_Init_Copy(GF2N *R, const GF2N *A);
	GF2N a, b;
	GF2N_Init_Rand(&a, 4, DEFAULT);
	GF2N_Init_Copy(&b, &a);
	GF2N_Print_poly("GF2N_Init_Copy_poly.txt", &a);
	GF2N_Print_poly("GF2N_Init_Copy_poly.txt", &b);
	GF2N_Zero_Free(&a);
	GF2N_Zero_Free(&b);
#endif 
#if 0
// void GF2N_Zeroize(GF2N *A);
	GF2N a;
	GF2N_Init_Rand(&a, 4, DEFAULT);
	GF2N_Print_bin("GF2N_Zeroize_bin.txt", &a);
	GF2N_Print_poly("GF2N_Zeroize_poly.txt", &a);
	GF2N_Zeroize(&a);
	GF2N_Print_bin("GF2N_Zeroize_bin.txt", &a);
	GF2N_Print_poly("GF2N_Zeroize_poly.txt", &a);
	GF2N_Zero_Free(&a);
	// Optimize
	GF2N_Init_Rand(&a, 4, OPTIMIZE);
	GF2N_Print_bin("GF2N_Zeroize_bin.txt", &a);
	GF2N_Print_poly("GF2N_Zeroize_poly.txt", &a);
	GF2N_Zeroize(&a);
	GF2N_Print_bin("GF2N_Zeroize_bin.txt", &a);
	GF2N_Print_poly("GF2N_Zeroize_poly.txt", &a);
	GF2N_Zero_Free(&a);
#endif 
#if 0
// void GF2N_Copy(GF2N *R, const GF2N *A);
	GF2N a, b;
	GF2N_Init_Rand(&a, 4, DEFAULT);
	GF2N_Init_Rand(&b, 4, DEFAULT);
	GF2N_Zeroize(&b);
	GF2N_Print_bin("GF2N_Copy_bin.txt", &a);
	GF2N_Print_bin("GF2N_Copy_bin.txt", &b);
	GF2N_Copy(&b, &a);
	GF2N_Print_bin("GF2N_Copy_bin.txt", &a);
	GF2N_Print_bin("GF2N_Copy_bin.txt", &b);
	GF2N_Zero_Free(&a);
	GF2N_Zero_Free(&b);
#endif 
#if 0
// void GF2N_Realloc_Mem(GF2N *A, const UNWORD size); void GF2N_Zero_Realloc_Mem(GF2N *A, const UNWORD size);
	GF2N a;
	// GF2N_Realloc_Mem
	GF2N_Init_Rand(&a, 4, DEFAULT);
	GF2N_Print_bin("GF2N_Realloc_Mem_bin.txt", &a);
	GF2N_Realloc_Mem(&a, 1);
	GF2N_Print_bin("GF2N_Realloc_Mem_bin.txt", &a);
	GF2N_Zero_Free(&a);
	// GF2N_Zero_Realloc_Mem
	GF2N_Init_Rand(&a, 4, OPTIMIZE);
	GF2N_Print_bin("GF2N_Zero_Realloc_Mem_bin.txt", &a);
	GF2N_Zero_Realloc_Mem(&a, 1);
	GF2N_Print_bin("GF2N_Zero_Realloc_Mem_bin.txt", &a);
	GF2N_Zero_Free(&a);
#endif 
#if 0
// void GF2N_Optimize_Out(GF2N *A);
	GF2N a;
	// GF2N_Realloc_Mem
	GF2N_Init(&a, 8, OPTIMIZE);
	GF2N_Randomize(&a);
	GF2N_Print_bin("GF2N_Optimize_Out_bin.txt", &a);
	a.Num[a.Length - 1] = 0;
	a.Num[a.Length - 2] = 0;
	GF2N_Print_bin("GF2N_Optimize_Out_bin.txt", &a);
	GF2N_Optimize_Out(&a);
	GF2N_Print_bin("GF2N_Optimize_Out_bin.txt", &a);
	GF2N_Zero_Free(&a);
#endif 
#if 0
// void GF2N_Free(GF2N *R, const GF2N *A); void GF2N_Zero_Free(GF2N *R, const GF2N *A);
	GF2N a;
	// GF2N_Free
	GF2N_Init_Rand(&a, 4, DEFAULT);
	GF2N_Print_bin("GF2N_Free_bin.txt", &a);
	GF2N_Print_poly("GF2N_Free_poly.txt", &a);
	GF2N_Free(&a);
	GF2N_Print_bin("GF2N_Free_bin.txt", &a);
	GF2N_Print_poly("GF2N_Free_poly.txt", &a);
	// GF2N_Zero_Free
	GF2N_Init_Rand(&a, 4, OPTIMIZE);
	GF2N_Print_bin("GF2N_Free_bin.txt", &a);
	GF2N_Print_poly("GF2N_Free_poly.txt", &a);
	GF2N_Zero_Free(&a);
	GF2N_Print_bin("GF2N_Free_bin.txt", &a);
	GF2N_Print_poly("GF2N_Free_poly.txt", &a);
#endif 
#if 0
// void GF2N_Deg(GF2N *R, const GF2N *A);
	GF2N a;
	FILE *fp;
	GF2N_Init_Rand(&a, 4, DEFAULT);
	GF2N_Print_poly("GF2N_Deg_poly.txt", &a);
	fopen_s(&fp, "GF2N_Deg_poly.txt", "at");
	printf("%d\n", GF2N_Deg(&a));
	fprintf(fp, "%d\n", GF2N_Deg(&a));
	fclose(fp);
	GF2N_Zero_Free(&a);
#endif 
#if 0
// void GF2N_LShift_Bit(GF2N *R, const GF2N *A, const UNWORD s_bit);
	GF2N a, r;
	UNWORD sft;
	FILE *fp;
	// DEFAULT
	if(rand() & 1)
	{
		GF2N_Init_Rand(&a, 4, DEFAULT);
		GF2N_Init_Rand(&r, 4, DEFAULT);
	}
	else
	{
		GF2N_Init_Rand(&a, 4, OPTIMIZE);
		GF2N_Init_Rand(&r, 4, OPTIMIZE);
	}
	fopen_s(&fp, "GF2N_LShift_Bit_bin.txt", "at");
	printf("bin(");
	fprintf(fp, "bin(");
	fclose(fp);
	GF2N_Print_bin("GF2N_LShift_Bit_bin.txt", &a);
	sft = rand() % 100;
	fopen_s(&fp, "GF2N_LShift_Bit_bin.txt", "at");
	printf(" << %d) == bin(", sft);
	fprintf(fp, " << %d) == bin(", sft);
	fclose(fp);
	GF2N_LShift_Bit(&r, &a, sft);
	GF2N_Print_bin("GF2N_LShift_Bit_bin.txt", &r);
	fopen_s(&fp, "GF2N_LShift_Bit_bin.txt", "at");
	printf(")\n", sft);
	fprintf(fp, ")\n", sft);
	fclose(fp);
	GF2N_Zero_Free(&a);
	GF2N_Zero_Free(&r);	
#endif 
#if 0
// void GF2N_RShift_Bit(GF2N *R, const GF2N *A, const UNWORD s_bit);
	GF2N a, r;
	UNWORD sft;
	FILE *fp;
	// DEFAULT
	if(rand() & 1)
	{
		GF2N_Init_Rand(&a, 4, DEFAULT);
		GF2N_Init_Rand(&r, 4, DEFAULT);
	}
	else
	{
		GF2N_Init_Rand(&a, 4, OPTIMIZE);
		GF2N_Init_Rand(&r, 4, OPTIMIZE);
	}
	fopen_s(&fp, "GF2N_RShift_Bit_bin.txt", "at");
	printf("bin(");
	fprintf(fp, "bin(");
	fclose(fp);
	GF2N_Print_bin("GF2N_RShift_Bit_bin.txt", &a);
	sft = rand() % 100;
	fopen_s(&fp, "GF2N_RShift_Bit_bin.txt", "at");
	printf(" >> %d) == bin(", sft);
	fprintf(fp, " >> %d) == bin(", sft);
	fclose(fp);
	GF2N_RShift_Bit(&r, &a, sft);
	GF2N_Print_bin("GF2N_RShift_Bit_bin.txt", &r);
	fopen_s(&fp, "GF2N_RShift_Bit_bin.txt", "at");
	printf(")\n", sft);
	fprintf(fp, ")\n", sft);
	fclose(fp);
	GF2N_Zero_Free(&a);
	GF2N_Zero_Free(&r);	
#endif 




}


//
//void sagetest_bignum()
//{
//	SNWORD i;
//	UNWORD n;
//    BIGNUM A, B, R;
//	FILE *fp;
//	
//    srand(time(NULL));
//	
//#if 1 // 기본 함수 테스트 
//	for(n = 0 ; n < 10 ; n++)
//	{
//		//// BIGNUM 랜덤 생성
//		BN_Init_Rand(&A, 8);
//		BN_Init_Rand(&B, 8);
//
//		//BN_Init_Zero(&A);
//		//BN_Init_Zero(&B);
//		
//		//// 기존의 BIGNUM 구조체 랜덤화
//		//BN_Init(&A, 8, PLUS);
//		//BN_Init(&B, 8, PLUS);
//		//BN_Init(&B, 16, PLUS);
//		//BN_Rand(&A);
//		//BN_Rand(&B);
//		
//		//// 모든 BN.Num[] = 0 으로 세팅
//		//BN_Zero(&A);
//		//BN_Zero(&B);
//
//		//// BIGNUM 동적할당 해지 
//		//BN_Free(&A);
//		//BN_Free(&B);
//		//BN_Zero_Free(&A);
//		//BN_Zero_Free(&B);
//
//		//BN_Realloc_Mem(&A, A.Length);
//		//BN_Realloc_Mem(&B, A.Length);
//
//		//// 빅넘 복사 
//		//BN_Copy(&B, &A);
//
//		////// 빅넘 크기 비교;
//		//printf("AbsCmp : %s\n", (BN_Abs_Cmp(&A, &B) == 1 ? "A > B" : "A < B"));
//		//printf("Cmp : %s\n", (BN_Cmp(&A, &B) == 1 ? "A > B" : "A < B"));
//		//printf("\n"); 
//		
//		printf("A : ");
//		printf("hex(%s0x", (A.Sign == -1) ? "-" : "+");
//		for(i = A.Length - 1 ; i >= 0 ; i--)
//			printf("%08x", A.Num[i]);
//		printf(")\n"); 
//	
//		printf("B : ");
//		printf("hex(%s0x", (B.Sign == -1) ? "-" : "+");
//		for(i = B.Length - 1 ; i >= 0 ; i--)
//		    printf("%08x", B.Num[i]);
//		printf(")\n"); 
//		printf("\n"); 
//
//		
//#endif
//	}
//}
//
//void sagetest_bn_operation()
//{
//	SNWORD i;
//	UNWORD n;
//    BIGNUM A, B, R;
//	FILE *fp;
//	
//    srand(time(NULL));
//	fopen_s(&fp, "sagetest_bn_operation.txt", "at");   
//
//// 연산 테스트 
//#if 0
//	for(n = 0 ; n < 1 ; n++)
//	{
//		//// BIGNUM 랜덤 생성
//		//BN_Init_Rand(&A, 8);
//		//BN_Init_Rand(&B, 8);
//		
//		//// 기존의 BIGNUM 구조체 랜덤화
//		BN_Init(&A, 4, PLUS);
//		BN_Init(&B, 4, PLUS);
//		BN_Init(&R, 8, PLUS);
//		//BN_Rand(&A);
//		//BN_Rand(&R);
//
//		/*
//		fprintf(fp, "hex((%s0x", (R.Sign == -1) ? "-" : "+");
//		for(i = R.Length - 1 ; i >= 0 ; i--)
//			fprintf(fp, "%08x", R.Num[i]);
//		*/
//
//		A.Num[0] = 0xffffffff;
//		A.Num[1] = 0xffffffff;
//		A.Num[2] = 0xffffffff;
//		A.Num[3] = 0xffffffff;
//		//
//		B.Num[0] = 0xffffffff;
//		B.Num[1] = 0xffffffff;
//		B.Num[2] = 0xffffffff;
//		B.Num[3] = 0xffffffff;
//		
//		
//		//BN_Abs_Add(&R, &A, &B);
//		//BN_Abs_Sub(&R, &A, &B);
//		//BN_Add(&R, &A, &B);
//		//BN_Sub(&R, &R, &R);
//		BN_Kara_Mul(&R, &A, &B);
//
//
//		//UW_Mul(R.Num, A.Num[0], A.Num[0]);
//		//UW_Sqr(R.Num, A.Num[0]);
//		//UW_Mul2(R.Num, A.Num[0], B.Num[0]);
//				
//		//BN_Basic_Mul(&R, &A, &A);
//		
//		//BN_Sqr(&R, &A);
//					
//		
//		fprintf(fp, "hex((%s0x", (A.Sign == -1) ? "-" : "+");
//		for(i = A.Length - 1 ; i >= 0 ; i--)
//			fprintf(fp, "%08x", A.Num[i]);
//		
//
//		
//		
//		fprintf(fp, ") * "); // 연산
//		
//		/*
//		fprintf(fp, "(%s0x", (A.Sign == -1) ? "-" : "+");
//		for(i = A.Length - 1 ; i >= 0 ; i--)
//		    fprintf(fp, "%08x", A.Num[i]);
//		fprintf(fp, ")) == ");
//		*/
//		
//		fprintf(fp, "(%s0x", (B.Sign == -1) ? "-" : "+");
//		for(i = B.Length - 1 ; i >= 0 ; i--)
//		    fprintf(fp, "%08x", B.Num[i]);
//		fprintf(fp, ")) == ");
//		
//		
//		// result
//		fprintf(fp, "hex(%s0x", (R.Sign == -1) ? "-" : "+");
//		for(i = R.Length - 1 ; i >= 0 ; i--)
//		    fprintf(fp, "%08x", R.Num[i]);
//		fprintf(fp, ")\n");
//		
//		
//	}
//#endif
//
//	fclose(fp);
//
//	BN_Free(&A);
//	BN_Free(&B);
//	BN_Free(&R);
//
//
//	
//	
//
//
//
//#if 0//DEBUG
//	for(i = 0; i < A.Length; i++)
//        printf(" 0x%X", A.Num[i]);
//	puts("");
//	for(i = 0; i < B.Length; i++)
//        printf(" 0x%X", B.Num[i]);
//	puts("");
//#endif
//
//}

void Sage_Test()
{
	UNWORD i;
	srand(time(NULL));
	for(i = 0 ; i < TEST_NUM ; i++)
	{
		Sage_Test_GF2N();
		Sage_Test_BIGNUM();
	}
}