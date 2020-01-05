#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
using namespace std;

//y：需要开根号的值
//n：精确到的位数
void mySqrt(double y, int n)
{
	double low = 0.0f, high = y, mid = low+(high-low)/2, last = 0.0f;
	printf("mid:%f, fabs(last-mid):%f\n", mid, fabs(last-mid));
	while( fabs(last-mid) > pow(10,-n) )
	{
		last = mid;
		if ( y/mid > mid )
		{
			low = mid; 
		}
		else
		{
			high = mid;
		}

		mid = low+(high-low)/2;
		printf("low:%f, high:%f, mid:%f\n", low, high, mid);
	}
	printf( "n=%f, sqrt(%f) = %f\n", pow(10,-n), y, mid );
}

int main(int argc, char const *argv[])
{
	if ( 3 != argc )
	{
		printf("./sqrt number presion\n");
		return -1;
	}

	double y = atof( argv[1] );
	int n = atoi( argv[2] );
	mySqrt( y, n );

	return 0;
}