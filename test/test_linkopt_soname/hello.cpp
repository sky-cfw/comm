#include <stdio.h>
#include "hello.h"

void hello( const char *name )
{
	printf("hello %s, welcome! 3.0.0\n", name);

}

//2.0.0
void age(const char *age)
{
	printf("age:%s\n", age);
}
//3.0.0
void sex(const char *sex)
{
	printf("sex:%s\n", sex);
}
