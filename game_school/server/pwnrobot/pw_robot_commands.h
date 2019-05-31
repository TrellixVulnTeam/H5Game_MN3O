#ifndef _pw_robot_commands_
#define _pw_robot_commands_

namespace pwngs
{
	extern void InitialHandlers();
	extern bool handleQ(const char* cmd,int argc,char** argv);
	extern bool handleClose(const char* cmd,int argc,char** argv);
	extern bool handleC(const char* cmd,int argc,char** argv);
	extern bool handleSetServer(const char* cmd,int argc,char** argv);
	extern bool handleCreateAdventure(const char* cmd,int argc,char** argv);
	extern bool handleObjectCount(const char* cmd,int argc,char** argv);
	extern bool handleGM(const char* cmd,int argc,char** argv);
	extern bool handleMoveTo(const char* cmd,int argc,char** argv);	
	extern bool handleMoveToRandom(const char* cmd,int argc,char** argv);
	extern bool handleCaster(const char* cmd,int argc,char** argv);
	extern bool handleLadderStart(const char* cmd,int argc,char** argv);
	extern bool handleLadderClean(const char* cmd,int argc,char** argv);
	
}

#endif // _pw_robot_commands_