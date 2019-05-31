#include "main.h"
#include "pw_utils.h"
#ifdef _MSC_VER
	#include <ObjBase.h>
#endif

void GenerateMsgDef(std::vector<std::string>& output,google::protobuf::DescriptorPool& pool,const std::string& file)
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

	std::cout << __FUNCTION__ << " " << filename.c_str() << std::endl;

	char uuidbuf[200] = "";
	sprintf(uuidbuf,"_msgdef_%s_",filename.c_str());
/*
#ifdef _MSC_VER
	GUID guid;
	CoCreateGuid(&guid);
	GetStringFromGUID(guid,uuidbuf);
#else
	uuid_t uid;
	uuid_generate(uid);
	uuid_unparse(uid,uuidbuf);
#endif
	*/

	for(int i = 0; i < sizeof(uuidbuf); ++i)
	{
		if(uuidbuf[i] == '.')
			uuidbuf[i] = '_';
		if(uuidbuf[i] == 0)
			break;
	}

	output.push_back(std::string("#ifndef _msg_proto_") + uuidbuf + "_include_");
	output.push_back(std::string("#define _msg_proto_") + uuidbuf + "_include_");

	for(int i = 0; i < namespaces.size(); ++i)
	{
		std::string tabs = GenTabs(i);
		output.push_back(tabs + "namespace " + namespaces[i]);
		output.push_back(tabs + "{");
	}

	std::string tabs = GenTabs(namespaces.size());

	for(int i = 0; i < desc->message_type_count(); ++i)
	{
		const google::protobuf::Descriptor* descriptor = desc->message_type(i);
		assert(descriptor);

		int id = descriptor->options().GetExtension(pwngs::msgid);
		if(id != 0)
		{
			char buf[100];
			sprintf(buf,"%u",id);

			output.push_back(tabs + "const int msgid_" + descriptor->name() + " = " + buf + ";");
		}
	}

	//output.push_back(std::string("\n"));

	for(int i = (int)(namespaces.size() - 1); i >= 0; --i)
	{
		std::string tabs = GenTabs(i);
		output.push_back(tabs + "} //end namespace " + namespaces[i]);
	}
	output.push_back(std::string("#endif //_msg_proto_") + uuidbuf + "_include_");
	output.push_back("");
}