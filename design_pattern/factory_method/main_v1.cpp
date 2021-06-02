#include <stdio.h>

int main( int argc, char **argv )
{
	//画图
	int shape = argv[1];
	if ( "line" == shape )
	{
		//画线
		printf("draw line!\n");
	}
	else if ( "circle" == shape )
	{
		//画圆
		printf("draw circle!\n");
	}
	//需求来了，要求也能够画正方形，传统的方式是增加if分支，本质上是修改(非扩展)，没有隔离变化，带来的问题是
	//需要重新测试整个单元
	else if ( "rect" == shape )
	{
		//画正方形
		printf("draw rect\n");
	}

	return 0;
}
