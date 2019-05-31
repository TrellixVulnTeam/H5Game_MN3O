#include <iostream>
#include <string>
#include <string.h>
#include <stdexcept>
#include <fstream>
#include "stdio.h"
#include "pw_gdb_parser.h"
#include "pw_gdb_generator.h"

using namespace std;
using namespace gdb;

int main(int argc,char** argv)
{
    if(argc <= 2)
    {
        std::cout << "usage: filename outdir" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string output_directory = argv[2];

/*
    FILE* f = ::fopen(filename.c_str(),"r");
    if(f == NULL)
    {
        std::cout << "cant open file:" << filename << std::endl;
        return 1;
    }
    ::fseek(f,0,SEEK_END);
    long size = ::ftell(f);
    ::fseek(f,0,SEEK_SET);

    char* content = new char[size];
    long readed_size = fread(content,size,1,f);
    fclose(f);
*/

	std::fstream fs;
	fs.open(filename.c_str(),std::ios_base::in);
	fs.seekg(0,std::ios::end);
	long size = fs.tellg();
	fs.seekg(0,std::ios::beg);

	char* content = new char[size];
	fs.read(content,size);

    gdb::Lexer lexer(new Input(content,size));
    delete [] content;

    try
    {
        lexer.parse();
    }
    catch(gdb::ParserError& err)
    {
        std::cout << "parse failed:" << err.what() << " line:" << lexer.GetInput()->getLinenum() << std::endl;
        return 1;
    }

    std::vector<Table*>& tables = lexer.getTables();

	g_objAllTables = tables;

    for(size_t i = 0; i < tables.size(); ++i)
    {
        Table* t = tables[i];
        gdb::TableGenerator generator;
        generator.gen(t,output_directory);
    }

	ReflectionGenerator gen;
	gen.genIncludeFile(tables,output_directory);
	gen.gen(tables,output_directory);
	gen.genCollection(tables,output_directory);

    return 0;
}

