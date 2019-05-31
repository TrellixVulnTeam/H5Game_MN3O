#include "pw_gdb_idl.h"

namespace  gdb
{
    Attrs* Field::find(const std::string& name)
    {
        for(size_t i = 0; i < this->attrs.size(); ++i)
        {
            if(this->attrs[i].name == name)
                return &attrs[i];
        }
        return NULL;
    }

	std::string Field::findAttrValue( const std::string& name,size_t pos /*= 0*/,const std::string& errorReturn )
	{
		Attrs* a = this->find(name);
		if(a == NULL || a->args.size() <= pos)
			return errorReturn;
		return a->args[pos];
	}

	bool Field::isHashmapIntegerKey()
	{
		std::string f = findAttrValue("hashmap");
		return f.find("int") != std::string::npos;
	}

	int Field::findAsInteger( const std::string& name,int nullval )
	{
		Attrs* a = find(name);
		if(a == NULL)
			return nullval;
		if(a->args.size() == 0)
			return nullval;

		return atoi(a->args[0].c_str());
	}


	Attrs* Table::find( const std::string& name )
	{
		for(size_t i = 0; i < this->attrs.size(); ++i)
		{
			if(this->attrs[i].name == name)
				return &attrs[i];
		}
		return NULL;
	}

	Field* Table::findField( const std::string& name )
	{
		std::vector<std::string> classes;
		for(size_t i = 0; i < fields.size(); ++i)
		{
			Field* r = fields[i];
			if(r->name == name)
				return r;
		}
		return NULL;
	}

	Field* Table::findAutoIncrField()
	{
		std::vector<std::string> classes;
		for(size_t i = 0; i < fields.size(); ++i)
		{
			Field* r = fields[i];
			if(r->find("autoincr") != NULL)
				return r;
		}
		return NULL;
	}

	Field* Table::findFiedHasAttr(const std::string& attr)
	{
		for(size_t i = 0; i < fields.size(); ++i)
		{
			Field* r = fields[i];
			if(r->find(attr) != NULL)
				return r;
		}
		return NULL;
	}

	Attrs* Table::findAttrAndValue( const std::string& name,const std::string& value )
	{
		Attrs* attr = this->find(name);
		if(attr == NULL || attr->args.size() == 0)
			return NULL;
		if(value == attr->args[0])
			return attr;
		return NULL;
	}

	bool Table::isValueType()
	{
		for(size_t i = 0; i < fields.size(); ++i)
		{
			Field* r = fields[i];
			if(r->isValueType())
				continue;
			if(r->IsBuiltType())
				continue;
			if(r->isSimpleStruct() || r->isArray() || r->isHashmap())
				return false;
		}
		return true;
	}

	bool Table::isSlave()
	{
		return this->find("slave") != NULL;
	}

	bool Table::isSlaveTable()
	{
		return this->find("slave_table") != NULL;
	}

	bool Table::isIgnoreCollection()
	{
		return this->find("ignore_collection") != NULL;
	}

	bool Table::isIgnoreReflectionDefine()
	{
		return this->find("ignore_reflection_define") != NULL;
	}






}
