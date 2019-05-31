#include "pw_ngs_logic_utils.h"
#include "pwngs/protocol/worldsrv/00000_00000_def.pb.h"

namespace pwutils
{

	/*extern void TranslateTencentUserInfoStruct(const orm::DTencentUserInfo& src,pwngs::STencentUserInfo& dst)
	{
		pwutils::strncpy(dst.platform,src.platform.c_str(),_countof(dst.platform));
		pwutils::strncpy(dst.openid,src.openid.c_str(),_countof(dst.openid));
		pwutils::strncpy(dst.openkey,src.openkey.c_str(),_countof(dst.openkey));
		pwutils::strncpy(dst.platform_key,src.platform_key.c_str(),_countof(dst.platform_key));

		dst.is_blue_vip = src.is_blue_vip;
		dst.is_blue_year_vip = src.is_blue_year_vip;
		dst.is_super_blue_vip = src.is_super_blue_vip;
		dst.blue_vip_level = src.blue_vip_level;

		dst.is_yellow_vip = src.is_yellow_vip;
		dst.is_yellow_year_vip = src.is_yellow_year_vip;
		dst.is_super_yellow_vip = src.is_super_yellow_vip;
		dst.yellow_vip_level = src.yellow_vip_level;

		dst.tgp_level = src.tgp_level;

		dst.pid = src.pid;
	}

	extern void TranslateTencentUserInfoStruct(const pwngs::STencentUserInfo& src,orm::DTencentUserInfo& dst)
	{
		dst.platform = src.platform;
		dst.platform_key = src.platform_key;
		dst.openid = src.openid;
		dst.openkey = src.openkey;

		dst.is_blue_vip = src.is_blue_vip;
		dst.is_blue_year_vip = src.is_blue_year_vip;
		dst.is_super_blue_vip = src.is_super_blue_vip;
		dst.blue_vip_level = src.blue_vip_level;

		dst.is_yellow_vip = src.is_yellow_vip;
		dst.is_yellow_year_vip = src.is_yellow_year_vip;
		dst.is_super_yellow_vip = src.is_super_yellow_vip;
		dst.yellow_vip_level = src.yellow_vip_level;

		dst.tgp_level = src.tgp_level;

		dst.pid = src.pid;

	}

	extern void TranslateTencentUserInfoStruct(const orm::DTencentUserInfo& src,MsgW(STencentUserInfo)* dst)
	{
		dst->set_platform(src.platform);

		dst->set_is_blue_vip(src.is_blue_vip);
		dst->set_is_blue_year_vip(src.is_blue_year_vip);
		dst->set_is_super_blue_vip(src.is_super_blue_vip);
		dst->set_blue_vip_level(src.blue_vip_level);

		dst->set_is_yellow_vip(src.is_yellow_vip);
		dst->set_is_yellow_year_vip(src.is_yellow_year_vip);
		dst->set_is_super_yellow_vip(src.is_super_yellow_vip);
		dst->set_yellow_vip_level(src.yellow_vip_level);

		dst->set_tgp_level(src.tgp_level);
	}

	extern void TranslateTencentUserInfoStruct( const orm::DTencentUserInfo& src,lua_State* L )
	{
		lua_newtable(L);

		pwlua::_detail::stack_helper<const char*>::push(L,src.platform.c_str());
		lua_setfield(L,-2,"platform");

		pwlua::_detail::stack_helper<bool>::push(L,src.is_blue_vip);
		lua_setfield(L,-2,"is_blue_vip");
		pwlua::_detail::stack_helper<bool>::push(L,src.is_blue_year_vip);
		lua_setfield(L,-2,"is_blue_year_vip");
		pwlua::_detail::stack_helper<bool>::push(L,src.is_super_blue_vip);
		lua_setfield(L,-2,"is_super_blue_vip");
		pwlua::_detail::stack_helper<int>::push(L,src.blue_vip_level);
		lua_setfield(L,-2,"blue_vip_level");

		pwlua::_detail::stack_helper<bool>::push(L,src.is_yellow_vip);
		lua_setfield(L,-2,"is_yellow_vip");
		pwlua::_detail::stack_helper<bool>::push(L,src.is_yellow_year_vip);
		lua_setfield(L,-2,"is_yellow_year_vip");
		pwlua::_detail::stack_helper<bool>::push(L,src.is_super_yellow_vip);
		lua_setfield(L,-2,"is_super_yellow_vip");
		pwlua::_detail::stack_helper<int>::push(L,src.yellow_vip_level);
		lua_setfield(L,-2,"yellow_vip_level");

		pwlua::_detail::stack_helper<int>::push(L,src.tgp_level);
		lua_setfield(L,-2,"tgp_level");
	}*/

	void TranslateTencentUserInfoStruct( const pwngs::STencentUserInfo& info,MsgW(STencentUserInfo)* msg )
	{
		if(info.valid())
		{
			msg->set_platform(info.platform);

			msg->set_is_blue_vip(info.is_blue_vip);
			msg->set_is_blue_year_vip(info.is_blue_year_vip);
			msg->set_is_super_blue_vip(info.is_super_blue_vip);
			msg->set_blue_vip_level(info.blue_vip_level);

			msg->set_is_yellow_vip(info.is_yellow_vip);
			msg->set_is_yellow_year_vip(info.is_yellow_year_vip);
			msg->set_is_super_yellow_vip(info.is_super_yellow_vip);
			msg->set_yellow_vip_level(info.yellow_vip_level);

			msg->set_tgp_level(info.tgp_level);
		}
	}

}