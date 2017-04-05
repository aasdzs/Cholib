#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG 0


typedef	unsigned	char	UCHAR;
typedef				char	SCHAR;
typedef	unsigned	int		UNINT;
typedef				int		SNINT;

/*
typedef				__int64 INT64;
typedef	unsigned	short	USHOT;
typedef				short	SSHOT;
typedef				double	DOUBL;
typedef				float	FLOAT;
*/

// CONFIG
#define BIT_LEN 32

#if (BIT_LEN == 8)
#define UNWORD		    UCHAR
#define SNWORD		    SCHAR
#define WORD_MASK		0xFF
#define WORD_MASK_H		0xF0
#define WORD_MASK_L		0x0F

#elif (BIT_LEN == 32)
#define UNWORD		    UNINT
#define SNWORD		    SNINT
#define WORD_MASK		0xFFFFFFFF
#define WORD_MASK_H		0xFFFF0000
#define WORD_MASK_L		0x0000FFFF
#endif

#define SUCCESS		1
#define FAILURE	   -1

#define PLUS	    1
#define	ZERO		0
#define MINUS      -1

#define LARGE		1
#define	EQUAL		0
#define SMALL	   -1

#define OPTIMIZE    1
#define DEFAULT     0


// Define Function 
//void sagetest_bignum();
//void sagetest_bn_operation();

#else
#endif

