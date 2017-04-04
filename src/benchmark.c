#include "benchmark.h"
#include "config.h"

////////////////////////////////////////////////////////////////////////////
// The source of this code is from the Keccak(SHA-3) code,
// released in Keccak homepage(http://keccak.noekeon.org)
////////////////////////////////////////////////////////////////////////////

/************** Timing routine (for performance measurements) ***********/
/* By Doug Whiting */
/* unfortunately, this is generally assembly code and not very portable */
#if defined(_M_IX86) || defined(__i386) || defined(_i386) || defined(__i386__) || defined(i386) || \
	defined(_X86_)   || defined(__x86_64__) || defined(_M_X64) || defined(__x86_64)
#define _Is_X86_    1
#endif
#if  defined(_Is_X86_) && (!defined(__STRICT_ANSI__)) && (defined(__GNUC__) || !defined(__STDC__)) && \
	(defined(__BORLANDC__) || defined(_MSC_VER) || defined(__MINGW_H) || defined(__GNUC__))
#define HI_RES_CLK_OK         1          /* it's ok to use RDTSC opcode */
#if defined(_MSC_VER) // && defined(_M_X64)
#include <intrin.h>
#pragma intrinsic(__rdtsc)         /* use MSVC rdtsc call where defined */
#endif
#endif

////////////////////////////////////////////////////////////////////////////////

uint_32t HiResTime(void)           /* return the current value of time stamp counter */
{
#if defined(HI_RES_CLK_OK)
	uint_32t x[2];
#if   defined(__BORLANDC__)
#define COMPILER_ID "BCC"
	__emit__(0x0F,0x31);           /* RDTSC instruction */
	_asm { mov x[0],eax };
#elif defined(_MSC_VER)
#define COMPILER_ID "MSC"
#if defined(_MSC_VER) // && defined(_M_X64)
	x[0] = (uint_32t) __rdtsc();
#else
	_asm { _emit 0fh }; _asm { _emit 031h };
	_asm { mov x[0],eax };
#endif
#elif defined(__MINGW_H) || defined(__GNUC__)
#define COMPILER_ID "GCC"
	asm volatile("rdtsc" : "=a"(x[0]), "=d"(x[1]));
#else
#error  "HI_RES_CLK_OK -- but no assembler code for this platform (?)"
#endif
	return x[0];
#else
	/* avoid annoying MSVC 9.0 compiler warning #4720 in ANSI mode! */
#if (!defined(_MSC_VER)) || (!defined(__STDC__)) || (_MSC_VER < 1300)
	FatalError("No support for RDTSC on this CPU platform\n");
#endif
	return 0;
#endif /* defined(HI_RES_CLK_OK) */
}

////////////////////////////////////////////////////////////////////////////////

uint_32t calibrate()
{
	uint_32t dtMin = 0xFFFFFFFF;        /* big number to start */
	uint_32t t0, t1, i;

	for (i = 0 ;i < ITERATION_COUNT ; i++)  /* calibrate the overhead for measuring time */
	{
		t0 = HiResTime();
		t1 = HiResTime();
		if (dtMin > t1-t0)              /* keep only the minimum time */
			dtMin = t1-t0;
	}
	return dtMin;
}

void Benchmark_Test()
{
	//시간 Check 변수
	uint_32t calibration;

	uint_32t tMin = 0xFFFFFFFF;         // big number to start 
	uint_32t Average = 0;		        // Average 
	
	uint_32t t0, t1;
	uint_32t it_1, it_2;

	srand(time(NULL)&0xFFFFFFFF);

	// 시간 측정
	printf("------------------------------------------------------------\n");
	printf("	Benchmark Result (Average : %d, Iteration : %d)\n", AVERAGE_COUNT, ITERATION_COUNT);
	printf("------------------------------------------------------------\n");
	printf("\n");

	calibration = calibrate(); // HiResTime(); 호출시간을 측정해서 최소값을 넣고 나중에 뺌

	// 평균치 측정 위한 반복
	for (it_1 = 0 ; it_1 < AVERAGE_COUNT ; it_1++)
	{
		tMin = 0xFFFFFFFF;
		
		// 반복 수행 했을 때 최소 시간 측정
		for (it_2 = 0 ; it_2 < ITERATION_COUNT ; it_2++)  // calibrate the overhead for measuring time //
		{
			t0 = HiResTime();
			
			Benchmark_Target();
			
			t1 = HiResTime();

			if (tMin > t1 - t0 - calibration)       // keep only the minimum time //
				tMin = t1 - t0 - calibration;
		}
		printf("	%d / %d	Benchmark : %d cycles\n",AVERAGE_COUNT, ITERATION_COUNT, (tMin));
		
		Average += tMin;
		Average >>= 1;

	}
	
	printf("------------------------------------------------------------\n");
	printf("	Average : %d cycles\n", (Average));
	printf("------------------------------------------------------------\n");
}

void Benchmark_Target()
{

}