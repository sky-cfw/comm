#include <stdio.h>
#include "weak_ref.h"

int foo()
{
	printf( "customn strong symbol override!\n" );
	return 0;
}


int main()
{
	foo();
	return 0;
}
