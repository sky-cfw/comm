#include <stdio.h>
#include "factory_method.h"

int main( int argc, char **argv )
{
	//画图
	std::string shape = argv[1];
	/*
	CShapDraw *pShapDraw = NULL;
	if ( "line" == shape )
	{
		//画线
		pShapDraw = new CLineDraw();//存在的问题:依赖具体类,对象的创建和使用紧耦合
	}
	else if ( "circle" == shape )
	{
		//画圆
		pShapDraw = new CCircleDraw();//存在的问题:依赖具体类,对象的创建和使用紧耦合
	}
	//需求来了，要求也能够画正方形，传统的方式是增加if分支，本质上是修改(非扩展)，没有隔离变化，带来的问题是
	//需要重新测试整个单元
	else if ( "rect" == shape )
	{
		//画正方形
		pShapDraw = new CRectDraw();//存在的问题:依赖具体类,对象的创建和使用紧耦合
	}
	*/
	
	CShapDraw *pShapDraw = CShapDrawFactory::Create( shape );//使用单独的工厂类来创建绘画类，解耦对象的创建和使用
	pShapDraw->Draw();

	return 0;
}
