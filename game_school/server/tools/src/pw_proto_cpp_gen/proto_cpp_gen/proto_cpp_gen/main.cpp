// proto_cpp_gen.cpp : 定义控制台应用程序的入口点。
//

#include "main.h"

using namespace google::protobuf;

void tokenize(const std::string& str, std::vector<std::string>& result,
	const std::string& delimiters, const std::string& delimiters_preserve,
	const std::string& quote, const std::string& esc)
{
	// clear the std::vector
	if (false == result.empty())
	{
		result.clear();
	}

	std::string::size_type pos = 0; // the current position (char) in the std::string
	char ch = 0; // buffer for the current character
	char delimiter = 0;    // the buffer for the delimiter char which
	// will be added to the tokens if the delimiter
	// is preserved
	char current_quote = 0; // the char of the current open quote
	bool quoted = false; // indicator if there is an open quote
	std::string token;  // std::string buffer for the token
	bool token_complete = false; // indicates if the current token is
	// read to be added to the result std::vector
	std::string::size_type len = str.length();  // length of the input-std::string

	// for every char in the input-std::string
	while (len > pos)
	{
		// get the character of the std::string and reset the delimiter buffer
		ch = str.at(pos);
		delimiter = 0;

		// assume ch isn't a delimiter
		bool add_char = true;

		// check ...

		// ... if the delimiter is an escaped character
		bool escaped = false; // indicates if the next char is protected
		if (false == esc.empty()) // check if esc-chars are  provided
		{
			if (std::string::npos != esc.find_first_of(ch))
			{
				// get the escaped char
				++pos;
				if (pos < len) // if there are more chars left
				{
					// get the next one
					ch = str.at(pos);

					// add the escaped character to the token
					add_char = true;
				}
				else // cannot get any more characters
				{
					// don't add the esc-char
					add_char = false;
				}

				// ignore the remaining delimiter checks
				escaped = true;
			}
		}

		// ... if the delimiter is a quote
		if (false == quote.empty() && false == escaped)
		{
			// if quote chars are provided and the char isn't protected
			if (std::string::npos != quote.find_first_of(ch))
			{
				// if not quoted, set state to open quote and set
				// the quote character
				if (false == quoted)
				{
					quoted = true;
					current_quote = ch;

					// don't add the quote-char to the token
					add_char = false;
				}
				else // if quote is open already
				{
					// check if it is the matching character to close it
					if (current_quote == ch)
					{
						if (token.length() == 0)
							token.push_back('\0');

						// close quote and reset the quote character
						quoted = false;
						current_quote = 0;

						// don't add the quote-char to the token
						add_char = false;
					}
				} // else
			}
		}

		// ... if the delimiter isn't preserved
		if (false == delimiters.empty() && false == escaped &&
			false == quoted)
		{
			// if a delimiter is provided and the char isn't protected by
			// quote or escape char
			if (std::string::npos != delimiters.find_first_of(ch))
			{
				// if ch is a delimiter and the token std::string isn't empty
				// the token is complete
				if (false == token.empty()) // BUGFIX: 2006-03-04
				{
					token_complete = true;
				}

				// don't add the delimiter to the token
				add_char = false;
			}
		}

		// ... if the delimiter is preserved - add it as a token
		bool add_delimiter = false;
		if (false == delimiters_preserve.empty() && false == escaped &&
			false == quoted)
		{
			// if a delimiter which will be preserved is provided and the
			// char isn't protected by quote or escape char
			if (std::string::npos != delimiters_preserve.find_first_of(ch))
			{
				// if ch is a delimiter and the token std::string isn't empty
				// the token is complete
				if (false == token.empty()) // BUGFIX: 2006-03-04
				{
					token_complete = true;
				}

				// don't add the delimiter to the token
				add_char = false;

				// add the delimiter
				delimiter = ch;
				add_delimiter = true;
			}
		}


		// add the character to the token
		if (true == add_char)
		{
			// add the current char
			token.push_back(ch);
		}

		// add the token if it is complete
		if (true == token_complete && false == token.empty())
		{
			// add the token std::string
			result.push_back(token);

			// clear the contents
			token.clear();

			// build the next token
			token_complete = false;
		}

		// add the delimiter
		if (true == add_delimiter)
		{
			// the next token is the delimiter
			std::string delim_token;
			delim_token.push_back(delimiter);
			result.push_back(delim_token);

			// REMOVED: 2006-03-04, Bugfix
		}

		// repeat for the next character
		++pos;
	} // while

	// add the final token
	if (false == token.empty())
	{
		result.push_back(token);
	}
}

bool isSameLines(const std::string& filename, std::vector<std::string>& lines)
{
	std::vector<std::string> oldlines;
	std::fstream stream;
	stream.open(filename.c_str(), std::ios_base::in);
	if (!stream.good())
	{
		std::cout << filename << " ! stream.good " << std::endl;
		return false;
	}

	size_t count = 0;
	while (stream.good())
	{
		char tmpbuf[10 * 1024] = { 0 };
		stream.getline(tmpbuf, sizeof(tmpbuf), '\n');
		// 		if(char* s = strchr(tmpbuf,'\n'))
		// 			*s = 0;
		oldlines.push_back(tmpbuf);

		// 		std::cout << filename << " getline=" << tmpbuf << std::endl;
	}

	size_t minsize = __min(oldlines.size(), lines.size());
	// 	if(oldlines.size() != lines.size())
	// 	{
	// 		std::cout << filename << " osize= " << oldlines.size() << " nsize=" << lines.size() << std::endl;
	// 		return false;
	// 	}

	for (size_t i = 0; i < minsize; ++i)
	{
		if (oldlines[i] != lines[i])
		{
			// 			std::cout << filename << " oline= " << oldlines[i] << " nline=" << lines[i] << std::endl;
			// 			std::cout << filename << " oline= " << oldlines[i].length() << " nline=" << lines[i].length() << std::endl;
			// 			std::cout << filename << " oline= " << (int)(lines[i][lines[i].size() - 1]) << std::endl;
			return false;
		}
	}
	return true;
}

int ParseProtoFile(const string& file, FileDescriptorProto* file_desc_proto)
{
	using namespace google::protobuf;
	using namespace google::protobuf::io;
	using namespace google::protobuf::compiler;

	FILE* proto_file = fopen(file.c_str(), "r");
	{

		if (proto_file == NULL)
		{
			return -1;

		}
		FileInputStream proto_input_stream(fileno(proto_file));
		Tokenizer tokenizer(&proto_input_stream, NULL);
		Parser parser;
		if (!parser.Parse(&tokenizer, file_desc_proto))
		{
			return -2;

		}
	}
	fclose(proto_file);

	if (!file_desc_proto->has_name())
	{
		file_desc_proto->set_name(file);
	}
	return 0;
}

std::string dirname(std::string path)
{
	size_t i = path.rfind('/');
	if (i == path.npos)
		return "";
	return path.substr(0, i + 1);
}

std::string filename2(std::string path)
{
	size_t i = path.rfind('/');
	if (i == path.npos)
		return "";
	return path.substr(i + 1);
}

std::string GenTabs(int n)
{
	std::string result;
	for (int i = 0; i < n; ++i)
	{
		result = result + "\t";
	}
	return result;
}

void Print(std::vector<std::string>& output)
{
	for (int i = 0; i < output.size(); ++i)
		std::cout << output[i] << std::endl;
}

int WriteToFile(std::vector<std::string>& output, const std::string& filename)
{
	if (isSameLines(filename, output))
	{
		std::cout << __FUNCTION__ << " writetofile ignore:" << filename << std::endl;
		return 0;
	}
	unlink(filename.c_str());

	std::fstream f(filename.c_str(), std::ios::out);
	if (!f.good())
	{
		std::cout << "open file " << filename << " failed" << std::endl;
		return 6;
	}

	for (int i = 0; i < output.size(); ++i)
	{
		f.write(output[i].c_str(), output[i].length());
		f.write("\n", 1);
	}
	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 5 && argc != 4)
	{
		std::cout << "Useage: qx_proto_cpp_gen protofile outputpath namespace" << std::endl;
		return 1;
	}

	std::string dir = dirname(argv[1]);
	if (dir.length() == 0)
	{
		std::cout << "invalid input" << std::endl;
		return 2;
	}

	const std::string optionsFile = dir + "options.proto";
	const std::string descriptorFile = dir + "google/protobuf/descriptor.proto";

	FileDescriptorProto file_desc_proto0;
	ParseProtoFile(descriptorFile, &file_desc_proto0);
	file_desc_proto0.set_name("google/protobuf/descriptor.proto");

	FileDescriptorProto file_desc_proto1;
	ParseProtoFile(optionsFile, &file_desc_proto1);
	file_desc_proto1.set_name("options.proto");

	FileDescriptorProto file_desc_proto2;
	ParseProtoFile(argv[1], &file_desc_proto2);

	google::protobuf::DescriptorPool pool;
	const google::protobuf::FileDescriptor* file_desc0 = pool.BuildFile(file_desc_proto0);
	if (file_desc0 == NULL)
	{
		std::cout << "Cannot get file descriptor(descriptor.proto):" << file_desc_proto0.DebugString() << std::endl;
		return 3;
	}

	const google::protobuf::FileDescriptor* file_desc1 = pool.BuildFile(file_desc_proto1);
	if (file_desc1 == NULL)
	{
		std::cout << "Cannot get file descriptor(options.proto):" << file_desc_proto1.DebugString() << std::endl;
		return 4;
	}

	const google::protobuf::FileDescriptor* file_desc2 = pool.BuildFile(file_desc_proto2);
	if (file_desc2 == NULL)
	{
		std::cout << "Cannot get file descriptor(" << argv[2] << "):" << file_desc_proto2.DebugString() << std::endl;
		return 5;
	}

	std::string strMsgHpp1;
	std::string strMsgCpp1;
	std::string strMsgHpp2 = filename2(argv[1]);
	size_t i = strMsgHpp2.find(".proto");
	if (i != std::string::npos)
	{
		strMsgHpp1 = strMsgHpp2.substr(0, i) + ".pb.h";
		strMsgCpp1 = strMsgHpp2.substr(0, i) + ".pb.cc";
	}

	std::vector<std::string> defs;
	std::vector<std::string> cpps;
	std::vector<std::string> hpps;
	std::vector<std::string> luacpps;
	std::vector<std::string> luahpps;
	std::vector<MsgHandlerSource> processes;

	GenerateMsgDef(defs, pool, argv[1]);
	GenerateMsgHandlerCpp(cpps, pool, argv[1], argv[3], "MsgHandler");
	GenerateMsgProcess(processes, pool, argv[1], argv[3], "MsgHandler");
	if (argc == 5)
	{
		GenerateMsgHandlerHpp(hpps, pool, argv[1], argv[3], "MsgHandler", strMsgHpp1, argv[4]);
		GenerateLuaHpps(luahpps, argv[3], pool, argv[1], argv[4]);
	}
	else
	{
		GenerateMsgHandlerHpp(hpps, pool, argv[1], argv[3], "MsgHandler", strMsgHpp1, "");
		GenerateLuaHpps(luahpps, argv[3], pool, argv[1], "");
	}

	GenerateLuaCpps(luacpps, argv[3], pool, argv[1]);

	//Print(cpps);

	std::string output_path(argv[2]);
	if (output_path[output_path.length() - 1] != '/')
		output_path = output_path + "/";

	cpps.insert(cpps.begin(), "");
	cpps.insert(cpps.begin(), "#include \"qx_logger.h\"");
	cpps.insert(cpps.begin(), "#include \"msg.handler.h\"");
	cpps.insert(cpps.begin(), "#include \"msg.def.h\"");

	if (argc == 5)
		cpps.insert(cpps.begin(), "#include \"worldsrv.pb.h\"");
	else
		cpps.insert(cpps.begin(), "#include \"accsrv.pb.h\"");

	WriteToFile(defs, output_path + "msg.def.h");
	WriteToFile(hpps, output_path + "msg.handler.h");
	WriteToFile(cpps, output_path + "msg.handler.cpp");
	WriteToFile(luahpps, output_path + "../../libdefs/qx_msg_export_" + argv[3] + ".h");

	luacpps.insert(luacpps.begin(), std::string() + "#include \"qx_msg_export_" + argv[3] + ".h\"");
	WriteToFile(luacpps, output_path + "../../libdefs/qx_msg_export_" + argv[3] + ".cpp");

	for (int i = 0; i < processes.size(); ++i)
	{
		std::string file = output_path + "msg.handler." + processes[i].name + ".cpp";

#ifdef _MSC_VER
		DWORD d = GetFileAttributesA(file.c_str());

		// 		std::cout << d << " : " << file << std::endl;
		if (d != 0xFFFFFFFF)
			continue;
#else
		if (access(file.c_str(), R_OK) == 0)
			continue;
#endif
		processes[i].lines.insert(processes[i].lines.begin(), "");
		processes[i].lines.insert(processes[i].lines.begin(), "#include \"msg.handler.h\"");
		WriteToFile(processes[i].lines, file);

	}

	if (argc == 5)
	{
#ifdef _MSC_VER
		// 		std::string temp(argv[2]) ;
		// 		std::string delStr = temp + "/" + strMsgHpp1;
		// 		if(DeleteFile(delStr.c_str()))
		// 		{
		// 			std::cout << "success" << strMsgHpp1.c_str() << std::endl;
		// 		}
		// 		else
		// 		{
		// 			std::cout << "fail" << strMsgHpp1.c_str() << std::endl;
		// 		}
		// 
		// 		delStr = temp + "/" + strMsgCpp1;
		// 		if(DeleteFile(delStr.c_str()))
		// 		{
		// 			std::cout << "success" << strMsgCpp1.c_str() << std::endl;
		// 		}
		// 		else
		// 		{
		// 			std::cout << "fail" << strMsgCpp1.c_str() << std::endl;
		// 		}
#else

#endif
	}



	return 0;
}
