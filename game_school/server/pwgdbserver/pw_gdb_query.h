#ifndef _pw_gdb_query_
#define _pw_gdb_query_

#include <string>
#include "pw_types.h"
#include "bson/bson.h"
#include "kvdb/pw_bsontocpp.h"

namespace gdb
{
	namespace _detail
	{
		/*
		 @class Condition
		 @author cbh
		 @date 2014/7/8 10:55:19
		 @file pw_gdb_query.h
		 @brief 过滤条件基类
		*/
		class Condition
		{
		public:
			virtual ~Condition();
		public:
			virtual bool IsMatch(mongo::BSONObj bsonobj) { return true; }
			virtual void GetMatchedDottedName(std::string& name) {}
		};

		/*
		 @class CompositeCondition
		 @author cbh
		 @date 2014/7/8 10:55:30
		 @file pw_gdb_query.h
		 @brief 组合过滤条件(and/or)
		*/
		class CompositeCondition : public Condition
		{
		public:
			enum { AND,OR, };
		public:
			CompositeCondition(unsigned type);
			virtual ~CompositeCondition();
		public:
			virtual bool IsMatch(mongo::BSONObj bsonobj);
			virtual void GetMatchedDottedName(std::string& name);
			virtual void AddChildCondition(Condition* cond);
		public:
			typedef std::vector<Condition*> CollectionConditionsT;
		protected:
			unsigned m_nType;
			CollectionConditionsT m_vConds;
			std::string m_sLastMatchDottedField;
		};

		class FieldCondition;

		/*
		 @class ValueCondtion
		 @author cbh
		 @date 2014/7/8 10:55:47
		 @file pw_gdb_query.h
		 @brief 字段值子条件
		*/
		class ValueCondtion
		{
		public:
			enum
			{
				OP_EQ,
				OP_GREAT,
				OP_GREAT_EQUAL,
				OP_LESS,
				OP_LESS_EQUAL,
				OP_NOT_EQUAL,
				OP_LIKE,
				OP_CONTAIN,
				OP_EXISTS,

				OP_IN = 10,
				OP_ELEMENT,

				OP_DEFAULT = 200,
			};
		public:
			virtual ~ValueCondtion() {}
			virtual bool IsMatch(ValueCondtion* defaultValue,mongo::BSONElement be) = 0;
		public:
			inline unsigned GetOp()
			{
				return m_nOp;
			}

			inline void SetOp(unsigned op)
			{
				m_nOp = op;
			}
		protected:
			unsigned m_nOp;
		};

		/*
		 @class ValueConditionElement
		 @author cbh
		 @date 2014/7/8 10:56:01
		 @file pw_gdb_query.h
		 @brief 数组字段成员值过滤
		*/
		class ValueConditionElement : public ValueCondtion
		{
		public:
			ValueConditionElement();
			virtual ~ValueConditionElement();
		public:
			bool IsMatch(ValueCondtion* defaultValue,mongo::BSONElement be);		

			bool Parse(mongo::BSONElement be,std::string& error);
		public:
			Condition* m_pCond;
		};

		/*
		 @class ValueConditionT
		 @author cbh
		 @date 2014/7/8 10:56:21
		 @file pw_gdb_query.h
		 @brief 单值过滤条件类
		*/
		template<class T> class ValueConditionT : public ValueCondtion
		{
		public:
			void SetCompareValue(const T& v)
			{
				m_vCompareValue = v;
			}
		public:
			virtual bool IsMatch(ValueCondtion* defaultValue,mongo::BSONElement be)
			{
				switch(m_nOp)
				{
				case OP_EXISTS:
					{
						return !be.isNull() && be.type() != mongo::EOO;
					}
					break;
				case OP_CONTAIN:
					{
						if(!be.isABSONObj())
							return false;
						mongo::BSONObj obj = be.Obj();
						mongo::BSONObjIterator iter(obj);
						while(iter.more())
						{
							mongo::BSONElement tmpbe = iter.next();
							T tmp;
							if(!pwutils::bsonToCppVariable(tmp,tmpbe))
								continue;

							if(tmp == m_vCompareValue)
								return true;
						}
						return false;
					}
					break;
				};
		
				T tmp;

				if(!be.isNull() && be.type() != mongo::EOO)
				{
					if(!pwutils::bsonToCppVariable(tmp,be))
						return false;
				}
				else if(defaultValue != NULL)
					tmp = static_cast<ValueConditionT<T>*>(defaultValue)->m_vCompareValue;
				else
					return false;

				switch(m_nOp)
				{
				case OP_EQ:
					return tmp == m_vCompareValue;
				case OP_GREAT:
					return tmp >  m_vCompareValue;
				case OP_GREAT_EQUAL:
					return tmp >= m_vCompareValue;
				case OP_LESS:
					return tmp <  m_vCompareValue;
				case OP_LESS_EQUAL:
					return tmp <= m_vCompareValue;
				case OP_NOT_EQUAL:
					return tmp != m_vCompareValue;
				case OP_LIKE:
					return IsLike(tmp);
				}
				return false;
			}
		public:
			virtual bool IsLike(const T& tmp)
			{
				return false;
			}
		protected:
			T m_vCompareValue;
		};

		/*
		 @class ValueConditionIN
		 @author cbh
		 @date 2014/7/8 10:56:34
		 @file pw_gdb_query.h
		 @brief 单值过滤条件,值是否在指定数组内
		*/
		template<class T> class ValueConditionIN : public ValueCondtion
		{
		public:
			virtual bool IsMatch(ValueCondtion* defaultValue,mongo::BSONElement be)
			{
				if(be.isABSONObj())
					return false;

				T tmp;
				if(!pwutils::bsonToCppVariable(tmp,be))
					return false;
				
				return std::lower_bound(m_vCompareValues.begin(),m_vCompareValues.end(),tmp) != m_vCompareValues.end();
			}

			bool Parse(mongo::BSONElement& be,std::string& error)
			{
				if(be.type() != mongo::Object)
				{
					error.append("$in need a array value");
					return false;
				}

				mongo::BSONObjIterator iter(be.Obj());
				while(iter.more())
				{
					mongo::BSONElement tmpbe = iter.next();
					
					T tmp;
					if(!pwutils::bsonToCppVariable(tmp,tmpbe))
						continue;

					m_vCompareValues.push_back(tmp);
				}

				std::sort(m_vCompareValues.begin(),m_vCompareValues.end());

				return true;
			}
		protected:
			std::vector<T> m_vCompareValues;
		};

		/*
		 @class ValueConditionTString
		 @author cbh
		 @date 2014/7/8 10:56:55
		 @file pw_gdb_query.h
		 @brief 单值过滤,字符串过滤Like特殊处理
		*/
		class ValueConditionTString : public ValueConditionT<std::string>
		{
		public:
			virtual bool IsLike(const std::string& tmp)
			{
				return tmp.find(m_vCompareValue) != std::string::npos;
			}
		};

		/*
		 @class FieldCondtion
		 @author cbh
		 @date 2014/7/8 10:57:14
		 @file pw_gdb_query.h
		 @brief 字段过滤条件
		*/
		class FieldCondition : public Condition
		{
		public:
			FieldCondition(const char* key);
			virtual ~FieldCondition();
		public:
			virtual bool IsMatch(mongo::BSONObj bsonobj);
			virtual void GetMatchedDottedName(std::string& name);
			virtual bool Compile(mongo::BSONObj condobj,std::string& error);
		public:
			bool _IsMatch(mongo::BSONObj bsonobj,size_t index);
			bool _IsMatch(mongo::BSONElement be);
		public:
			static ValueCondtion* Parse(const char* oper,mongo::BSONElement be,std::string& error);
		protected:
			typedef std::vector<ValueCondtion*> CollectionConditionsT;
		protected:
			std::vector<std::string> m_sKeys;
			std::vector<const char*> m_vFieldStack;
			CollectionConditionsT m_vConds;
			ValueCondtion* m_pDefaultValue;
		};
	}

	/*
	 @class Query
	 @author cbh
	 @date 2014/7/8 10:57:23
	 @file pw_gdb_query.h
	 @brief 查询类
	*/
	class Query
	{
	public:
		Query();
		virtual ~Query();
	public:
		bool Compile(const char* data,size_t size,std::string& error);
		bool Compile(mongo::BSONObj bsonobj,std::string& error);
	public:
		bool IsMatch(mongo::BSONObj bsonobj);
		void GetMatchedDottedName(std::string& name);
	public:
		static _detail::Condition* Parse(mongo::BSONObj bsonobj,std::string& error);
	protected:
		_detail::Condition* m_pRootCond;
		std::string m_sLastMatchDottedField;
	};
}

#endif // _pw_gdb_query_