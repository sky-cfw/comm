#include "factory_method.h"

/*
void CShapDrawFactory::RegisterIn( const std::string &sShap, CShapDraw *pShapDraw )
{
	m_mapShapDraw.insert( std::pair< const std::string, CShapDraw*>( sShap, pShapDraw ) );
}
*/
CShapDraw *CShapDrawFactory::Create( const std::string &sShap )
{
	std::map<const std::string, CShapDraw*>::iterator itr = m_mapShapDraw.find(sShap);
	if ( itr == m_mapShapDraw.end() )
	{
		return NULL;
	}
	else
	{
		return itr->second;
	}

	return NULL;
}


CShapDraw::CShapDraw()
{

}

CShapDraw::~CShapDraw()
{

}

CLineDraw::CLineDraw()
{

}

CLineDraw::~CLineDraw()
{

}

void CLineDraw::LineDraw()
{
	printf( "draw line!\n" );
}

CCircleDraw::CCircleDraw()
{
	
}

CCircleDraw::~CCircleDraw()
{
	
}

void CCircleDraw::CircleDraw()
{
	printf("circle draw!\n");
}
