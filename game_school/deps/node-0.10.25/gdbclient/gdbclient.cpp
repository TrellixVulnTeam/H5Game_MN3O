// gdbclient.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "gdbclient.h"
#include <stdio.h>
#include "gdb/pw_iconv.h"
#include "node_buffer.h"
#include <time.h>
#include <fstream>

static const char* cst_type_int64 = "(longlong)";

namespace utils
{
	long long atoi(const char* str)
	{
		if(str == NULL)
			return 0LL;

	#ifdef _MSC_VER
		return _atoi64(str);
	#else
		return ::atoll(str);
	#endif
	}

	void mylocaltime_r(time_t* t,tm* tt)
	{
#ifdef __linux
		::localtime_r(t,tt);
#else
		::localtime_s(tt,t);
#endif
	}
}

bool ClientUtils::ToInt64(const Local<String>& obj,long long& result)
{
	char vtmpbuf[1024] = {0};
	obj->WriteAscii(vtmpbuf,0,1000);;

	if(memcmp(vtmpbuf,cst_type_int64,strlen(cst_type_int64)) == 0)
	{
		result = utils::atoi(&vtmpbuf[strlen(cst_type_int64)]);
		return true;
	}
	return false;
}

std::string ClientUtils::ExtractString(const Local<String>& str)
{
	std::string result;
	result.resize(str->Length()*3);
	str->WriteUtf8(&result[0]);
	result.resize(strlen(result.c_str()));
	return pwutils::utf8_to_mbs(result);
}

void ClientUtils::BuildPackets(ClientObject* cli,Local<Array>& obj)
{
	std::vector<gdb::SProtocolPacket*> packets;
	cli->GetResponse()->ToArray(packets);

	for(size_t i = 0; i < packets.size(); ++i)
	{
		gdb::SProtocolPacket* pkt = packets[i];
		if(pkt->IsDecimal())
			obj->Set(i,v8::Number::New(pkt->AsDecimal()));
		else if(pkt->IsInteger())
			obj->Set(i,v8::Number::New(pkt->AsInteger()));
		else if(pkt->IsString())
		{
			std::string newstr = pwutils::utf8_from_mbs(std::string(pkt->data,pkt->size));
			obj->Set(i,v8::String::New(newstr.c_str(),newstr.length()));
		}
		else if(pkt->IsNil())
			obj->Set(i,v8::Null());
		else if(pkt->IsBuffer())
		{
			try
			{
				if(pkt->size < sizeof(int))
					throw bson::assertion(0,"");

				const int size = *reinterpret_cast<const int*>(pkt->data);
				if(size != pkt->size)
					throw bson::assertion(0,"");

				mongo::BSONObj bsonobj(pkt->data);
				std::string str = bsonobj.toString();

				Handle<Object> tmpobj = Object::New();
				BsonToJsObject(bsonobj,tmpobj);
				obj->Set(i,tmpobj);
			}
			catch(bson::assertion e)
			{
				if(pkt->size == sizeof(int64))
				{
					obj->Set(i,v8::Number::New(pkt->AsInteger(true)));
				}
				else
				{
					std::string newstr = pwutils::utf8_from_mbs(std::string(pkt->data,pkt->size));
					obj->Set(i,v8::String::New(newstr.c_str(),newstr.length()));
				}
			}
		}
	}		
}

void ClientUtils::BsonToJsObject( const mongo::BSONObj& bsonobj,Handle<Object>& obj )
{
	mongo::BSONObjIterator iter(bsonobj);
	while(iter.more())
	{
		mongo::BSONElement be = iter.next();

		Local<String> fieldName = String::New(be.fieldName());
		
		switch(be.type())
		{
		case mongo::NumberInt:
			obj->Set(fieldName,v8::Number::New(be.numberInt()));
			break;
		case mongo::NumberDouble:
			obj->Set(fieldName,v8::Number::New(be.numberDouble()));
			break;
		case mongo::NumberLong:
			{
				if(be.numberLong() < std::numeric_limits<unsigned int>::max()
					&& be.numberLong() > std::numeric_limits<unsigned int>::min())
				{
					obj->Set(fieldName,v8::Number::New(be.numberLong()));
				}
				else
				{
					std::stringstream ss;
					ss << cst_type_int64 << be.numberLong();
					obj->Set(fieldName,v8::String::New(ss.str().c_str()));
				}
			}
			break;
		case mongo::Bool:
			obj->Set(fieldName,v8::Boolean::New(be.boolean()));
			break;
		case mongo::String:
			{
				std::string newstr = pwutils::utf8_from_mbs(std::string(be.valuestrsafe(),be.valuestrsize() - 1));
				obj->Set(fieldName,v8::String::New(newstr.c_str(),newstr.length()));
			}
			break;
		case mongo::jstNULL:
			obj->Set(fieldName,v8::Null());
			break;
		case mongo::BinData:
			{
				obj->Set(fieldName,v8::Undefined());
			}
			break;
		case mongo::Object:
			{
				Handle<Object> tmpobj = Object::New();
				BsonToJsObject(be.Obj(),tmpobj);
				obj->Set(fieldName,tmpobj);
			}
			break;
		case mongo::Array:
			{
				Handle<Array> tmpobj = Array::New();
				BsonArrayToJsObject(be.Obj(),tmpobj);
				obj->Set(fieldName,tmpobj);
			}
			break;
		default:
			obj->Set(fieldName,v8::Null());
			break;
		}
	}
}

void ClientUtils::BsonArrayToJsObject( const mongo::BSONObj& bsonobj,Handle<Array>& obj )
{
	mongo::BSONObjIterator iter(bsonobj);
	while(iter.more())
	{
		mongo::BSONElement be = iter.next();

		uint32 fieldName = ::atoi(be.fieldName());

		switch(be.type())
		{
		case mongo::NumberInt:
			obj->Set(fieldName,v8::Number::New(be.numberInt()));
			break;
		case mongo::NumberDouble:
			obj->Set(fieldName,v8::Number::New(be.numberDouble()));
			break;
		case mongo::NumberLong:
			{
				if(be.numberLong() < std::numeric_limits<unsigned int>::max() && be.numberLong() > std::numeric_limits<unsigned int>::min())
				{
					obj->Set(fieldName,v8::Number::New(be.numberLong()));
				}
				else
				{
					std::stringstream ss;
					ss << cst_type_int64 << be.numberLong();
					obj->Set(fieldName,v8::String::New(ss.str().c_str()));
				}
			}
			// obj->Set(fieldName,v8::Number::New(be.numberLong()));
			break;
		case mongo::Bool:
			obj->Set(fieldName,v8::Boolean::New(be.boolean()));
			break;
		case mongo::String:
			{
				std::string newstr = pwutils::utf8_from_mbs(std::string(be.valuestrsafe(),be.valuestrsize() - 1));
				obj->Set(fieldName,v8::String::New(newstr.c_str(),newstr.length()));
			}
			break;
		case mongo::jstNULL:
			obj->Set(fieldName,v8::Null());
			break;
		case mongo::BinData:
			obj->Set(fieldName,v8::Undefined());
			break;
		case mongo::Object:
			{
				Handle<Object> tmpobj = Object::New();
				BsonToJsObject(be.Obj(),tmpobj);
				obj->Set(fieldName,tmpobj);
			}
			break;
		case mongo::Array:
			{
				Handle<Array> tmpobj = Array::New();
				BsonArrayToJsObject(be.Obj(),tmpobj);
				obj->Set(fieldName,tmpobj);
			}
			break;
		default:
			obj->Set(fieldName,v8::Null());
			break;
		}
	}
}

bool ClientUtils::JsObjectToBson( const Handle<Object>& obj,mongo::BSONObjBuilder& builder )
{
	Local<Array> names = obj->GetPropertyNames();
	for(uint32 i = 0; i < names->Length(); ++i)
	{
		Handle<Value> name = names->Get(i);
		Handle<Value> value = obj->Get(name);

		std::string field = ClientUtils::ExtractString(name->ToString());
		
		if(value->IsNumber())
		{
			if(value->ToNumber()->NumberValue() == (int32)value->ToNumber()->NumberValue())
				builder.append(field,(int32)value->ToNumber()->NumberValue());
			else if(value->ToNumber()->NumberValue() == (long long)value->ToNumber()->NumberValue())
				builder.append(field,(long long)value->ToNumber()->NumberValue());
			else
				builder.append(field,value->ToNumber()->NumberValue());
		}
		else if(value->IsString())
		{
			long long int64value = 0;
			if(ClientUtils::ToInt64(value->ToString(),int64value))
			{
				builder.append(field,int64value);
			}
			else
			{
				std::string strvalue = ClientUtils::ExtractString(value->ToString());
				builder.append(field,strvalue);
			}
		}
		else if(value->IsBoolean())
		{
			builder.append(field,value->ToBoolean()->BooleanValue());
		}
		else if(value->IsNull())
		{
			builder.appendNull(field);
		}
		else if(value->IsObject())
		{
			mongo::BSONObjBuilder tmpbuilder;
			if(!JsObjectToBson(value->ToObject(),tmpbuilder))
				return false;
			builder.append(field,tmpbuilder.obj());
		}
		else if(value->IsArray())
		{
			mongo::BSONArrayBuilder tmpbuilder;
			if(!JsObjectToBsonArray(value->ToObject(),tmpbuilder))
				return false;
			builder.append(field,tmpbuilder.obj());
		}
		else if(value->IsUndefined())
		{
			std::string detailstring = ClientUtils::ExtractString(value->ToDetailString());
			std::cout << __FUNCTION__ << " invalid type:" << detailstring << std::endl;
			return false;
		}
	}
	return true;
}

bool ClientUtils::JsObjectToBsonArray( const Handle<Object>& obj,mongo::BSONArrayBuilder& builder )
{
	Local<Array> names = obj->GetPropertyNames();
	for(uint32 i = 0; i < names->Length(); ++i)
	{
		Handle<Value> name = names->Get(i);
		Handle<Value> value = obj->Get(name);

		if(value->IsNumber())
		{
			if(value->ToNumber()->NumberValue() == (int32)value->ToNumber()->NumberValue())
				builder.append((int32)value->ToNumber()->NumberValue());
			else if(value->ToNumber()->NumberValue() == (long long)value->ToNumber()->NumberValue())
				builder.append((long long)value->ToNumber()->NumberValue());
			else
				builder.append(value->ToNumber()->NumberValue());
		}
		else if(value->IsString())
		{
			long long int64value = 0;
			if(ClientUtils::ToInt64(value->ToString(),int64value))
			{
				builder.append(int64value);
			}
			else
			{
				std::string strvalue = ClientUtils::ExtractString(value->ToString());
				builder.append(strvalue);
			}
		}
		else if(value->IsBoolean())
		{
			builder.append(value->ToBoolean()->BooleanValue());
		}
		else if(value->IsNull())
		{
			builder.appendNull();
		}
		else if(value->IsObject())
		{
			mongo::BSONObjBuilder tmpbuilder;
			if(!JsObjectToBson(value->ToObject(),tmpbuilder))
				return false;
			builder.append(tmpbuilder.obj());
		}
		else if(value->IsArray())
		{
			mongo::BSONArrayBuilder tmpbuilder;
			if(!JsObjectToBsonArray(value->ToObject(),tmpbuilder))
				return false;
			builder.append(tmpbuilder.obj());
		}
		else if(value->IsUndefined())
		{
			std::string detailstring = ClientUtils::ExtractString(value->ToDetailString());
			std::cout << __FUNCTION__ << " invalid type:" << detailstring << std::endl;
			return false;
		}
	}
	return true;
}

std::string ClientUtils::ExtractBuffer( const Local<Value>& str )
{
	if(str->IsString())
		return ExtractString(str->ToString());
	else if(str->IsObject())
	{
		mongo::BSONObjBuilder builder;
		if(!JsObjectToBson(str->ToObject(),builder))
			return std::string();

		mongo::BSONObj obj = builder.obj();

		return std::string(obj.objdata(),obj.objsize());
	}
	else if(str->IsNumber())
	{
		int64 value = (int64)str->ToNumber()->NumberValue();
		return std::string((char*)&value,sizeof(int64));
	}
	return std::string();
}

Handle<Value> ClientUtils::js_TestUtf8( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 1)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> str = args[0]->ToString();
	char strbuf[1024] = "";
	str->WriteUtf8(strbuf);

	std::string mbs = pwutils::utf8_to_mbs(strbuf);
	std::string utf = pwutils::utf8_from_mbs(mbs);

	return scope.Close(String::New(utf.c_str()));
}

Handle<Value> ClientObject::New(const Arguments& args)
{
	HandleScope scope;
	ClientObject* cli = new ClientObject();
	args.This()->SetPointerInInternalField(0,cli);
	return scope.Close(args.This());
}

void ClientObject::Initialize(Handle<Object> target)
{
	HandleScope scope;

	{
		Local<FunctionTemplate> t = FunctionTemplate::New(ClientObject::New);
		t->InstanceTemplate()->SetInternalFieldCount(1);

		NODE_SET_PROTOTYPE_METHOD(t,"connect",&ClientObject::js_Connect);
		NODE_SET_PROTOTYPE_METHOD(t,"reconnect",&ClientObject::js_Reconnect);
		NODE_SET_PROTOTYPE_METHOD(t,"close",&ClientObject::js_Close);
		NODE_SET_PROTOTYPE_METHOD(t,"auth",&ClientObject::js_Authentication);
		NODE_SET_PROTOTYPE_METHOD(t,"authentication",&ClientObject::js_Authentication);
		NODE_SET_PROTOTYPE_METHOD(t,"create",&ClientObject::js_CreateDatabase);
		NODE_SET_PROTOTYPE_METHOD(t,"delete",&ClientObject::js_DeleteDatabase);
		NODE_SET_PROTOTYPE_METHOD(t,"select",&ClientObject::js_SelectDatabase);
		NODE_SET_PROTOTYPE_METHOD(t,"list",&ClientObject::js_ListDatabase);
		NODE_SET_PROTOTYPE_METHOD(t,"remove_datas",&ClientObject::js_RemoveDatas);

		NODE_SET_PROTOTYPE_METHOD(t,"load",&ClientObject::js_LoadDatabase);
		NODE_SET_PROTOTYPE_METHOD(t,"unload",&ClientObject::js_UnloadDatabase);
		NODE_SET_PROTOTYPE_METHOD(t,"copy",&ClientObject::js_CopyDatabase);

		NODE_SET_PROTOTYPE_METHOD(t,"adduser",&ClientObject::js_AddUser);
		NODE_SET_PROTOTYPE_METHOD(t,"moduser",&ClientObject::js_ModUser);
		NODE_SET_PROTOTYPE_METHOD(t,"deluser",&ClientObject::js_DelUser);

		NODE_SET_PROTOTYPE_METHOD(t,"hget",&ClientObject::js_Hget);
		NODE_SET_PROTOTYPE_METHOD(t,"hmget",&ClientObject::js_Hmget);
		NODE_SET_PROTOTYPE_METHOD(t,"hset",&ClientObject::js_Hset);
		NODE_SET_PROTOTYPE_METHOD(t,"hmset",&ClientObject::js_Hmset);
		NODE_SET_PROTOTYPE_METHOD(t,"hdel",&ClientObject::js_Hdel);
		NODE_SET_PROTOTYPE_METHOD(t,"hmdel",&ClientObject::js_Hmdel);
		NODE_SET_PROTOTYPE_METHOD(t,"hall",&ClientObject::js_Hall);
		NODE_SET_PROTOTYPE_METHOD(t,"hkeys",&ClientObject::js_Hkeys);
		NODE_SET_PROTOTYPE_METHOD(t,"hvals",&ClientObject::js_Hvals);
		NODE_SET_PROTOTYPE_METHOD(t,"hsize",&ClientObject::js_Hsize);
		NODE_SET_PROTOTYPE_METHOD(t,"hscan",&ClientObject::js_Hscan);
		NODE_SET_PROTOTYPE_METHOD(t,"hclear",&ClientObject::js_Hclear);
		NODE_SET_PROTOTYPE_METHOD(t,"hsize",&ClientObject::js_Hsize);
		NODE_SET_PROTOTYPE_METHOD(t,"hincr",&ClientObject::js_Hincr);
		NODE_SET_PROTOTYPE_METHOD(t,"hincrfloat",&ClientObject::js_Hincrfloat);
		NODE_SET_PROTOTYPE_METHOD(t,"hquery",&ClientObject::js_HQuery);
		NODE_SET_PROTOTYPE_METHOD(t,"hupdate",&ClientObject::js_HUpdate);

		NODE_SET_PROTOTYPE_METHOD(t,"hcrossall",&ClientObject::js_Hcrossall);
		NODE_SET_PROTOTYPE_METHOD(t,"hcrossvals",&ClientObject::js_Hcrossvals);
		NODE_SET_PROTOTYPE_METHOD(t,"hcrossclear",&ClientObject::js_Hcrossclear);
		NODE_SET_PROTOTYPE_METHOD(t,"hcrossquery",&ClientObject::js_HCrossQuery);
		NODE_SET_PROTOTYPE_METHOD(t,"hcrossupdate",&ClientObject::js_HCrossUpdate);

		NODE_SET_PROTOTYPE_METHOD(t,"hcreateindex",&ClientObject::js_HCreateIndex);
		NODE_SET_PROTOTYPE_METHOD(t,"hdeleteindex",&ClientObject::js_HDeleteIndex);
		NODE_SET_PROTOTYPE_METHOD(t,"hindexquery",&ClientObject::js_HIndexQuery);
		NODE_SET_PROTOTYPE_METHOD(t,"hindexqueryrange",&ClientObject::js_HIndexQueryRange);

		NODE_SET_PROTOTYPE_METHOD(t,"zset",&ClientObject::js_Zset);
		NODE_SET_PROTOTYPE_METHOD(t,"zget",&ClientObject::js_Zget);
		NODE_SET_PROTOTYPE_METHOD(t,"zdel",&ClientObject::js_Zdel);
		NODE_SET_PROTOTYPE_METHOD(t,"ztop",&ClientObject::js_Ztop);
		NODE_SET_PROTOTYPE_METHOD(t,"zrtop",&ClientObject::js_Zrtop);
		NODE_SET_PROTOTYPE_METHOD(t,"zsize",&ClientObject::js_Zsize);
		NODE_SET_PROTOTYPE_METHOD(t,"zclear",&ClientObject::js_Zclear);
		NODE_SET_PROTOTYPE_METHOD(t,"zlist",&ClientObject::js_Zlist);

		NODE_SET_PROTOTYPE_METHOD(t,"luaset",&ClientObject::js_Luaset);
		NODE_SET_PROTOTYPE_METHOD(t,"luaclr",&ClientObject::js_Luaclr);
		NODE_SET_PROTOTYPE_METHOD(t,"luaexec",&ClientObject::js_Luaexec);
		NODE_SET_PROTOTYPE_METHOD(t,"luaflt",&ClientObject::js_Luaflt);

		NODE_SET_PROTOTYPE_METHOD(t,"modload",&ClientObject::js_ModLoad);
		NODE_SET_PROTOTYPE_METHOD(t,"modexec",&ClientObject::js_ModExec);
		NODE_SET_PROTOTYPE_METHOD(t,"modunload",&ClientObject::js_ModUnload);

		NODE_SET_PROTOTYPE_METHOD(t,"help",&ClientObject::js_Help);

		target->Set(String::NewSymbol("Client"),t->GetFunction());
	}
	// NODE_SET_METHOD(target,"test_utf8",&ClientUtils::js_TestUtf8);
	NODE_SET_METHOD(target,"int2u",&ClientObject::js_Int32ToUint32);
	NODE_SET_METHOD(target,"str2ll",&ClientObject::js_StrToInt64);
	NODE_SET_METHOD(target,"ll2str",&ClientObject::js_Int64ToStr);
	NODE_SET_METHOD(target,"time2str",&ClientObject::js_ShowTime);	
	NODE_SET_METHOD(target,"runfile",&ClientObject::js_RunFile);	
}

Handle<Value> ClientObject::js_Connect(const Arguments& args)
{
	HandleScope scope;
		
	if(args.Length() < 2)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);

	Local<String> host = args[0]->ToString();
	Local<Int32> port = args[1]->ToInt32();

	if(host.IsEmpty() || port.IsEmpty())
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	char actual_host[1024] = "";
	host->WriteAscii(actual_host);

	if(cli->Connect(actual_host,port->Int32Value()) != 0)
		return v8::ThrowException(v8::Exception::Error(String::New("SOCKET_CONNECT_FAILED")));

	cli->m_bConnected = true;

	return scope.Close(Boolean::New(true));
}

Handle<Value> ClientObject::js_Reconnect(const Arguments& args)
{
	HandleScope scope;

	if(args.Length() != 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);

	if(cli->IsConnected())
		return scope.Close(Boolean::New(true));

	if(cli->Reconnect() == 0)
		return scope.Close(Boolean::New(true));
	return scope.Close(Boolean::New(false));
}

Handle<Value> ClientObject::js_Close( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	cli->Close();

	return scope.Close(Boolean::New(true));
}

Handle<Value> ClientObject::js_Authentication(const Arguments& args)
{		
	HandleScope scope;

	if(args.Length() < 2)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> user = args[0]->ToString();
	Local<String> pswd = args[1]->ToString();

	if(user.IsEmpty() || pswd.IsEmpty())
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	char actual_user[1024] = "";
	char actual_pswd[1024] = "";
	user->WriteAscii(actual_user);
	pswd->WriteAscii(actual_pswd);

	if(cli->Authentication(actual_user,actual_pswd) == 0)
		return scope.Close(Boolean::New(true));
	return scope.Close(String::New(cli->LastErrorString()));
}

Handle<Value> ClientObject::js_CreateDatabase(const Arguments& args)
{		
	HandleScope scope;

	if(args.Length() < 1)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> dbname = args[0]->ToString();

	if(dbname.IsEmpty())
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	char actual_dbname[1024] = "";
	dbname->WriteAscii(actual_dbname);

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	if(cli->CreateDatabase(actual_dbname) == 0)
		return scope.Close(Boolean::New(true));
	return scope.Close(Boolean::New(false));
}

Handle<Value> ClientObject::js_DeleteDatabase(const Arguments& args)
{		
	HandleScope scope;

	if(args.Length() < 1)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> dbname = args[0]->ToString();

	if(dbname.IsEmpty())
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	char actual_dbname[1024] = "";
	dbname->WriteAscii(actual_dbname);

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	if(cli->DeleteDatabase(actual_dbname) == 0)
		return scope.Close(Boolean::New(true));
	return scope.Close(Boolean::New(false));
}

Handle<Value> ClientObject::js_SelectDatabase(const Arguments& args)
{		
	HandleScope scope;

	if(args.Length() < 1)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> dbname = args[0]->ToString();

	if(dbname.IsEmpty())
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	char actual_dbname[1024] = "";
	dbname->WriteAscii(actual_dbname);

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	if(cli->SelectDatabase(actual_dbname) == 0)
		return scope.Close(Boolean::New(true));
	return scope.Close(String::New(cli->LastErrorString()));
}

Handle<Value> ClientObject::js_ListDatabase(const Arguments& args)
{		
	HandleScope scope;

	if(args.Length() != 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::vector<std::string> list;
	cli->ListDatabases(list);

	Local<Array> result = Array::New();
	for(size_t i = 0; i < list.size(); ++i)
		result->Set(i,String::New(list[i].c_str()));
	return scope.Close(result);
}

Handle<Value> ClientObject::js_RemoveDatas(const Arguments& args)
{
	HandleScope scope;

	if(args.Length() != 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::vector<std::string> list;
	cli->RemoveAll();

	Local<Array> result = Array::New();
	for(size_t i = 0; i < list.size(); ++i)
		result->Set(i,String::New(list[i].c_str()));
	return scope.Close(result);
}

Handle<Value> ClientObject::js_Hget(const Arguments& args)
{		
	HandleScope scope;

	if(args.Length() != 2)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();
	Local<String> key = args[1]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);
	std::string akey = ClientUtils::ExtractString(key);

	if(aname.length() <= 0 || akey.length() <= 0 )
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Hget(aname,akey);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}
	
	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_Hmget(const Arguments& args)
{
	HandleScope scope;

	if(args.Length() != 2)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();
	Local<Object> keys = args[1]->ToObject();

	if(!keys->IsArray())
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<Array> array_keys = Local<Array>::Cast(keys);

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);
	
	std::vector<std::string> akeys;
	for(size_t i = 0; i < array_keys->Length(); ++i)
	{
		Local<String> k = Local<String>::Cast(array_keys->Get(i));
		akeys.push_back(ClientUtils::ExtractString(k));
	}

	cli->Hmultiget(aname,akeys);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_Hset( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 3)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();
	Local<String> key = args[1]->ToString();
	Local<Value> val = args[2];

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);
	std::string akey = ClientUtils::ExtractString(key);
	std::string aval = ClientUtils::ExtractBuffer(val);

	if(aname.length() <= 0 || akey.length() <= 0  || aval.length() <= 0 )
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Hset(aname,akey,aval);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	return scope.Close(Boolean::New(true));
}

Handle<Value> ClientObject::js_Hmset( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 3)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();
	Local<Object> keys = args[1]->ToObject();
	Local<Object> vals = args[2]->ToObject();

	if(!keys->IsArray() || !vals->IsArray())
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<Array> array_keys = Local<Array>::Cast(keys);
	Local<Array> array_vals = Local<Array>::Cast(vals);
	if(array_keys->Length() != array_vals->Length())
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS_KEYVAL_SIZE_NOMATCH")));

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);

	std::vector<std::string> akeys;
	std::vector<std::string> avals;
	for(size_t i = 0; i < array_keys->Length(); ++i)
	{
		Local<String> k = Local<String>::Cast(array_keys->Get(i));
		Local<Object> v = Local<Object>::Cast(array_vals->Get(i));

		akeys.push_back(ClientUtils::ExtractString(k));
		avals.push_back(ClientUtils::ExtractBuffer(v));
	}

	cli->Hmultiset(aname,akeys,avals);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_Hdel( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 2)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();
	Local<String> key = args[1]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);
	std::string akey = ClientUtils::ExtractString(key);

	if(aname.length() <= 0 || akey.length() <= 0 )
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Hdel(aname,akey);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	return scope.Close(Boolean::New(true));
}

Handle<Value> ClientObject::js_Hmdel(const Arguments& args)
{
	HandleScope scope;

	if(args.Length() != 2)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();
	Local<Object> keys = args[1]->ToObject();

	if(!keys->IsArray())
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<Array> array_keys = Local<Array>::Cast(keys);

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);

	std::vector<std::string> akeys;
	for(size_t i = 0; i < array_keys->Length(); ++i)
	{
		Local<String> k = Local<String>::Cast(array_keys->Get(i));
		akeys.push_back(ClientUtils::ExtractString(k));
	}

	cli->Hmultidel(aname,akeys);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_Hall( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 1)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);

	if(aname.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Hall(aname);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_Hkeys(const Arguments& args)
{
	HandleScope scope;

	if(args.Length() != 1)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);

	if(aname.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Hkeys(aname);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_Hvals( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 1)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);

	if(aname.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Hvals(aname);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_Hcrossall( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 1)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);

	if(aname.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Hcrossall(aname);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_Hcrossclear(const Arguments& args)
{
	HandleScope scope;

	if(args.Length() != 1)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);

	if(aname.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Hcrossclear(aname);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_Hcrossvals(const Arguments& args)
{
	HandleScope scope;

	if(args.Length() != 1)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);

	if(aname.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Hcrossall(aname,false);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_Hsize( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 1)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);

	if(aname.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Hsize(aname);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_Hscan( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 4)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();
	Local<String> pattern = args[1]->ToString();
	Local<String> start = args[2]->ToString();
	Local<Integer> limit = args[3]->ToInteger();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);
	std::string apattern = ClientUtils::ExtractString(pattern);
	std::string astart = ClientUtils::ExtractString(start);
	int64 alimit = limit->IntegerValue();


	if(aname.length() <= 0 || apattern.length() <= 0 || alimit <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Hscan(aname,apattern,astart,alimit);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_Hincr( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 3)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> hname = args[0]->ToString();
	Local<String> hkey = args[1]->ToString();
	Local<Number> ivalue = args[2]->ToNumber();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(hname);
	std::string akey = ClientUtils::ExtractString(hkey);
	int64 incr = (int64)ivalue->NumberValue();

	if(aname.length() <= 0 || akey.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Hincrby(aname,akey,incr);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);

}

Handle<Value> ClientObject::js_Hincrfloat( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 3)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> hname = args[0]->ToString();
	Local<String> hkey = args[1]->ToString();
	Local<Number> ivalue = args[2]->ToNumber();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(hname);
	std::string akey = ClientUtils::ExtractString(hkey);
	double incr = (double)ivalue->NumberValue();

	if(aname.length() <= 0 || akey.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Hincrbyfloat(aname,akey,incr);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);

}

Handle<Value> ClientObject::js_HQuery(const Arguments& args)
{
	HandleScope scope;

	if(args.Length() != 2)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> hname = args[0]->ToString();
	Local<Object> query_object = args[1]->ToObject();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(hname);
	
	mongo::BSONObjBuilder builder;
	ClientUtils::JsObjectToBson(query_object,builder);
	mongo::BSONObj bsonobj = builder.obj();

	if(aname.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Hquery(aname,bsonobj.objdata(),bsonobj.objsize());

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_HUpdate(const Arguments& args)
{
	HandleScope scope;

	if(args.Length() != 3)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> hname = args[0]->ToString();
	Local<Object> query_object = args[1]->ToObject();
	Local<Object> update_object = args[2]->ToObject();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(hname);

	mongo::BSONObjBuilder builder;
	ClientUtils::JsObjectToBson(query_object,builder);
	mongo::BSONObj bsonobj = builder.obj();

	mongo::BSONObjBuilder updatebuilder;
	ClientUtils::JsObjectToBson(update_object,updatebuilder);
	mongo::BSONObj updatebsonobj = updatebuilder.obj();

	if(aname.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Hupdate(aname,bsonobj.objdata(),bsonobj.objsize(),updatebsonobj.objdata(),updatebsonobj.objsize());

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_HCrossQuery(const Arguments& args)
{
	HandleScope scope;

	if(args.Length() != 2)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> hname = args[0]->ToString();
	Local<Object> query_object = args[1]->ToObject();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(hname);

	mongo::BSONObjBuilder builder;
	ClientUtils::JsObjectToBson(query_object,builder);
	mongo::BSONObj bsonobj = builder.obj();

	if(aname.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Hcrossquery(aname,bsonobj.objdata(),bsonobj.objsize());

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_HCrossUpdate(const Arguments& args)
{
	HandleScope scope;

	if(args.Length() != 3)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> hname = args[0]->ToString();
	Local<Object> query_object = args[1]->ToObject();
	Local<Object> update_object = args[2]->ToObject();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(hname);

	mongo::BSONObjBuilder builder;
	ClientUtils::JsObjectToBson(query_object,builder);
	mongo::BSONObj bsonobj = builder.obj();

	mongo::BSONObjBuilder updatebuilder;
	ClientUtils::JsObjectToBson(update_object,updatebuilder);
	mongo::BSONObj updatebsonobj = updatebuilder.obj();

	if(aname.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Hcrossupdate(aname,bsonobj.objdata(),bsonobj.objsize(),updatebsonobj.objdata(),updatebsonobj.objsize());

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_Hclear( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 1)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);

	if(aname.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Hclear(aname);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_Zset( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 3)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();
	Local<String> key = args[1]->ToString();
	Local<Number> val = args[2]->ToNumber();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);
	std::string akey = ClientUtils::ExtractString(key);
	int64 aval = (int64)val->NumberValue();

	if(aname.length() <= 0 || akey.length() <= 0 )
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Zset(aname,akey,aval);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	return scope.Close(Boolean::New(true));
}

Handle<Value> ClientObject::js_Zget( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 2)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();
	Local<String> key = args[1]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);
	std::string akey = ClientUtils::ExtractString(key);

	if(aname.length() <= 0 || akey.length() <= 0 )
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Zget(aname,akey);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_Zdel( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 2)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();
	Local<String> key = args[1]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);
	std::string akey = ClientUtils::ExtractString(key);

	if(aname.length() <= 0 || akey.length() <= 0 )
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Zdel(aname,akey);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	return scope.Close(Boolean::New(true));
}

Handle<Value> ClientObject::js_Ztop( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 2)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();
	Local<Number> limit = args[1]->ToNumber();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);
	int64 alimit = (int64)limit->NumberValue();

	if(aname.length() <= 0 || alimit <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Ztop(aname,alimit);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_Zrtop( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 2)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();
	Local<Number> limit = args[1]->ToNumber();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);
	int64 alimit = (int64)limit->NumberValue();

	if(aname.length() <= 0 || alimit <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Zrtop(aname,alimit);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_Zsize( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 1)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);

	if(aname.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Zsize(aname);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_Zclear( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 1)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);

	if(aname.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Zclear(aname);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_Zlist( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	cli->Zlist();

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_AddUser( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 3)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();
	Local<String> pswd = args[0]->ToString();
	Local<Boolean> super = args[0]->ToBoolean();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);
	std::string apswd = ClientUtils::ExtractString(pswd);

	if(aname.length() <= 0 || apswd.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	if(cli->AddUser(aname,apswd,super->BooleanValue()) != 0)
	{
		return scope.Close(String::New(cli->LastErrorString()));
	}

	return scope.Close(Boolean::New(true));
}

Handle<Value> ClientObject::js_ModUser( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 3)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();
	Local<String> pswd = args[0]->ToString();
	Local<Boolean> super = args[0]->ToBoolean();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);
	std::string apswd = ClientUtils::ExtractString(pswd);

	if(aname.length() <= 0 || apswd.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	if(cli->ModUser(aname,apswd,super->BooleanValue()) != 0)
	{
		return scope.Close(String::New(cli->LastErrorString()));
	}
	return scope.Close(Boolean::New(true));
}

Handle<Value> ClientObject::js_DelUser( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 1)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);

	if(aname.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	if(cli->DelUser(aname) != 0)
	{
		return scope.Close(String::New(cli->LastErrorString()));
	}

	return scope.Close(Boolean::New(true));
}

Handle<Value> ClientObject::js_Help( const Arguments& args )
{
	HandleScope scope;

	Local<Array> result = Array::New();
	
	result->Set(result->Length(),String::New("connect(host,port)"));
	result->Set(result->Length(),String::New("close()"));
	result->Set(result->Length(),String::New("authentication(user,pswd)"));
	result->Set(result->Length(),String::New("create(dbname)"));
	result->Set(result->Length(),String::New("delete(dbname)"));
	result->Set(result->Length(),String::New("select(dbname)"));
	result->Set(result->Length(),String::New("list()"));

	result->Set(result->Length(),String::New("adduser(user,pswd,super<bool>)"));
	result->Set(result->Length(),String::New("moduser(user,pswd,super<bool>)"));
	result->Set(result->Length(),String::New("deluser(user)"));

	result->Set(result->Length(),String::New("hget(hname,key)"));
	result->Set(result->Length(),String::New("hdel(hname,key)"));
	result->Set(result->Length(),String::New("hset(hname,key,val)"));
	result->Set(result->Length(),String::New("hall(hname)"));
	result->Set(result->Length(),String::New("hkeys(hname)"));
	result->Set(result->Length(),String::New("hvals(hname)"));
	result->Set(result->Length(),String::New("hscan(hname,pattern,start,limit)"));
	result->Set(result->Length(),String::New("hclear(hname)"));
	result->Set(result->Length(),String::New("hincr(hname,incr)"));
	result->Set(result->Length(),String::New("hincrfloat(hname,incr)"));
	
	result->Set(result->Length(),String::New("hcrossall(hname)"));
	result->Set(result->Length(),String::New("hcrossvals(hname)"));
	result->Set(result->Length(),String::New("hcrossclear(hname)"));
	
	result->Set(result->Length(),String::New("zset(zname,key,val<int64>)"));
	result->Set(result->Length(),String::New("zget(zname,key)"));
	result->Set(result->Length(),String::New("zdel(zname,key)"));
	result->Set(result->Length(),String::New("zsize(zname)"));
	result->Set(result->Length(),String::New("ztop(zname,limit<int64>)"));
	result->Set(result->Length(),String::New("zrtop(zname,limit<int64>)"));
	result->Set(result->Length(),String::New("zclear(zname)"));

	result->Set(result->Length(),String::New("luaset(filename)"));
	result->Set(result->Length(),String::New("luaclr()"));
	result->Set(result->Length(),String::New("luaflt(func)"));
	result->Set(result->Length(),String::New("luaexec(func,para)"));

	result->Set(result->Length(),String::New("reconnect()"));
	return scope.Close(result);
}

Handle<Value> ClientObject::js_LoadDatabase( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() < 1)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> dbname = args[0]->ToString();

	if(dbname.IsEmpty())
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	char actual_dbname[1024] = "";
	dbname->WriteAscii(actual_dbname);

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	if(cli->LoadDatabase(actual_dbname) == 0)
		return scope.Close(Boolean::New(true));
	return scope.Close(Boolean::New(false));
}

Handle<Value> ClientObject::js_UnloadDatabase( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() < 1)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> dbname = args[0]->ToString();

	if(dbname.IsEmpty())
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	char actual_dbname[1024] = "";
	dbname->WriteAscii(actual_dbname);

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	if(cli->UnloadDatabase(actual_dbname) == 0)
		return scope.Close(Boolean::New(true));
	return scope.Close(Boolean::New(false));
}

Handle<Value> ClientObject::js_CopyDatabase( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() < 2)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> srcdbname = args[0]->ToString();
	Local<String> dstdbname = args[1]->ToString();

	if(srcdbname.IsEmpty() || dstdbname.IsEmpty())
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	char actual_srcdbname[1024] = "";
	char actual_dstdbname[1024] = "";
	srcdbname->WriteAscii(actual_srcdbname);
	dstdbname->WriteAscii(actual_dstdbname);

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	if(cli->CopyDatabase(actual_srcdbname,actual_dstdbname) == 0)
		return scope.Close(Boolean::New(true));
	return scope.Close(Boolean::New(false));
}

Handle<Value> ClientObject::js_Int32ToUint32( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 1)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<Uint32> value = args[0]->ToUint32();

	return scope.Close(Integer::NewFromUnsigned(value->Value()));
}

Handle<Value> ClientObject::js_Int64ToStr(const Arguments& args)
{
	HandleScope scope;

	if(args.Length() != 1 || !args[0]->IsString())
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS:STRING")));

	long long result;
	if(!ClientUtils::ToInt64(args[0]->ToString(),result))
		return scope.Close(v8::Undefined());

	std::stringstream ss;
	ss << result;
	return scope.Close(v8::String::New(ss.str().c_str()));
}

Handle<Value> ClientObject::js_StrToInt64(const Arguments& args)
{
	HandleScope scope;

	if(args.Length() != 1 || !args[0]->IsString())
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS:STRING")));

	char vtmpbuf[1024] = {0};
	args[0]->ToString()->WriteAscii(vtmpbuf,0,1000);;

	std::string newval(cst_type_int64);
	newval.append(vtmpbuf);

	return scope.Close(v8::String::New(newval.c_str()));
}

Handle<Value> ClientObject::js_ShowTime(const Arguments& args)
{
	HandleScope scope;

	if(args.Length() != 1 || !args[0]->IsString())
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS:STRING")));

	char ktmpbuf[1024] = {0};
	char vtmpbuf[1024] = {0};
	Local<String> kstr = args[0]->ToString();
	kstr->WriteAscii(vtmpbuf,0,1000);

	time_t curr = utils::atoi(vtmpbuf);
	
	struct tm tmcurr = {0};
	utils::mylocaltime_r(&curr,&tmcurr);
	strftime(ktmpbuf,1000,"%Y-%m-%d %H:%M:%S",&tmcurr);

	return scope.Close(v8::String::New(ktmpbuf));
}

Handle<Value> ClientObject::js_RunFile(const Arguments& args)
{
	HandleScope scope;

	if(args.Length() != 1 || !args[0]->IsString())
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS:STRING")));

	char vtmpbuf[1024] = {0};
	Local<String> kstr = args[0]->ToString();
	kstr->WriteAscii(vtmpbuf,0,1000);

	std::fstream stream;
	stream.open(vtmpbuf,std::ios_base::in);
	if(!stream.good())
		return v8::ThrowException(v8::Exception::Error(String::New("OPEN_FILE_FAILED")));

	stream.seekg(0,std::ios_base::end);
	size_t size = stream.tellg();
	stream.seekg(0,std::ios_base::beg);

	char* buf = new char[size];
	stream.read(buf,size);
	
	Handle<String> str = String::New(buf,size);
	delete [] buf;

	TryCatch trycatch;
	Handle<Script> script = Script::Compile(str);
	if(trycatch.HasCaught())
		return v8::ThrowException(trycatch.Exception());

	Handle<Value> result = script->Run();
	if(trycatch.HasCaught())
		return v8::ThrowException(trycatch.Exception());

	return scope.Close(result);
}

Handle<Value> ClientObject::js_Luaset( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 1)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> filename = args[0]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string afile = ClientUtils::ExtractString(filename);

	if(afile.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	if(cli->LuasetFile(afile) != 0)
		return scope.Close(String::New("read file failed"));

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	return scope.Close(Boolean::New(true));
}

Handle<Value> ClientObject::js_Luaflt( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 1)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> func = args[0]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string afunc = ClientUtils::ExtractString(func);

	if(afunc.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Luaflt(afunc);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	return scope.Close(Boolean::New(true));
}

Handle<Value> ClientObject::js_Luaexec( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 2)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> func = args[0]->ToString();
	Local<String> para = args[1]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string afunc = ClientUtils::ExtractString(func);
	std::string apara = ClientUtils::ExtractString(para);

	if(afunc.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Luaexec(afunc,apara);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_Luaclr( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	cli->Luaclr();

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	return scope.Close(Boolean::New(true));
}

Handle<Value> ClientObject::js_ModLoad( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 2)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();
	Local<String> file = args[1]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);
	std::string afile = ClientUtils::ExtractString(file);

	if(aname.length() <= 0 || afile.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->ModLoad(aname,afile);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	return scope.Close(Boolean::New(true));
}

Handle<Value> ClientObject::js_ModExec( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 2)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);
	std::string aparams = ClientUtils::ExtractBuffer(args[1]);

	if(aname.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->ModExec(aname,aparams.c_str(),aparams.length());

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_ModUnload( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 1)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);

	if(aname.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->ModUnload(aname);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	return scope.Close(Boolean::New(true));
}

Handle<Value> ClientObject::js_HCreateIndex( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 3)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();
	Local<String> field = args[1]->ToString();
	Local<String> type = args[2]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);
	std::string afield = ClientUtils::ExtractString(field);
	std::string atype = ClientUtils::ExtractString(type);

	if(aname.length() <= 0 || afield.length() <= 0 || atype.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	if(atype != "string" && atype != "number")
		return v8::ThrowException(v8::Exception::Error(String::New("TYPE_EXPECT_string|number")));

	if(atype == "string")
		cli->Hcreateindex(aname,afield,gdb::ClientInterface::INDEX_TYPE_STRING);
	else if(atype == "number")
		cli->Hcreateindex(aname,afield,gdb::ClientInterface::INDEX_TYPE_NUMBER);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	return scope.Close(Boolean::New(true));
}

Handle<Value> ClientObject::js_HDeleteIndex( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 3)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();
	Local<String> field = args[1]->ToString();
	Local<String> type = args[2]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);
	std::string afield = ClientUtils::ExtractString(field);
	std::string atype = ClientUtils::ExtractString(type);

	if(aname.length() <= 0 || afield.length() <= 0 || atype.length() <= 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	if(atype != "string" && atype != "number")
		return v8::ThrowException(v8::Exception::Error(String::New("TYPE_EXPECT_string|number")));

	if(atype == "string")
		cli->Hdeleteindex(aname,afield,gdb::ClientInterface::INDEX_TYPE_STRING);
	else if(atype == "number")
		cli->Hdeleteindex(aname,afield,gdb::ClientInterface::INDEX_TYPE_NUMBER);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	return scope.Close(Boolean::New(true));
}

Handle<Value> ClientObject::js_HIndexQuery( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 3)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();
	Local<String> field = args[2]->ToString();
	Local<String> value = args[3]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);
	std::string afield = ClientUtils::ExtractString(field);
	std::string avalue = ClientUtils::ExtractString(value);

	if(aname.length() == 0 || afield.length() == 0 || avalue.length() == 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Hindexquery(aname,afield,avalue);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}

Handle<Value> ClientObject::js_HIndexQueryRange( const Arguments& args )
{
	HandleScope scope;

	if(args.Length() != 4)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	Local<String> name = args[0]->ToString();
	Local<String> field = args[2]->ToString();
	Local<String> start = args[3]->ToString();
	Local<String> ended = args[4]->ToString();

	ClientObject* cli = (ClientObject*)args.This()->GetPointerFromInternalField(0);
	if(cli == NULL || !cli->IsConnected())
		return scope.Close(String::New("Client Closed"));

	std::string aname = ClientUtils::ExtractString(name);
	std::string afield = ClientUtils::ExtractString(field);
	std::string astart = ClientUtils::ExtractString(start);
	std::string aended = ClientUtils::ExtractString(ended);

	if(aname.length() == 0 || afield.length() == 0 || aended.length() == 0 || aended.length() == 0)
		return v8::ThrowException(v8::Exception::Error(String::New("INVALID_ARGS")));

	cli->Hindexqueryrange(aname,afield,astart,aended);

	if(!cli->GetResponse()->IsSuccessful())
	{
		return scope.Close(String::New(cli->GetResponse()->GetErrorString()));
	}

	Local<Array> result = Array::New();
	ClientUtils::BuildPackets(cli,result);
	return scope.Close(result);
}


extern "C"
{
	void init(Handle<Object> target)
	{
		HandleScope scope;
		ClientObject::Initialize(target);
	}

};

NODE_MODULE(gdbclient,init)
