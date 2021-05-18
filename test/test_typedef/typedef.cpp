#include <stdio.h>
#include <iostream>

using namespace std;

int add(int a, int b)
{
	return a+b;
}

typedef int test(int , int);

int main()
{
	test *t = &add;

	cout << t(2, 3) << endl;
	
	return 0;
}
