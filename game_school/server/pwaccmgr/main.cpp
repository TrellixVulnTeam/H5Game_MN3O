#include <stdio.h>
#include "arg_parser.h"
#include "pw_utils.h"
#include "gdb/pw_gdb_def.h"
#include "gdb/pw_gdb_client.h"
#include "gdb/pw_gdb_synchronous_client.h"
#include "kvorm/pw_orm_passport.h"

static long g_passwords_num = 0;
static char g_passwords[100] = {0};

int initpswd()
{
	if(g_passwords_num != 0)
		return 0;

// 	for(char c = 'A'; c <= 'Z'; ++c)
// 	{
// 		g_passwords[g_passwords_num] = c;
// 		++g_passwords_num;
// 	}

	for(char c = 'a'; c <= 'z'; ++c)
	{
		g_passwords[g_passwords_num] = c;
		++g_passwords_num;
	}

	for(char c = '0'; c <= '9'; ++c)
	{
		g_passwords[g_passwords_num] = c;
		++g_passwords_num;
	}
	return 0;
}

int makepswd(char* buf)
{
	for(int i = 0; i < 6; ++i)
	{
		int n = (int)pwutils::random(0,g_passwords_num);
		buf[i] = g_passwords[n];
	}
	return 0;
}

int main(int argc,char** argv)
{
	printf("usage -h host -p port -n account_prefix -s startid -e endid -g spec_pswd\n");
	int ccc = strcmp("haccount|7=account_cbh1","haccount|7=account_cbh1");

	initpswd();

	struct Arg_parser::Option options[] = 
	{
		{ 'h',"host",Arg_parser::yes, },
		{ 'p',"port",Arg_parser::yes, },
		{ 'n',"prefix",Arg_parser::yes, },
		{ 's',"start",Arg_parser::yes, },
		{ 'e',"ended",Arg_parser::yes, },
		{ 'g',"spec pswd",Arg_parser::yes, },

		{ 'U',"user",Arg_parser::yes, },
		{ 'P',"pswd",Arg_parser::yes, },
		{ 'D',"dbname",Arg_parser::yes, },
	};
	Arg_parser parser(argc,argv,options,false);

	std::string host("127.0.0.1");
	std::string default_pswd;
	std::string prefix("cbh");
	int port = 3306;
	int start = 1,ended = 200;
	std::string user,pswd,dbname;

	for(int i = 0; i < parser.arguments(); ++i)
	{
		int c = parser.code(i);
		switch(c)
		{
		case 'U':
			user = parser.argument(i);
			break;
		case 'P':
			pswd = parser.argument(i);
			break;
		case 'D':
			dbname = parser.argument(i);
			break;
		case 'h':
			{
				host = parser.argument(i);
			}
			break;
		case 'p':
			{
				port = (int)pwutils::atoi(parser.argument(i).c_str());
			}
			break;
		case 'n':
			prefix = parser.argument(i);
			break;
		case 's':
			start = (int)pwutils::atoi(parser.argument(i).c_str());
			break;
		case 'e':
			ended = (int)pwutils::atoi(parser.argument(i).c_str());
			break;
		case 'g':
			default_pswd = parser.argument(i);
			break;
		}
	}
	if(prefix.length() <= 0)
	{
		printf("error args,need -M prefix\n");
		return 1;
	}

	platform::init();

	gdb::SynchronousClient client;
	if(client.Connect(host.c_str(),port) != 0)
	{
		return 2;
	}

	client.Update(-1);
	client.doref();

	if(client.Authentication(user.c_str(),pswd.c_str()) != 0)
	{
		printf("auth failed\n");
		return 1;
	}

	if(client.SelectDatabase(dbname.c_str()) != 0)
	{
		printf("select db %s failed\n",dbname.c_str());
		return 1;
	}


	printf("name\t\tpswd\n");
	printf("===========================================\n");
	for(int i = start; i <= ended; ++i)
	{
		
		char sql[4096] = "";
		char buf[4096] = "";
		char pswdbuf[100] = {0};

		if(default_pswd.length() > 0)
			strcpy(pswdbuf,default_pswd.c_str());
		else
			makepswd(pswdbuf);

		sprintf(buf,"%s%d",prefix.c_str(),i);		

		orm::Passport acc;
		acc.set_name(buf);
		acc.set_pswd(pswdbuf);

		std::string tmpbuf;
		acc.to_bson(tmpbuf);

		gdb::Client::Response response;
		{
			client.Hdel(orm::Passport::meta(),acc.getkey());
			response = *client.GetResponse();
		}
		{
			client.Hset(orm::Passport::meta(),acc.getkey(),tmpbuf);
			response = *client.GetResponse();
		}
		assert(response.IsSuccessful());

		printf("%s\t\t%s\n",buf,pswdbuf);
	}
	return 0;
};