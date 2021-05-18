#include <stdio.h>
__attribute__ ((weak)) int foo()
{
	printf( "default weak foo is running!\n" );
	return 0;
}

