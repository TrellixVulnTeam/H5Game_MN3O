#ifndef _pw_message_builder_notify_
#define _pw_message_builder_notify_

#include "pw_def.h"
#include "31000_31999_chat_mail.pb.h"

#include "pw_message_builder.h"
#include <sstream>
#include "pw_lua_ext.h"
#include "pw_logger.h"
#include "pw_utils.h"
#include "pw_luaseri.h"
#include "pw_chat_def.h"

namespace pwngs
{
	class NotifyMessageBuilder : public MessageBuilder
	{
	public:
		NotifyMessageBuilder(int32 strid,int32 mode = CHAT_MODE_SYSTEM,int32 textType = CHAT_TEXT_SYSTEM,bool isHref = false)
		{
			m_objMsg.set_text_id(strid);
			m_objMsg.set_text_type(textType);
			m_objMsg.set_mode(mode);
			m_objMsg.set_is_href(isHref);
		}
	public:
		void AddTextParamsFromValist(const_char_ptr fmt,va_list v)
		{
			std::vector<std::string> vtArgs;
			pwutils::valist_to_stringlist(fmt,v,vtArgs);

			for(size_t i = 0; i < vtArgs.size(); ++i)
				m_objMsg.add_text_args(vtArgs[i].c_str());
		}

		void AddTextParamsFromTable(pwlua::Table* table)
		{
			pwlua::UnpackHelper::Var vars[20] = {0};
			int count = table->ReadTo(vars,_countof(vars));
			for(int i = 0; i < count; ++i)
			{
				switch(vars[i].type)
				{
				case LUA_TNIL:
					break;
				case LUA_TBOOLEAN:
					break;
				case LUA_TNUMBER:
					{
						char buf[100] = "";
						pwutils::ftoa(buf,vars[i].f64);
						m_objMsg.add_text_args(buf);
					}
					break;
				case LUA_TSTRING:
					{
						m_objMsg.add_text_args(vars[i].str);
					}
					break;
				case pwlua::LUA_TINT64:
					{
						char buf[100] = "";
						pwutils::itoa(buf,vars[i].i64);
						m_objMsg.add_text_args(vars[i].str);
					}
					break;
				}
			}
		}

		template<class P> void AddTextParams(P v)
		{
			std::stringstream str;
			str << v;
			m_objMsg.add_text_args(str.str());
		}

		virtual int SerializeToArray(char* buf,size_t len)
		{
			int bytes = m_objMsg.ByteSize();
			assert(bytes <= (int)len);
			m_objMsg.SerializeToArray(buf,bytes);
			return bytes;
		}
	public:
		pwngs::protocol::worldsrv::SCNotify m_objMsg;
	};


}

#endif // _pw_message_builder_notify_