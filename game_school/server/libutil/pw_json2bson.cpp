#include "pw_json2bson.h"
#include "json/json.h"
#include "bson/bson.h"
#include <assert.h>

namespace pwutils
{
	static void __json2bson(Json::Value& json,mongo::BSONObjBuilder& bsonbuilder);

	static void __json2bson_helper(const char* field,Json::Value& json,mongo::BSONObjBuilder& bsonbuilder)
	{
		switch(json.type())
		{
		case Json::arrayValue:
			{
				mongo::BSONObjBuilder tmpbsonbuilder;
				__json2bson(json,tmpbsonbuilder);
				bsonbuilder.appendArray(field,tmpbsonbuilder.obj());
			}
			break;
		case Json::objectValue:
			{
				mongo::BSONObjBuilder tmpbsonbuilder;
				__json2bson(json,tmpbsonbuilder);
				bsonbuilder.append(field,tmpbsonbuilder.obj());
			}
			break;
		case Json::nullValue:
			{
				bsonbuilder.appendNull(field);
			}
			break;
		case Json::intValue:
		case Json::uintValue:
			{
				bsonbuilder.append(field,json.asInt());
			}
			break;
		case Json::realValue:
			{
				bsonbuilder.append(field,json.asDouble());
			}
			break;
		case Json::stringValue:
			{
				bsonbuilder.append(field,json.asString());
			}
			break;
		case Json::booleanValue:
			{
				bsonbuilder.append(field,json.asBool());
			}
			break;
		}
	}

	static void __json2bson(Json::Value& json,mongo::BSONObjBuilder& bsonbuilder)
	{
		switch(json.type())
		{
		case Json::arrayValue:
			{
				Json::UInt size = json.size();
				for(Json::UInt i = 0; i < size; ++i)
				{
					char fieldname[100] = "";
					sprintf(fieldname,"%lld",i);
					__json2bson_helper(fieldname,json[i],bsonbuilder);
				}
			}
			break;
		case Json::objectValue:
			{
				Json::Value::Members fields = json.getMemberNames();
				for(size_t i = 0; i < fields.size(); ++i)
				{
					std::string& r = fields[i];
					__json2bson_helper(r.c_str(),json[r.c_str()],bsonbuilder);
				}
			}
			break;
		default:
			{
				assert(false && "json need root is a object or array");
			}
			break;
		}
	}

	extern bool json2bson( const char* jsonstr,size_t jsonlen,std::string& bson,std::string& error )
	{
		Json::Value jsonobj;
		Json::Reader parser;
		if(!parser.parse(jsonstr,jsonstr + jsonlen,jsonobj))
		{
			error = parser.getFormatedErrorMessages();
			return false;
		}

		mongo::BSONObjBuilder builder;
		__json2bson(jsonobj,builder);

		mongo::BSONObj bsonobj = builder.obj();

		bson.clear();
		bson.reserve(bsonobj.objsize());
		bson.append(bsonobj.objdata(),bsonobj.objsize());
		
		return true;
	}

}