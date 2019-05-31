#include "main.h"
#include "pw_utils.h"
#ifdef _MSC_VER
	#include <ObjBase.h>
	#include <io.h>
	#include <string>
#endif

#ifdef _MSC_VER
	VOID GetStringFromGUID(GUID& FilterCLSID, char* lpszString)
	{
		sprintf(lpszString, "%08X_%04X_%04X_%02X%02X_%02X%02X%02X%02X%02X%02X",
			FilterCLSID.Data1, FilterCLSID.Data2, FilterCLSID.Data3,
			FilterCLSID.Data4[0], FilterCLSID.Data4[1], FilterCLSID.Data4[2], FilterCLSID.Data4[3], 
			FilterCLSID.Data4[4], FilterCLSID.Data4[5], FilterCLSID.Data4[6], FilterCLSID.Data4[7]
		);
	}
#endif


void GenerateMsgHandlerHpp(std::vector<std::string>& output,google::protobuf::DescriptorPool& pool,const std::string& file,
                           const std::string& _namespace,const std::string& class_,
                           const std::string& _msg_hpp,
						   const std::string& directory)
{
	std::string filename = filename2(file);

	const google::protobuf::FileDescriptor* desc = pool.FindFileByName(file);
	if(desc == 0)
	{
		std::cout << "not found file " << file << std::endl;
		return;
	}
	
	std::cout << __FUNCTION__ << " " << filename.c_str() << std::endl;

	char uuidbuf[200] = "";
	sprintf(uuidbuf,"_msghandler_%s_",filename.c_str());
// 	GUID guid;
// 	CoCreateGuid(&guid);
// 	GetStringFromGUID(guid,uuidbuf);
// #else
// 	uuid_t uid;
// 	uuid_generate(uid);
// 	uuid_unparse(uid,uuidbuf);
// #endif
// 
	for(int i = 0; i < sizeof(uuidbuf); ++i)
	{
		if(uuidbuf[i] == '.')
			uuidbuf[i] = '_';
		if(uuidbuf[i] == 0)
			break;
	}

	std::vector<std::string> namespaces;
	tokenize(desc->package(),namespaces,".");

	std::string msg_namespace = "";
	for(int i = 0; i < namespaces.size(); ++i)
		msg_namespace = msg_namespace + "::" + namespaces[i];

	std::string tabsDef = GenTabs(1);
	std::string tabsFun = GenTabs(2);
	std::string tabsFuncImpl = GenTabs(3);

	output.push_back(std::string("#ifndef _msg_handler_") + uuidbuf + "_include_");
	output.push_back(std::string("#define _msg_handler_") + uuidbuf + "_include_");
	output.push_back("");
	
	output.push_back("#include \"pw_def.h\"");
	output.push_back("#include \"pwdist_def.h\"");
	

	/*
	HANDLE file;
		WIN32_FIND_DATA fileData;
		char line[1024];
		wchar_t fn[1000];
		mbstowcs(fn, directory.c_str(), 999);
		file = FindFirstFile((LPCSTR)fn, &fileData);
		FindNextFile(file, &fileData);
		while(FindNextFile(file, &fileData))
		{
			wcstombs(line, (const wchar_t*)fileData.cFileName, 259);
			//output.push_back("#include \"" + line + "\"");
		}*/
	
	if (directory != "")
	{
		output.push_back("");
		output.push_back("namespace pwngs");
		output.push_back("{");
		output.push_back("\tnamespace protocol");
		output.push_back("\t{");
		output.push_back("\t\tnamespace worldsrv");
		output.push_back("\t\t{");
		for(int i = 0; i < desc->message_type_count(); ++i)
		{
			const google::protobuf::Descriptor* descriptor = desc->message_type(i);
			assert(descriptor);

			output.push_back(std::string("\t\t\t") + "class " + descriptor->name() + ";");
		}
		output.push_back("\t\t}");
		output.push_back("\t}");
		output.push_back("}");
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
// 
// 				int count = tempName.length();
// 				if (count < 4)
// 				{
// 					continue;
// 				}
// 
// 				if (tempName == ".." || tempName == ".svn" ||  tempName.substr(count-5) =="pb.cc")
// 				{
// 					continue;
// 				}
// 
// 
// 				output.push_back("#include \"" + tempName + "\"");
// 
// 			}
// 		}
	}
	else
	{
		output.push_back("#include \"" + _msg_hpp + "\"");
	}
	output.push_back("");
	output.push_back("namespace " + _namespace);
	output.push_back("{");
	output.push_back(tabsDef + "class " + class_);
	output.push_back(tabsDef + "{");
	output.push_back(tabsDef + "public:");
	output.push_back(tabsDef + "\tvirtual bool IsAccept(int msgid) { return true; }");	
	output.push_back(tabsDef + "public:");
	output.push_back(tabsDef + "\t" + class_ + "(void* context) : mContext(context){}");
	output.push_back(tabsDef + "\tvirtual ~" + class_ + "(){}");
	output.push_back(tabsDef + "public:");
	output.push_back(tabsFun + "int Process(pwdist::sint64 conn,pwdist::uint32 msgid,const char* buf,size_t len);");
	output.push_back(tabsDef + "public:");


	for(int i = 0; i < desc->message_type_count(); ++i)
	{
		const google::protobuf::Descriptor* descriptor = desc->message_type(i);
		assert(descriptor);

		int id = descriptor->options().GetExtension(pwngs::msgid);
		if(id == 0)
			continue;

		char buf[100];
		sprintf(buf,"%u",id);
		std::string msgidname = std::string("msgid_") + descriptor->name();

		if(descriptor->name().substr(0,2) == "SC")
			continue;


		std::string _typename = msg_namespace + "::" + descriptor->name();

		std::string _comment = std::string("// msgid:") + buf + " name:" + descriptor->name();

		output.push_back(tabsFun + "int Process(pwdist::sint64 conn," + _typename + "& msg);" + _comment);

	}
	output.push_back(tabsDef + "public:");
	output.push_back(tabsDef + "\tvoid* mContext;");
	output.push_back(tabsDef + "};");
	output.push_back("");

	// ----------------------------------------------------

	output.push_back("} //end namespace " + _namespace);
	output.push_back("");
	output.push_back(std::string("#endif //_msg_handler_") + uuidbuf + "_include_");
}
