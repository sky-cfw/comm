#include "rapidjson_tools.h"

namespace tools {

bool RapidJsonWrapper::ParseObj(const std::string &s)
{
	if (m_doc.Parse(s.c_str()).HasParseError() || !m_doc.IsObject()) {
		return false;
	}
	return true;
}

bool RapidJsonWrapper::ParseArray(const std::string &s)
{
	if (m_doc.Parse(s.c_str()).HasParseError() || !m_doc.IsArray()) {
		return false;
	}
	return true;
}

void RapidJsonWrapper::ToString(std::string &s)
{
	rapidjson::StringBuffer strBuf;
	rapidjson::Writer<rapidjson::StringBuffer> w(strBuf);
	m_doc.Accept(w);
	s.assign(strBuf.GetString());
}

int RapidJsonWrapper::Int(const char *key, int defaultVal)
{
	rapidjson::Value::MemberIterator it = m_doc.FindMember(key);
	if (it != m_doc.MemberEnd() && it->value.IsInt()) {
		return it->value.GetInt();

	} else {
		return defaultVal;
	}
}

int64_t RapidJsonWrapper::Int64(const char *key, int64_t defaultVal)
{
	rapidjson::Value::MemberIterator it = m_doc.FindMember(key);
	if (it != m_doc.MemberEnd() && it->value.IsInt64()) { 
		return it->value.GetInt64(); 

	} else { 
		return defaultVal; 
	}
}

unsigned int RapidJsonWrapper::Uint(const char *key, unsigned int defaultVal) 
{
	rapidjson::Value::MemberIterator it = m_doc.FindMember(key);
	if (it != m_doc.MemberEnd() && it->value.IsUint()) { 
		return it->value.GetUint(); 

	} else { 
		return defaultVal; 
	}
}

uint64_t RapidJsonWrapper::Uint64(const char *key, uint64_t defaultVal) 
{
	rapidjson::Value::MemberIterator it = m_doc.FindMember(key);
	if (it != m_doc.MemberEnd() && it->value.IsUint64()) { 
		return it->value.GetUint64(); 

	} else { 
		return defaultVal; 
	}
}

double RapidJsonWrapper::Double(const char *key, double defaultVal) 
{
	rapidjson::Value::MemberIterator it = m_doc.FindMember(key);
	if (it != m_doc.MemberEnd() && it->value.IsDouble()) { 
		return it->value.GetDouble(); 

	} else { 
		return defaultVal; 
	}
}

const char *RapidJsonWrapper::String(const char *key, const char *defaultVal) 
{
	rapidjson::Value::MemberIterator it = m_doc.FindMember(key);
	if (it != m_doc.MemberEnd() && it->value.IsString()) { 
		return it->value.GetString(); 

	} else { 
		return defaultVal; 
	}
}

bool RapidJsonWrapper::Bool(const char *key, bool defaultVal) 
{
	rapidjson::Value::MemberIterator it = m_doc.FindMember(key);
	if (it != m_doc.MemberEnd()) {
		if (it->value.IsBool()) { 
			return it->value.GetBool(); 
		}
		if (it->value.IsUint() && it->value.GetUint() <= 1) { 
			return it->value.GetUint(); 
		}
	}
	return defaultVal;
}

bool RapidJsonWrapper::Obj(const char *key, rapidjson::Value::MemberIterator *it) 
{
	if (it == NULL) return false;
	rapidjson::Value::MemberIterator tmpIt = m_doc.FindMember(key);
	if (tmpIt != m_doc.MemberEnd() && tmpIt->value.IsObject()) { 
		*it = tmpIt; 
		return true; 
	}
	return false;
}

bool RapidJsonWrapper::Array(const char *key, rapidjson::Value::MemberIterator *it) 
{
	if (it == NULL) return false;
	rapidjson::Value::MemberIterator tmpIt = m_doc.FindMember(key);
	if (tmpIt != m_doc.MemberEnd() && tmpIt->value.IsArray()) { 
		*it = tmpIt; 
		return true; 
	}
	return false;
}

void RapidJsonWrapper::SetInt(const char *key, int val) 
{
	rapidjson::Value::MemberIterator it = m_doc.FindMember(key);
	if (it == m_doc.MemberEnd()) {
		m_doc.AddMember(rapidjson::Value().SetString(key, m_alloc),
		              rapidjson::Value().SetInt(val),
		              m_alloc);
	} else {
		it->value.SetInt(val);
	}
}

void RapidJsonWrapper::SetInt64(const char *key, int64_t val) 
{
	rapidjson::Value::MemberIterator it = m_doc.FindMember(key);
	if (it == m_doc.MemberEnd()) {
		m_doc.AddMember(rapidjson::Value().SetString(key, m_alloc),
		              rapidjson::Value().SetInt64(val),
		              m_alloc);
	} else {
		it->value.SetInt64(val);
	}
}

void RapidJsonWrapper::SetUint(const char *key, unsigned int val) 
{
	rapidjson::Value::MemberIterator it = m_doc.FindMember(key);
	if (it == m_doc.MemberEnd()) {
		m_doc.AddMember(rapidjson::Value().SetString(key, m_alloc),
		              rapidjson::Value().SetUint(val),
		              m_alloc);
	} else {
		it->value.SetUint(val);
	}
}

void RapidJsonWrapper::SetUint64(const char *key, uint64_t val) 
{
	rapidjson::Value::MemberIterator it = m_doc.FindMember(key);
	if (it == m_doc.MemberEnd()) {
		m_doc.AddMember(rapidjson::Value().SetString(key, m_alloc),
		              rapidjson::Value().SetUint64(val),
		              m_alloc);
	} else {
		it->value.SetUint64(val);
	}
}

void RapidJsonWrapper::SetBool(const char *key, bool val) 
{
	rapidjson::Value::MemberIterator it = m_doc.FindMember(key);
	if (it == m_doc.MemberEnd()) {
		m_doc.AddMember(rapidjson::Value().SetString(key, m_alloc),
		              rapidjson::Value().SetBool(val),
		              m_alloc);
	} else {
		it->value.SetBool(val);
	}
}

void RapidJsonWrapper::SetString(const char *key, const std::string &val) 
{
	rapidjson::Value::MemberIterator it = m_doc.FindMember(key);
	if (it == m_doc.MemberEnd()) {
		m_doc.AddMember(rapidjson::Value().SetString(key, m_alloc),
		              rapidjson::Value().SetString(val.c_str(), m_alloc),
		              m_alloc);
	} else {
		it->value.SetString(val.c_str(), m_alloc);
	}
}

void RapidJsonWrapper::SetVal(const char *key, rapidjson::Value &val) 
{
	rapidjson::Value::MemberIterator it = m_doc.FindMember(key);
	if (it == m_doc.MemberEnd()) {
		m_doc.AddMember(rapidjson::Value().SetString(key, m_alloc), val, m_alloc);

	} else {
		it->value = val;
	}
}

void RapidJsonWrapper::SetCopyVal(const char *key, rapidjson::Value &val ) 
{
	rapidjson::Value::MemberIterator it = m_doc.FindMember(key);
	if (it == m_doc.MemberEnd()) {
		rapidjson::Value copy_value(val, m_alloc);
		m_doc.AddMember(rapidjson::Value().SetString(key, m_alloc), copy_value, m_alloc);

	} else {
		it->value = val;
	}
}

void RapidJsonWrapper::PushInt(int val) 
{
	m_doc.PushBack(rapidjson::Value().SetInt(val), m_alloc);
}

void RapidJsonWrapper::PushInt64(int64_t val) 
{
	m_doc.PushBack(rapidjson::Value().SetInt64(val), m_alloc);
}

void RapidJsonWrapper::PushUint(unsigned int val) 
{
	m_doc.PushBack(rapidjson::Value().SetUint(val), m_alloc);
}

void RapidJsonWrapper::PushUint64(uint64_t val) 
{
	m_doc.PushBack(rapidjson::Value().SetUint64(val), m_alloc);
}

void RapidJsonWrapper::PushBool(bool val) 
{
	m_doc.PushBack(rapidjson::Value().SetBool(val), m_alloc);
}

void RapidJsonWrapper::PushString(const std::string &val) 
{
	m_doc.PushBack(rapidjson::Value().SetString(val.c_str(), m_alloc), m_alloc);
}

void RapidJsonWrapper::PushVal(rapidjson::Value &val) 
{
	// note PushBack is move operation, so make a copy
	rapidjson::Value copy_value(val, m_alloc);
	m_doc.PushBack(copy_value, m_alloc);
}

bool GetRapidJsonInt( const rapidjson::Value &obj, const std::string &key, int &v ) {
	if ( !obj.IsObject() || !obj.HasMember( key.c_str() ) || !obj[key.c_str()].IsInt() ) {
		return false;
	}\
	v = obj[key.c_str()].GetInt();
	return true;
}

bool GetRapidJsonInt64( const rapidjson::Value &obj, const std::string &key, int64_t &v ) {
	if ( !obj.IsObject() || !obj.HasMember( key.c_str() ) || !obj[key.c_str()].IsInt64() ) {
		return false;
	}\
	v = obj[key.c_str()].GetInt64();
	return true;
}

bool GetRapidJsonUint( const rapidjson::Value &obj, const std::string &key, uint32_t &v ) {
	if ( !obj.IsObject() || !obj.HasMember( key.c_str() ) || !obj[key.c_str()].IsUint() ) {
		return false;
	}\
	v = obj[key.c_str()].GetUint();
	return true;
}

bool GetRapidJsonUint64( const rapidjson::Value &obj, const std::string &key, uint64_t &v ) {
	if ( !obj.IsObject() || !obj.HasMember( key.c_str() ) || !obj[key.c_str()].IsUint64() ) {
		return false;
	}\
	v = obj[key.c_str()].GetUint64();
	return true;
}

bool GetRapidJsonDouble( const rapidjson::Value &obj, const std::string &key, double &v ) {
	if ( !obj.IsObject() || !obj.HasMember( key.c_str() ) || !obj[key.c_str()].IsDouble() ) {
		return false;
	}\
	v = obj[key.c_str()].GetDouble();
	return true;
}

bool GetRapidJsonString( const rapidjson::Value &obj, const std::string &key, std::string &v ) {
	if ( !obj.IsObject() || !obj.HasMember( key.c_str() ) || !obj[key.c_str()].IsString() ) {
		return false;
	}\
	v = obj[key.c_str()].GetString();
	return true;
}

bool GetRapidJsonBool( const rapidjson::Value &obj, const std::string &key, bool &v ) {
	if ( !obj.IsObject() || !obj.HasMember( key.c_str() ) || !obj[key.c_str()].IsBool() ) {
		return false;
	}\
	v = obj[key.c_str()].GetBool();
	return true;
}



bool GetRapidJsonInt( const rapidjson::Value &rv, int &v ) {
	if ( !rv.IsInt() ) {
		return false;
	}\
	v = rv.GetInt();
	return true;
}

bool GetRapidJsonInt64( const rapidjson::Value &rv, int64_t &v ) {
	if ( !rv.IsInt64() ) {
		return false;
	}\
	v = rv.GetInt64();
	return true;
}

bool GetRapidJsonUint( const rapidjson::Value &rv, uint32_t &v ) {
	if ( !rv.IsUint() ) {
		return false;
	}\
	v = rv.GetUint();
	return true;
}

bool GetRapidJsonUint64( const rapidjson::Value &rv, uint64_t &v ) {
	if ( !rv.IsUint64() ) {
		return false;
	}\
	v = rv.GetUint64();
	return true;
}

bool GetRapidJsonDouble( const rapidjson::Value &rv, double &v ) {
	if ( !rv.IsDouble() ) {
		return false;
	}\
	v = rv.GetDouble();
	return true;
}

bool GetRapidJsonString( const rapidjson::Value &rv, std::string &v ) {
	if ( !rv.IsString() ) {
		return false;
	}\
	v = rv.GetString();
	return true;
}

bool GetRapidJsonBool( const rapidjson::Value &rv, bool &v ) {
	if ( !rv.IsBool() ) {
		return false;
	}\
	v = rv.GetBool();
	return true;
}


}// namespace tools


