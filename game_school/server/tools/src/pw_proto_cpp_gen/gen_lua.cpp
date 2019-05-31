#include "main.h"
#include <io.h>


using namespace google::protobuf;


void my_tolower(std::string& val)
{
	for(size_t i = 0; i < val.length(); ++i)
	{
		val[i] = ::tolower(val[i]);
	}
}

std::string PopFieldToMsg(const FieldDescriptor* fdd)
{
	std::string fieldName = fdd->name();
	my_tolower(fieldName);

	switch (fdd->type())
	{
	case FieldDescriptor::TYPE_FIXED32:
	case FieldDescriptor::TYPE_INT32:
	case FieldDescriptor::TYPE_UINT32:
	case FieldDescriptor::TYPE_SFIXED32:
	case FieldDescriptor::TYPE_SINT32:
		if(fdd->is_repeated())
			return "msg.add_" + fieldName + "(lua_tointeger(L,-1));";
		else
			return "msg.set_" + fieldName + "(lua_tointeger(L,-1));";
		break;

	case FieldDescriptor::TYPE_DOUBLE:
		if(fdd->is_repeated())
			return "msg.add_" + fieldName + "(lua_tonumber(L,-1));";
		else
			return "msg.set_" + fieldName + "(lua_tonumber(L,-1));";
		break;
	case FieldDescriptor::TYPE_FLOAT:
		if(fdd->is_repeated())
			return "msg.add_" + fieldName + "((float)lua_tonumber(L,-1));";
		else
			return "msg.set_" + fieldName + "((float)lua_tonumber(L,-1));";
		break;
	case FieldDescriptor::TYPE_INT64:
	case FieldDescriptor::TYPE_UINT64:
	case FieldDescriptor::TYPE_FIXED64:
	case FieldDescriptor::TYPE_SFIXED64:
	case FieldDescriptor::TYPE_SINT64:
		if(fdd->is_repeated())
			return "msg.add_" + fieldName + "(pwlua::_detail::stack_helper<int64>::cast(L,-1));";
		else
			return "msg.set_" + fieldName + "(pwlua::_detail::stack_helper<int64>::cast(L,-1));";
		break;
	case FieldDescriptor::TYPE_BOOL:
		if(fdd->is_repeated())
			return "msg.add_" + fieldName + "(lua_toboolean(L,-1));";
		else
			return "msg.set_" + fieldName + "(lua_toboolean(L,-1));";
		break;
	case FieldDescriptor::TYPE_STRING:
	case FieldDescriptor::TYPE_BYTES:
		if(fdd->is_repeated())
			return "msg.add_" + fieldName + "(lua_tostring(L,-1));";
		else
			return "msg.set_" + fieldName + "(lua_tostring(L,-1));";
		break;
	case FieldDescriptor::TYPE_MESSAGE:
		{
			std::string msgname = fdd->message_type()->name();
			std::string result;
			if(fdd->is_repeated())
			{
				result += msgname + "* tmpmsg = msg.add_" + fieldName + "();";
				result += "LuaToMsg(L,-1,*tmpmsg);";
			}
			else
			{
				result += msgname + "* tmpmsg = msg.mutable_" + fieldName + "();";
				result += "LuaToMsg(L,-1,*tmpmsg);";
			}
			return result;
		}
		break;
	case FieldDescriptor::TYPE_ENUM:
		{
			std::string enumname = fdd->enum_type()->name();

			if(fdd->is_repeated())
				return "msg.add_" + fieldName + "((" + enumname + ")lua_tointeger(L,-1));";
			else
				return "msg.set_" + fieldName + "((" + enumname + ")lua_tointeger(L,-1));";
		}
		break;
	}
	return "Error type";
}

std::string PushField(const FieldDescriptor* fdd)
{
	std::string fieldName = fdd->name();
	my_tolower(fieldName);

	switch (fdd->type())
	{
	case FieldDescriptor::TYPE_FIXED32:
	case FieldDescriptor::TYPE_INT32:
	case FieldDescriptor::TYPE_UINT32:
	case FieldDescriptor::TYPE_SFIXED32:
	case FieldDescriptor::TYPE_SINT32:
		if(fdd->is_repeated())
			return "lua_pushinteger(L,msg." + fieldName + "(i));";
		else
			return "lua_pushinteger(L,msg." + fieldName + "());";
		break;
	case FieldDescriptor::TYPE_DOUBLE:
	case FieldDescriptor::TYPE_FLOAT:
		if(fdd->is_repeated())
			return "lua_pushnumber(L,msg." + fieldName + "(i));";
		else
			return "lua_pushnumber(L,msg." + fieldName + "());";
		break;
	case FieldDescriptor::TYPE_INT64:
	case FieldDescriptor::TYPE_UINT64:
	case FieldDescriptor::TYPE_FIXED64:
	case FieldDescriptor::TYPE_SFIXED64:
	case FieldDescriptor::TYPE_SINT64:
		if(fdd->is_repeated())
			return "pwlua::_detail::stack_helper<int64>::push(L,msg." + fieldName + "(i));";
		else
			return "pwlua::_detail::stack_helper<int64>::push(L,msg." + fieldName + "());";
		break;
	case FieldDescriptor::TYPE_BOOL:
		if(fdd->is_repeated())
			return "lua_pushboolean(L,msg." + fieldName + "(i));";
		else
			return "lua_pushboolean(L,msg." + fieldName + "());";
		break;
	case FieldDescriptor::TYPE_STRING:
	case FieldDescriptor::TYPE_BYTES:
		if(fdd->is_repeated())
			return "lua_pushstring(L,msg." + fieldName + "(i).c_str());";
		else
			return "lua_pushstring(L,msg." + fieldName + "().c_str());";
		break;
	case FieldDescriptor::TYPE_MESSAGE:
		if(fdd->is_repeated())
			return "MsgToLua(L,msg." + fieldName + "(i));";
		else
			return "MsgToLua(L,msg." + fieldName + "());";
		break;
	case FieldDescriptor::TYPE_ENUM:
		if(fdd->is_repeated())
			return "lua_pushinteger(L,(int)msg." + fieldName + "(i));";
		else
			return "lua_pushinteger(L,(int)msg." + fieldName + "());";
		break;
	}
	return "Error type";
}


void GenerateLuaHpps(std::vector<std::string>& scripteds,const std::string& nm,google::protobuf::DescriptorPool& pool,const std::string& file, const std::string& directory)
{
	std::string actualnm = nm.substr(2);

	// lua scripted support
	scripteds.push_back("#ifndef _pw_scripted_msg_" + nm);
	scripteds.push_back("#define _pw_scripted_msg_" + nm);

	scripteds.push_back("");
	scripteds.push_back("#include <cassert>");
	scripteds.push_back("#include \"pw_lua.h\"");

	if(nm == "pwworldsrv" && directory != "")
	{
// 		std::string strSourceDir = directory + "\/*.*";
// 		_finddata_t file;
// 		long longf;
// 		if((longf = _findfirst(strSourceDir.c_str(), &file)) == -1l)
// 		{
// 
// 		}
// 		else
// 		{
// 			std::string tempName;
// 
// 			while(_findnext(longf, &file) == 0)
// 			{
// 				tempName = "";
// 				tempName = file.name;
// 				int count = tempName.length();
// 				if (count < 4)
// 				{
// 					continue;
// 				}
// 
// 				if (tempName == ".." || tempName == ".svn"||  tempName.substr(count-5) =="pb.cc")
// 				{
// 					continue;
// 				}
// 				scripteds.push_back("#include \"" + tempName + "\"");
// 
// 			}
// 		}
		scripteds.push_back("#include \"worldsrv.pb.h\"");
	}
	else
		scripteds.push_back("#include \"accsrv.pb.h\"");

	std::string fullnm = "pwngs::protocol::" + actualnm + "::";

	scripteds.push_back("");
	scripteds.push_back("namespace pwngs");
	scripteds.push_back("{");
	scripteds.push_back("");
	scripteds.push_back("\t""class MsgCluster;");
	scripteds.push_back("");

	std::string tabs1 = GenTabs(1);
	std::string tabs2 = GenTabs(2);
	std::string tabs3 = GenTabs(3);
	std::string tabs4 = GenTabs(4);

	const FileDescriptor* fd = pool.FindFileByName(file);

	scripteds.push_back(tabs1 + "extern void ExportMsgIdToLua(lua_State* L);");
	scripteds.push_back(tabs1 + "extern void LuaToMsgCluster(lua_State* L,int stackIndex,int msgid,MsgCluster& msg);");
	// MsgToLua
	for(int i = 0; i < fd->message_type_count(); ++i)
	{
		const Descriptor* descriptor = fd->message_type(i);

		int id = descriptor->options().GetExtension(pwngs::msgid);

		scripteds.push_back("");
		scripteds.push_back("// ----------------------------------------------------------------------------- ");
		scripteds.push_back("");

		scripteds.push_back(tabs1 + "extern void MsgToLua(lua_State* L,const " + fullnm + descriptor->name() + "& msg);");
		scripteds.push_back(tabs1 + "extern void LuaToMsg(lua_State* L,int stackIndex," + fullnm + descriptor->name() + "& msg);");

	}

	scripteds.push_back("}");
	scripteds.push_back("#endif // _pw_scripted_msg_" + nm);
}

void GenerateLuaCpps(std::vector<std::string>& scripteds,const std::string& nm,google::protobuf::DescriptorPool& pool,const std::string& file)
{
	std::string actualnm = nm.substr(2);

	scripteds.push_back("#include <cassert>");
	scripteds.push_back("#include \"msg.def.h\"");
	
// 	if(nm == "pwworldsrv")
// 		scripteds.push_back("#include \"worldsrv.pb.h\"");
// 	else
// 		scripteds.push_back("#include \"accsrv.pb.h\"");

	scripteds.push_back("#include \"pw_msg_cluster.h\"");
	scripteds.push_back("");
	scripteds.push_back("using namespace pwngs::protocol::" + actualnm + ";");
	scripteds.push_back("");
	scripteds.push_back("namespace pwngs");
	scripteds.push_back("{");
	scripteds.push_back("");

	std::string tabs1 = GenTabs(1);
	std::string tabs2 = GenTabs(2);
	std::string tabs3 = GenTabs(3);
	std::string tabs4 = GenTabs(4);

	const FileDescriptor* fd = pool.FindFileByName(file);

	// MsgId To Lua
	scripteds.push_back(tabs1 + "void ExportMsgIdToLua(lua_State* L)");
	scripteds.push_back(tabs1 + "{");
	scripteds.push_back(tabs2 + "lua_newtable(L);");
	for(int i = 0; i < fd->message_type_count(); ++i)
	{
		const Descriptor* descriptor = fd->message_type(i);
		int id = descriptor->options().GetExtension(pwngs::msgid);
		if(id == 0)
			continue;

		scripteds.push_back(tabs2 + "lua_pushstring(L,\"" + descriptor->name() + "\");");
		scripteds.push_back(tabs2 + "lua_pushinteger(L,msgid_" + descriptor->name() + ");");
		scripteds.push_back(tabs2 + "lua_settable(L,-3);");
		scripteds.push_back(tabs2);
	}
	scripteds.push_back(tabs2 + "lua_setglobal(L,\"msgids\");");
	scripteds.push_back(tabs1 + "}");
	scripteds.push_back("");

	// LuaToMsgCluster

	scripteds.push_back(tabs1 + "void LuaToMsgCluster(lua_State* L,int stackIndex,int msgid,MsgCluster& msgCluster)");
	scripteds.push_back(tabs1 + "{");
	scripteds.push_back(tabs2 + "switch(msgid)");
	scripteds.push_back(tabs2 + "{");
	for(int i = 0; i < fd->message_type_count(); ++i)
	{
		const Descriptor* descriptor = fd->message_type(i);
		int id = descriptor->options().GetExtension(pwngs::msgid);
		if(id == 0)
			continue;

		scripteds.push_back(tabs2 + "case msgid_" + descriptor->name() + ":");
		scripteds.push_back(tabs3 + "{");
		scripteds.push_back(tabs4 + descriptor->name() + " msg;");
		scripteds.push_back(tabs4 + "LuaToMsg(L,stackIndex,msg);");
		scripteds.push_back(tabs4 + "msgCluster.Add(msgid_" + descriptor->name() + ",msg);");
		scripteds.push_back(tabs3 + "}");
		scripteds.push_back(tabs3 + "break;");
	}
	scripteds.push_back(tabs2 + "default:");
	scripteds.push_back(tabs4 + "assert(false);");
	scripteds.push_back(tabs3 + "break;");
	scripteds.push_back(tabs2 + "}");
	scripteds.push_back(tabs1 + "}");
	// MsgToLua
	for(int i = 0; i < fd->message_type_count(); ++i)
	{
		scripteds.push_back("");
		scripteds.push_back("// ----------------------------------------------------------------------------- ");
		scripteds.push_back("");

		const Descriptor* descriptor = fd->message_type(i);

		int id = descriptor->options().GetExtension(pwngs::msgid);
		
		scripteds.push_back(tabs1 + "void MsgToLua(lua_State* L,const " + descriptor->name() + "& msg)");
		scripteds.push_back(tabs1 + "{");
		scripteds.push_back(tabs2 + "lua_newtable(L);");
		scripteds.push_back(tabs2);

		if(id != 0)
		{
			scripteds.push_back(tabs2 + "lua_pushstring(L,\"msgid\");");
			scripteds.push_back(tabs2 + "lua_pushinteger(L,msgid_" + descriptor->name() + ");");
			scripteds.push_back(tabs2 + "lua_settable(L,-3);");
			scripteds.push_back(tabs2);
		}

		for(int j = 0; j < descriptor->field_count(); ++j)
		{
			const FieldDescriptor* fdd = descriptor->field(j);

			std::string fieldName = fdd->name();
			my_tolower(fieldName);

			if(fdd->is_repeated())
			{
				scripteds.push_back(tabs2 + "lua_pushstring(L,\"" + fieldName + "\");");
				scripteds.push_back(tabs2 + "lua_newtable(L);");
				scripteds.push_back(tabs2 + "for(int i = 0; i < msg." + fieldName + "_size(); ++i)");
				scripteds.push_back(tabs2 + "{");
				scripteds.push_back(tabs3 + "lua_pushinteger(L,i+1);");
				scripteds.push_back(tabs3 + PushField(fdd));
				scripteds.push_back(tabs3 + "lua_settable(L,-3);");
				scripteds.push_back(tabs2 + "}");
				scripteds.push_back(tabs2 + "lua_settable(L,-3);");
			}
			else if(fdd->is_optional())
			{
				scripteds.push_back(tabs2 + "if(msg.has_" + fieldName + "())");
				scripteds.push_back(tabs2 + "{");
				scripteds.push_back(tabs3 + "lua_pushstring(L,\"" + fieldName + "\");");
				scripteds.push_back(tabs3 + PushField(fdd));
				scripteds.push_back(tabs3 + "lua_settable(L,-3);");
				scripteds.push_back(tabs2 + "}");
			}
			else
			{
				scripteds.push_back(tabs2 + "lua_pushstring(L,\"" + fieldName + "\");");
				scripteds.push_back(tabs2 + PushField(fdd));
				scripteds.push_back(tabs2 + "lua_settable(L,-3);");
			}
			scripteds.push_back(tabs2);
		}
		scripteds.push_back(tabs1 + "}");
		scripteds.push_back("");
	
		// ---------------------------------------------------------------------------------------

		scripteds.push_back(tabs1 + "void LuaToMsg(lua_State* L,int stackIndex," + descriptor->name() + "& msg)");
		scripteds.push_back(tabs1 + "{");
		scripteds.push_back(tabs2 + "lua_pushvalue(L,stackIndex);");
		scripteds.push_back(tabs2);

		for(int j = 0; j < descriptor->field_count(); ++j)
		{
			const FieldDescriptor* fdd = descriptor->field(j);

			std::string fieldName = fdd->name();
			my_tolower(fieldName);

			scripteds.push_back(tabs2 + "lua_pushstring(L,\"" + fieldName + "\");");
			scripteds.push_back(tabs2 + "lua_gettable(L,-2);");
			scripteds.push_back(tabs2 + "if(lua_type(L,-1) != LUA_TNIL)");
			scripteds.push_back(tabs2 + "{");

			if(fdd->is_repeated())
			{
				scripteds.push_back(tabs3 + "assert(lua_type(L,-1) == LUA_TTABLE);");
				scripteds.push_back(tabs3 + "int len = lua_objlen(L,-1);");
				scripteds.push_back(tabs3 + "for(int i = 0; i < len; ++i)");
				scripteds.push_back(tabs3 + "{");
				scripteds.push_back(tabs4 + "lua_pushinteger(L,i+1);");
				scripteds.push_back(tabs4 + "lua_gettable(L,-2);");
				scripteds.push_back(tabs4 + PopFieldToMsg(fdd));
				scripteds.push_back(tabs4 + "lua_pop(L,1);");
				scripteds.push_back(tabs3 + "}");
			}
			else
			{
				scripteds.push_back(tabs3 + PopFieldToMsg(fdd));
			}
			scripteds.push_back(tabs2 + "}");
			scripteds.push_back(tabs2 + "lua_pop(L,1);");

			scripteds.push_back(tabs2);
		}
		scripteds.push_back(tabs2 + "lua_pop(L,1);");
		scripteds.push_back(tabs1 + "}");
		scripteds.push_back("");

		// -----------------------------------------------------------------------------
// 
// 		if(id != 0)
// 		{
// 			char buf[100];
// 			sprintf(buf,"%d",id);
// 
// 			scripteds.push_back(tabs1 + "void LuaToMsgCluster(lua_State* L,int stackIndex,MsgCluster& msgCluster)");
// 			scripteds.push_back(tabs1 + "{");
// 			scripteds.push_back(tabs2 + descriptor->name() + " actualMsg;");
// 			scripteds.push_back(tabs2 + "LuaToMsg(L,stackIndex,actualMsg);");
// 			scripteds.push_back(tabs2 + "msgCluster.Add(" + buf + ",actualMsg);");
// 			scripteds.push_back(tabs1 + "}");
// 			scripteds.push_back(tabs1);
// 		}

	}

	scripteds.push_back("}");
}

/*
void GenerateLuas(std::vector<std::string>& scripteds,
					const std::string& nm,
					google::protobuf::DescriptorPool& pool,const std::string& file)
{

	std::string actualnm = nm.substr(2);

	// lua scripted support
	scripteds.push_back("#ifndef _pw_scripted_msg_" + nm);
	scripteds.push_back("#define _pw_scripted_msg_" + nm);

	scripteds.push_back("");
	scripteds.push_back("#include \"pw_lua.h\"");
	if(nm == "pwworldsrv")
		scripteds.push_back("#include \"worldsrv.pb.h\"");
	else
		scripteds.push_back("#include \"accsrv.pb.h\"");
	scripteds.push_back("");
	scripteds.push_back("using namespace pwngs::protocol::" + actualnm + ";");
	scripteds.push_back("");
	scripteds.push_back("namespace pwngs");
	scripteds.push_back("{");
	scripteds.push_back("");
	scripteds.push_back("\t" "int ExportScriptedMessage(lua_State* L)");
	scripteds.push_back("\t" "{");

	std::string tabs2 = GenTabs(2);
	std::string tabs3 = GenTabs(3);

	const FileDescriptor* fd = pool.FindFileByName(file);

	for(int i = 0; i < fd->message_type_count(); ++i)
	{
		const Descriptor* descriptor = fd->message_type(i);
// 		int scripted = descriptor->options().GetExtension(pwngs::scripted);
// 		if(scripted == 0)
// 			continue;

		scripteds.push_back(tabs2 + "pwlua::class_<" + descriptor->name() + ">(L,\"" + descriptor->name() + "\")");
		scripteds.push_back(tabs3 + ".ctor()");

		for(int j = 0; j < descriptor->field_count(); ++j)
		{
			const FieldDescriptor* fdd = descriptor->field(j);
			std::string type_name;

			switch(fdd->type())
			{
			case FieldDescriptor::TYPE_DOUBLE:
				type_name = "double";
				break;
			case FieldDescriptor::TYPE_FLOAT:
				type_name = "float";
				break;
			case FieldDescriptor::TYPE_INT64:
			case FieldDescriptor::TYPE_UINT64:
			case FieldDescriptor::TYPE_FIXED64:
			case FieldDescriptor::TYPE_SFIXED64:
			case FieldDescriptor::TYPE_SINT64:
				type_name = "int64";
				break;
			case FieldDescriptor::TYPE_FIXED32:
			case FieldDescriptor::TYPE_INT32:
			case FieldDescriptor::TYPE_UINT32:
			case FieldDescriptor::TYPE_SFIXED32:
			case FieldDescriptor::TYPE_SINT32:
				type_name = "int32";
				break;
			case FieldDescriptor::TYPE_BOOL:
				type_name = "bool";
				break;
			case FieldDescriptor::TYPE_STRING:
			case FieldDescriptor::TYPE_BYTES:
				type_name = "const_char_ptr";
				break;
			case FieldDescriptor::TYPE_MESSAGE:
				type_name = fdd->message_type()->name();
				break;
			case FieldDescriptor::TYPE_ENUM:
				type_name = "unsigned";
				break;
			}

			assert(type_name.length() > 0);

			if(fdd->type() == FieldDescriptor::TYPE_MESSAGE)
			{
				if(fdd->is_repeated())
				{
					scripteds.push_back(tabs3 + ".method<" + type_name + "*>(\"" + fdd->name() + "_size\",&" + descriptor->name() + "::add_" + fdd->name() + ")");
					scripteds.push_back(tabs3 + ".method<int>(\"" + fdd->name() + "_size\",&" + descriptor->name() + "::" + fdd->name() + "_size)");
					scripteds.push_back(tabs3 + ".method<" + type_name + "&>(\"" + fdd->name() + "\",&" + descriptor->name() + "::" + fdd->name() + ")");
				}
				else
				{
					scripteds.push_back(tabs3 + ".method<" + type_name + "*>(\"mutable_" + fdd->name() + "\",&" + descriptor->name() + "::mutable_" + fdd->name() + ")");
				}
			}
			else
			{
				if(fdd->is_repeated())
				{
					scripteds.push_back(tabs3 + ".method<" + type_name + "*>(\"add_" + fdd->name() +  "\",&" + descriptor->name() + "::add_" + fdd->name() + ")");
					scripteds.push_back(tabs3 + ".method<int>(\"" + fdd->name() + "_size\",&" + descriptor->name() + "::" + fdd->name() + "_size)");
					scripteds.push_back(tabs3 + ".method<" + type_name + "&>(\"" + fdd->name() + "\",&" + descriptor->name() + "::" + fdd->name() + ")");
				}
				else
				{
					scripteds.push_back(tabs3 + ".method<" + type_name + ">(\"" + fdd->name() + "\",&" + descriptor->name() + "::" + fdd->name() + ")");

					if(fdd->type() == FieldDescriptor::TYPE_BYTES)
						scripteds.push_back(tabs3 + ".method<void,void (" + descriptor->name() + "::*)(" + type_name + ")>(\"set_" + fdd->name() + "\",&" + descriptor->name() + "::set_" + fdd->name() + ")");
					else
						scripteds.push_back(tabs3 + ".method<void>(\"set_" + fdd->name() + "\",&" + descriptor->name() + "::set_" + fdd->name() + ")");
					if(fdd->is_optional())
					{
						scripteds.push_back(tabs3 + ".method<bool>(\"has_" + fdd->name() + "\",&" + descriptor->name() + "::has_" + fdd->name() + ")");
					}
				}
			}
		}
		scripteds.push_back(tabs2 + ";");
	}

	scripteds.push_back("\t" "}");
	scripteds.push_back("}");
	scripteds.push_back("#endif // _pw_scripted_msg_" + nm);
}
*/