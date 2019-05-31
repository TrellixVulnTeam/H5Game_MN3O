#include "main.h"


void GenerateMsgProcess(std::vector<MsgHandlerSource>& output_,google::protobuf::DescriptorPool& pool,
                        const std::string& file,const std::string _namespace,const std::string class_)
{
	std::string filename = filename2(file);

	const google::protobuf::FileDescriptor* desc = pool.FindFileByName(file);
	if(desc == 0)
	{
		std::cout << "not found file " << file << std::endl;
		return;
	}

	std::vector<std::string> namespaces;
	tokenize(desc->package(),namespaces,".");

	std::string msg_namespace = "";
	for(int i = 0; i < namespaces.size(); ++i)
		msg_namespace = msg_namespace + "::" + namespaces[i];

	std::string tabsDef = GenTabs(1);
	std::string tabsImp = GenTabs(2);
	std::string tabsCase = GenTabs(3);

	// 处理函数

	for(int i = 0; i < desc->message_type_count(); ++i)
	{
		MsgHandlerSource source;

		const google::protobuf::Descriptor* descriptor = desc->message_type(i);
		assert(descriptor);

		int id = descriptor->options().GetExtension(pwngs::msgid);
		if(id == 0)
			continue;

		char buf[100];
		sprintf(buf,"%u",id);


		source.name = descriptor->name();
		
		if(source.name.substr(0,2) == "SC")
			continue;
			
		std::vector<std::string>& output = source.lines;

		output.push_back("namespace " + _namespace);
		output.push_back("{");

		std::string _typename = msg_namespace + "::" + descriptor->name();
		output.push_back(tabsDef + "// msgid:" + buf + " name:" + descriptor->name());
		output.push_back(tabsDef + "int " + class_ + "::Process(pwdist::sint64 conn," + _typename + "& msg)");
		output.push_back(tabsDef + "{");
		output.push_back(tabsDef + "\tusing namespace pwngs;");
		output.push_back(tabsDef + "\treturn -1;");
		output.push_back(tabsDef + "}");
		output.push_back("} //end namespace " + _namespace);
		output.push_back("");

		output_.push_back(source);
	}
}


void GenerateMsgHandlerCpp(std::vector<std::string>& output,google::protobuf::DescriptorPool& pool,const std::string& file,
                           const std::string _namespace,const std::string class_)
{
	std::string filename = filename2(file);

	const google::protobuf::FileDescriptor* desc = pool.FindFileByName(file);
	if(desc == 0)
	{
		std::cout << "not found file " << file << std::endl;
		return;
	}
	output.push_back("namespace " + _namespace);
	output.push_back("{");

	std::vector<std::string> namespaces;
	tokenize(desc->package(),namespaces,".");

	std::string msg_namespace = "";
	for(int i = 0; i < namespaces.size(); ++i)
		msg_namespace = msg_namespace + "::" + namespaces[i];

	std::string tabsDef = GenTabs(1);
	std::string tabsImp = GenTabs(2);
	std::string tabsCase = GenTabs(3);


	// 处理函数

	output.push_back(tabsDef + "int " + class_ + "::Process(pwdist::sint64 conn,pwdist::uint32 msgid,const char* buf,size_t len)");
	output.push_back(tabsDef + "{");
	output.push_back(tabsImp + "using namespace " + msg_namespace + ";");
	output.push_back(tabsImp + "");
	output.push_back(tabsImp + "if(!IsAccept(msgid))");
	output.push_back(tabsImp + "\treturn -1;");
	output.push_back(tabsImp + "");
	output.push_back(tabsImp + "switch(msgid)");
	output.push_back(tabsImp + "{");

	for(int i = 0; i < desc->message_type_count(); ++i)
	{
		const google::protobuf::Descriptor* descriptor = desc->message_type(i);
		assert(descriptor);

		int id = descriptor->options().GetExtension(pwngs::msgid);
		if(id != 0)
		{
			char buf[100];
			sprintf(buf,"%u",id);
			std::string msgidname = std::string("msgid_") + descriptor->name();

			if(descriptor->name().substr(0,2) == "SC")
				continue;

			output.push_back(tabsImp + "case " + msgidname + ":");
			output.push_back(tabsCase + "{");
			output.push_back(tabsCase + "\t" + descriptor->name() + " actualMsg;");
			output.push_back(tabsCase + "\tif(!actualMsg.ParseFromArray(buf,len))");
			output.push_back(tabsCase + "\t\treturn -1;");
			output.push_back(tabsCase + "\treturn Process(conn,actualMsg);");
			output.push_back(tabsCase + "}");
			output.push_back(tabsCase + "break;");

		}
	}
	output.push_back(tabsImp + "default:");
	output.push_back(tabsCase + "{");
	output.push_back(tabsCase + "\tgErrorStream( \"unexpected msg:\" << msgid );");
	output.push_back(tabsCase + "} //end default");
	output.push_back(tabsCase + "break;");
	output.push_back(tabsImp + "} //end switch");
	output.push_back(tabsImp + "return -1;");
	output.push_back(tabsDef + "}");

	output.push_back("");

	// ----------------------------------------------------

	output.push_back("} //end namespace " + _namespace);
}
