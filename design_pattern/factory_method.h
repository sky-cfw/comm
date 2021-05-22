#ifndef FACTORY_H
#define FACTORY_H

class CCfgParse
{
public:
	CCfgParse();
	virtual ~CCfgParse();

	virtual void DoParseFile( const std::string &sFileExtension ) = 0;
};

class CXmlCfgParse : public CCfgParse
{
public:
	CXmlCfgParse();
	~CXmlCfgParse();

public:
	DoParseFile( const std::string &sFileExtension );
};

class CJsonCfgParse : public CCfgParse
{
public:
	CJsonCfgParse();
	~CJsonCfgParse();

public:
	DoParseFile( const std::string &sFileExtension );
};

#endif
