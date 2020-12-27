#include <iostream>
#include <dlfcn.h>
using namespace std;

int main( int argc, char *argv[] )
{
	if ( 3 != argc )
	{
		cout << "./main_ld <libname> <symname>" << endl;
		return 0;
	}

	std::string sLibName = argv[1];
	std::string sSymName = argv[2];
	cout << "input libname:" << sLibName << ", symname:" <<  sSymName << endl;
	void *libHandle = dlopen(argv[1], RTLD_LAZY | RTLD_GLOBAL);
	if ( NULL == libHandle )
	{
		cout << "dlopen failed, libname:" << sLibName << ", sysname:" << sSymName << ", errmsg:" << dlerror()  << endl;
		return -1;
	}
	//cout << "test" << dlerror() << endl;
	
	//typedef int (*fp) (int, int);
	int (*fp) (int, int);
	//fp func = (int (*) (int, int))dlsym(libHandle, argv[2]);
	fp = (int (*) (int, int))dlsym(libHandle, argv[2]);
	//fp = dlsym(libHandle, argv[2]);
	if (NULL == fp)
	{
		cout << "dlsym failed, libname:" << sLibName << ", sysname:" << sSymName << ", errmsg:" << dlerror()  << endl;
		return -1;
	}

	cout << "3, 5, " << sSymName << " is " << fp(3, 5) << endl;

	return 0;
}
