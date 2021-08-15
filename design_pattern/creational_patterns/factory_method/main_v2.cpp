#include <stdio.h>
#include "factory_method.h"

int main( int argc, char **argv )
{
	//画图
	int shape = argv[1];
	if ( "line" == shape )
	{
		//画线
		CLineDraw pLineDraw = new CLineDraw();//存在的问题:依赖具体类,属于静态绑定,对象的创建和使用紧耦合
		pLineDraw->LineDraw();
	}
	else if ( "circle" == shape )
	{
		//画圆
		CCircleDraw pCircleDraw = new CCircleDraw();//存在的问题:依赖具体类,属于静态绑定,对象的创建和使用紧耦合
		pCircleDraw->CircleDraw();
	}
	//需求来了，要求也能够画正方形，传统的方式是增加if分支，本质上是修改(非扩展)，没有隔离变化，带来的问题是
	//需要重新测试整个单元
	else if ( "rect" == shape )
	{
		//画正方形
		CRectDraw pRectDraw = new CRectDraw();//存在的问题:依赖具体类,属于静态绑定,对象的创建和使用紧耦合
		pRectDraw->RectDraw();
	}

	return 0;
}
