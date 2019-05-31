#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_reflection.h"
#include "kvorm/pw_orm_sub.h"
#include "kvorm/pw_orm_ts_gmland_queryinfo.h"
#include "kvorm/pw_orm_ts_gmland_setgs.h"
#include "kvorm/pw_orm_ts_gmland_setgm.h"
#include "kvorm/pw_orm_ts_gmland_lockchat.h"
#include "kvorm/pw_orm_ts_gmland_unlockchat.h"
#include "kvorm/pw_orm_ts_gmland_lockhuman.h"
#include "kvorm/pw_orm_ts_gmland_unlockhuman.h"
#include "kvorm/pw_orm_ts_gmland_sendgold.h"
#include "kvorm/pw_orm_systemconfigure.h"
#include "kvorm/pw_orm_systemmergeinfo.h"
#include "kvorm/pw_orm_passport.h"
#include "kvorm/pw_orm_passportitems.h"
#include "kvorm/pw_orm_passportloaditems.h"
#include "kvorm/pw_orm_passportgold.h"
#include "kvorm/pw_orm_passportvip.h"
#include "kvorm/pw_orm_passportmisc.h"
#include "kvorm/pw_orm_dpo_market.h"
#include "kvorm/pw_orm_dpo_charge.h"
#include "kvorm/pw_orm_passportoperation.h"
#include "kvorm/pw_orm_passportnull.h"
#include "kvorm/pw_orm_ghotfixcommand.h"
#include "kvorm/pw_orm_namedhuman.h"
#include "kvorm/pw_orm_human.h"
#include "kvorm/pw_orm_passporthuman.h"
#include "kvorm/pw_orm_globalwelfare.h"
#include "kvorm/pw_orm_globalcharge.h"
#include "kvorm/pw_orm_globaldailyinfolianyun.h"
#include "kvorm/pw_orm_mail.h"
#include "kvorm/pw_orm_notifyball.h"
#include "kvorm/pw_orm_shopitem.h"
#include "kvorm/pw_orm_mallitem.h"
#include "kvorm/pw_orm_relation.h"
#include "kvorm/pw_orm_chatmsg.h"

namespace orm
{

	const char* cst_slaves_of_Passport[] = {
		"passportgold",
		"passportvip",
		"passportmisc",
		NULL
	};
	int64 cst_slaves_hash_of_Passport[] = {
		5645524480354,
		5270530066723,
		5671307670626,
		0LL
	};
	const char* cst_slave_tables_of_Passport[] = {
		"passportitems",
		"passportloaditems",
		"passportnull",
		NULL
	};
	int64 cst_slave_tables_hash_of_Passport[] = {
		6177166419358,
		7962882353940,
		5735734633181,
		NULL
	};

	extern pwutils::KvormBase* createObject(const char* __data,size_t __size)
	{
		mongo::BSONObj __obj(__data);
		pwassertn(__obj.objsize() == __size);
		return createObject(__obj);
	}
	extern pwutils::KvormBase* createObject(bson::bo& __obj)
	{
		std::string metaname;
		mongo::BSONObjIterator iter(__obj);
		while(iter.more())
		{
			mongo::BSONElement __be = iter.next();
			if(pwutils::strcmp(__be.fieldName(),"_T") == 0)
			{
				metaname = __be.str();
				break;
			}
		}
		pwutils::KvormBase* result = NULL;
		int64 hash = pwutils::bkdr_hash_and_sum(metaname.c_str());
		switch(hash)
		{
		case orm::Sub::meta_hash:
			result = new orm::Sub();
			break;
		case orm::TS_Gmland_QueryInfo::meta_hash:
			result = new orm::TS_Gmland_QueryInfo();
			break;
		case orm::TS_Gmland_SetGS::meta_hash:
			result = new orm::TS_Gmland_SetGS();
			break;
		case orm::TS_Gmland_SetGM::meta_hash:
			result = new orm::TS_Gmland_SetGM();
			break;
		case orm::TS_Gmland_LockChat::meta_hash:
			result = new orm::TS_Gmland_LockChat();
			break;
		case orm::TS_Gmland_UnlockChat::meta_hash:
			result = new orm::TS_Gmland_UnlockChat();
			break;
		case orm::TS_Gmland_LockHuman::meta_hash:
			result = new orm::TS_Gmland_LockHuman();
			break;
		case orm::TS_Gmland_UnlockHuman::meta_hash:
			result = new orm::TS_Gmland_UnlockHuman();
			break;
		case orm::TS_Gmland_SendGold::meta_hash:
			result = new orm::TS_Gmland_SendGold();
			break;
		case orm::SystemConfigure::meta_hash:
			result = new orm::SystemConfigure();
			break;
		case orm::SystemMergeInfo::meta_hash:
			result = new orm::SystemMergeInfo();
			break;
		case orm::Passport::meta_hash:
			result = new orm::Passport();
			break;
		case orm::PassportItems::meta_hash:
			result = new orm::PassportItems();
			break;
		case orm::PassportLoadItems::meta_hash:
			result = new orm::PassportLoadItems();
			break;
		case orm::PassportGold::meta_hash:
			result = new orm::PassportGold();
			break;
		case orm::PassportVip::meta_hash:
			result = new orm::PassportVip();
			break;
		case orm::PassportMisc::meta_hash:
			result = new orm::PassportMisc();
			break;
		case orm::DPO_Market::meta_hash:
			result = new orm::DPO_Market();
			break;
		case orm::DPO_Charge::meta_hash:
			result = new orm::DPO_Charge();
			break;
		case orm::PassportOperation::meta_hash:
			result = new orm::PassportOperation();
			break;
		case orm::PassportNull::meta_hash:
			result = new orm::PassportNull();
			break;
		case orm::GHotfixCommand::meta_hash:
			result = new orm::GHotfixCommand();
			break;
		case orm::NamedHuman::meta_hash:
			result = new orm::NamedHuman();
			break;
		case orm::Human::meta_hash:
			result = new orm::Human();
			break;
		case orm::PassportHuman::meta_hash:
			result = new orm::PassportHuman();
			break;
		case orm::GlobalWelfare::meta_hash:
			result = new orm::GlobalWelfare();
			break;
		case orm::GlobalCharge::meta_hash:
			result = new orm::GlobalCharge();
			break;
		case orm::GlobalDailyInfoLianYun::meta_hash:
			result = new orm::GlobalDailyInfoLianYun();
			break;
		case orm::Mail::meta_hash:
			result = new orm::Mail();
			break;
		case orm::NotifyBall::meta_hash:
			result = new orm::NotifyBall();
			break;
		case orm::ShopItem::meta_hash:
			result = new orm::ShopItem();
			break;
		case orm::MallItem::meta_hash:
			result = new orm::MallItem();
			break;
		case orm::Relation::meta_hash:
			result = new orm::Relation();
			break;
		case orm::ChatMsg::meta_hash:
			result = new orm::ChatMsg();
			break;
		}
		if(result != NULL)
			result->from_bson(__obj);
		return result;
	}
}

