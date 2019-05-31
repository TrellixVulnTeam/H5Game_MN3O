#include "pw_gdb_update.h"
#include "pw_gdb_database.h"
#include "pw_gdb_operation_hashtable.h"
#include "bson/bson-inl.h"
#include "pw_logger.h"

namespace gdb
{
	namespace _detail
	{
		struct SUpdateDef
		{
			const char* opname;
			unsigned	op;
		};

		static SUpdateDef g_update_defs[] = {
			{ "$set",		BaseModifier::OP_SET,		},
			{ "$unset",		BaseModifier::OP_UNSET,		},
			{ "$inc",		BaseModifier::OP_INC,		},
			{ NULL,			0,},
		};

		BaseModifier* BaseModifier::Parse( mongo::BSONObj obj,std::string& error )
		{
			mongo::BSONElement _op = obj.firstElement();

			const char* opstr = _op.fieldName();
			SUpdateDef* opdef = NULL;
			
			for(size_t i = 0; i < _countof(g_update_defs); ++i)
			{
				SUpdateDef* tmp = &g_update_defs[i];
				if(tmp->opname == NULL)
					break;

				if(strcmp(tmp->opname,opstr) == 0)
				{
					opdef = tmp;
					break;
				}
			}

			if(opdef == NULL)
			{
				error.append("invalid op:").append(opstr);
				return NULL;
			}

			switch(opdef->op)
			{
			case BaseModifier::OP_UNSET:
				{
					if(_op.isABSONObj())
					{
						error = error.append("invalid params,op:").append(opstr);
						return NULL;
					}
					UnsetModifier* m = new UnsetModifier(opdef->op);
					m->Parse(_op.valuestrsafe());
					return m;
				}
				break;
			default:
				{
					if(!_op.isABSONObj())
					{
						error = error.append("invalid params,op:").append(opstr);
						return NULL;
					}

					mongo::BSONObj opbson = _op.Obj();
					switch(opbson.firstElementType())
					{
					case mongo::NumberInt:
					case mongo::NumberLong:
						{
							ModifierT<int64>* m = new ModifierT<int64>(opdef->op);
							if(!m->Parse(opbson,error))
							{
								delete m;
								return NULL;
							}
							return m;
						}
						break;
					case mongo::String:
						{
							ModifierT<std::string>* m = new ModifierT<std::string>(opdef->op);
							if(!m->Parse(opbson,error))
							{
								delete m;
								return NULL;
							}
							return m;
						}
						break;
					case mongo::Bool:
						{
							ModifierT<bool>* m = new ModifierT<bool>(opdef->op);
							if(!m->Parse(opbson,error))
							{
								delete m;
								return NULL;
							}
							return m;
						}
						break;
					case mongo::NumberDouble:
						{
							ModifierT<double>* m = new ModifierT<double>(opdef->op);
							if(!m->Parse(opbson,error))
							{
								delete m;
								return NULL;
							}
							return m;
						}
						break;
					case mongo::Array:
					case mongo::Object:
						{
							if(opdef->op != BaseModifier::OP_SET)
							{
								error = error.append("only $set can use object/array params:").append(opstr);
								return NULL;
							}

							BsonModifier* m = new BsonModifier(opdef->op);
							if(!m->Parse(opbson,error))
							{
								delete m;
								return NULL;
							}
							return m;
						}
						break;
					default:
						{
							error.append("params nosupport,op:").append(opdef->opname);
							return NULL;
						}
						break;
					}
				}
				break;
			}
			return NULL;
		}

		BaseModifier::BaseModifier( unsigned op )
			: m_nOp(op)
		{

		}

		BaseModifier::~BaseModifier()
		{

		}

		mongo::mutablebson::Element BaseModifier::findElementByDottedPath( mongo::mutablebson::Element& parent,const std::vector<std::string>& path,size_t size )
		{
			mongo::mutablebson::Element root = parent;
			for(size_t i = 0; i < size; ++i)
			{
				mongo::mutablebson::Element child = root.findFirstChildNamed(path[i]);
				root = child;

				if(!child.ok())
					break;
			}
			return root;
		}

		void UnsetModifier::Parse( const char* field )
		{
			::tokenize(field,m_vFieldPath,".");
		}

		BaseModifier::EResult UnsetModifier::Handle(mongo::mutablebson::Element& doc)
		{
			mongo::mutablebson::Element parent = doc;
			mongo::mutablebson::Element elem = BaseModifier::findElementByDottedPath(parent,m_vFieldPath,m_vFieldPath.size());

			if(elem.ok())
			{
				elem.remove();
				return RESULT_CHANGED;
			}
			return RESULT_NONE;
		}		

		bool BsonModifier::Parse( mongo::BSONObj obj,std::string& error )
		{
			::tokenize(obj.firstElement().fieldName(),m_vFieldPath,".");

			m_cKeepParams = obj.objsize();
			m_pKeepParams = new char[m_cKeepParams];
			memcpy(m_pKeepParams,obj.objdata(),m_cKeepParams);

			m_vKeepParams = mongo::BSONObj(m_pKeepParams);
			m_vOpValue = m_vKeepParams.firstElement();

			return true;
		}

		BsonModifier::BsonModifier( unsigned op )
			: BaseModifier(op)
			, m_pKeepParams(0)
			, m_cKeepParams(0)
		{

		}

		BsonModifier::~BsonModifier()
		{
			delete [] m_pKeepParams;
		}

		BaseModifier::EResult BsonModifier::Handle( mongo::mutablebson::Element& doc )
		{

			mongo::mutablebson::Element parent = doc;
			mongo::mutablebson::Element elem = BaseModifier::findElementByDottedPath(parent,m_vFieldPath,m_vFieldPath.size());

			switch(m_nOp)
			{
			case OP_SET:
				{
					if(elem.ok())
					{
						switch(m_vOpValue.type())
						{
						case mongo::Array:
							elem.setValueArray(m_vOpValue.Obj());
							break;
						case mongo::Object:
							elem.setValueObject(m_vOpValue.Obj());
							break;
						default:
							return RESULT_NONE;
						}
						return RESULT_CHANGED;
					}
					else
					{
						elem = BaseModifier::findElementByDottedPath(parent,m_vFieldPath,m_vFieldPath.size()-1);
						if(elem.ok())
						{
							switch(m_vOpValue.type())
							{
							case mongo::Array:
								elem.appendArray(m_vFieldPath.back(),m_vOpValue.Obj());
								break;
							case mongo::Object:
								elem.appendObject(m_vFieldPath.back(),m_vOpValue.Obj());
								break;
							default:
								return RESULT_NONE;
							}
							return RESULT_CHANGED;
						}
					}
				}
				break;
			}
			return RESULT_NONE;
		}

	}

	bool Modifier::Handle( Database* db,const gdb::Slice& name,const gdb::Slice& key,mongo::BSONObj& oldobj )
	{
		bool changed = false;
		size_t size = m_vModifiers.size();
		
		if(size == 0)
			return false;

		mongo::mutablebson::Document doc(oldobj);
		mongo::mutablebson::Element root = doc.root();

		for(size_t i = 0; i < size; ++i)
		{
			_detail::BaseModifier::EResult r = m_vModifiers[i]->Handle(root);
			if( r == _detail::BaseModifier::RESULT_CHANGED)
			{
				changed = true;
			}
			else if(changed)
			{
				// error,has failed;
				changed = false;
				gErrorStream(__FUNCTION__ << " name=" << std::string(name.data(),name.size()) << " key=" << std::string(key.data(),key.size()));
				break;
			}
		}

		if(changed)
		{
			mongo::BSONObj newobj = doc.getObject();

			gdb::OperationEnvironment env(db);
			gdb::OperationResult result;
			gdb::HashTableOperations::Set(env,result,name,key,gdb::Slice(newobj.objdata(),newobj.objsize()));

			if(result.IsSuccessful())
				db->Commit(result.MutableOplog());
		}

		return changed;
	}

	bool Modifier::Compile( const char* data,size_t size,std::string& error )
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

	bool Modifier::Compile( mongo::BSONObj bsonobj,std::string& error )
	{
		if(bsonobj.firstElement().type() == mongo::EOO)
		{
			error = "empty update rule";
			return false;
		}

		if(bsonobj.couldBeArray())
		{
			mongo::BSONObjIterator iter(bsonobj);
			while(iter.more())
			{
				mongo::BSONElement be = iter.next();
				if(!be.isABSONObj())
				{
					error = "update rule mustbe bson object";
					return false;
				}
				_detail::BaseModifier* m = _detail::BaseModifier::Parse(be.Obj(),error);
				if(m != NULL)
					m_vModifiers.push_back(m);
				else
					return false;
			}
		}
		else
		{
			_detail::BaseModifier* m = _detail::BaseModifier::Parse(bsonobj,error);
			if(m != NULL)
				m_vModifiers.push_back(m);
			else
				return false;
		}
		return true;
	}

	Modifier::~Modifier()
	{
		for(size_t i = 0; i < m_vModifiers.size(); ++i)
			_safe_delete(m_vModifiers[i]);
		m_vModifiers.clear();
	}

}