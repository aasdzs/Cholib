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
#define TEST_NUM 50
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
	FILE *fp;
	fp = fopen("GF2N_Init.txt", "at");
	GF2N_Init(&a, 4, DEFAULT);
	GF2N_Print_bin(&a);
	GF2N_FPrint_bin(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Print_bin(&a);
	GF2N_FPrint_bin(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	fclose(fp);
	GF2N_Zero_Free(&a);
#endif 
#if 0
//void GF2N_Init_Rand(GF2N *A, const UNWORD maxsize);
	GF2N a;
	FILE *fp;
	fp = fopen("GF2N_Init_Rand.txt", "at");
	GF2N_Init_Rand(&a, 4);
	GF2N_Print_bin(&a);
	GF2N_FPrint_bin(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Print_poly(&a);
	GF2N_FPrint_poly(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	fclose(fp);
	GF2N_Zero_Free(&a);
#endif 
#if 0
// void GF2N_Init_Zero(GF2N *A);
	GF2N a;
	FILE *fp;
	fp = fopen("GF2N_Init_Zero.txt", "at");
	GF2N_Init_Zero(&a);
	GF2N_Print_bin(&a);
	GF2N_FPrint_bin(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Print_poly(&a);
	GF2N_FPrint_poly(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	fclose(fp);
	GF2N_Zero_Free(&a);
#endif 
#if 0
// void GF2N_Init_One(GF2N *A);
	GF2N a;
	FILE *fp;
	fp = fopen("GF2N_Init_Zero.txt", "at");
	GF2N_Init_One(&a);
	GF2N_Print_bin(&a);
	GF2N_FPrint_bin(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Print_poly(&a);
	GF2N_FPrint_poly(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	fclose(fp);
	GF2N_Zero_Free(&a);
#endif 
#if 0
// void GF2N_Init_Copy(GF2N *R, const GF2N *A);
	GF2N a, b;
	FILE *fp;
	fp = fopen("GF2N_Init_Copy.txt", "at");
	GF2N_Init_Rand(&a, 4);
	GF2N_Init_Copy(&b, &a);
	GF2N_Print_bin(&a);
	GF2N_FPrint_bin(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Print_poly(&a);
	GF2N_FPrint_poly(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Print_bin(&b);
	GF2N_FPrint_bin(fp, &b);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Print_poly(&b);
	GF2N_FPrint_poly(fp, &b);
	printf("\n");
	fprintf(fp, "\n");
	fclose(fp);
	GF2N_Zero_Free(&a);
	GF2N_Zero_Free(&b);
#endif 
#if 0
// void GF2N_Randomize(GF2N *A);
	GF2N a;
	FILE *fp;
	fp = fopen("GF2N_Randomize.txt", "at");
	GF2N_Init(&a, 4, DEFAULT);
	GF2N_Print_bin(&a);
	GF2N_FPrint_bin(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Print_poly(&a);
	GF2N_FPrint_poly(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Randomize(&a);
	GF2N_Print_bin(&a);
	GF2N_FPrint_bin(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Print_poly(&a);
	GF2N_FPrint_poly(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	fclose(fp);
	GF2N_Zero_Free(&a);
#endif 
#if 0
// void GF2N_Zero(GF2N *A);
	GF2N a;
	FILE *fp;
	fp = fopen("GF2N_Zero.txt", "at");
	GF2N_Init_Rand(&a, 4);
	GF2N_Print_bin(&a);
	GF2N_FPrint_bin(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Print_poly(&a);
	GF2N_FPrint_poly(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Zero(&a);
	GF2N_Print_bin(&a);
	GF2N_FPrint_bin(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Print_poly(&a);
	GF2N_FPrint_poly(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	fclose(fp);
	GF2N_Zero_Free(&a);
#endif 
#if 0
// void GF2N_Zeroize(GF2N *A);
	GF2N a;
	FILE *fp;
	fp = fopen("GF2N_Zeroize.txt", "at");
	GF2N_Init_Rand(&a, 4);
	GF2N_Print_bin(&a);
	GF2N_FPrint_bin(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Print_poly(&a);
	GF2N_FPrint_poly(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Zeroize(&a);
	GF2N_Print_bin(&a);
	GF2N_FPrint_bin(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Print_poly(&a);
	GF2N_FPrint_poly(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	fclose(fp);
	GF2N_Zero_Free(&a);
#endif 
#if 0
// void GF2N_Copy(GF2N *R, const GF2N *A);
	GF2N a, b;
	FILE *fp;
	fp = fopen("GF2N_Copy.txt", "at");
	GF2N_Init_Rand(&a, 4);
	GF2N_Init_Zero(&b);
	GF2N_Copy(&b, &a);
	GF2N_Print_bin(&a);
	GF2N_FPrint_bin(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Print_poly(&a);
	GF2N_FPrint_poly(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Print_bin(&b);
	GF2N_FPrint_bin(fp, &b);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Print_poly(&b);
	GF2N_FPrint_poly(fp, &b);
	printf("\n");
	fprintf(fp, "\n");
	fclose(fp);
	GF2N_Zero_Free(&a);
	GF2N_Zero_Free(&b);
#endif 
#if 0
// void GF2N_Realloc_Mem(GF2N *A, const UNWORD size); void GF2N_Zero_Realloc_Mem(GF2N *A, const UNWORD size);
	GF2N a;
	FILE *fp;
	// GF2N_Free
	fopen_s(&fp, "GF2N_Realloc_Mem.txt", "at");
	GF2N_Init_Rand(&a, 4);
	GF2N_Print_poly(&a);
	GF2N_FPrint_poly(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Realloc_Mem(&a, 1);
	GF2N_Print_poly(&a);
	GF2N_FPrint_poly(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	fclose(fp);
	GF2N_Free(&a);
	// GF2N_Zero_Free
	fopen_s(&fp, "GF2N_Zero_Realloc_Mem.txt", "at");
	GF2N_Init_Rand(&a, 4);
	GF2N_Print_poly(&a);
	GF2N_FPrint_poly(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Zero_Realloc_Mem(&a, 1);
	GF2N_Print_poly(&a);
	GF2N_FPrint_poly(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Free(&a);
	fclose(fp);
#endif 
#if 0
// void GF2N_Optimize_Out(GF2N *A);
	GF2N a;
	FILE *fp;
	// GF2N_Free
	fopen_s(&fp, "GF2N_Optimize_Out.txt", "at");
	GF2N_Init_Rand(&a, 4);
	a.Num[a.Length - 1] = 0;
	GF2N_Print_bin(&a);
	GF2N_FPrint_bin(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Optimize_Out(&a);
	GF2N_Print_bin(&a);
	GF2N_FPrint_bin(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	fclose(fp);
	GF2N_Free(&a);
#endif 
#if 0
// void GF2N_Free(GF2N *R, const GF2N *A); void GF2N_Zero_Free(GF2N *R, const GF2N *A);
	GF2N a;
	FILE *fp;
	// GF2N_Free
	fopen_s(&fp, "GF2N_Free.txt", "at");
	GF2N_Init_Rand(&a, 4, DEFAULT);
	GF2N_Print_bin(&a);
	GF2N_FPrint_bin(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Free(&a);
	GF2N_Print_bin(&a);
	GF2N_FPrint_bin(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	fclose(fp);
	GF2N_Free(&a);
	// GF2N_Zero_Free
	fopen_s(&fp, "GF2N_Zero_Free.txt", "at");
	GF2N_Init_Rand(&a, 4, DEFAULT);
	GF2N_Print_bin(&a);
	GF2N_FPrint_bin(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Zero_Free(&a);
	GF2N_Print_bin(&a);
	GF2N_FPrint_bin(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	GF2N_Free(&a);
	fclose(fp);
#endif 
#if 0
// void GF2N_Deg(GF2N *R, const GF2N *A);
	GF2N a;
	FILE *fp;
	fopen_s(&fp, "GF2N_Deg.txt", "at");
	GF2N_Init_Rand(&a, 4, DEFAULT);
	GF2N_Print_poly(&a);
	GF2N_FPrint_poly(fp, &a);
	printf(")\n");
	fprintf(fp, ")\n");
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
	fopen_s(&fp, "GF2N_LShift_Bit.txt", "at");
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
	printf("bin(");
	fprintf(fp, "bin(");
	GF2N_Print_bin(&a);
	GF2N_FPrint_bin(fp, &a);
	sft = rand() % 100;
	printf(" << %d) == bin(", sft);
	fprintf(fp, " << %d) == bin(", sft);
	GF2N_LShift_Bit(&r, &a, sft);
	GF2N_Print_bin(&r);
	GF2N_FPrint_bin(fp, &r);
	printf(")\n");
	fprintf(fp, ")\n");
	fclose(fp);
	GF2N_Zero_Free(&a);
	GF2N_Zero_Free(&r);	
#endif 
#if 0
// void GF2N_RShift_Bit(GF2N *R, const GF2N *A, const UNWORD s_bit);
	GF2N a, r;
	UNWORD sft;
	FILE *fp;
	fopen_s(&fp, "GF2N_RShift_Bit.txt", "at");
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
	printf("bin(");
	fprintf(fp, "bin(");
	GF2N_Print_bin(&a);
	GF2N_FPrint_bin(fp, &a);
	sft = rand() % 100;
	printf(" >> %d) == bin(", sft);
	fprintf(fp, " >> %d) == bin(", sft);
	GF2N_RShift_Bit(&r, &a, sft);
	GF2N_Print_bin(&r);
	GF2N_FPrint_bin(fp, &r);
	printf(")\n");
	fprintf(fp, ")\n");
	fclose(fp);
	GF2N_Zero_Free(&a);
	GF2N_Zero_Free(&r);	
#endif 




}

void Sage_Test_BIGNUM()
{
#if 0
// void BN_Init(GF2N *A, const UNWORD len, const SNWORD flag);
	BIGNUM a;
	FILE *fp;
	fp = fopen("BN_Init.txt", "at");
	BN_Init(&a, 4, PLUS, DEFAULT);
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf("\n");
	fprintf(fp, "\n");
	fclose(fp);
	BN_Zero_Free(&a);
#endif 
#if 0
// void BN_Init_Rand(BIGNUM *A, const UNWORD maxsize);
	BIGNUM a;
	FILE *fp;
	fp = fopen("BN_Init_Rand.txt", "at");
	BN_Init_Rand(&a, 4);
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf("\n");	
	fprintf(fp, "\n");
	fclose(fp);
	BN_Zero_Free(&a);
#endif 
#if 0
// void BN_Init_Zero(BIGNUM *A);
	BIGNUM a;
	FILE *fp;
	fp = fopen("BN_Init_Zero.txt", "at");
	BN_Init_Zero(&a);
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf("\n");	
	fprintf(fp, "\n");
	fclose(fp);
	BN_Zero_Free(&a);
#endif 
#if 0
// void BN_Init_One(BIGNUM *A);
	BIGNUM a;
	FILE *fp;
	fp = fopen("BN_Init_One.txt", "at");
	BN_Init_One(&a);
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf("\n");	
	fprintf(fp, "\n");
	fclose(fp);
	BN_Zero_Free(&a);
#endif 
#if 0
// void BN_Init_Copy(BIGNUM *R, const BIGNUM *A);
	BIGNUM a, b;
	FILE *fp;
	fp = fopen("BN_Init_Copy.txt", "at");
	BN_Init_Rand(&a, 4);
	BN_Init_Copy(&b, &a);
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf(" == ");	
	fprintf(fp, " == ");
	BN_Print_hex(&b);
	BN_FPrint_hex(fp, &b);
	printf("\n");	
	fprintf(fp, "\n");
	fclose(fp);
	BN_Zero_Free(&a);
#endif 
#if 0
// void BN_Randomize(BIGNUM *A);
	BIGNUM a;
	FILE *fp;
	fp = fopen("BN_Randomize.txt", "at");
	BN_Init(&a, 4, PLUS, DEFAULT);
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf("\n");	
	fprintf(fp, "\n");
	BN_Randomize(&a);
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf("\n");	
	fprintf(fp, "\n");
	fclose(fp);
	BN_Zero_Free(&a);
#endif
#if 0
// void BN_Zero(BIGNUM *A);
	BIGNUM a;
	FILE *fp;
	fp = fopen("BN_Zero.txt", "at");
	BN_Init_Rand(&a, 4);
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf("\n");	
	fprintf(fp, "\n");
	BN_Zero(&a);
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf("\n");	
	fprintf(fp, "\n");
	fclose(fp);
	BN_Zero_Free(&a);
#endif  
#if 0
// void BN_Zeroize(BIGNUM *A);
	BIGNUM a;
	FILE *fp;
	fp = fopen("BN_Zeroize.txt", "at");
	BN_Init_Rand(&a, 4);
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf("\n");	
	fprintf(fp, "\n");
	BN_Zeroize(&a);
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf("\n");	
	fprintf(fp, "\n");
	fclose(fp);
	BN_Zero_Free(&a);
#endif 
#if 0
// void BN_Copy(BIGNUM *R, const BIGNUM *A);
	BIGNUM a, b;
	FILE *fp;
	fp = fopen("BN_Copy.txt", "at");
	BN_Init_Rand(&a, 4);
	BN_Init_Rand(&b, 4);
	BN_Copy(&b, &a);
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf(" == ");	
	fprintf(fp, " == ");
	BN_Print_hex(&b);
	BN_FPrint_hex(fp, &b);
	printf("\n");	
	fprintf(fp, "\n");
	fclose(fp);
	BN_Zero_Free(&a);
#endif 
#if 0
// void BN_Realloc_Mem(BIGNUM *A, const UNWORD size);
	BIGNUM a;
	FILE *fp;
	fp = fopen("BN_Realloc_Mem.txt", "at");
	BN_Init_Rand(&a, 4);
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf("\n");	
	fprintf(fp, "\n");
	//BN_Realloc_Mem(&a, 1);
	BN_Realloc_Mem(&a, 8);	
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf("\n");	
	fprintf(fp, "\n");
	fclose(fp);
	BN_Zero_Free(&a);
#endif 
#if 0
// void BN_Zero_Realloc_Mem(BIGNUM *A, const UNWORD size);
	BIGNUM a;
	FILE *fp;
	fp = fopen("BN_Zero_Realloc_Mem.txt", "at");
	BN_Init_Rand(&a, 4);
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf("\n");	
	fprintf(fp, "\n");
	BN_Zero_Realloc_Mem(&a, 1);
	//BN_Zero_Realloc_Mem(&a, 8);
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf("\n");	
	fprintf(fp, "\n");
	fclose(fp);
	BN_Zero_Free(&a);
#endif 
#if 0
// void BN_Optimize_In(BIGNUM *A, const UNWORD size);
	BIGNUM a;
	FILE *fp;
	fp = fopen("BN_Optimize_In.txt", "at");
	BN_Init_Rand(&a, 4);
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf("\n");	
	fprintf(fp, "\n");
	//BN_Optimize_In(&a, 1);
	BN_Optimize_In(&a, 8);
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf("\n");	
	fprintf(fp, "\n");
	fclose(fp);
	BN_Zero_Free(&a);
#endif 
#if 0
// void BN_Optimize(BIGNUM *A);
	BIGNUM a;
	FILE *fp;
	fp = fopen("BN_Optimize.txt", "at");
	BN_Init_Rand(&a, 8);
	a.Num[a.Length - 1] = 0;	
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf("\n");	
	fprintf(fp, "\n");
	BN_Optimize(&a);
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf("\n");	
	fprintf(fp, "\n");
	fclose(fp);
	BN_Zero_Free(&a);
#endif
#if 0
// void BN_Free(BIGNUM *A);
	BIGNUM a;
	FILE *fp;
	fp = fopen("BN_Free.txt", "at");
	BN_Init_Rand(&a, 8);
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf("\n");	
	fprintf(fp, "\n");
	BN_Free(&a);
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf("\n");	
	fprintf(fp, "\n");
	fclose(fp);
	BN_Zero_Free(&a);
#endif 
#if 0
// void BN_Zero_Free(BIGNUM *A);
	BIGNUM a;
	FILE *fp;
	fp = fopen("BN_Zero_Free.txt", "at");
	BN_Init_Rand(&a, 8);
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf("\n");	
	fprintf(fp, "\n");
	BN_Zero_Free(&a);
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf("\n");	
	fprintf(fp, "\n");
	fclose(fp);
	BN_Zero_Free(&a);
#endif 
#if 0
// void BN_RShift_Bit(BIGNUM *R, const BIGNUM *A, const UNWORD s_bit);
	BIGNUM a, r;
	UNWORD sft;
	FILE *fp;
	fopen_s(&fp, "BN_RShift_Bit.txt", "at");
	// DEFAULT
	if(rand() & 1)
	{
		BN_Init_Rand(&a, 1);
		BN_Init_Zero(&r);
	}
	else
	{
		BN_Init_Rand(&a, 1);
		BN_Init_Zero(&r);
	}
	a.Sign = -1;
	printf("hex(");
	fprintf(fp, "hex(");
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);									
	sft = 10;//rand() % 100;
	printf(" >> %d) == hex(", sft);
	fprintf(fp, " >> %d) == hex(", sft);
	BN_RShift_Bit(&r, &a, sft);
	BN_Print_hex(&r);
	BN_FPrint_hex(fp, &r);
	printf(")\n");
	fprintf(fp, ")\n");
	fclose(fp);
	BN_Zero_Free(&a);
	BN_Zero_Free(&r);	
#endif 
#if 0
// void BN_LShift_Bit(BIGNUM *R, const BIGNUM *A, const UNWORD s_bit);
	BIGNUM a, r;
	UNWORD sft;
	FILE *fp;
	fopen_s(&fp, "BN_LShift_Bit.txt", "at");
	// DEFAULT
	if(rand() & 1)
	{
		BN_Init_Rand(&a, 4);
		BN_Init_Rand(&r, 4);
	}
	else
	{
		BN_Init_Rand(&a, 4);
		BN_Init_Rand(&r, 4);
	};
	printf("hex(");
	fprintf(fp, "hex(");
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);									
	sft = rand() % 100;
	printf(" << %d) == hex(", sft);
	fprintf(fp, " << %d) == hex(", sft);
	BN_LShift_Bit(&r, &a, sft);
	BN_Print_hex(&r);
	BN_FPrint_hex(fp, &r);
	printf(")\n");
	fprintf(fp, ")\n");
	fclose(fp);
	BN_Zero_Free(&a);
	BN_Zero_Free(&r);	
#endif 
#if 0
// void BN_Abs_Add(BIGNUM *R, const BIGNUM *A, const UNWORD s_bit);
	BIGNUM a, b, r;
	UNWORD sft;
	FILE *fp;
	fopen_s(&fp, "BN_Abs_Add.txt", "at");
	// DEFAULT
	BN_Init(&a, 4, PLUS, DEFAULT);
	BN_Randomize(&a);
	BN_Init_Rand(&b, 4);
	BN_Init(&r, 5, PLUS, DEFAULT);
	a.Sign = b.Sign = r.Sign = PLUS;
	printf("hex(");
	fprintf(fp, "hex(");
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf(" + ");
	fprintf(fp, " + ");
	BN_Print_hex(&b);
	BN_FPrint_hex(fp, &b);	
	printf(") == hex(");
	fprintf(fp, ") == hex(");
	BN_Abs_Add(&r, &a, &b);								
	BN_Print_hex(&r);
	BN_FPrint_hex(fp, &r);
	printf(")\n");
	fprintf(fp, ")\n");
	fclose(fp);
	BN_Zero_Free(&a);
	BN_Zero_Free(&b);
	BN_Zero_Free(&r);	
#endif 
#if 0
// void BN_Abs_Sub(BIGNUM *R, const BIGNUM *A, const UNWORD s_bit);
	BIGNUM a, b, r;
	UNWORD sft;
	FILE *fp;
	fopen_s(&fp, "BN_Abs_Sub.txt", "at");
	// DEFAULT
	BN_Init(&a, 4, PLUS, DEFAULT);
	BN_Randomize(&a);
	BN_Init_Rand(&b, 3);
	BN_Init(&r, 4, PLUS, DEFAULT);
	a.Sign = b.Sign = r.Sign = PLUS;
	printf("hex(");
	fprintf(fp, "hex(");
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf(" - ");
	fprintf(fp, " - ");
	BN_Print_hex(&b);
	BN_FPrint_hex(fp, &b);	
	printf(") == hex(");
	fprintf(fp, ") == hex(");
	BN_Abs_Sub(&r, &a, &b);								
	BN_Print_hex(&r);
	BN_FPrint_hex(fp, &r);
	printf(")\n");
	fprintf(fp, ")\n");
	fclose(fp);
	BN_Zero_Free(&a);
	BN_Zero_Free(&b);
	BN_Zero_Free(&r);	
#endif 
#if 0
// void BN_Add(BIGNUM *R, const BIGNUM *A, const UNWORD s_bit);
	BIGNUM a, b, r;
	UNWORD sft;
	FILE *fp;
	fopen_s(&fp, "BN_Add.txt", "at");
	// DEFAULT
	BN_Init_Rand(&a, 4);
	BN_Init_Rand(&b, 4);
	BN_Init(&r, 5, PLUS, DEFAULT);
	printf("hex(");
	fprintf(fp, "hex(");
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf(" + ");
	fprintf(fp, " + ");
	BN_Print_hex(&b);
	BN_FPrint_hex(fp, &b);	
	printf(") == hex(");
	fprintf(fp, ") == hex(");
	BN_Add(&r, &a, &b);								
	BN_Print_hex(&r);
	BN_FPrint_hex(fp, &r);
	printf(")\n");
	fprintf(fp, ")\n");
	fclose(fp);
	BN_Zero_Free(&a);
	BN_Zero_Free(&b);
	BN_Zero_Free(&r);
#endif 
#if 0
// void BN_Sub(BIGNUM *R, const BIGNUM *A, const UNWORD s_bit);
	BIGNUM a, b, r;
	UNWORD sft;
	FILE *fp;
	fopen_s(&fp, "BN_Sub.txt", "at");
	// DEFAULT
	BN_Init_Rand(&a, 4);
	BN_Init_Rand(&b, 4);
	BN_Init(&r, 4, PLUS, DEFAULT);
	printf("hex(");
	fprintf(fp, "hex(");
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf(" - ");
	fprintf(fp, " - ");
	BN_Print_hex(&b);
	BN_FPrint_hex(fp, &b);	
	printf(") == hex(");
	fprintf(fp, ") == hex(");
	BN_Sub(&r, &a, &b);								
	BN_Print_hex(&r);
	BN_FPrint_hex(fp, &r);
	printf(")\n");
	fprintf(fp, ")\n");
	fclose(fp);
	BN_Zero_Free(&a);
	BN_Zero_Free(&b);
	BN_Zero_Free(&r);
#endif 
#if 0
// void BN_Basic_Mul(BIGNUM *R, const BIGNUM *A, const BIGNUM *B)
	BIGNUM a, b, r;
	UNWORD sft;
	FILE *fp;
	fopen_s(&fp, "BN_Basic_Mul.txt", "at");
	// DEFAULT
	BN_Init_Rand(&a, 4);
	BN_Init_Rand(&b, 4);
	BN_Init(&r, 8, PLUS, DEFAULT);
	printf("hex(");
	fprintf(fp, "hex(");
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf(" * ");
	fprintf(fp, " * ");
	BN_Print_hex(&b);
	BN_FPrint_hex(fp, &b);	
	printf(") == hex(");
	fprintf(fp, ") == hex(");
	BN_Basic_Mul(&r, &a, &b);								
	BN_Print_hex(&r);
	BN_FPrint_hex(fp, &r);
	printf(")\n");
	fprintf(fp, ")\n");
	fclose(fp);
	BN_Zero_Free(&a);
	BN_Zero_Free(&b);
	BN_Zero_Free(&r);
#endif 
#if 0 // TESTVECTOR 필요
// void BN_Kara_Mul(BIGNUM *R, const BIGNUM *A, const BIGNUM *B)
	BIGNUM a, b, r;
	UNWORD sft;
	FILE *fp;
	fopen_s(&fp, "BN_Kara_Mul.txt", "at");
	// DEFAULT
	BN_Init_Rand(&a, 4);
	BN_Init_Rand(&b, 4);
	BN_Init(&r, 8, PLUS, DEFAULT);
	printf("hex(");
	fprintf(fp, "hex(");
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf(" * ");
	fprintf(fp, " * ");
	BN_Print_hex(&b);
	BN_FPrint_hex(fp, &b);	
	printf(") == hex(");
	fprintf(fp, ") == hex(");
	BN_Kara_Mul(&r, &a, &b);								
	BN_Print_hex(&r);
	BN_FPrint_hex(fp, &r);
	printf(")\n");
	fprintf(fp, ")\n");
	fclose(fp);
	BN_Zero_Free(&a);
	BN_Zero_Free(&b);
	BN_Zero_Free(&r);
#endif 
#if 0
// void BN_Sqr(BIGNUM *R, const BIGNUM *A, const BIGNUM *B)
	BIGNUM a, r;
	UNWORD sft;
	FILE *fp;
	fopen_s(&fp, "BN_Sqr.txt", "at");
	// DEFAULT
	BN_Init_Rand(&a, 4);
	BN_Init(&r, 8, PLUS, DEFAULT);
	printf("hex((");
	fprintf(fp, "hex((");
	BN_Print_hex(&a);
	BN_FPrint_hex(fp, &a);
	printf(")^2 ");
	fprintf(fp, ")^2 ");
	printf(") == hex(");
	fprintf(fp, ") == hex(");
	BN_Sqr(&r, &a);								
	BN_Print_hex(&r);
	BN_FPrint_hex(fp, &r);
	printf(")\n");
	fprintf(fp, ")\n");
	fclose(fp);
	BN_Zero_Free(&a);
	BN_Zero_Free(&r);
#endif 
#if 0
// void BN_Bar_Redc(BIGNUM *R, const BIGNUM *Z, const BIGNUM *P, const BIGNUM *MU)
	
#endif 



}



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