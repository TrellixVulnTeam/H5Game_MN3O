#include "kvorm/pw_orm_collection_passport.h"
#include "pw_logger.h"
#include "pw_utils.h"
#include "snappy/snappy.h"

#include "kvorm/pw_orm_passport.h"
#include "kvorm/pw_orm_passportgold.h"
#include "kvorm/pw_orm_passportmisc.h"
#include "kvorm/pw_orm_passportvip.h"
#include "kvorm/pw_orm_passportitems.h"
#include "kvorm/pw_orm_passportloaditems.h"
#include "kvorm/pw_orm_passportnull.h"

namespace orm
{

	void PassportCollection::load(std::string& compressedBuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(compressedBuf.c_str(),compressedBuf.length(),&tmpbuf);
		this->load(tmpbuf.c_str(),tmpbuf.length());
	}

	void PassportCollection::load(const char* __buf,size_t __len)
	{
		mongo::BSONObj __obj(__buf);
		pwassert(__obj.objsize() == __len);

		mongo::BSONObjIterator iter(__obj);
		while(iter.more())
		{
			mongo::BSONElement __be = iter.next();
			pwassertop(__be.isABSONObj(),continue);
			mongo::BSONObj __tmpobj = __be.Obj();
			int64 hash = pwutils::bkdr_hash_and_sum(__be.fieldName());
			switch(hash)
			{
			case 3831688010902: // Passport
				{
					mutable_passport()->from_bson(__tmpobj);
				}
				break;
			case 5645524480354: // PassportGold
				{
					mutable_passportgold()->from_bson(__tmpobj);
				}
				break;
			case 5671307670626: // PassportMisc
				{
					mutable_passportmisc()->from_bson(__tmpobj);
				}
				break;
			case 5270530066723: // PassportVip
				{
					mutable_passportvip()->from_bson(__tmpobj);
				}
				break;
			case 6177166419358: // PassportItems
				{
					load_passportitems(__tmpobj);
				}
				break;
			case 7962882353940: // PassportLoadItems
				{
					load_passportloaditems(__tmpobj);
				}
				break;
			case 5735734633181: // PassportNull
				{
					load_passportnull(__tmpobj);
				}
				break;
			default:
				{
					pwasserte(false && "invalid metahash");
				}
				break;
			}
		}
	}

	void PassportCollection::save(std::string& compressedBuf,size_t builderInitSize)
	{
		mongo::BSONObjBuilder __builder(builderInitSize);
		save(__builder);
		mongo::BSONObj __tmpobj = __builder.obj();
		snappy::Compress(__tmpobj.objdata(),__tmpobj.objsize(),&compressedBuf);
	}

	void PassportCollection::save(mongo::BSONObjBuilder& __builder)
	{
		if(m_pPassport != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pPassport->to_bson(__tmpobj);
			__builder.append(Passport::meta(),__tmpobj);
		}

		if(m_pPassportGold != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pPassportGold->to_bson(__tmpobj);
			__builder.append(PassportGold::meta(),__tmpobj);
		}

		if(m_pPassportMisc != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pPassportMisc->to_bson(__tmpobj);
			__builder.append(PassportMisc::meta(),__tmpobj);
		}

		if(m_pPassportVip != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pPassportVip->to_bson(__tmpobj);
			__builder.append(PassportVip::meta(),__tmpobj);
		}

		{
			mongo::BSONArrayBuilder __tmpbuilder;
			this->save_passportitems(__tmpbuilder);
			__builder.append(PassportItems::meta(),__tmpbuilder.obj());
		}

		{
			mongo::BSONArrayBuilder __tmpbuilder;
			this->save_passportloaditems(__tmpbuilder);
			__builder.append(PassportLoadItems::meta(),__tmpbuilder.obj());
		}

		{
			mongo::BSONArrayBuilder __tmpbuilder;
			this->save_passportnull(__tmpbuilder);
			__builder.append(PassportNull::meta(),__tmpbuilder.obj());
		}

	}

	PassportCollection::PassportCollection()
	{
		m_pPassport = NULL;
		m_pPassportGold = NULL;
		m_pPassportMisc = NULL;
		m_pPassportVip = NULL;
	}

	PassportCollection::~PassportCollection()
	{
		_safe_delete(m_pPassport);
		_safe_delete(m_pPassportGold);
		_safe_delete(m_pPassportMisc);
		_safe_delete(m_pPassportVip);
	}

	Passport* PassportCollection::mutable_passport()
	{
		if(m_pPassport == NULL)
		{
			m_pPassport = new Passport();
			m_pPassport->set_masterid(m_vMasterId.c_str());
		}
		return m_pPassport;
	}

	PassportGold* PassportCollection::mutable_passportgold()
	{
		if(m_pPassportGold == NULL)
		{
			m_pPassportGold = new PassportGold();
			m_pPassportGold->set_masterid(m_vMasterId.c_str());
		}
		return m_pPassportGold;
	}

	PassportMisc* PassportCollection::mutable_passportmisc()
	{
		if(m_pPassportMisc == NULL)
		{
			m_pPassportMisc = new PassportMisc();
			m_pPassportMisc->set_masterid(m_vMasterId.c_str());
		}
		return m_pPassportMisc;
	}

	PassportVip* PassportCollection::mutable_passportvip()
	{
		if(m_pPassportVip == NULL)
		{
			m_pPassportVip = new PassportVip();
			m_pPassportVip->set_masterid(m_vMasterId.c_str());
		}
		return m_pPassportVip;
	}

	void PassportCollection::cleanup_passport()
	{
		_safe_delete(m_pPassport);
	}

	void PassportCollection::cleanup_passportgold()
	{
		_safe_delete(m_pPassportGold);
	}

	void PassportCollection::cleanup_passportmisc()
	{
		_safe_delete(m_pPassportMisc);
	}

	void PassportCollection::cleanup_passportvip()
	{
		_safe_delete(m_pPassportVip);
	}

	PassportItems* PassportCollection::new_passportitems(bool manager)
	{
		PassportItems* tmp = new PassportItems();
		tmp->set_masterid(m_vMasterId.c_str());
		if(manager)
			m_vPassportItems.push_back(tmp);
		return tmp;
	}

	bool PassportCollection::del_passportitems(PassportItems* value,bool freeIt)
	{
		return m_vPassportItems.remove(value,freeIt);
	}

	void PassportCollection::load_passportitems(mongo::BSONObj& __obj)
	{
		m_vPassportItems.cleanup();
		mongo::BSONObjIterator iter(__obj);
		while(iter.more())
		{
			mongo::BSONElement __be = iter.next();
			pwassertop(__be.isABSONObj(),continue);
			PassportItems* tmp = new_passportitems(true);
			tmp->from_bson(__be.Obj());
		}
	}

	void PassportCollection::save_passportitems(mongo::BSONArrayBuilder& __tmpbuilder)
	{
		for(size_t i = 0; i < m_vPassportItems.size(); ++i)
		{
			mongo::BSONObj __tmpobj;
			PassportItems* tmp = m_vPassportItems[i];
			tmp->to_bson(__tmpobj);
			__tmpbuilder.append(__tmpobj);
		}
	}

	PassportLoadItems* PassportCollection::new_passportloaditems(bool manager)
	{
		PassportLoadItems* tmp = new PassportLoadItems();
		tmp->set_masterid(m_vMasterId.c_str());
		if(manager)
			m_vPassportLoadItems.push_back(tmp);
		return tmp;
	}

	bool PassportCollection::del_passportloaditems(PassportLoadItems* value,bool freeIt)
	{
		return m_vPassportLoadItems.remove(value,freeIt);
	}

	void PassportCollection::load_passportloaditems(mongo::BSONObj& __obj)
	{
		m_vPassportLoadItems.cleanup();
		mongo::BSONObjIterator iter(__obj);
		while(iter.more())
		{
			mongo::BSONElement __be = iter.next();
			pwassertop(__be.isABSONObj(),continue);
			PassportLoadItems* tmp = new_passportloaditems(true);
			tmp->from_bson(__be.Obj());
		}
	}

	void PassportCollection::save_passportloaditems(mongo::BSONArrayBuilder& __tmpbuilder)
	{
		for(size_t i = 0; i < m_vPassportLoadItems.size(); ++i)
		{
			mongo::BSONObj __tmpobj;
			PassportLoadItems* tmp = m_vPassportLoadItems[i];
			tmp->to_bson(__tmpobj);
			__tmpbuilder.append(__tmpobj);
		}
	}

	PassportNull* PassportCollection::new_passportnull(bool manager)
	{
		PassportNull* tmp = new PassportNull();
		tmp->set_masterid(m_vMasterId.c_str());
		if(manager)
			m_vPassportNull.push_back(tmp);
		return tmp;
	}

	bool PassportCollection::del_passportnull(PassportNull* value,bool freeIt)
	{
		return m_vPassportNull.remove(value,freeIt);
	}

	void PassportCollection::load_passportnull(mongo::BSONObj& __obj)
	{
		m_vPassportNull.cleanup();
		mongo::BSONObjIterator iter(__obj);
		while(iter.more())
		{
			mongo::BSONElement __be = iter.next();
			pwassertop(__be.isABSONObj(),continue);
			PassportNull* tmp = new_passportnull(true);
			tmp->from_bson(__be.Obj());
		}
	}

	void PassportCollection::save_passportnull(mongo::BSONArrayBuilder& __tmpbuilder)
	{
		for(size_t i = 0; i < m_vPassportNull.size(); ++i)
		{
			mongo::BSONObj __tmpobj;
			PassportNull* tmp = m_vPassportNull[i];
			tmp->to_bson(__tmpobj);
			__tmpbuilder.append(__tmpobj);
		}
	}

}
