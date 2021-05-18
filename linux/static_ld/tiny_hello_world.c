char *str = "Hello world!\n";

//eax:调用号,系统调用通过0x80中断实现
//ebx/ecx/edx通用寄存器用来传递参数
void print()
{
	asm("mov1 $13,%%edx \n\t"
		"mov1 $0,%%ecx \n\t"
		"movl $0,%%ebx \n\t"
		"movl $4,%%eax \n\t"
		"int $0x80 \n\t"
		::"r"(str):"edx","ecx","ebx");

}

void exit()
{
	asm("movl $42, %ebx \n\t"
		"movl $1, %eax \n\t"
		"int $0x80 \n\t");
}


void nomain()
{
	print();
	exit();
}
