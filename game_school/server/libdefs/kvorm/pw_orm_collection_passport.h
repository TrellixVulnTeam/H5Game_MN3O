#ifndef _pw_orm_collection_passport_
#define _pw_orm_collection_passport_

#include "kvdb/pw_kvorm.h"
#include "kvdb/pw_kvorm_array.h"

namespace orm
{

	class Passport;
	class PassportGold;
	class PassportMisc;
	class PassportVip;
	class PassportItems;
	class PassportLoadItems;
	class PassportNull;

	class PassportCollection : public pwutils::KvormCollectionString
	{
	public:
		PassportCollection();
		~PassportCollection();
	public:
		void load(const char* __buf,size_t __len);
		void load(std::string& compressedBuf);
		void save(std::string& compressedBuf,size_t builderInitSize = 1*1024*1024);
		void save(mongo::BSONObjBuilder& __builder);
	public:
		template<class VISITOR,class PARAM> void visit(VISITOR visitor,PARAM& param)
		{
			if(!visitor(m_pPassport,param))
				return ;
			if(!visitor(m_pPassportGold,param))
				return ;
			if(!visitor(m_pPassportMisc,param))
				return ;
			if(!visitor(m_pPassportVip,param))
				return ;

			for(pwutils::KvormObjectArray<PassportItems*>::iterator iter = m_vPassportItems.begin(); iter != m_vPassportItems.end(); ++iter)
			{
				if(!visitor(*iter,param))
					return;
			}
			for(pwutils::KvormObjectArray<PassportLoadItems*>::iterator iter = m_vPassportLoadItems.begin(); iter != m_vPassportLoadItems.end(); ++iter)
			{
				if(!visitor(*iter,param))
					return;
			}
			for(pwutils::KvormObjectArray<PassportNull*>::iterator iter = m_vPassportNull.begin(); iter != m_vPassportNull.end(); ++iter)
			{
				if(!visitor(*iter,param))
					return;
			}
		}
	public:
		Passport* passport() { return m_pPassport; }
		Passport* mutable_passport();
		void cleanup_passport();

		PassportGold* passportgold() { return m_pPassportGold; }
		PassportGold* mutable_passportgold();
		void cleanup_passportgold();

		PassportMisc* passportmisc() { return m_pPassportMisc; }
		PassportMisc* mutable_passportmisc();
		void cleanup_passportmisc();

		PassportVip* passportvip() { return m_pPassportVip; }
		PassportVip* mutable_passportvip();
		void cleanup_passportvip();

	public:
		inline pwutils::KvormObjectArray< PassportItems* >& passportitems() { return m_vPassportItems; }
		inline pwutils::KvormObjectArray< PassportLoadItems* >& passportloaditems() { return m_vPassportLoadItems; }
		inline pwutils::KvormObjectArray< PassportNull* >& passportnull() { return m_vPassportNull; }
	public:
		PassportItems* new_passportitems(bool manager = true);
		bool del_passportitems(PassportItems* value,bool freeIt = false);
		void load_passportitems(mongo::BSONObj& __obj);
		void save_passportitems(mongo::BSONArrayBuilder& __tmpbuilder);

		PassportLoadItems* new_passportloaditems(bool manager = true);
		bool del_passportloaditems(PassportLoadItems* value,bool freeIt = false);
		void load_passportloaditems(mongo::BSONObj& __obj);
		void save_passportloaditems(mongo::BSONArrayBuilder& __tmpbuilder);

		PassportNull* new_passportnull(bool manager = true);
		bool del_passportnull(PassportNull* value,bool freeIt = false);
		void load_passportnull(mongo::BSONObj& __obj);
		void save_passportnull(mongo::BSONArrayBuilder& __tmpbuilder);

	private:
		Passport* m_pPassport;
		PassportGold* m_pPassportGold;
		PassportMisc* m_pPassportMisc;
		PassportVip* m_pPassportVip;
	private:
		pwutils::KvormObjectArray<PassportItems* > m_vPassportItems;
		pwutils::KvormObjectArray<PassportLoadItems* > m_vPassportLoadItems;
		pwutils::KvormObjectArray<PassportNull* > m_vPassportNull;
	};
}

#endif // _pw_orm_collection_passport_
