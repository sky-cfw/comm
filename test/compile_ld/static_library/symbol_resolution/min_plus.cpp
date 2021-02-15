#include "min_plus.h"
#include <iostream>
using namespace std;

int min(int x, int y)
{
	return (x < y) ? x : y;
}

int intplus(int x, int y)
{
	cout << "min intplus" << endl;
	return x+y;
}
