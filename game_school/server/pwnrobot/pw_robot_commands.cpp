#include "pw_robot_commands.h"
#include "main.h"
#include "arg_parser.h"
#include "pw_utils.h"
#include "pw_class.h"
#include "pw_robot_human.h"
#include "pw_robot_module_socket.h"
#include "pw_robot_thread.h"
#include "pw_robot_module_motion.h"
#include "pw_robot_module_magic.h"
#include "pw_robot_module_ladder.h"

#include "../pwworldsrv/msg/msg.def.h"
#include "worldsrv.pb.h"

namespace pwngs
{
	using namespace pwngs::protocol::worldsrv;
	
	static std::string g_strServerIp("127.0.0.1");
	static int g_nServerPort = 8000;

	void InitialHandlers()
	{
		g_mapCommandHandlers["q"] = &handleQ;
		g_mapCommandHandlers["c"] = &handleC;
		g_mapCommandHandlers["server"] = &handleSetServer;
		g_mapCommandHandlers["createadventure"] = &handleCreateAdventure;
		g_mapCommandHandlers["objnum"] = &handleObjectCount;
		g_mapCommandHandlers["close"] = &handleClose;
		g_mapCommandHandlers["gm"] = &handleGM;
		g_mapCommandHandlers["moveto"] = &handleMoveTo;
		g_mapCommandHandlers["movetorandom"] = &handleMoveToRandom;
		g_mapCommandHandlers["caster"] = &handleCaster;
		g_mapCommandHandlers["ladder_start"] = &handleLadderStart;
		g_mapCommandHandlers["ladder_clean"] = &handleLadderClean;
	}

	bool handleQ( const char* cmd,int argc,char** argv )
	{
		printf("exit -- handleQ\n");
		handleClose(cmd,argc,argv);
		return false;
	}

	extern void pfnBroadcastThreadCharacterMessage(void* param1,void* param2);

	template<class T> void BroadcastThreadCharacterMessageT(pfnThreadCharacterFunc func,T* obj)
	{
		RobotThreadMessageT<T>* msg = new RobotThreadMessageT<T>();
		msg->m_func = &pfnBroadcastThreadCharacterMessage;
		msg->m_targetfn = func;
		msg->m_object = obj;
		msg->doref();

		for(int i = 0; i < cst_thread_num; ++i)
		{
			g_pRobotThreads[i]->ExecuteMessage(msg);
		}

		msg->unref();
	}

	template<class T> void CollectThreadData(pfnThreadFunc func,void* param1,void* param2,T& result)
	{
		RobotThreadCollectorT<T>* msg = new RobotThreadCollectorT<T>();
		msg->m_func = func;
		msg->m_param1 = param1;
		msg->m_param2 = param2;
		msg->m_nThreadNum = cst_thread_num;
		msg->doref();

		for(int i = 0; i < cst_thread_num; ++i)
		{
			g_pRobotThreads[i]->ExecuteMessage(msg);
		}

		while(!msg->IsFinished() && !msg->IsTimeout())
		{
			pwutils::time::sleep(100);
		}

		result = msg->m_objValue;

		msg->unref();
	}


	// --------------------------------------------------------


	template<class T> struct SRangedCommand
	{
		int start;
		int ended;
		T value;

		bool IsRangeValid()
		{
			return start != -1 && ended != -1;
		}

		bool IsValid(int id)
		{
			return !IsRangeValid() || (id >= start && id <= ended);
		}
	};

	struct SCreateHumanContext
	{
		int accid;
		std::string account;
	};

	static void pfnCreateHuman(void* param1,void* param2)
	{
		pwutils::ScopePtr<SCreateHumanContext> ctx((SCreateHumanContext*)param1);

		RobotHuman* human = new RobotHuman(ctx->accid,ctx->account.c_str(),"1");
		if(human->GetModSocket()->ConnectSync(g_strServerIp.c_str(),g_nServerPort) != 0)
		{
			delete human;
			return ;
		}
		if(GetCurrentRobotThread()->Add(human) != 0)
		{
			delete human;
			return ;
		}

		GetCurrentReactor()->Add(human->GetModSocket(),pwutils::SocketReactor::MASK_DEFAULT);

		human->OnConnected();
	}


	bool handleC( const char* cmd,int argc,char** argv )
	{
		Arg_parser::Option options[] =
		{
			{ 'N', "account",	Arg_parser::yes  },
			{ 's', "startid",	Arg_parser::yes  },
			{ 'e', "endedid",   Arg_parser::yes  },
			{  0,   0,			Arg_parser::no	} 
		};

		Arg_parser parser(argc,argv,options,false);
		if(parser.error().length() > 0)
		{
			print_response("error args: %s",parser.error().c_str());
			return true;
		}

		std::string account;
		int start = 0;
		int ended = 0;

		for( int i = 0; i < parser.arguments(); ++i)
		{
			int code = parser.code(i);
			const char* arg = parser.argument(i).c_str();

			switch(code)
			{
			case 'N':
				account = arg;
				break;
			case 's':
				start = (int)pwutils::atoi(arg);
				break;
			case 'e':
				ended = (int)pwutils::atoi(arg);
				break;
			}
		}

		if(account.length() > 0 && start != 0 && ended != 0)
		{
			for(int i = start; i <= ended; ++i)
			{
				char buf[100] = "";
				pwutils::itoa(buf,i);

				int n = pwutils::random(0,cst_thread_num);

				SCreateHumanContext* ctx = new SCreateHumanContext();
				ctx->account = account;
				ctx->account.append(buf);
				ctx->accid = i;
				g_pRobotThreads[n]->ExecuteMessage(&pfnCreateHuman,ctx);
			}
		}
		else
		{
			print_response("error args");
		}

		return true;
	}

	extern bool handleSetServer( const char* cmd,int argc,char** argv )
	{
		Arg_parser::Option options[] =
		{
			{ 'i', "ip",	Arg_parser::yes  },
			{ 'p', "port",	Arg_parser::yes  },
			{  0,   0,			Arg_parser::no	} 
		};

		Arg_parser parser(argc,argv,options,false);
		if(parser.error().length() > 0)
		{
			print_response("error args: %s",parser.error().c_str());
			return true;
		}

		if(parser.arguments() > 0)
		{
			std::string ip;
			int port = 0;

			for( int i = 0; i < parser.arguments(); ++i)
			{
				int code = parser.code(i);
				const char* arg = parser.argument(i).c_str();

				switch(code)
				{
				case 'i':
					ip = arg;
					break;
				case 'p':
					port = (int)pwutils::atoi(arg);
					break;
				}
			}

			if(port != 0)
				g_nServerPort = port;
			if(ip.length() > 0)
				g_strServerIp = ip;
		}
		else
		{
			print_response("server = %s ,port = %d",g_strServerIp.c_str(),g_nServerPort);
		}
		return true;
	}

	static void pfnhandleCreateAdventure(RobotCharacter* character,void* param1)
	{
		int64 id = *(int64*)param1;

		CSCreateAdventure msg;
		msg.set_item_id(id);
		character->SendMsg(msgid_CSCreateAdventure,msg);
	}

	extern bool handleCreateAdventure( const char* cmd,int argc,char** argv )
	{
		if(argc < 2)
		{
			print_response("useage with: confid ");
		}

		int64 id = pwutils::atoi(argv[1]);
		if(id > 0)
		{
			BroadcastThreadCharacterMessageT<int64>(&pfnhandleCreateAdventure,new int64(id));
		}
		return true;
	}

	static void pfnhandleHumanCount(void* param1,void* param2)
	{
		RobotThread* thr = GetCurrentRobotThread();
		RobotThreadCollectorT<int>* msg = (RobotThreadCollectorT<int>*)thr->m_pCurrentMessage;

		msg->Plus((int)thr->m_mapObjects.size());

		print_response("0x%p character = %d",(void*)thr,(int)thr->m_mapObjects.size());
	}

	bool handleObjectCount( const char* cmd,int argc,char** argv )
	{
		int count = 0;
		CollectThreadData<int>(&pfnhandleHumanCount,NULL,NULL,count);
		print_response("total obj num = %d",count);
		return true;
	}

	static void pfnhandleClose(RobotCharacter* character,void* param1)
	{
		if(RobotHuman* h = character->QueryObjectEx<RobotHuman>())
		{
			h->LeaveWorld("pfnhandleClose");
			h->DiscardObject();
		}
	}

	bool handleClose( const char* cmd,int argc,char** argv )
	{
		BroadcastThreadCharacterMessage(&pfnhandleClose,NULL);
		pwutils::time::sleep(2000);
		return true;
	}

	static void pfnhandleGM(RobotCharacter* character,void* param1)
	{
		SRangedCommand<std::string>* ctx = (SRangedCommand<std::string>*)(param1);

		if(RobotHuman* h = character->QueryObjectEx<RobotHuman>())
		{
			if(ctx->IsValid(h->GetAccId()))
			{
				CSChat msg;
				msg.set_mode(0);
				msg.set_text_type(0);
				msg.set_to(0);
				msg.set_to_name("");
				msg.set_text(ctx->value);


				if(character->IsBitSet(ROBOT_BITEX_INWORLD))
					character->SendMsg(msgid_CSChat,msg);
			}
		}
	}

	bool handleGM( const char* cmd,int argc,char** argv )
	{
		if(argc < 2)
		{
			print_response("useage with: text -s start -e ended");
			return true;
		}

		Arg_parser::Option options[] =
		{
			{ 's', "startid",	Arg_parser::yes  },
			{ 'e', "endedid",   Arg_parser::yes  },
			{  0,   0,			Arg_parser::no	} 
		};


		Arg_parser parser(argc,argv,options,false);
		if(parser.error().length() > 0)
		{
			print_response("error args: %s",parser.error().c_str());
			return true;
		}

		SRangedCommand<std::string>* ctx = new SRangedCommand<std::string>();
		ctx->start = -1;
		ctx->ended = -1;

		for( int i = 0; i < parser.arguments(); ++i)
		{
			int code = parser.code(i);
			const char* arg = parser.argument(i).c_str();

			switch(code)
			{
			case 's':
				ctx->start = (int)pwutils::atoi(arg);
				break;
			case 'e':
				ctx->ended = (int)pwutils::atoi(arg);
				break;
			case 0:
				{
					ctx->value.append(arg);
					ctx->value.append(" ");
				}
				break;
			}
		}
		ctx->value.resize(ctx->value.size() - 1);

		BroadcastThreadCharacterMessageT<SRangedCommand<std::string> >(&pfnhandleGM,ctx);

		return true;
	}

	static void pfnhandleMoveTo(RobotCharacter* character,void* param1)
	{
		G3D::Vector3* pos = (G3D::Vector3*)param1;

		if(RobotHuman* h = character->QueryObjectEx<RobotHuman>())
		{
			if(h->IsBitSet(ROBOT_BITEX_INWORLD))
				h->GetModMotion()->MoveWaypoint(*pos);
		}
	}

	bool handleMoveTo( const char* cmd,int argc,char** argv )
	{
		if(argc < 4)
		{
			print_response("useage with: x y z ");
			return true;
		}

		G3D::Vector3* pos = new G3D::Vector3();

		pos->x = pwutils::atof(argv[1]);
		pos->y = pwutils::atof(argv[2]);
		pos->z = pwutils::atof(argv[3]);

		BroadcastThreadCharacterMessageT<G3D::Vector3>(&pfnhandleMoveTo,pos);

		return true;
	}

	struct SMoveToRandom
	{
		G3D::Vector3 pos;
		float random_dist;
	};

	static void pfnhandleMoveToRandom(RobotCharacter* character,void* param1)
	{
		SMoveToRandom* r = (SMoveToRandom*)param1;

		if(RobotHuman* h = character->QueryObjectEx<RobotHuman>())
		{
			if(h->IsBitSet(ROBOT_BITEX_INWORLD))
			{
				h->GetModMotion()->MoveWaypointRandom(r->pos,r->random_dist);
			}
		}
	}

	extern bool handleMoveToRandom( const char* cmd,int argc,char** argv )
	{
		if(argc < 5)
		{
			print_response("useage with: x y z dist");
			return true;
		}

		SMoveToRandom* r = new SMoveToRandom();

		r->pos.x = pwutils::atof(argv[1]);
		r->pos.y = pwutils::atof(argv[2]);
		r->pos.z = pwutils::atof(argv[3]);
		r->random_dist = pwutils::atof(argv[4]);

		BroadcastThreadCharacterMessageT<SMoveToRandom>(&pfnhandleMoveToRandom,r);

		return true;
	}

	static void pfnhandleCaster(RobotCharacter* character,void* param1)
	{
		if(RobotHuman* h = character->QueryObjectEx<RobotHuman>())
		{
			if(h->IsBitSet(ROBOT_BITEX_INWORLD))
			{
				if(param1 == NULL)
					h->GetModMagic()->CleanAutomaticCaster();
				else
					h->GetModMagic()->StartAutomaticCaster();
			}
		}
	}

	bool handleCaster( const char* cmd,int argc,char** argv )
	{
		if(argc < 2)
		{
			print_response("useage with: subcmd");
			return true;
		}

		if(strcmp(argv[1],"start") == 0)
		{
			BroadcastThreadCharacterMessage(&pfnhandleCaster,(void*)1);
		}
		else if(strcmp(argv[1],"stop") == 0)
		{
			BroadcastThreadCharacterMessage(&pfnhandleCaster,(void*)0);
		}
		else
		{
			print_response("error subcmd: use start | stop");
		}
		return true;
	}

	// -----------------------------------------------------------------------------------------

	static void pfnhandleLadderStart(RobotCharacter* character,void* param1)
	{
		if(RobotHuman* h = character->QueryObjectEx<RobotHuman>())
		{
			h->GetModLadder()->Startup();
		}
	}

	static void pfnhandleLadderClean(RobotCharacter* character,void* param1)
	{
		if(RobotHuman* h = character->QueryObjectEx<RobotHuman>())
		{
			h->GetModLadder()->Cleanup();
		}
	}

	extern bool handleLadderStart( const char* cmd,int argc,char** argv )
	{
		BroadcastThreadCharacterMessage(&pfnhandleLadderStart,NULL);
		return true;
	}

	extern bool handleLadderClean( const char* cmd,int argc,char** argv )
	{
		BroadcastThreadCharacterMessage(&pfnhandleLadderClean,NULL);
		return true;
	}

}