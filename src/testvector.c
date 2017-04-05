#include "config.h"
#include "bignum.h"
#include "bn_operation.h"
#include "wd_operation.h"

void sagetest_bignum()
{
	SNWORD i;
	UNWORD n;
    BIGNUM A, B, R;
	FILE *fp;
	
    srand(time(NULL));
	
#if 1 // 기본 함수 테스트 
	for(n = 0 ; n < 10 ; n++)
	{
		//// BIGNUM 랜덤 생성
		BN_Init_Rand(&A, 8);
		BN_Init_Rand(&B, 8);

		//BN_Init_Zero(&A);
		//BN_Init_Zero(&B);
		
		//// 기존의 BIGNUM 구조체 랜덤화
		//BN_Init(&A, 8, PLUS);
		//BN_Init(&B, 8, PLUS);
		//BN_Init(&B, 16, PLUS);
		//BN_Rand(&A);
		//BN_Rand(&B);
		
		//// 모든 BN.Num[] = 0 으로 세팅
		//BN_Zero(&A);
		//BN_Zero(&B);

		//// BIGNUM 동적할당 해지 
		//BN_Free(&A);
		//BN_Free(&B);
		//BN_Zero_Free(&A);
		//BN_Zero_Free(&B);

		//BN_Realloc_Mem(&A, A.Length);
		//BN_Realloc_Mem(&B, A.Length);

		//// 빅넘 복사 
		//BN_Copy(&B, &A);

		////// 빅넘 크기 비교;
		//printf("AbsCmp : %s\n", (BN_Abs_Cmp(&A, &B) == 1 ? "A > B" : "A < B"));
		//printf("Cmp : %s\n", (BN_Cmp(&A, &B) == 1 ? "A > B" : "A < B"));
		//printf("\n"); 
		
		printf("A : ");
		printf("hex(%s0x", (A.Sign == -1) ? "-" : "+");
		for(i = A.Length - 1 ; i >= 0 ; i--)
			printf("%08x", A.Num[i]);
		printf(")\n"); 
	
		printf("B : ");
		printf("hex(%s0x", (B.Sign == -1) ? "-" : "+");
		for(i = B.Length - 1 ; i >= 0 ; i--)
		    printf("%08x", B.Num[i]);
		printf(")\n"); 
		printf("\n"); 

		
#endif
	}
}

void sagetest_bn_operation()
{
	SNWORD i;
	UNWORD n;
    BIGNUM A, B, R;
	FILE *fp;
	
    srand(time(NULL));
	fopen_s(&fp, "sagetest_bn_operation.txt", "at");   

// 연산 테스트 
#if 1
	for(n = 0 ; n < 1 ; n++)
	{
		//// BIGNUM 랜덤 생성
		//BN_Init_Rand(&A, 8);
		//BN_Init_Rand(&B, 8);
		
		//// 기존의 BIGNUM 구조체 랜덤화
		BN_Init(&A, 4, PLUS);
		BN_Init(&B, 4, PLUS);
		BN_Init(&R, 8, PLUS);
		//BN_Rand(&A);
		//BN_Rand(&R);

		/*
		fprintf(fp, "hex((%s0x", (R.Sign == -1) ? "-" : "+");
		for(i = R.Length - 1 ; i >= 0 ; i--)
			fprintf(fp, "%08x", R.Num[i]);
		*/

		A.Num[0] = 0xffffffff;
		A.Num[1] = 0xffffffff;
		A.Num[2] = 0xffffffff;
		A.Num[3] = 0xffffffff;
		//
		B.Num[0] = 0xffffffff;
		B.Num[1] = 0xffffffff;
		B.Num[2] = 0xffffffff;
		B.Num[3] = 0xffffffff;
		
		
		//BN_Abs_Add(&R, &A, &B);
		//BN_Abs_Sub(&R, &A, &B);
		//BN_Add(&R, &A, &B);
		//BN_Sub(&R, &R, &R);
		BN_Kara_Mul(&R, &A, &B);


		//UNWORD_Mul(R.Num, A.Num[0], A.Num[0]);
		//UNWORD_Sqr(R.Num, A.Num[0]);
		//UNWORD_2_Mul(R.Num, A.Num[0], B.Num[0]);
				
		//BN_Basic_Mul(&R, &A, &A);
		
		//BN_Sqr(&R, &A);
					
		
		fprintf(fp, "hex((%s0x", (A.Sign == -1) ? "-" : "+");
		for(i = A.Length - 1 ; i >= 0 ; i--)
			fprintf(fp, "%08x", A.Num[i]);
		

		
		
		fprintf(fp, ") * "); // 연산
		
		/*
		fprintf(fp, "(%s0x", (A.Sign == -1) ? "-" : "+");
		for(i = A.Length - 1 ; i >= 0 ; i--)
		    fprintf(fp, "%08x", A.Num[i]);
		fprintf(fp, ")) == ");
		*/
		
		fprintf(fp, "(%s0x", (B.Sign == -1) ? "-" : "+");
		for(i = B.Length - 1 ; i >= 0 ; i--)
		    fprintf(fp, "%08x", B.Num[i]);
		fprintf(fp, ")) == ");
		
		
		// result
		fprintf(fp, "hex(%s0x", (R.Sign == -1) ? "-" : "+");
		for(i = R.Length - 1 ; i >= 0 ; i--)
		    fprintf(fp, "%08x", R.Num[i]);
		fprintf(fp, ")\n");
		
		
	}
#endif

	fclose(fp);

	BN_Free(&A);
	BN_Free(&B);
	BN_Free(&R);


	
	



#if 0//DEBUG
	for(i = 0; i < A.Length; i++)
        printf(" 0x%X", A.Num[i]);
	puts("");
	for(i = 0; i < B.Length; i++)
        printf(" 0x%X", B.Num[i]);
	puts("");
#endif

}