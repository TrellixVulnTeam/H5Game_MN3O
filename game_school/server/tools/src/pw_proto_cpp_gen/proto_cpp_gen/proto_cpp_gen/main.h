
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

#include <google/protobuf/descriptor.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/tokenizer.h>
#include <google/protobuf/compiler/parser.h>
#include "options.pb.h"
//#include "tokenizer.h"

#ifndef _MSC_VER
#include <uuid/uuid.h>
#else
#include <Windows.h>
extern void GetStringFromGUID(GUID& FilterCLSID, char* lpszString);
#endif


struct MsgHandlerSource
{
	std::string name;
	std::vector<std::string> lines;
};

extern std::string dirname(std::string path);

extern std::string filename2(std::string path);

extern std::string GenTabs(int n);

extern void Print(std::vector<std::string>& output);

extern int WriteToFile(std::vector<std::string>& output, const std::string& filename);


extern void GenerateMsgDef(std::vector<std::string>& output, google::protobuf::DescriptorPool& pool, const std::string& file);
extern void GenerateMsgHandlerCpp(std::vector<std::string>& output, google::protobuf::DescriptorPool& pool, const std::string& file,
	const std::string _namespace, const std::string class_);
extern void GenerateMsgHandlerHpp(std::vector<std::string>& output, google::protobuf::DescriptorPool& pool, const std::string& file,
	const std::string& _namespace, const std::string& class_, const std::string& _msg_hpp, const std::string& directory);

extern void GenerateMsgProcess(std::vector<MsgHandlerSource>& output_, google::protobuf::DescriptorPool& pool,
	const std::string& file, const std::string _namespace, const std::string class_);

extern void GenerateLuaHpps(std::vector<std::string>& scripteds,
	const std::string& nm,
	google::protobuf::DescriptorPool& pool, const std::string& file,
	const std::string& directory
	);
extern void GenerateLuaCpps(std::vector<std::string>& scripteds,
	const std::string& nm,
	google::protobuf::DescriptorPool& pool, const std::string& file);

// cy 20170523 解决包含tokenizer.h 无法解析的外部命令 
void tokenize(const std::string& str, std::vector<std::string>& result,
	const std::string& delimiters, const std::string& delimiters_preserve = "",
	const std::string& quote = "\"", const std::string& esc = "\\");