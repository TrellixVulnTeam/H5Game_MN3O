#include "pw_gdb_query.h"
#include "tokenizer.h"

namespace gdb
{
	namespace _detail
	{
		struct SValueConditionDef
		{
			const char* opname;
			unsigned	op;
			bool		single_value;
		};

		static SValueConditionDef g_valcond_defs[] = {
			{ "$eq",		ValueCondtion::OP_EQ,				true, },
			{ "$great",		ValueCondtion::OP_GREAT,			true, },
			{ "$ge",		ValueCondtion::OP_GREAT_EQUAL,		true, },
			{ "$less",		ValueCondtion::OP_LESS,				true, },
			{ "$le",		ValueCondtion::OP_LESS_EQUAL,		true, },
			{ "$ne",		ValueCondtion::OP_NOT_EQUAL,		true, },
			{ "$like",		ValueCondtion::OP_LIKE,				true, },
			{ "$contain",	ValueCondtion::OP_CONTAIN,			true, },
			{ "$exists",	ValueCondtion::OP_EXISTS,			true, },

			{ "$in",		ValueCondtion::OP_IN,				false, },
			{ "$element",	ValueCondtion::OP_ELEMENT,			false, },

			{ "$default",	ValueCondtion::OP_DEFAULT,			true, },

			{ NULL,			0,									false, },
		};

		// ********************************************************************************

		Condition::~Condition()
		{

		}

		// ********************************************************************************

		CompositeCondition::CompositeCondition(unsigned type)
			: m_nType(type)
		{		
		}

		CompositeCondition::~CompositeCondition()
		{
			for(size_t i = 0; i < m_vConds.size(); ++i)
				_safe_delete(m_vConds[i]);
			m_vConds.clear();
		}

		bool CompositeCondition::IsMatch( mongo::BSONObj bsonobj )
		{
			switch(m_nType)
			{
			case CompositeCondition::AND:
				{
					for(size_t i = 0; i < m_vConds.size(); ++i)
					{
						Condition* cond = m_vConds[i];
						if(!cond->IsMatch(bsonobj))
							return false;
						cond->GetMatchedDottedName(m_sLastMatchDottedField);
					}
					return true;
				}
				break;
			case CompositeCondition::OR:
				{
					for(size_t i = 0; i < m_vConds.size(); ++i)
					{
						Condition* cond = m_vConds[i];
						if(cond->IsMatch(bsonobj))
						{
							cond->GetMatchedDottedName(m_sLastMatchDottedField);
							return true;
						}
					}
					return false;
				}
				break;
			}
			return false;
		}

		void CompositeCondition::GetMatchedDottedName(std::string& name)
		{
			name = m_sLastMatchDottedField;
		}

		void CompositeCondition::AddChildCondition( Condition* cond )
		{
			m_vConds.push_back(cond);
		}

		// ********************************************************************************

		ValueConditionElement::ValueConditionElement()
			: m_pCond(NULL)
		{

		}

		ValueConditionElement::~ValueConditionElement()
		{
			_safe_delete(m_pCond);
		}

		bool ValueConditionElement::Parse( mongo::BSONElement be,std::string& error )
		{
			_safe_delete(m_pCond);
			m_pCond = Query::Parse(be.Obj(),error);
			if(m_pCond == NULL)
				return false;
			return true;
		}

		bool ValueConditionElement::IsMatch( ValueCondtion* defaultValue,mongo::BSONElement be )
		{
			if(!be.isABSONObj())
				return false;

			mongo::BSONObjIterator iter(be.Obj());
			while(iter.more())
			{
				mongo::BSONElement tmpbe = iter.next();
				if(!tmpbe.isABSONObj())
					continue;
				if(m_pCond->IsMatch(tmpbe.Obj()))
					return true;
			}
			return false;
		}

		// ********************************************************************************

		FieldCondition::FieldCondition(const char* key)
			: m_pDefaultValue(NULL)
		{
			::tokenize(key,m_sKeys,".");
		}

		FieldCondition::~FieldCondition()
		{
			for(size_t i = 0; i < m_vConds.size(); ++i)
				_safe_delete(m_vConds[i]);
			m_vConds.clear();
			_safe_delete(m_pDefaultValue);
		}

		bool FieldCondition::IsMatch(mongo::BSONObj bsonobj)
		{
			if(m_sKeys.size() == 0)
				return false;

			m_vFieldStack.clear();

			return _IsMatch(bsonobj,0);
		}

		void FieldCondition::GetMatchedDottedName(std::string& name)
		{
			name.clear();
			for(size_t i = 0; i < m_vFieldStack.size(); ++i)
			{
				name.append(m_vFieldStack[i]);
				if(i != (m_vFieldStack.size() - 1))
					name.append(".");
			}
		}

		bool FieldCondition::_IsMatch(mongo::BSONObj bsonobj,size_t index)
		{
			if(index == m_sKeys.size())
				return false;

			std::string& rfield = m_sKeys[index];

			if(rfield == "$")
			{
				mongo::BSONObjIterator iter(bsonobj);
				while(iter.more())
				{
					mongo::BSONElement be = iter.next();

					m_vFieldStack.push_back(be.fieldName());
					
					if(!be.isABSONObj())
						return (index == (m_sKeys.size()-1)) && _IsMatch(be);

					if(_IsMatch(be.Obj(),index + 1))
						return true;

					m_vFieldStack.pop_back();
				}
				return false;
			}

			m_vFieldStack.push_back(rfield.c_str());
			
			mongo::BSONElement be = bsonobj.getField(rfield);
			if(!be.isABSONObj())
			{
				bool result = (index == (m_sKeys.size()-1)) && _IsMatch(be);
				if( !result ) m_vFieldStack.pop_back();
				return result;
			}

			{
				bool result = _IsMatch(be.Obj(),index + 1);
				if( !result ) m_vFieldStack.pop_back();
				return result;
			}
		}

		bool FieldCondition::_IsMatch(mongo::BSONElement be)
		{
			for(size_t i = 0; i < m_vConds.size(); ++i)
			{
				ValueCondtion* cond = m_vConds[i];
				if(!cond->IsMatch(m_pDefaultValue,be))
					return false;
			}
			return true;
		}

		bool FieldCondition::Compile( mongo::BSONObj condobj,std::string& error )
		{
			mongo::BSONObjIterator iter(condobj);
			while(iter.more())
			{
				mongo::BSONElement be = iter.next();
				const char* operatorName = be.fieldName();

				if(operatorName[0] != '$')
				{
					error.append("keycondition body key must be $xxx,error=").append(operatorName);
					return false;
				}

				ValueCondtion* cond = this->Parse(operatorName,be,error);
				if(cond != NULL)
				{
					if(cond->GetOp() == ValueCondtion::OP_DEFAULT)
					{
						_safe_delete(m_pDefaultValue)
						m_pDefaultValue = cond;
					}
					else
					{
						m_vConds.push_back(cond);
					}
				}

				if(error.length() > 0)
					return false;
			}
			return true;
		}

		ValueCondtion* FieldCondition::Parse(const char* oper,mongo::BSONElement be,std::string& error)
		{
			for(size_t i = 0; i < _countof(g_valcond_defs); ++i)
			{
				SValueConditionDef& r = g_valcond_defs[i];

				if(r.opname == NULL)
					break;

				if(strcmp(oper,r.opname) == 0)
				{
					if(r.single_value && be.isABSONObj())
					{
						error.append("operator ").append(r.opname).append(" need a single value");
						return NULL;
					}

					if(r.op == ValueCondtion::OP_LIKE && be.type() != mongo::String)
					{
						error.append("operator ").append(r.opname).append(" need a string value");
						return NULL;
					}

					if(r.op == ValueCondtion::OP_IN && be.type() != mongo::Object)
					{
						error.append("operator ").append(r.opname).append(" need a array value");
						return NULL;
					}

					if(r.op == ValueCondtion::OP_ELEMENT && be.type() != mongo::Object)
					{
						error.append("operator ").append(r.opname).append(" need a object value");
						return NULL;
					}

					switch(be.type())
					{
					case mongo::NumberInt:
					case mongo::NumberLong:
						{
							if(r.single_value)
							{
								ValueConditionT<int64>* cond = new ValueConditionT<int64>();
								cond->SetOp(r.op);
								cond->SetCompareValue(be.numberLong());
								return cond;
							}
						}
						break;
					case mongo::NumberDouble:
						{
							if(r.single_value)
							{
								ValueConditionT<double>* cond = new ValueConditionT<double>();
								cond->SetOp(r.op);
								cond->SetCompareValue(be.numberDouble());
								return cond;
							}
						}
						break;
					case mongo::String:
						{
							if(r.single_value)
							{
								ValueConditionTString* cond = new ValueConditionTString();
								cond->SetOp(r.op);
								cond->SetCompareValue(be.String());
								return cond;
							}
						}
						break;
					case mongo::Bool:
						{
							if(r.single_value)
							{
								ValueConditionT<bool>* cond = new ValueConditionT<bool>();
								cond->SetOp(r.op);
								cond->SetCompareValue(be.boolean());
								return cond;
							}
						}
						break;
					case mongo::Array:
					case mongo::Object:
						{
							switch(r.op)
							{
							case ValueCondtion::OP_ELEMENT:
								{
									ValueConditionElement* cond = new ValueConditionElement();
									if(!cond->Parse(be,error))
									{
										_safe_delete(cond);
										return NULL;
									}
									return cond;
								}
								break;
							case ValueCondtion::OP_IN:
								{
									int type = be.Obj().firstElementType();
									switch(type)
									{
									case mongo::NumberInt:
									case mongo::NumberLong:
										{
											ValueConditionIN<int64> * cond = new ValueConditionIN<int64>();
											if(!cond->Parse(be,error))
											{
												_safe_delete(cond);
												return NULL;
											}
											return cond;
										}
										break;
									case mongo::String:
										{
											ValueConditionIN<std::string> * cond = new ValueConditionIN<std::string>();
											if(!cond->Parse(be,error))
											{
												_safe_delete(cond);
												return NULL;
											}
											return cond;
										}
										break;
									default:
										{
											error.append("$in array must be string | int");
											return NULL;
										}
										break;
									}								
								}
								break;
							}
						}
						break;
					default:
						{
							error.append("unexpect type in operator:").append(r.opname);
							return NULL;
						}
						break;
					}
				}
			}
			error.append("unexpect operator:").append(oper);
			return NULL;
		}
	}

	// ********************************************************************************
	// ********************************************************************************
	// ********************************************************************************

	bool Query::Compile( const char* data,size_t size,std::string& error )
	{
		try
		{
			mongo::BSONObj bsonobj(data);
			if(bsonobj.objsize() != size)
				mongo::massert(-1000,"not a valid bson object",false);
			return this->Compile(bsonobj,error);
		}
		catch(const bson::assertion& e)
		{
			error = e.what();
			return false;
		}
		return false;
	}

	bool Query::Compile( mongo::BSONObj bsonobj,std::string& error )
	{
		m_pRootCond = Parse(bsonobj,error);
		
		if(error.length() > 0)
		{
			_safe_delete(m_pRootCond);
			return false;
		}
		return true;
	}

	Query::Query()
		: m_pRootCond(NULL)
	{

	}

	Query::~Query()
	{
		_safe_delete(m_pRootCond);
	}

	_detail::Condition* Query::Parse( mongo::BSONObj bsonobj,std::string& error )
	{
		mongo::BSONElement be = bsonobj.firstElement();
		const char* fieldName = be.fieldName();

		// ¿Õ¶ÔÏó
		if(be.type() == mongo::EOO)
		{
			return new _detail::Condition();
		}

		if(!be.isABSONObj())
		{
			error.append("invalid composite struct,field:").append(fieldName).append(" not abson object");
			return NULL;
		}

		if(fieldName[0] == '$')
		{
			_detail::CompositeCondition* cond = NULL;

			if(strcmp(fieldName,"$or") == 0)
			{
				cond = new _detail::CompositeCondition(_detail::CompositeCondition::OR);
			}
			else if(strcmp(fieldName,"$and") == 0)
			{
				cond = new _detail::CompositeCondition(_detail::CompositeCondition::AND);				
			}
			else
			{
				error.append("invalid composite operator:").append(fieldName);
				return false;
			}

			mongo::BSONObjIterator iter(be.Obj());
			while(iter.more())
			{
				mongo::BSONElement tmpbe = iter.next();
				_detail::Condition* childCond = Parse(tmpbe.Obj(),error);
				if(childCond == NULL)
					break;
				cond->AddChildCondition(childCond);
			}
			return cond;
		}
		else
		{
			_detail::FieldCondition* cond = new _detail::FieldCondition(fieldName);
			cond->Compile(be.Obj(),error);
			return cond;
		}
		return NULL;
	}

	bool Query::IsMatch( mongo::BSONObj bsonobj )
	{
		if(m_pRootCond == NULL)
			return false;
		if(!m_pRootCond->IsMatch(bsonobj))
			return false;

		m_pRootCond->GetMatchedDottedName(m_sLastMatchDottedField);

#ifdef _DEBUG
		std::cout << __FUNCTION__ << " matched:" << m_sLastMatchDottedField << std::endl;
#endif
		return true;
	}

	void Query::GetMatchedDottedName( std::string& name )
	{
		name = m_sLastMatchDottedField;
	}

}