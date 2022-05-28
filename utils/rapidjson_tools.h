/*
 * @Author: sky wcf0118@gmail.com
 * @Date: 2022-05-28 13:07:19
 * @LastEditors: sky wcf0118@gmail.com
 * @LastEditTime: 2022-05-28 21:59:16
 * @FilePath: /comm/utils/rapidjson_tools.h
 * @Description: rapidjson解析封装库
 */
#ifndef RAPIDJSON_TOOLS_H
#define RAPIDJSON_TOOLS_H

#include <stdint.h>
#include <string>
#include <iostream>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

namespace tools
{

bool GetRapidJsonInt( const rapidjson::Value &obj, const std::string &key, int &v );
bool GetRapidJsonInt64( const rapidjson::Value &obj, const std::string &key, int64_t &v );
bool GetRapidJsonUint( const rapidjson::Value &obj, const std::string &key, uint32_t &v );
bool GetRapidJsonUint64( const rapidjson::Value &obj, const std::string &key, uint64_t &v );
bool GetRapidJsonDouble( const rapidjson::Value &obj, const std::string &key, double &v );
bool GetRapidJsonString( const rapidjson::Value &obj, const std::string &key, std::string &v );
bool GetRapidJsonBool( const rapidjson::Value &obj, const std::string &key, bool &v );

bool GetRapidJsonInt( const rapidjson::Value &rv, int &v );
bool GetRapidJsonInt64( const rapidjson::Value &rv, int64_t &v );
bool GetRapidJsonUint( const rapidjson::Value &rv, uint32_t &v );
bool GetRapidJsonUint64( const rapidjson::Value &rv, uint64_t &v );
bool GetRapidJsonDouble( const rapidjson::Value &rv, double &v );
bool GetRapidJsonString( const rapidjson::Value &rv, std::string &v );
bool GetRapidJsonBool( const rapidjson::Value &rv, bool &v );


class RapidJsonWrapper {

private:
	rapidjson::Document m_doc;
	rapidjson::Type m_type;
	rapidjson::Document::AllocatorType &m_alloc;

public:
	RapidJsonWrapper(rapidjson::Type type) : m_type(type), m_alloc(m_doc.GetAllocator()) {

		if (type == rapidjson::kObjectType) {
			m_doc.SetObject();

		} else if (type == rapidjson::kArrayType) {
			m_doc.SetArray();
		}
	}

	rapidjson::Document &GetDoc() { return m_doc; }
	rapidjson::Document::AllocatorType &GetAlloc() { return m_alloc; }
	rapidjson::Type &GetType() { return m_type; }

public:
	// m_doc's type is rapidjson::kObjectType
	bool ParseObj(const std::string &s);

	// m_doc's type is rapidjson::kArrayType
	bool ParseArray(const std::string &s);

	void ToString(std::string &s);

	// Get
	int Int(const char *key, int defaultVal);
	int64_t Int64(const char *key, int64_t defaultVal);
	unsigned int Uint(const char *key, unsigned int defaultVal);
	uint64_t Uint64(const char *key, uint64_t defaultVal);
	double Double(const char *key, double defaultVal);
	const char *String(const char *key, const char *defaultVal);
	bool Bool(const char *key, bool defaultVal);
	bool Obj(const char *key, rapidjson::Value::MemberIterator *it);
	bool Array(const char *key, rapidjson::Value::MemberIterator *it);

	// Set Object
	// m_doc's type is rapidjson::kObjectType
	void SetInt(const char *key, int val);
	void SetInt64(const char *key, int64_t val);
	void SetUint(const char *key, unsigned int val);
	void SetUint64(const char *key, uint64_t val);
	void SetBool(const char *key, bool val);
	void SetString(const char *key, const std::string &val);
	void SetVal(const char *key, rapidjson::Value &val);
	void SetCopyVal(const char *key, rapidjson::Value &val );

	// Set Array
	// m_doc's type is rapidjson::kObjectType
	void PushInt(int val);
	void PushInt64(int64_t val);
	void PushUint(unsigned int val);
	void PushUint64(uint64_t val);
	void PushBool(bool val);
	void PushString(const std::string &val);
	void PushVal(rapidjson::Value &val);

};

}

# endif
