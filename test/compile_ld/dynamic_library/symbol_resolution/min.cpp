#include "min.h"
#include <iostream>
using namespace std;

int intmin(int x, int y)
{
	cout << "this is min.cpp's min" << endl;	
	return (x < y) ? x : y;
}

int min(int x, int y)
{
	return intmin(x,y);
}
