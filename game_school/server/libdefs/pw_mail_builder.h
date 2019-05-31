#ifndef _pw_mail_builder_
#define _pw_mail_builder_

#include "pw_def.h"
#include "pw_time.h"
#include "pw_utils.h"
#include "pw_mail_def.h"
#include "pw_rpc_proxy.h"
#include "pw_ngs_def.h"

namespace pwngs
{
	const sint32 cst_max_multi_mail_num = 1024; 

	class MultiMailBuilder : public std::vector<pwngs::SMail>
	{
	public:
		inline int Commit(pwdist::Port* port)
		{
			if(this->empty())
				return 0;

			pwassertf(port);
			pwngs::SMail tmpmails[cst_max_multi_mail_num];
			size_t tmpmailsnum = __min(this->size(),cst_max_multi_mail_num);
			
			for(size_t i = 0; i < tmpmailsnum; ++i)
			{
				tmpmails[i] = at(i);
			}

			pwngs::ctrlsrv::MailMgrProxy prx(port);
			prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_common,SIMPL_COMMON_MGR_TYPE_MAIL);
			prx._rpc_call_SendMultiMail(NULL,pwdist::Chunk(&tmpmails[0],sizeof(tmpmails[0])*tmpmailsnum));
			return 0;
		}
	};

	class MailBuilder
	{
	public:
		MailBuilder(int32 mode)
		{
			m_objMail.mode = mode;
			m_objMail.send_date = pwutils::time::clib_time();
		}
	public:
		inline void AddSubject(const_char_ptr fmt,...)
		{
			std::stringstream ss;

			va_list v;
			va_start(v,fmt);
			for(size_t i = 0; i < strlen(fmt); ++i)
			{
				switch(fmt[i])
				{
				case 'i':
					ss << va_arg(v,int32) << ",";
					break;
				case 'l':
					ss << va_arg(v,int64) << ",";
					break;
				case 's':
					ss << va_arg(v,const_char_ptr) << ",";
					break;
				default:
					pwasserte(false && "invalid param type");
				}
			}
			va_end(v);

			pwutils::strncat(m_objMail.subject,ss.str().c_str(),_countof(m_objMail.subject));
		}

		inline void AddContent(const_char_ptr fmt,...)
		{
			std::stringstream ss;

			va_list v;
			va_start(v,fmt);
			for(size_t i = 0; i < strlen(fmt); ++i)
			{
				switch(fmt[i])
				{
				case 'i':
					ss << va_arg(v,int32) << ",";
					break;
				case 'l':
					ss << va_arg(v,int64) << ",";
					break;
				case 's':
					ss << va_arg(v,const_char_ptr) << ",";
					break;
				default:
					pwasserte(false && "invalid param type");
				}
			}
			va_end(v);

			pwutils::strncat(m_objMail.content,ss.str().c_str(),_countof(m_objMail.content));
		}

		inline void AddItemContent(const CollectionPackItemsT* items = NULL)
		{
			std::stringstream ss;

			if(items)
			{
				for(size_t i = 0; i < items->size(); ++i)
				{
					ss << "|" << items->at(i).tid << "-" << items->at(i).count;
				}
				ss << "|" << ",";
			}
			else
			{
				for(size_t i = 0; i < m_vtPackItems.size(); ++i)
				{
					ss << "|" << m_vtPackItems[i].tid << "-" << m_vtPackItems[i].count;
				}
				ss << "|" << ",";
			}

			pwutils::strncat(m_objMail.content,ss.str().c_str(),_countof(m_objMail.content));
		}
	public:
		inline void AddMoney(int32 silver,int32 gold_gifts = 0,int32 gold = 0)
		{
			if(silver > 0)
				this->AddItem(ITEM_MISC_TYPE_ID_SILVER,silver);

			if(gold_gifts > 0)
				this->AddItem(ITEM_MISC_TYPE_ID_GOLD_GIFTS,gold_gifts);

			if(gold > 0)
				this->AddItem(ITEM_MISC_TYPE_ID_GOLD,gold);
		}

		inline void AddExp(int32 exp)
		{
			if(exp > 0)
				this->AddItem(ITEM_MISC_TYPE_ID_EXP,exp);
		}

		inline void AddVipExp(int32 vipexp)
		{
			if (vipexp > 0)
				this->AddItem(ITEM_MISC_TYPE_ID_VIP_EXP, vipexp);
		}

		inline void AddReputation(int32 reputation)
		{
			if(reputation > 0)
				this->AddItem(ITEM_MISC_TYPE_ID_REPUTATION,reputation);
		}

		inline void AddDragonic(int32 dragonic)
		{
			if(dragonic > 0)
				this->AddItem(ITEM_MISC_TYPE_ID_LILIAN, dragonic);
		}

		inline void AddAura(int32 aura)
		{
			if(aura > 0)
				this->AddItem(ITEM_MISC_TYPE_ID_AURA,aura);
		}

		inline void AddItem(int32 tid,int32 count = 1)
		{
			pwngs::SPackItem item = {tid,count};
			m_vtPackItems.push_back(item);
		}

		inline void AddItem(const pwngs::SPackItem& item)
		{
			m_vtPackItems.push_back(item);
		}

		//inline void AddItem(const pwngs::SItem& item)
		//{
		//	m_objMail.real_items[0] = item;
		//	//memcpy(&m_objMail.real_items[0],&item,sizeof(pwngs::SItem));
		//}

		inline void AddItems(const CollectionPackItemsT& vtItems)
		{
			if(!vtItems.empty())
				m_vtPackItems.insert(m_vtPackItems.end(),vtItems.begin(),vtItems.end());
		}

		inline void AppendData(const_char_ptr fmt,...)
		{
			va_list v;
			va_start(v,fmt);
			vsnprintf(m_objMail.append_data,sizeof(m_objMail.append_data),fmt,v);
			va_end(v);
		}
	public:
		inline void SetItemBinded()
		{
			m_objMail.item_binded = true;
		}
	public:
		inline int Send(pwdist::Port* port, int64 target)
		{
			pwassertf(port && target > 0);

			pwngs::SMail tmpmail;
			BuildStruct(tmpmail);

			tmpmail.receiver_id = target;

			pwngs::ctrlsrv::MailMgrProxy prx(port);
			prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_common,SIMPL_COMMON_MGR_TYPE_MAIL);
			prx._rpc_call_SendMail(NULL,pwdist::Chunk(&tmpmail,sizeof(tmpmail)));
			return 0;
		}

		static int Send(pwdist::Port* port, pwngs::SMail& mail, int64 target)
		{
			pwassertf(port && target > 0);
			mail.receiver_id = target;

			pwngs::ctrlsrv::MailMgrProxy prx(port);
			prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_common,SIMPL_COMMON_MGR_TYPE_MAIL);
			prx._rpc_call_SendMail(NULL,pwdist::Chunk(&mail,sizeof(mail)));
			return 0;
		}

		inline int Send(MultiMailBuilder* mmb, int64 target)
		{
			pwassertf(mmb && target > 0);

			pwngs::SMail tmpmail;
			BuildStruct(tmpmail);
			tmpmail.receiver_id = target;

			mmb->push_back(tmpmail);
			return 0;
		}

		static int Send(MultiMailBuilder* mmb, pwngs::SMail& mail, int64 target)
		{
			pwassertf(mmb && target > 0);
			
			mail.receiver_id = target;
			mmb->push_back(mail);
			return 0;
		}
	public:
		inline int BuildStruct(pwngs::SMail& mail)
		{
			mail = m_objMail;
			mail.receiver_id = 0;

			size_t maxcount = __min(cst_mail_item_max_num,_countof(mail.pack_items));
			for(size_t i = 0; i < m_vtPackItems.size(); ++i)
			{
				pwassertop(i < maxcount,break);

				const SPackItem& item = m_vtPackItems[i];
				pwassertop(item.tid > 0 && item.count > 0,continue);
				SPackItemToDPackItem(item,mail.pack_items[i]);
			}
			return 0;
		}
	private:
		pwngs::SMail m_objMail;
		CollectionPackItemsT m_vtPackItems;
	};
}

#endif // _pw_mail_builder_