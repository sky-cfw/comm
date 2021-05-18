#include <iostream>
using namespace std;

class CSingleton
{
	private:
		CSingleton() {}//防止外部创建类的实例
		CSingleton(const CSingleton &rhs);//防止外部调用复制构造函数创建类的实例
		const CSingleton & operator = ( const CSingleton &rhs);//防止外部通过赋值操作符来构造类的实例
	public:
		~CSingleton() {}//保证类的实例能够正常释放
		static CSingleton *GetInstance()
		{
			static CSingleton cSingleton;
			return &cSingleton;
		}

		void Log( const std::string &sMsg )
		{
			cout << sMsg.c_str() << endl;
		}
};


#define SINGLETON CSingleton::GetInstance()


int main()
{
	SINGLETON->Log( "hungry singleon!" );

	return 0;
}
