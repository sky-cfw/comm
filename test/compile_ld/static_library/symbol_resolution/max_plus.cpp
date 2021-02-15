#include "max_plus.h"
#include <iostream>
using namespace std;

int max(int x, int y)
{
	return (x < y) ? y : x;
}

int intplus(int x, int y)
{
	cout << "max intplus" << endl;
	return x+y;
}
