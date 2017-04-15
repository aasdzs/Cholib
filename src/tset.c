#include "config.h"
#include "GF2N.h"

#if 1



SNWORD main ()
{	
	UNWORD *a;
	UNWORD *b;

	a = (UNWORD *)calloc(4, sizeof(UNWORD)); 
	b = (UNWORD *)calloc(4, sizeof(UNWORD)); 

	printf("%x \n", a);
	printf("%x \n", b);

	a = (UNWORD *)realloc(a, 4 * sizeof(UNWORD)); 
	b = (UNWORD *)realloc(b, 8 * sizeof(UNWORD)); 

	printf("%x \n", a);
	printf("%x \n", b);

	return 0;	
}

#endif