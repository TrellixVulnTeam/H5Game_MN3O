#ifndef _gdb_client_
#define _gdb_client_

#include "node.h"
#include "v8.h"
#include "gdb/pw_gdb_client.h"
#include "gdb/pw_gdb_synchronous_client.h"
#include <string>
#include "bson/bson.h"
#include "mongo/assert_util.h"

using namespace std;
using namespace v8;
using namespace gdb;


class ClientObject;

class ClientUtils
{
public:
	static bool ToInt64(const Local<String>& obj,long long& result);
	static std::string ExtractString(const Local<String>& str);
	static std::string ExtractBuffer(const Local<Value>& str);
	static void BuildPackets(ClientObject* cli,Local<Array>& obj);

	static void BsonToJsObject(const mongo::BSONObj& bsonobj,Handle<Object>& obj);
	static void BsonArrayToJsObject(const mongo::BSONObj& bsonobj,Handle<Array>& obj);

	static bool JsObjectToBson(const Handle<Object>& obj,mongo::BSONObjBuilder& builder);
	static bool JsObjectToBsonArray(const Handle<Object>& obj,mongo::BSONArrayBuilder& builder);

	static Handle<Value> js_TestUtf8(const Arguments& args);
};

class ClientObject : public gdb::SynchronousClient,public node::ObjectWrap
{
public:
	static Handle<Value> New(const Arguments& args);
	static void Initialize(Handle<Object> target);

	static Handle<Value> js_Int32ToUint32(const Arguments& args);
	static Handle<Value> js_StrToInt64(const Arguments& args);
	static Handle<Value> js_Int64ToStr(const Arguments& args);
	static Handle<Value> js_ShowTime(const Arguments& args);
	static Handle<Value> js_RunFile(const Arguments& args);
	static Handle<Value> js_Help(const Arguments& args);

	static Handle<Value> js_AddUser(const Arguments& args);
	static Handle<Value> js_ModUser(const Arguments& args);
	static Handle<Value> js_DelUser(const Arguments& args);

	static Handle<Value> js_Connect(const Arguments& args);
	static Handle<Value> js_Reconnect(const Arguments& args);
	static Handle<Value> js_Close(const Arguments& args);
	static Handle<Value> js_Authentication(const Arguments& args);
	static Handle<Value> js_CreateDatabase(const Arguments& args);
	static Handle<Value> js_DeleteDatabase(const Arguments& args);
	static Handle<Value> js_SelectDatabase(const Arguments& args);
	static Handle<Value> js_ListDatabase(const Arguments& args);
	static Handle<Value> js_RemoveDatas(const Arguments& args);

	static Handle<Value> js_LoadDatabase(const Arguments& args);
	static Handle<Value> js_UnloadDatabase(const Arguments& args);
	static Handle<Value> js_CopyDatabase(const Arguments& args);

	static Handle<Value> js_Hget(const Arguments& args);
	static Handle<Value> js_Hmget(const Arguments& args);
	static Handle<Value> js_Hset(const Arguments& args);
	static Handle<Value> js_Hmset(const Arguments& args);
	static Handle<Value> js_Hdel(const Arguments& args);
	static Handle<Value> js_Hmdel(const Arguments& args);
	static Handle<Value> js_Hall(const Arguments& args);
	static Handle<Value> js_Hkeys(const Arguments& args);
	static Handle<Value> js_Hvals(const Arguments& args);
	static Handle<Value> js_Hsize(const Arguments& args);
	static Handle<Value> js_Hscan(const Arguments& args);
	static Handle<Value> js_Hclear(const Arguments& args);
	static Handle<Value> js_Hincr(const Arguments& args);
	static Handle<Value> js_Hincrfloat(const Arguments& args);
	static Handle<Value> js_HQuery(const Arguments& args);
	static Handle<Value> js_HUpdate(const Arguments& args);
	static Handle<Value> js_HCrossQuery(const Arguments& args);
	static Handle<Value> js_HCrossUpdate(const Arguments& args);

	static Handle<Value> js_HCreateIndex(const Arguments& args);
	static Handle<Value> js_HDeleteIndex(const Arguments& args);
	static Handle<Value> js_HIndexQuery(const Arguments& args);
	static Handle<Value> js_HIndexQueryRange(const Arguments& args);

	static Handle<Value> js_Hcrossall(const Arguments& args);
	static Handle<Value> js_Hcrossvals(const Arguments& args);
	static Handle<Value> js_Hcrossclear(const Arguments& args);

	static Handle<Value> js_Zset(const Arguments& args);
	static Handle<Value> js_Zget(const Arguments& args);
	static Handle<Value> js_Zdel(const Arguments& args);
	static Handle<Value> js_Ztop(const Arguments& args);
	static Handle<Value> js_Zrtop(const Arguments& args);
	static Handle<Value> js_Zsize(const Arguments& args);
	static Handle<Value> js_Zclear(const Arguments& args);
	static Handle<Value> js_Zlist(const Arguments& args);

	static Handle<Value> js_Luaset(const Arguments& args);
	static Handle<Value> js_Luaflt(const Arguments& args);
	static Handle<Value> js_Luaexec(const Arguments& args);
	static Handle<Value> js_Luaclr(const Arguments& args);

	static Handle<Value> js_ModLoad(const Arguments& args);
	static Handle<Value> js_ModExec(const Arguments& args);
	static Handle<Value> js_ModUnload(const Arguments& args);

};

#endif // _gdb_client_