extern int ext;

int weak;
int strong = 1;
int __attribute__((weak)) weak2 = 2;

int main()
{
	return 0;
}
