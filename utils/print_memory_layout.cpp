/*
 * @Author: sky wcf0118@gmail.com
 * @Date: 2022-05-03 14:27:42
 * @LastEditors: sky wcf0118@gmail.com
 * @LastEditTime: 2022-05-03 16:44:29
 * @FilePath: /comm/utils/print_memory_layout.cpp
 * @Description: 打印c++程序变量的内存布局，支持16进制打印 和 2进制打印
 */
#include <string>
#include "print_memory_layout.h"


void boss::char2bin(unsigned char tmp)
{
	string data;
	unsigned char mask = 0x80;	// 这里不能用char，因为本编译器将char视为signed char，带有符号位 0x80 >>1 得到0xc0，0x80 >>2 得到0xe0
	for (int i = 0; i < 8; i++)
	{
		if (tmp & (mask >> i))
		{
			data += '1';
		}
		else
		{
			data += '0';
		}

	}
	printf("%s\n", data.c_str());
}

void boss::show_bytes(unsigned char* start, int len)
{
	for (int i = 0; i < len; i++)
	{
		printf("%02x ", start[i]);	// 小端存储，所以最先输出的是最低位的，以十六进制输出
		unsigned char tmp = start[i];
		// printf("%02x ", tmp);
		// char tmp_1 = start[i];	// printf函数在解析unsigned char和char的时候，会进行高位符号拓展，如果是char，且符号位为1的时候，printf输出高位会出现ffffff
		// printf("%02x ", tmp_1);
		char2bin(tmp);
	}
	printf("\n");
}


// int main(int argc, char const *argv[]) {
    
//     bool a = true;
// 	bool b = false;
// 	int c = 2;
// 	float d = 1.1;
// 	double e = 1.1;

// 	show_bytes((unsigned char *)&a, sizeof(a));
// 	show_bytes((unsigned char *)&b, sizeof(b));
// 	show_bytes((unsigned char *)&c, sizeof(c));
// 	show_bytes((unsigned char *)&d, sizeof(d));
// 	show_bytes((unsigned char *)&e, sizeof(e));

//     return 0;
// }
