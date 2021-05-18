#include <iostream>
using namespace std;

class A;

int main()
{
	A a;
	
	//cout << "sizeof(A) = " << sizeof(A) << endl;
	
	return 0;
}

class A
{
	public:
		A() {};
		~A() {};
	
	public:
		int m_iCnt;
};
