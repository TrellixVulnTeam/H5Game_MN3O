#ifndef _pw_ngs_utils_
#define _pw_ngs_utils_

#include <vector>
#include <string>
#include "G3D/G3D.h"
#include "pwdist_common.h"
#include "pw_entrance_def.h"
#include "pw_platform.h"

namespace pwutils
{
	extern unsigned char* GetDefaultHMACKey();
	extern size_t GetDefaultHMACLen();

	extern std::string GetSImplAny(const char* fmt,int _max);
	extern std::string GetSImplSend(int i);
	extern std::string GetSImplAcc(int i);
	extern bool gethostaddresses(std::vector<std::string>& addresses);
	// 金币转化为rmb分
	extern int64 GoldToRmbfen(int64 gold);

//	extern std::string GetStage(int mapid);
	
	extern bool IsFloatEqual(float a,float b);
	
	/**
	 * @brief 计算夹角 0-360度 以逆时针为正方向,忽略y轴
	 * @param v1
	 * @param v2
	 * @return 
	 */
	extern float angle(const G3D::Vector3& v1,const G3D::Vector3& v2);
	/**
	 * @brief 计算夹角 0-180度,无方向,忽略y轴
	 * @param v1
	 * @param v2
	 * @return 
	 */
	extern float angle2(const G3D::Vector3& v1,const G3D::Vector3& v2);
	
	extern float radian_to_drgree(float radian);
	extern float degree_to_radian(float degree);

	extern const char* GetProfessionNameUTF(int pro);


	/**
	 * @brief 在天梯服中触发该rpc(普通服中使用)
	 * @return 
	 */
	extern void LadderExecuteCall(pwdist::MsgCall& call,bool expectResult = false,int32 ladder_level = 0);

	/**
	 * @brief 在天梯服中找到Human触发该rpc(普通服中使用)
	 * @return 
	 */
	extern void LadderExecuteHumanCall(pwdist::MsgCall& call,int64 hid,int32 ladder_level = 0);
	/**
	 * @brief 在普通服中触发该rpc(天梯服中使用)
	 * @return 
	 */
	extern void NormalExecuteCall(pwdist::MsgCall& call,int64 server_group,bool expectResult = false);

	/**
	* @brief 在所有普通服出发rpc(天梯服中使用)
	* @return
	*/
	extern void AllNormalExecuteCall(pwdist::MsgCall& call, bool expectResult = false);

	/**
	 * @brief 在普通服中找到Human触发该rpc(天梯服中使用)
	 * @return 
	 */
	extern void NormalExecuteHumanCall(pwdist::MsgCall& call,int64 hid,int64 server_group);

	
	//************************************************************************************************

	/**
	 * @brief 同步Human信息到本地服(天梯服中使用)
	 * @return 
	 */
	extern void SyncLadderHumanInfo(int64 hid,int64 server_group,const pwngs::entrance::SSyncLadderHumanInfo& info,int64 flags);

	/**
	 * @brief 同步Human信息到天梯服(本地服中使用)
	 * @return 
	 */
	extern void SyncNormalHumanInfo(int64 hid,int64 ladder_level,const pwngs::entrance::SSyncNormalHumanInfo& info,int64 flags);

	/**
	 * @brief 同步队伍信息到本地服(天梯服中使用)
	 * @return 
	 */
	extern void SyncLadderTeamInfo(int64 server_group,const pwngs::entrance::SSyncLadderTeamInfo& info,int64 flags);

	/**
	 * @brief 同步队伍信息到天梯服(本地服中使用)
	 * @return 
	 */
	extern void SyncNormalTeamInfo(int64 ladder_level,const pwngs::entrance::SSyncNormalTeamInfo& info,int64 flags);

	/**
	 * @brief 同步队伍中PVE襄阳守卫奖励信息到本地服(天梯服中使用)
	 * @return
	*/
	extern void SyncLadderTeamReward(int64 server_group, const pwngs::entrance::SSyncLadderTeamReward& info, int64 flags);

	/**
	* 跨服联盟战 -- 跨服rpc通信
	* 消息流向(本地服中使用)：本地服务器 >> 天梯服务器
	*/
	// GM指令
	extern void LadderExcute_KF_GMCommand(int64 ladder_level, const char *pParam1, const char *pParam2);
	// 同步神佑排行数据
	extern void LadderExcute_KF_UpdateSYRankInfo(int64 ladder_level, int32 nWarZoneId, pwngs::entrance::SYRankInfo &tmpSYRankInfo);
	// 获取神佑排行数据
	extern void LadderExcute_KF_ObtainSYRankInfo(int64 ladder_level, int32 nWarZoneId, int64 nServerGroupId);


	/**
	* 跨服联盟战 -- 跨服rpc通信
	* 消息流向(天梯服中使用)：天梯服务器 >> 本地服务器
	*/
	// 同步神佑排行榜数据
	extern void NormalExcute_KF_SyncSYRankInfo(int nWarZoneId, std::vector<pwngs::entrance::SYRankInfo> &vtSYRankInfo);
	extern void NormalExcute_KF_SyncSYRankInfo(int64 nServerGroupid, int nWarZoneId, std::vector<pwngs::entrance::SYRankInfo> &vtSYRankInfo);
	extern void NormalExcute_KF_SyncTTSInfo(int nWarZoneId, int nRound, pwngs::entrance::STTSInfoList &sTTSInfoList);
	extern void NormalExcute_KF_SyncStatus(int nStatus);
	extern void NormalExcute_KF_TTSReward(int nWarZoneId);

	/**
	 * @brief 竞技场开启关闭时间判断
	 * @return 
	 */
	extern bool IsArena1v1BeginTime(sint32 curweek,sint32 curhour,sint32 curmins);
	extern bool IsArena1v1OpeningTime(sint32 curweek,sint32 curhour,sint32 curmins);
	extern bool IsArena1v1EndedTime(sint32 curweek,sint32 curhour,sint32 curmins);
	extern bool IsArena3v3BeginTime(sint32 curweek,sint32 curhour,sint32 curmins);
	extern bool IsArena3v3OpeningTime(sint32 curweek,sint32 curhour,sint32 curmins);
	extern bool IsArena3v3EndedTime(sint32 curweek,sint32 curhour,sint32 curmins);
	extern bool IsArena1v1BeginWeek(sint32 curweek) ;
	extern bool IsArena3v3BeginWeek(sint32 curweek) ;
	
	/**
	 * @brief 战场开启时间判断
	 * @return 
	 */
	extern bool IsBattleOpeningTime(sint32 curweek,sint32 curhour,sint32 curmins);

	/**
	* @brief PVE开启关闭时间判断
	* @return
	*/
	extern bool IsPVEBeginTime(sint32 curweek, sint32 curhour, sint32 curmins);
	extern bool IsPVEBeginWeek(sint32 curweek);
}

#endif //_pw_ngs_utils_