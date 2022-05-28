/*
 * @Author: sky wcf0118@gmail.com
 * @Date: 2022-05-28 15:16:40
 * @LastEditors: sky wcf0118@gmail.com
 * @LastEditTime: 2022-05-29 00:10:43
 * @FilePath: /comm/test/test_rapidjson/test_rapidjson.cpp
 * @Description: rapidjson测试程序
 */
#include "rapidjson_tools.h"
#include "tlog.h"
#include "defs.h"

/*
{
  "int": 1,
  "int64": 2,
  "uint": 3,
  "uint64": 4,
  "bool": true,
  "string": "stringvalue",
  "double": 5.1234,
  "object": {
    "obj.int": 11,
    "obj.string": "obj.stringvalue",
    "obj.double": 15.1234,
    "obj.bool": false
  },
  "array1": [
    {
      "arr.obj.int": 111,
      "arr.obj.string": "arr.obj.stringvalue",
      "arr.obj.double": 115.1234,
      "arr.obj.bool": false
    },
    {
      "arr.obj.int": 211,
      "arr.obj.string": "arr.obj.stringvalue",
      "arr.obj.double": 215.1234,
      "arr.obj.bool": true
    }
  ],
  "array2": [
    311,
    411,
    511
  ],
  "array3": [
    "string1",
    "string2",
    "string3"
  ],
  "array4": [
    1.1,
    2.2,
    3,
    3
  ]
}
*/

int main(int argc, char const *argv[])
{
    TLOG->Init( "test_rapidjson", 2 );
    TLOG_MSG( "start" );

    std::string sJon = "{\"int\":1,\"int64\":2,\"uint\":3,\"uint64\":4,\"bool\":true,\"string\":\"stringvalue\",\"double\":5.1234,\"object\":{\"obj.int\":11,\"obj.string\":\"obj.stringvalue\",\"obj.double\":15.1234,\"obj.bool\":false},\"array1\":[{\"arr.obj.int\":111,\"arr.obj.string\":\"arr.obj.stringvalue\",\"arr.obj.double\":115.1234,\"arr.obj.bool\":false},{\"arr.obj.int\":211,\"arr.obj.string\":\"arr.obj.stringvalue\",\"arr.obj.double\":215.1234,\"arr.obj.bool\":true}],\"array2\":[311,411,511],\"array3\":[\"string1\",\"string2\",\"string3\"],\"array4\":[1.1,2.2,3.3]}";
    tools::RapidJsonWrapper jsonWrapper( rapidjson::kObjectType );
    RETURN_ON_BOOL_ERROR_MSG( jsonWrapper.ParseObj( sJon ), "parse obj[%s] failed", sJon.c_str() );
    
    int a;
    int64_t b;
    uint c;
    uint64_t d;
    bool e;
    std::string f;
    double g;
    a = jsonWrapper.Int( "int", 0 );
    b = jsonWrapper.Int64( "int64", 0 );
    c = jsonWrapper.Uint( "uint", 0 );
    d = jsonWrapper.Uint64( "uint64", 0 );
    e = jsonWrapper.Bool( "bool", 0 );
    f = jsonWrapper.String( "string", "" );
    g = jsonWrapper.Double( "double", 0.0 );
    TLOG_MSG( "a=%d, b=%ld, c=%u, d=%lu, e=%d, f=%s, g=%f", a, b, c, d, e, f.c_str(), g );

    rapidjson::Value::MemberIterator obj_itr;
    RETURN_ON_BOOL_ERROR_MSG( jsonWrapper.Obj( "object", &obj_itr ), "parse element [object] failed" );
    rapidjson::Value &object = obj_itr->value;
    RETURN_ON_BOOL_ERROR_MSG( tools::GetRapidJsonInt( object, "obj.int", a ), "parse element obj.int failed" );
    RETURN_ON_BOOL_ERROR_MSG( tools::GetRapidJsonString( object, "obj.string", f ), "parse element obj.string failed" );
    RETURN_ON_BOOL_ERROR_MSG( tools::GetRapidJsonDouble( object, "obj.double", g ), "parse element obj.double failed" );
    RETURN_ON_BOOL_ERROR_MSG( tools::GetRapidJsonBool( object, "obj.bool", e ), "parse element obj.bool failed" );
    TLOG_MSG( "object: a=%d, e=%d, f=%s, g=%f", a, e, f.c_str(), g );

    rapidjson::Value::MemberIterator arr_itr;
    RETURN_ON_BOOL_ERROR_MSG( jsonWrapper.Array( "array1", &arr_itr ), "parse element [array1] failed" );
    rapidjson::Value &array1 = arr_itr->value;
    for ( rapidjson::SizeType i = 0; i < array1.Size(); i++ ) {
        rapidjson::Value &object = array1[i];
        RETURN_ON_BOOL_ERROR_MSG( tools::GetRapidJsonInt( object, "arr.obj.int", a ), "parse element arr.obj.int failed" );
        RETURN_ON_BOOL_ERROR_MSG( tools::GetRapidJsonString( object, "arr.obj.string", f ), "parse element arr.obj.string failed" );
        RETURN_ON_BOOL_ERROR_MSG( tools::GetRapidJsonDouble( object, "arr.obj.double", g ), "parse element arr.obj.double failed" );
        RETURN_ON_BOOL_ERROR_MSG( tools::GetRapidJsonBool( object, "arr.obj.bool", e ), "parse element arr.obj.bool failed" );
        TLOG_MSG( "i=%u array1.object: a=%d, e=%d, f=%s, g=%f", i, a, e, f.c_str(), g );
    }

    rapidjson::Value::MemberIterator arr_itr2;
    RETURN_ON_BOOL_ERROR_MSG( jsonWrapper.Array( "array2", &arr_itr2 ), "parse element [array2] failed" );
    rapidjson::Value &array2 = arr_itr2->value;
    for ( rapidjson::SizeType i = 0; i < array2.Size(); i++ ) {
        rapidjson::Value &rv = array2[i];
        RETURN_ON_BOOL_ERROR_MSG( tools::GetRapidJsonInt( rv, a ), "parse element arr.int failed" );
        // RETURN_ON_BOOL_ERROR_MSG( tools::GetRapidJsonString( rv, f ), "parse element arr.string failed" );
        // RETURN_ON_BOOL_ERROR_MSG( tools::GetRapidJsonDouble( rv, g ), "parse element arr.double failed" );
        // RETURN_ON_BOOL_ERROR_MSG( tools::GetRapidJsonBool( rv, e ), "parse element arr.bool failed" );
        TLOG_MSG( "i=%u array2: a=%d", i, a );
    }

    rapidjson::Value::MemberIterator arr_itr3;
    RETURN_ON_BOOL_ERROR_MSG( jsonWrapper.Array( "array3", &arr_itr3 ), "parse element [array3] failed" );
    rapidjson::Value &array3 = arr_itr3->value;
    for ( rapidjson::SizeType i = 0; i < array3.Size(); i++ ) {
        rapidjson::Value &rv = array3[i];
        // RETURN_ON_BOOL_ERROR_MSG( tools::GetRapidJsonInt( rv, a ), "parse element arr.int failed" );
        RETURN_ON_BOOL_ERROR_MSG( tools::GetRapidJsonString( rv, f ), "parse element arr.string failed" );
        // RETURN_ON_BOOL_ERROR_MSG( tools::GetRapidJsonDouble( rv, g ), "parse element arr.double failed" );
        // RETURN_ON_BOOL_ERROR_MSG( tools::GetRapidJsonBool( rv, e ), "parse element arr.bool failed" );
        TLOG_MSG( "i=%u array3: f=%s", i, f.c_str() );
    }

    rapidjson::Value::MemberIterator arr_itr4;
    RETURN_ON_BOOL_ERROR_MSG( jsonWrapper.Array( "array4", &arr_itr4 ), "parse element [array4] failed" );
    rapidjson::Value &array4 = arr_itr4->value;
    for ( rapidjson::SizeType i = 0; i < array4.Size(); i++ ) {
        rapidjson::Value &rv = array4[i];
        // RETURN_ON_BOOL_ERROR_MSG( tools::GetRapidJsonInt( rv, a ), "parse element arr.int failed" );
        // RETURN_ON_BOOL_ERROR_MSG( tools::GetRapidJsonString( rv, f ), "parse element arr.string failed" );
        RETURN_ON_BOOL_ERROR_MSG( tools::GetRapidJsonDouble( rv, g ), "parse element arr.double failed" );
        // RETURN_ON_BOOL_ERROR_MSG( tools::GetRapidJsonBool( rv, e ), "parse element arr.bool failed" );
        TLOG_MSG( "i=%u array3: g=%f", i, g );
    }

    return 0;
}
