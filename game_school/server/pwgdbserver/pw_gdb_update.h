#ifndef _pw_gdb_update_
#define _pw_gdb_update_

#include <string>
#include <vector>
#include "pw_types.h"
#include "bson/bson.h"
#include "bson/mutable/document.h"
#include "kvdb/pw_bsontocpp.h"
#include "pw_gdb_operation_def.h"
#include "tokenizer.h"

namespace gdb
{
	namespace _detail
	{
		/*
		 @class Modifier
		 @author cbh
		 @date 2014/7/21 19:49:55
		 @file pw_gdb_update.h
		 @brief 修改器基类
		*/
		class BaseModifier
		{
		public:
			enum
			{
				OP_SET,
				OP_UNSET,
				OP_INC,
			};

			enum EResult
			{
				RESULT_NONE,
				RESULT_CHANGED,
			};
		public:
			BaseModifier(unsigned op);
			virtual ~BaseModifier();
		public:
			static mongo::mutablebson::Element findElementByDottedPath(mongo::mutablebson::Element& parent,const std::vector<std::string>& path,size_t size);
			static BaseModifier* Parse(mongo::BSONObj obj,std::string& error);
		public:
			virtual EResult Handle(mongo::mutablebson::Element& doc) { return RESULT_NONE; }
		protected:
			unsigned m_nOp;
			std::vector<std::string> m_vFieldPath;

		};

		template<class T> struct BSONTraits
		{

		};

		template<> struct BSONTraits<bool>
		{
			static void exec(mongo::mutablebson::Element elem,bool v)
			{
				elem.setValueBool(v);
			}

			static void inc(mongo::mutablebson::Element elem,bool v)
			{
				elem.setValueBool(elem.getValueBool() + v);
			}

			static void append(mongo::mutablebson::Element elem,const std::string& name,bool v)
			{
				elem.appendBool(name,v);
			}
		};

		template<> struct BSONTraits<int32>
		{
			static void exec(mongo::mutablebson::Element elem,int32 v)
			{
				elem.setValueSafeNum(v);
			}

			static void inc(mongo::mutablebson::Element elem,int32 v)
			{
				elem.setValueSafeNum(elem.getValueSafeNum() + v);
			}

			static void append(mongo::mutablebson::Element elem,const std::string& name,int32 v)
			{
				elem.appendInt(name,v);
			}
		};

		template<> struct BSONTraits<int64>
		{
			static void exec(mongo::mutablebson::Element elem,int64 v)
			{
				elem.setValueSafeNum(v);
			}

			static void inc(mongo::mutablebson::Element elem,int64 v)
			{
				elem.setValueSafeNum(elem.getValueSafeNum() + v);
			}

			static void append(mongo::mutablebson::Element elem,const std::string& name,int64 v)
			{
				elem.appendLong(name,v);
			}
		};

		template<> struct BSONTraits<double>
		{
			static void exec(mongo::mutablebson::Element elem,double v)
			{
				elem.setValueSafeNum(v);
			}

			static void inc(mongo::mutablebson::Element elem,double v)
			{
				elem.setValueSafeNum(elem.getValueSafeNum() + v);
			}

			static void append(mongo::mutablebson::Element elem,const std::string& name,double v)
			{
				elem.appendDouble(name,v);
			}
		};

		template<> struct BSONTraits<std::string>
		{
			static void exec(mongo::mutablebson::Element elem,const std::string& v)
			{
				elem.setValueString(v);
			}

			static void inc(mongo::mutablebson::Element elem,const std::string& v)
			{
				elem.setValueString(elem.getValueString().toString() + v);
			}

			static void append(mongo::mutablebson::Element elem,const std::string& name,const std::string& v)
			{
				elem.appendString(name,v);
			}
		};

		/*
		 @class ModifierT
		 @author cbh
		 @date 2014/7/21 19:50:11
		 @file pw_gdb_update.h
		 @brief 单值修改器
		*/
		template<class T> class ModifierT : public BaseModifier
		{
		public:
			bool Parse(mongo::BSONObj& obj,std::string& error)
			{
				mongo::BSONElement be = obj.firstElement();
				::tokenize(be.fieldName(),m_vFieldPath,".");

				if(!pwutils::bsonToCppVariable(m_vOpValue,be))
				{
					error.append("bsontocpp failed:").append(be.fieldName());
					return false;
				}
				return true;
			}
		public:
			ModifierT(unsigned op) : BaseModifier(op) {}
		public:
			virtual EResult Handle(mongo::mutablebson::Element& doc)
			{
				mongo::mutablebson::Element parent = doc;
				mongo::mutablebson::Element elem = BaseModifier::findElementByDottedPath(parent,m_vFieldPath,m_vFieldPath.size());

				switch(m_nOp)
				{
				case OP_SET:
					{
						if(elem.ok())
						{
							BSONTraits<T>::exec(elem,m_vOpValue);
							return RESULT_CHANGED;
						}
						else
						{
							elem = BaseModifier::findElementByDottedPath(parent,m_vFieldPath,m_vFieldPath.size()-1);
							if(elem.ok())
							{
								BSONTraits<T>::append(elem,m_vFieldPath.back(),m_vOpValue);
								return RESULT_CHANGED;
							}
						}
					}
					break;
				case OP_INC:
					{
						if(elem.ok())
						{
							BSONTraits<T>::inc(elem,m_vOpValue);
							return RESULT_CHANGED;
						}
						else
						{
							elem = BaseModifier::findElementByDottedPath(parent,m_vFieldPath,m_vFieldPath.size()-1);
							if(elem.ok())
							{
								BSONTraits<T>::append(elem,m_vFieldPath.back(),m_vOpValue);
								return RESULT_CHANGED;
							}
						}
					}
					break;
				}
				return RESULT_NONE;
			}		
		protected:
			T m_vOpValue;
		};

		/*
		 @class ModifierUnset
		 @author cbh
		 @date 2014/7/21 19:50:20
		 @file pw_gdb_update.h
		 @brief 清除修改器
		*/
		class UnsetModifier : public BaseModifier
		{
		public:
			UnsetModifier(unsigned op) : BaseModifier(op) {}
		public:
			void Parse(const char* field);
		public:
			virtual EResult Handle(mongo::mutablebson::Element& doc);
		};


		class BsonModifier : public BaseModifier
		{
		public:
			BsonModifier(unsigned op);
			virtual ~BsonModifier();
		public:
			bool Parse(mongo::BSONObj obj,std::string& error);
		public:
			virtual EResult Handle(mongo::mutablebson::Element& doc);
		protected:
			mongo::BSONObj m_vKeepParams;
			mongo::BSONElement m_vOpValue;
		protected:
			char*  m_pKeepParams;
			size_t m_cKeepParams;
		};
	}

	class Database;

	/*
	 @class Update
	 @author cbh
	 @date 2014/7/21 19:49:40
	 @file pw_gdb_update.h
	 @brief 更新器
	*/
	class Modifier
	{
	public:
		~Modifier();
	public:
		typedef std::vector<_detail::BaseModifier*> CollectionModifiersT;
	public:
		bool Handle(Database* db,const gdb::Slice& name,const gdb::Slice& key,mongo::BSONObj& oldobj);
	public:
		bool Compile(const char* data,size_t size,std::string& error);
		bool Compile(mongo::BSONObj bsonobj,std::string& error);
	protected:
		CollectionModifiersT m_vModifiers;
	};
}

#endif // _pw_gdb_update_