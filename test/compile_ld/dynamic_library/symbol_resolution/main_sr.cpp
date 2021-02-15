#include <iostream>
#include "min.h"
using namespace std;

int /*__attribute__ ((visibility("hidden")))*/ intmin(int x, int y)
{
	cout << endl << "this is main's min " << endl;
	return (x < y) ? x : y;
}

int main()
{
	int x = 3, y = 4;
	cout << x << ", " << y << ", min is " << min(x, y) << endl;
	return 0;
}
