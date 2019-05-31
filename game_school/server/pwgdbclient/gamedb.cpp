#include "gdb/pw_gdb_protocol.h"
#include "gdb/pw_gdb_client.h"
#include "gdb/pw_gdb_def.h"
#include "pw_time.h"
#include "pw_utils.h"
#include "pw_socket_client.h"
#include "pw_platform.h"
#include "pw_error_handler.h"
#include "pw_tss.h"

#include <stdio.h>
// #include <readline/readline.h>
// #include <readline/history.h>
#include "bson/bson.h"
#include "bson/bsonobjbuilder.h"
#include "algorithm/pw_md5.h"

using namespace gdb;


static gdb::Client* client = NULL;
static std::string g_output_filename = "";
//static AsynchronousClient client;

// -------------------------------------------------------------------------


#define CHECK_ARGS_NUM(x) if(count != ((x)+1)) { printf("need %d args\n",(x)); return 1; }
#define CHECK_ARGS_GREAT(x) if(count < ((x)+1)) { printf("need %d args less\n",(x)); return 1; }

void printVar(std::ostream& os,gdb::SProtocolPacket* pkt)
{
	os << "(" << pkt->size << ")";

	if(pkt->IsBuffer())
	{
		try
		{
			int size = *reinterpret_cast<const int*>(pkt->data);
			if(pkt->size == sizeof(int64))
				os << "asint:" << *reinterpret_cast<int64*>(pkt->data) << " raw: " << std::string(pkt->data,pkt->size)  << "\n";
			else if(size == pkt->size)
			{
				bson::bo tmp(pkt->data);
				os << "bson: " << tmp.toString() << "\n";
			}
			else
			{
				os << "raw: " << std::string(pkt->data,pkt->size) << "\n";
			}
		}
		catch(bson::assertion e)
		{
		}
	}
	else
	{
		if(pkt->IsInteger())
		{
			os << "int: " << pkt->AsInteger() << " ";
		}
		else if(pkt->IsDecimal())
		{
			os << "dec: " << pkt->AsInteger() << " ";
		}
		if(pkt->size == sizeof(int64))
			os << "asint:" << *reinterpret_cast<int64*>(pkt->data) << " raw: " << std::string(pkt->data,pkt->size)  << "\n";
		else
			os << "raw: " << std::string(pkt->data,pkt->size) << "\n";
	}
}

int parseCommandLine(char* line,char** args)
{
	int result = 0;
	char* curr = line;
	char* last = curr;
	while(*curr != 0)
	{
		if(*curr == ' ')
		{
			args[result] = last;
			last = &curr[1];
			++result;
			*curr = 0;
		}
		++curr;
	}
	if(*last != 0)
	{
		args[result] = last;
		result++;
	}
	return result;
}

int handleLine(char* line)
{
	char* args[1000] = {0};
	int count = ::parseCommandLine(line,args);
	if( count < 1 )
        return 1;

	gdb::Client::Request req;

	char* cmd = args[0];
	if(strcmp(cmd,"redir") == 0) {
		CHECK_ARGS_NUM(1);
		g_output_filename = args[1];
		printf("redir ok\n");
		return 0;
	}

	if(strcmp(cmd,"backup") == 0) {
		CHECK_ARGS_NUM(2);
		client->CreateRequest(req,CMD_SLAVE_MANAGE_BACKUP);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);
		req.GetWriter()->WriteS(args[2],cst_string_auto_len);
	}
	if(strcmp(cmd,"rawdel") == 0) {
		CHECK_ARGS_NUM(1);
		client->CreateRequest(req,CMD_RAWDEL);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len);
	}
	if(strcmp(cmd,"hcrossall") == 0) {
		CHECK_ARGS_NUM(1);
		client->CreateRequest(req,CMD_HCROSS_KEYVALS);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len);
	}
	if(strcmp(cmd,"hcrossclear") == 0) {
		CHECK_ARGS_NUM(1);
		client->CreateRequest(req,CMD_HCROSS_DROP);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len);
	}
	if(strcmp(cmd,"clear_all") == 0) {
		client->CreateRequest(req,CMD_REMOVE_ALL);
		req.GetWriter()->WriteNil();
	}

	if(strcmp(cmd,"r") == 0) {
		client->Reconnect();
		return 0;
	}

	// ------------------------------------------------------
	if(strcmp(cmd,"luaset") == 0) {
		CHECK_ARGS_NUM(1);
		client->CreateRequest(req,CMD_CLIENTSCRIPT_STARTUP);

		std::fstream f;
		f.open(args[1],std::ios_base::in);
		if(!f.good() || f.eof())
		{
			printf("invalid file:%s",args[1]);
			return 0;
		}
		f.seekg(0,std::ios_base::end);
		size_t size = f.tellg();
		f.seekg(0,std::ios_base::beg);

		char* script = new char[size+1];
		memset(script,0,size+1);
		f.read(script,size);
		req.GetWriter()->WriteS(script,cst_string_auto_len);
		delete [] script;
	}

	if(strcmp(cmd,"luaexec") == 0) {
		client->CreateRequest(req,CMD_CLIENTSCRIPT_EXECUTE);
		if(count >= 2)
			req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);
		if(count >= 3)
			req.GetWriter()->WriteS(args[2],cst_string_auto_len,true);
		req.GetWriter()->WriterTerminator();
	}

	if(strcmp(cmd,"luaclr") == 0) {
		client->CreateRequest(req,CMD_CLIENTSCRIPT_CLEANUP);
		req.GetWriter()->WriterTerminator();
	}

	if(strcmp(cmd,"luaflt") == 0) {
		client->CreateRequest(req,CMD_CLIENTSCRIPT_FILTER);
		if(count >= 2)
			req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);
		req.GetWriter()->WriterTerminator();
	}

	// ------------------------------------------------------

	if(strcmp(cmd,"create") == 0) {
		CHECK_ARGS_NUM(1);
		client->CreateRequest(req,CMD_CREATE_DATABASE);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len);
	}

	if(strcmp(cmd,"delete") == 0) {
		CHECK_ARGS_NUM(1);
		client->CreateRequest(req,CMD_DELETE_DATABASE);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len);
	}

	if(strcmp(cmd,"select") == 0) {
		CHECK_ARGS_NUM(1);
		client->CreateRequest(req,CMD_SELECT_DATABASE);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len);
	}
	// ------------------------------------------------------

    if(strcmp(cmd,"hget") == 0) {
		CHECK_ARGS_NUM(2);
		client->CreateRequest(req,CMD_HGET);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);
		req.GetWriter()->WriteS(args[2],cst_string_auto_len);
    }

    if(strcmp(cmd,"hset") == 0) {
		CHECK_ARGS_NUM(3);
		client->CreateRequest(req,CMD_HSET);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);
		req.GetWriter()->WriteS(args[2],cst_string_auto_len,true);
		req.GetWriter()->WriteS(args[3],cst_string_auto_len);
    }
    if(strcmp(cmd,"hdel") == 0) {
		CHECK_ARGS_NUM(2);
		client->CreateRequest(req,CMD_HDEL);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);
		req.GetWriter()->WriteS(args[2],cst_string_auto_len);
    }
    if(strcmp(cmd,"hsetnx") == 0) {
        CHECK_ARGS_NUM(3);
		client->CreateRequest(req,CMD_HSETNX);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);
		req.GetWriter()->WriteS(args[2],cst_string_auto_len,true);
		req.GetWriter()->WriteS(args[3],cst_string_auto_len);
    }
    if(strcmp(cmd,"hmget") == 0) {
        CHECK_ARGS_GREAT(2);
		
		client->CreateRequest(req,CMD_HMULTIGET);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);
        for(int i = 2; i < count; ++i)
			req.GetWriter()->WriteS(args[i],cst_string_auto_len,i != (count - 1));
    }

	if(strcmp(cmd,"hmsetl") == 0) {
		CHECK_ARGS_GREAT(3);

		if(((count - 1) % 3) != 0) {
			printf("error key/val pair number\n");
			return 1;
		}
		client->CreateRequest(req,CMD_HMULTISET_LOOSE);

		for(int i = 1; i < count; i+=3) {
			req.GetWriter()->WriteS(args[i+0],cst_string_auto_len,true);
			req.GetWriter()->WriteS(args[i+1],cst_string_auto_len,true);
			req.GetWriter()->WriteS(args[i+2],cst_string_auto_len,true);
		}
		req.GetWriter()->WriterTerminator();
	}

	if(strcmp(cmd,"hmdell") == 0) {
		CHECK_ARGS_GREAT(3);

		if(((count - 1) % 2) != 0) {
			printf("error key/val pair number\n");
			return 1;
		}
		client->CreateRequest(req,CMD_HMULTIDEL_LOOSE);

		for(int i = 1; i < count; i+=2) {
			req.GetWriter()->WriteS(args[i+0],cst_string_auto_len,true);
			req.GetWriter()->WriteS(args[i+1],cst_string_auto_len,true);
		}
		req.GetWriter()->WriterTerminator();
	}

	if(strcmp(cmd,"hmsetnxl") == 0) {
		CHECK_ARGS_GREAT(3);

		if(((count - 1) % 3) != 0) {
			printf("error key/val pair number\n");
			return 1;
		}
		client->CreateRequest(req,CMD_HMULTISETNX_LOOSE);

		for(int i = 1; i < count; i+=3) {
			req.GetWriter()->WriteS(args[i+0],cst_string_auto_len,true);
			req.GetWriter()->WriteS(args[i+1],cst_string_auto_len,true);
			req.GetWriter()->WriteS(args[i+2],cst_string_auto_len,true);
		}
		req.GetWriter()->WriterTerminator();
	}

    if(strcmp(cmd,"hmset") == 0) {
        CHECK_ARGS_GREAT(3);

        if((count % 2) != 0) {
            printf("error key/val pair number\n");
            return 1;
        }
		client->CreateRequest(req,CMD_HMULTISET);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);

        for(int i = 2; i < count; i+=2) {
			req.GetWriter()->WriteS(args[i+0],cst_string_auto_len,true);
			req.GetWriter()->WriteS(args[i+1],cst_string_auto_len,true);
        }
		req.GetWriter()->WriterTerminator();
    }

	if(strcmp(cmd,"hmsetnx") == 0) {
		CHECK_ARGS_GREAT(3);

		if((count % 2) != 0) {
			printf("error key/val pair number\n");
			return 1;
		}
		client->CreateRequest(req,CMD_HMULTISETNX);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);

		for(int i = 2; i < count; i+=2) {
			req.GetWriter()->WriteS(args[i+0],cst_string_auto_len,true);
			req.GetWriter()->WriteS(args[i+1],cst_string_auto_len,true);
		}
		req.GetWriter()->WriterTerminator();
	}

	if(strcmp(cmd,"hmdel") == 0) {
        CHECK_ARGS_GREAT(3);

		client->CreateRequest(req,CMD_HMULTIDEL);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);
		for(int i = 2; i < count; ++i)
			req.GetWriter()->WriteS(args[i],cst_string_auto_len,true);
		req.GetWriter()->WriterTerminator();
    }

    if(strcmp(cmd,"hincrby") == 0) {
        CHECK_ARGS_NUM(3);
        int64 incr = pwutils::atoi(args[3]);

		client->CreateRequest(req,CMD_HINCR);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);
		req.GetWriter()->WriteS(args[2],cst_string_auto_len,true);
		req.GetWriter()->WriteI(incr);
    }

    if(strcmp(cmd,"hincrbyfloat") == 0) {
        CHECK_ARGS_NUM(3);
        double incr = pwutils::atof(args[3]);

		client->CreateRequest(req,CMD_HINCR_FLOAT);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);
		req.GetWriter()->WriteS(args[2],cst_string_auto_len,true);
		req.GetWriter()->WriteD(incr);
    }

    if(strcmp(cmd,"hall") == 0) {
        CHECK_ARGS_NUM(1);
		client->CreateRequest(req,CMD_HKEYVALS);
        req.GetWriter()->WriteS(args[1],cst_string_auto_len);
    }
	if(strcmp(cmd,"hkeys") == 0) {
		CHECK_ARGS_NUM(1);
		client->CreateRequest(req,CMD_HKEYS);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len);
	}
	if(strcmp(cmd,"hvals") == 0) {
		CHECK_ARGS_NUM(1);
		client->CreateRequest(req,CMD_HVALS);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len);
	}
    if(strcmp(cmd,"hclear") == 0) {
        CHECK_ARGS_NUM(1);
		client->CreateRequest(req,CMD_HDROP);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len);
    }
	if(strcmp(cmd,"hmclear") == 0) {
		CHECK_ARGS_GREAT(2);

		client->CreateRequest(req,CMD_HMULTIDROP);

		for(int i = 1; i < count; i++) {
			req.GetWriter()->WriteS(args[i],cst_string_auto_len,true);
		}
		req.GetWriter()->WriterTerminator();

	}

	if(strcmp(cmd,"hsize") == 0) {
		CHECK_ARGS_NUM(1);
		client->CreateRequest(req,CMD_HSIZE);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len);
	}

	if(strcmp(cmd,"hscan") == 0) {
		CHECK_ARGS_NUM(4);
		int64 limit = pwutils::atoi(args[4]);

		client->CreateRequest(req,CMD_HSCAN);

		req.GetWriter()->WriteStdS(args[1],true);
		req.GetWriter()->WriteStdS(args[2],true);
		req.GetWriter()->WriteStdS(args[3],true);
		req.GetWriter()->WriteI(limit);
	}

	if(strcmp(cmd,"hrange") == 0) {
		CHECK_ARGS_NUM(3);
		int64 start = pwutils::atoi(args[2]);
		int64 limit = pwutils::atoi(args[3]);

		client->CreateRequest(req,CMD_HRANGE);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);
		req.GetWriter()->WriteI(start,true);
		req.GetWriter()->WriteI(limit);
	}

	if(strcmp(cmd,"hcreateindex") == 0) {
		CHECK_ARGS_NUM(3);
		int64 type = args[3][0];
		if(type != 'i' && type != 's')
		{
			std::cout << "hcreateindex param[3] mustbe i or s" << std::endl;
			return 0;
		}

		client->CreateRequest(req,CMD_HCREATE_INDEX);

		req.GetWriter()->WriteStdS(args[1],true);
		req.GetWriter()->WriteStdS(args[2],true);
		req.GetWriter()->WriteI(type,true);
		req.GetWriter()->WriterTerminator();
	}

	if(strcmp(cmd,"hdeleteindex") == 0) {
		CHECK_ARGS_NUM(2);
		client->CreateRequest(req,CMD_HDELETE_INDEX);

		req.GetWriter()->WriteStdS(args[1],true);
		req.GetWriter()->WriteStdS(args[2],true);
		req.GetWriter()->WriterTerminator();
	}

	if(strcmp(cmd,"hlistindex") == 0) {
		client->CreateRequest(req,CMD_HLIST_INDEX);

		req.GetWriter()->WriterTerminator();
	}

	if(strcmp(cmd,"hindexquery") == 0) {
		CHECK_ARGS_NUM(3);
		client->CreateRequest(req,CMD_HINDEX_QUERY);
		req.GetWriter()->WriteStdS(args[1],true); // hname
		req.GetWriter()->WriteStdS(args[2],true); // field
		req.GetWriter()->WriteStdS(args[3],true); // value
		req.GetWriter()->WriterTerminator();
	}

	if(strcmp(cmd,"hindexqueryrange") == 0) {
		CHECK_ARGS_NUM(4);
		client->CreateRequest(req,CMD_HINDEX_QUERY_RANGE);
		req.GetWriter()->WriteStdS(args[1],true); // hname
		req.GetWriter()->WriteStdS(args[2],true); // field
		req.GetWriter()->WriteStdS(args[3],true); // start
		req.GetWriter()->WriteStdS(args[4],true); // ended
		req.GetWriter()->WriterTerminator();
	}

	// ----------------------------------------------------------

    if(strcmp(cmd,"zget") == 0) {
        CHECK_ARGS_NUM(2);
		client->CreateRequest(req,CMD_ZGET);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);
		req.GetWriter()->WriteS(args[2],cst_string_auto_len);
    }

    if(strcmp(cmd,"zset") == 0) {
        CHECK_ARGS_NUM(3);
        int64 score = pwutils::atoi(args[3]);
		
		client->CreateRequest(req,CMD_ZSET);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);
		req.GetWriter()->WriteS(args[2],cst_string_auto_len,true);
		req.GetWriter()->WriteI(score);
    }

    if(strcmp(cmd,"zdel") == 0) {
        CHECK_ARGS_NUM(2);
		client->CreateRequest(req,CMD_ZDEL);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);
		req.GetWriter()->WriteS(args[2],cst_string_auto_len);
    }

    if(strcmp(cmd,"ztop") == 0) {
        CHECK_ARGS_NUM(2);
        int64 limit = pwutils::atoi(args[2]);

		client->CreateRequest(req,CMD_ZTOP);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);
		req.GetWriter()->WriteI(limit);
    }

    if(strcmp(cmd,"zrtop") == 0) {
		CHECK_ARGS_NUM(2);
		int64 limit = pwutils::atoi(args[2]);

		client->CreateRequest(req,CMD_ZRTOP);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);
		req.GetWriter()->WriteI(limit);
    }

    if(strcmp(cmd,"zclear") == 0) {
        CHECK_ARGS_NUM(1);
		client->CreateRequest(req,CMD_ZDROP);
        req.GetWriter()->WriteS(args[1],cst_string_auto_len);
    }

	if(strcmp(cmd,"zclear2") == 0) {
		CHECK_ARGS_NUM(1);
		client->CreateRequest(req,CMD_ZDROPEX);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len);
	}

	if(strcmp(cmd,"zsize") == 0) {
		CHECK_ARGS_NUM(1);
		client->CreateRequest(req,CMD_ZSIZE);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len);
	}

	if(strcmp(cmd,"zlist") == 0) {
		CHECK_ARGS_NUM(0);
		client->CreateRequest(req,CMD_ZLIST);
		req.GetWriter()->WriterTerminator();
	}

    // ----------------------------------------------------------

    if(strcmp(cmd,"dump") == 0) {
        client->CreateRequest(req,CMD_DUMP);
		req.GetWriter()->WriteNil();
    }

	if(strcmp(cmd,"list") == 0) {
		client->CreateRequest(req,CMD_LIST_DATABASES);
		req.GetWriter()->WriteNil();
	}

	if(strcmp(cmd,"adduser") == 0) {
		CHECK_ARGS_NUM(3);
		std::string pswd = pwutils::Md5(args[2]);
		int64 sys = pwutils::atoi(args[3]);

		client->CreateRequest(req,CMD_SYS_ADDUSER);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);
		req.GetWriter()->WriteS(pswd.c_str(),cst_string_auto_len,true);
		req.GetWriter()->WriteI(sys);
	}

	if(strcmp(cmd,"moduser") == 0) {
		CHECK_ARGS_NUM(3);
		std::string pswd = pwutils::Md5(args[2]);
		int64 sys = pwutils::atoi(args[3]);

		client->CreateRequest(req,CMD_SYS_MODUSER);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);
		req.GetWriter()->WriteS(pswd.c_str(),cst_string_auto_len,true);
		req.GetWriter()->WriteI(sys);
	}

	if(strcmp(cmd,"deluser") == 0) {
		CHECK_ARGS_NUM(1);
		int64 sys = pwutils::atoi(args[3]);

		client->CreateRequest(req,CMD_SYS_DELUSER);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len);
	}

	if(strcmp(cmd,"load") == 0) {
		CHECK_ARGS_NUM(1);
		client->CreateRequest(req,CMD_LOAD_DATABASE);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);
		req.GetWriter()->WriterTerminator();
	}

	if(strcmp(cmd,"unload") == 0) {
		CHECK_ARGS_NUM(1);
		client->CreateRequest(req,CMD_UNLOAD_DATABASE);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);
		req.GetWriter()->WriterTerminator();
	}

	if(strcmp(cmd,"copy") == 0) {
		CHECK_ARGS_NUM(2);
		client->CreateRequest(req,CMD_COPY_DATABASE);
		req.GetWriter()->WriteS(args[1],cst_string_auto_len,true);
		req.GetWriter()->WriteS(args[2],cst_string_auto_len,true);
		req.GetWriter()->WriterTerminator();
	}

    // ----------------------------------------------------------

    if(strcmp(cmd,"help") == 0)
    {
        printf("command list: \n"

				"\n"
				"\t""list"                      "\n"
               "\n"
               "\t""create dbname"                      "\n"
               "\t""select dbname"                      "\n"
               "\t""delete dbname"                      "\n"
               "\n"
               "\t""hget name key"                      "\n"
               "\t""hset name key value"                "\n"
               "\t""hdel name key"                      "\n"
               "\t""hsetnx name key value"              "\n"
               "\t""hmget name key1 key2 ..."       "\n"
               "\t""hmset name key1 val1 key2 val2 ..." "\n"
               "\t""hmdel name key1 key2 ..."           "\n"
               "\t""hincrby name key int64value"            "\n"
               "\t""hincrbyfloat name key doublevalue"      "\n"
               "\t""hall name"                              "\n"
			   "\t""hvals name"                              "\n"
               "\t""hclear name"                            "\n"
			   "\t""hsize name"								"\n"
               "\n"
               "\t""zget name key"                          "\n"
               "\t""zset name key score"                    "\n"
               "\t""zdel name key"                          "\n"
               "\t""ztop name min max"                      "\n"
               "\t""zrtop name min max"                     "\n"
               "\t""zclear name"                            "\n"
			   "\t""zsize name"                            "\n"
               "\n"
               "\t""dump"                                   "\n"
               );
        return 2;
    }

    // ----------------------------------------------------------

    if(strcmp(cmd,"exit") == 0) {
		return -1;
    }

	if(req.requestId != 0)
	{
		std::ostream* os = &std::cout;
		std::fstream fs;

		if(g_output_filename.length() > 0)
		{
			fs.open(g_output_filename.c_str(),std::ios_base::app | std::ios_base::out);
			if(fs.good())
				os = &fs;
		}

		gdb::Client::Response response;
		client->CommitRequest(req,&response);

		if(response.GetErrorCode() == gdb::FAILED_SUCCESSFUL)
		{
			for(size_t i = gdb::Client::PKT_INDEX_DATA0; i < response.packets.size(); ++i)
			{
				(*os) << "res(" << (i - gdb::Client::PKT_INDEX_DATA0) << ") = ";
				printVar(*os,response.packets[i]);
			}

		}
		else
		{
			for(size_t i = 0; i < response.packets.size(); ++i)
			{
				(*os) << "res(" << i << ") = ";
				printVar(*os,response.packets[i]);
			}

		}

		os->flush();

		if(g_output_filename.length() > 0)
			g_output_filename.clear();
	}
	else
	{
		printf("unknown command:%s\n",args[0]);
	}
    return 0;
}


static char g_line[102400] = "";

char* readline(const char* msg)
{
	printf("%s",msg);

	if(!std::cin.good())
		return NULL;
	std::cin.getline(g_line,_countof(g_line));

	return g_line;
}


void tool_mode()
{
    client->Update(-1);

    pwutils::time::sleep(1000);

    while(!pwngs::gClosed)
    {
        char* line = ::readline("gdbcli>");
		if(line == NULL)
			break;
        if(line == NULL || strlen(line) == 0)
            continue;
        int r = handleLine(line);        
        if(r < 0) break;
    }

}

int main(int argc,char** argv)
{
	platform::init();
	pwngs::MySigHandler_Init();
	std::string host("127.0.0.1");
	int port = 8600;

	client = new gdb::Client();
	client->doref();

	if(argc > 1)
		host = argv[1];
	if(argc > 2)
		port = pwutils::atoi(argv[2]);
		
	if(client->Connect(host.c_str(),port) < 0)
    {
        printf("can't connect to %s:%d\n",host.c_str(),port);
        return 1;
    }

	if(client->Authentication("test","test") != gdb::FAILED_SUCCESSFUL)
	{
		printf("auth failed\n");
		return 2;
	}

	if(client->CreateDatabase("testdb") != gdb::FAILED_SUCCESSFUL)
	{
		printf("CreateDatabase failed\n");
		//return 2;
	}

	if(client->SelectDatabase("testdb") != gdb::FAILED_SUCCESSFUL)
	{
		printf("SelectDatabase failed\n");
		return 2;
	}
	else
	{
		printf("select testdb\n");
	}
    // sync_test();
    //async_test();


    tool_mode();

	return 0;
}
