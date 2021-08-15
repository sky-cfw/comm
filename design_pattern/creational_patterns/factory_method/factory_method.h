#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include <string>


#define TO_REGISTER_IN(SHAP,_CLASS,_FCLASS)  extern "C" {\
	static _CLASS *obj_##_CLASS = new _CLASS();\
	_FCLASS::RegisterIn( SHAP, obj_##_CLASS );\
}


class CShapDraw
{
public:
	CShapDraw();
	virtual ~CShapDraw();

	virtual void Draw() = 0;
};

class CShapDrawFactory
{
public:
	CShapDrawFactory() {}
	virtual ~CShapDrawFactory() {}

	static void RegisterIn( std::string &sShap, CShapDraw *pShapDraw );
	static CShapDraw *Create( std::string &sShap );

private:
	static std::map<std::string, CShapDraw *> m_mapShapDraw;
};

class CLineDraw : public CShapDraw
{
public:
	CLineDraw();
	~CLineDraw();

public:
	void LineDraw();
	void Draw();
};

TO_REGISTER_IN("line",CLineDraw,CShapDrawFactory)

class CCircleDraw : public CShapDraw
{
public:
	CCircleDraw();
	~CCircleDraw();

public:
	void CircleDraw();
	void Draw();
};

//TO_REGISTER_IN("circle",CCircleDraw,CShapDrawFactory)



#endif
