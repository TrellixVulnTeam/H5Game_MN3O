#include "pw_gdb_generator.h"
#include "pw_gdb_parser.h"
#include "stdio.h"
#include <fstream>
#include <algorithm>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <set>
#include <locale>
#include <assert.h>

namespace gdb
{
	std::vector<Table*> g_objAllTables;

	bool IsLightWeightStruct(const std::string& name)
	{
		Table* r = NULL;

		for(size_t i = 0; i < g_objAllTables.size(); ++i)
		{
			if(g_objAllTables[i]->name == name)	
			{
				r = g_objAllTables[i];
				break;
			}
		}

		if(r == NULL)
			return false;
		return r->find("lightweight") != NULL;
	}

	INT64 bkdr_hash_and_sum(const char* str)
	{
		INT64 sum = 0;
		unsigned int seed = 131;
		unsigned int hash = 0;

		while(*str)
		{
			sum += *str;
			hash = hash * seed + (*str++);
		}
		return (sum << 32) + (hash & 0x7FFFFFFF);
	}

    std::string tabX(int i)
    {
        std::string result;
        while(i--)
            result.append("\t");
        return result;
    }

	bool isSameLines(const std::string& filename,std::vector<std::string>& lines)
	{
		std::fstream stream;
		stream.open(filename.c_str(),std::ios_base::in);
		if(!stream.good())
			return false;
		
		size_t count = 0;
		while(!stream.eof())
		{
			char tmpbuf[10*1024] = {0};
			stream.getline(tmpbuf,sizeof(tmpbuf));

			if(count >= lines.size())
			{
				if(stream.eof())
					break;
				return false;
			}

			if(lines[count] != tmpbuf)
				return false;
			++count;
		}
		return true;

	}	

    void TableGenerator::gen(Table* t,const std::string& outputdir)
    {
        this->genHpp(t,outputdir);
        this->genCpp(t,outputdir);
    }

    void TableGenerator::genHpp(Table* t,const std::string& outputdir)
    {
        m_lines.clear();
        m_lines.push_back(std::string("#ifndef _pw_orm_") + stringToLower(t->name) + "_");
        m_lines.push_back(std::string("#define _pw_orm_") + stringToLower(t->name) + "_");
		m_lines.push_back("");
        m_lines.push_back("#include \"pw_types.h\"");
		m_lines.push_back("#include \"snappy/snappy.h\"");
        m_lines.push_back("#include \"kvdb/pw_fixed_string.h\"");
        m_lines.push_back("#include \"kvdb/pw_kvorm.h\"");
		m_lines.push_back("#include \"kvdb/pw_kvorm_array.h\"");
		m_lines.push_back("#include \"kvdb/pw_kvorm_hashmap.h\"");
        m_lines.push_back("#include \"bson/bson.h\"");
        m_lines.push_back("#include \"bson/bsonobjbuilder.h\"");

		{
			std::vector<std::string> classes;
			for(size_t i = 0; i < t->fields.size(); ++i)
			{
				Field& r = *(t->fields[i]);
				if(r.isValueType() && r.isStruct())
				{
					classes.push_back(r.type);
				}
			}

			classes.erase(std::unique(classes.begin(),classes.end()),classes.end());
			for(size_t i = 0; i < classes.size(); ++i)
				m_lines.push_back("#include \"kvorm/pw_orm_" + stringToLower(classes[i]) + ".h\"");
		}

        m_lines.push_back("");
        m_lines.push_back("namespace orm");
        m_lines.push_back("{");
		m_lines.push_back("");

		{
			std::vector<std::string> classes;
			for(size_t i = 0; i < t->fields.size(); ++i)
			{
				Field& r = *(t->fields[i]);
				if(r.isStruct())
				{
					classes.push_back(r.type);
				}
			}

			classes.erase(std::unique(classes.begin(),classes.end()),classes.end());
			for(size_t i = 0; i < classes.size(); ++i)
				m_lines.push_back(tabX(1) + "class " + classes[i] + ";");
		}

		m_lines.push_back("");
		m_lines.push_back(tabX(1) + "class " + t->name + " : public pwutils::KvormBase");
        m_lines.push_back(tabX(1) + "{");
		m_lines.push_back(tabX(2) + "RTTI(" + t->name + ",pwutils::KvormBase);");
		
//         m_lines.push_back(tabX(1) + "public:");
//         m_lines.push_back(tabX(2) + "enum {");
// 
//         for(size_t i = 0; i < t->fields.size(); ++i)
//         {
//             Field& r = *(t->fields[i]);
//             m_lines.push_back(tabX(3) + "FIELD_" + stringToUpper(r.name) + ",");
//         }
//         m_lines.push_back(tabX(2) + "};");
// 
        m_lines.push_back(tabX(1) + "public:");
        m_lines.push_back(tabX(2) + t->name + "();");
		m_lines.push_back(tabX(2) + "virtual ~" + t->name + "();");

		m_lines.push_back(tabX(1) + "public:");
		m_lines.push_back(tabX(2) + "virtual bool is_default_value() const; // override");
		
		m_lines.push_back(tabX(1) + "public:");
		m_lines.push_back(tabX(2) + t->name + "* clone() const;");
		m_lines.push_back(tabX(1) + "public:");
		m_lines.push_back(tabX(2) + "virtual std::string rawkey();");
		m_lines.push_back(tabX(2) + "virtual std::string getkey();");
		m_lines.push_back(tabX(2) + "virtual std::string getmeta();");
		m_lines.push_back(tabX(1) + "public:");
		{
			std::string name = stringToLower(t->name);
			if(Attrs* attr = t->find("name"))
				name = attr->args[0];
			m_lines.push_back(tabX(2) + "static const char* meta() { return \"" + name + "\"; }");
			
			char hashbuf[1000] = "";
			INT64 hash = bkdr_hash_and_sum(name.c_str());
			::_i64toa(hash,hashbuf,10);

			m_lines.push_back(tabX(2) + "static const int64 meta_hash = " + hashbuf + ";");
			m_lines.push_back(tabX(2) + "static const char* prefix() { return \"" + name + "_\"; }");
		}

        m_lines.push_back(tabX(1) + "public:");
        m_lines.push_back(tabX(2) + "virtual void to_bson(std::string& __buf) const; // override");
		m_lines.push_back(tabX(2) + "virtual void to_bson(bson::bo& __obj) const; // override");
		m_lines.push_back(tabX(2) + "virtual void to_snappy_buffer(std::string& __buf) const; // override");
        m_lines.push_back(tabX(2) + "virtual void from_bson(const char* __data,size_t __size); // override");
		m_lines.push_back(tabX(2) + "virtual void from_bson(const bson::bo& __obj); // override");
		m_lines.push_back(tabX(2) + "virtual void from_snappy_buffer(const char* __data,size_t __size); // override");		
		m_lines.push_back(tabX(2) + "virtual void from_snappy_buffer(const std::string& __buf); // override");
		m_lines.push_back(tabX(1) + "public:");
		m_lines.push_back(tabX(2) + "virtual int64 hash_make(int64 seed);");
		m_lines.push_back(tabX(2) + "virtual int64 hash_origin() { return __hash; }");
		m_lines.push_back(tabX(2) + "virtual void  hash_update(int64 hash) { __hash = hash; }");

		m_lines.push_back(tabX(1) + "public:");
		m_lines.push_back(tabX(2) + "virtual void set_autoincr(int64 key); // override");	

		Field* field = NULL;
		if(t->isSlave() || t->isSlaveTable())
		{
			field = t->findFiedHasAttr("masterid");
			if(field == NULL)
				std::cout << "Warning::table no exists <masterid> field:"  << t->name << std::endl;
		}
		m_lines.push_back(tabX(1) + "public:");
		if(field != NULL)
		{
			if(field->isIntegerType())
			{
				m_lines.push_back(tabX(2) + "virtual int64 get_masterid() { return " + getMemberName(*field) +  "; } // override");	
				m_lines.push_back(tabX(2) + "virtual void  set_masterid(int64 v) { " + getMemberName(*field) +  " = v; } // override");	
				m_lines.push_back(tabX(2) + "virtual void  set_masterid(const char* v) { } // override");	
				m_lines.push_back(tabX(2) + "virtual const char* get_masterstrid() { return \"\"; } // override");	
			}
			else if(field->isStringType())
			{
				m_lines.push_back(tabX(2) + "virtual int64 get_masterid() { return 0; } // override");	
				m_lines.push_back(tabX(2) + "virtual void  set_masterid(int64 v) { } // override");	
				m_lines.push_back(tabX(2) + "virtual void  set_masterid(const char* v) { "+ getMemberName(*field) + " = v; } // override");	
				m_lines.push_back(tabX(2) + "virtual const char* get_masterstrid() { return " + getMemberName(*field) + ".c_str(); } // override");	
			}
			else
			{
				std::cerr << __FUNCTION__ << " invalid masterid field type: " << field->name << " " << field->type << std::endl;
			}
 		}
		else
		{
			m_lines.push_back(tabX(2) + "virtual int64 get_masterid() { return 0; } // override");	
			m_lines.push_back(tabX(2) + "virtual void  set_masterid(int64 v) { } // override");	
			m_lines.push_back(tabX(2) + "virtual void  set_masterid(const char* v) { } // override");	
			m_lines.push_back(tabX(2) + "virtual const char* get_masterstrid() { return \"\"; } // override");	
		}


        m_lines.push_back(tabX(1) + "public:");
        this->genHppFieldsGetterSetter(t);

		if(!t->isValueType())
		{
// 			m_lines.push_back(tabX(1) + "private:");
// 			m_lines.push_back(tabX(2) + t->name + "(const " + t->name + "& v);");
// 			m_lines.push_back(tabX(2) + "const " + t->name + "& operator=(const " + t->name + "& v);");
			m_lines.push_back(tabX(1) + "public:");
			m_lines.push_back(tabX(2) + t->name + "(const " + t->name + "& v);");
			m_lines.push_back(tabX(2) + "const " + t->name + "& operator=(const " + t->name + "& v) { this->from_obj(&v); return *this; }");
		}
        this->genHppFields(t);
        m_lines.push_back(tabX(1) + "};");
        m_lines.push_back("}");
        m_lines.push_back("");
        m_lines.push_back(std::string("#endif // _pw_orm_") + stringToLower(t->name) + "_");

        this->writeLinesToFile(outputdir + "/pw_orm_" + stringToLower(t->name) + ".h");
    }

    void TableGenerator::genHppFieldsGetterSetter(Table* t)
    {
        for(size_t i = 0; i < t->fields.size(); ++i)
        {
            Field& r = *(t->fields[i]);

            if(r.IsRawBaseType())
            {
				m_lines.push_back(tabX(2) + getGetterTypeName(r) + " get_" + stringToLower(r.name) + "() const;");
            }
        }

		// ---------------------------------------------

		for(size_t i = 0; i < t->fields.size(); ++i)
		{
			Field& r = *(t->fields[i]);

			if(i == 0)
				m_lines.push_back("");

			if(r.IsRawBaseType())
			{
				m_lines.push_back(tabX(2) + "void set_" + stringToLower(r.name) + "(" + getSetterTypeName(r) + " value);");
			}
		}

		// ===========================================

		for(size_t i = 0; i < t->fields.size(); ++i)
		{
			Field& r = *(t->fields[i]);

			if(i == 0)
				m_lines.push_back("");

			if(r.find("bitmask") && r.IsRawBaseType())
			{
				m_lines.push_back(tabX(2) + "void " + stringToLower(r.name) + "_include(" + r.type + " value) { " + getMemberName(r) + " |= value; }");
				m_lines.push_back(tabX(2) + "void " + stringToLower(r.name) + "_exclude(" + r.type + " value) { " + getMemberName(r) + " &= ~value; }");
				m_lines.push_back(tabX(2) + "bool is_" + stringToLower(r.name) + "_include(" + r.type + " value) { return " + getMemberName(r) + " & value; }");
				m_lines.push_back("");
			}
			if(r.find("count") && r.IsRawBaseType())
			{
				m_lines.push_back(tabX(2) + "void " + stringToLower(r.name) + "_plus(" + r.type + " value) { " + getMemberName(r) + " += value; }");
				m_lines.push_back(tabX(2) + "void " + stringToLower(r.name) + "_minus(" + r.type + " value) { " + getMemberName(r) + " -= value; }");
				m_lines.push_back("");
			}
		}

		// ===========================================

		for(size_t i = 0; i < t->fields.size(); ++i)
		{
			Field& r = *(t->fields[i]);

			if(r.type == "bytes")
			{
				m_lines.push_back(tabX(1) + "public:");
				m_lines.push_back(tabX(2) + "inline const char* " + stringToLower(r.name) + "_data () const { return " + getMemberName(r) + ".c_str(); }");
				m_lines.push_back(tabX(2) + "inline size_t " + stringToLower(r.name) + "_size() const { return " + getMemberName(r) + ".length(); }");				
				m_lines.push_back(tabX(1) + "public:");
				m_lines.push_back(tabX(2) + "void set_" + stringToLower(r.name) + "(const void* __buf,size_t __len);");
			}
		}

		// ===========================================

		size_t count = 0;

		for(size_t i = 0; i < t->fields.size(); ++i)
		{
			Field& r = *(t->fields[i]);

			if(r.isSimpleStruct())
			{
				if(count++ == 0)
					m_lines.push_back(tabX(1) + "public:");
				m_lines.push_back(tabX(2) + getCppType(r) + "* mutable_" + stringToLower(r.name) + "();");
			}
		}

		count = 0;

		for(size_t i = 0; i < t->fields.size(); ++i)
		{
			Field& r = *(t->fields[i]);

			if((r.isArray() && !r.isStaticArray())
				|| r.isHashmap())
			{
				if(count++ == 0)
					m_lines.push_back(tabX(1) + "public:");
				m_lines.push_back(tabX(2) + getStoreTypeName(r) + "* mutable_" + stringToLower(r.name) + "() { return &" + getMemberName(r) + "; }");
			}
		}
	}	

    void TableGenerator::genHppFields(Table* t)
    {
		int count = 0;

		for(size_t i = 0; i < t->fields.size(); ++i)
		{
			Field& r = *(t->fields[i]);

			if(count == 0)
			{
				m_lines.push_back(tabX(1) + "public:");
			}
			++count;

			std::string comment;
			Attrs* attr = r.find("comment");
			if(attr != NULL && attr->args.size() > 0)
				comment = " // " + attr->args[0];

			m_lines.push_back(tabX(2) + getMemberAndType(r) + ";" + comment);
		}
		m_lines.push_back(tabX(1) + "public:");
		m_lines.push_back(tabX(2) + "int64 __hash;");

    }

    void TableGenerator::writeLinesToFile(const std::string& filename)
    {
		if(isSameLines(filename,m_lines))
			return ;

		std::fstream f;
		f.open(filename.c_str(),std::ios_base::out | std::ios_base::trunc);

        for(size_t i = 0; i < m_lines.size(); ++i)
        {
            std::string& r = m_lines[i];
			f << r << std::endl;
        }
        f.flush();
    }

    std::string TableGenerator::getStoreElementTypeName(Field& r)
    {
        std::string type = r.type;
        if(r.type == "string")
        {
            Attrs* attr = r.find("len");
            if(attr == NULL || attr->args.size() != 1)
                type = "std::string";
            else if(r.isBaseType())
                type = std::string("pwutils::fixed_string<") + attr->args[0] + ">";
			else
				type = "std::string";
        }
        if(r.type == "bytes")
            type = "std::string";
		if(r.isStruct())
		{
			if(r.isValueType())
				type = r.type + "";
			else
				type = r.type + "*";
		}
        return type;
    }


	std::string TableGenerator::getMemberAndType( Field& r )
	{
		if(r.IsRawBaseType())
		{
			if(r.type == "string")
			{
				Attrs* attr = r.find("len");
				if(attr == NULL || attr->args.size() != 1)
					return "std::string " + r.getDefaultMemberName();
				return std::string("pwutils::fixed_string<") + attr->args[0] + "> " + r.getDefaultMemberName();
			}
			if(r.type == "bytes")
				return "std::string " + r.getDefaultMemberName();
			return r.type + " " + r.getDefaultMemberName();
		}

		if(r.isSimpleStruct())
		{
			return r.type + "* " + r.getDefaultMemberName();
		}

		if(r.isStruct() && r.isValueType() && !r.IsContainer())
		{
			return r.type + " " + r.getDefaultMemberName();
		}

		if(r.isArray())
		{
			std::string lenval;
			r.getLen(lenval);

			if(lenval.length() > 0)
			{
				if(r.isValueType() || r.IsBuiltType())
					return getCppType(r.type) + " " + r.getDefaultMemberName() + "[" + lenval + "]";
				else
					return getCppType(r.type) + "* " + r.getDefaultMemberName() + "[" + lenval + "]";
			}
			else
			{
				if(r.isValueType() || r.IsBuiltType())
					return std::string("pwutils::KvormArray< ") + getCppType(r.type) + " > " + r.getDefaultMemberName();
				else
					return std::string("pwutils::KvormObjectArray< ") + getCppType(r.type) + "* > " + r.getDefaultMemberName();
			}
		}

		if(r.isHashmap())
		{
			if(r.isValueType() || r.IsBuiltType())
			{
				return std::string("pwutils::KvormHashmap< ") + getCppType(r.findAttrValue("hashmap")) + "," + getCppType(r.type) + " > " + r.getDefaultMemberName();
			}
			else
			{
				return std::string("pwutils::KvormObjectHashmap< ") + getCppType(r.findAttrValue("hashmap")) + "," + getCppType(r.type) + "* > " + r.getDefaultMemberName();
			}
		}
		return "ERROR_" + r.lowername + __FUNCTION__;
	}

    std::string TableGenerator::getStoreTypeName(Field& r)
	{
		if(r.IsRawBaseType())
		{
			if(r.type == "string")
			{
				Attrs* attr = r.find("len");
				if(attr == NULL || attr->args.size() != 1)
					return "std::string";
				return std::string("pwutils::fixed_string<") + attr->args[0] + ">";
			}
			if(r.type == "bytes")
				return "std::string";
			return r.type;
		}

		if(r.isSimpleStruct())
		{
			return r.type + "*";
		}

		if(r.isStruct() && r.isValueType() && !r.IsContainer())
		{
			return r.type;
		}

		if(r.isArray())
		{
			std::string lenval;
			r.getLen(lenval);

			if(lenval.length() > 0)
			{
				if(r.isValueType() || r.IsBuiltType())
					return getCppType(r.type) + "*";
				else
					return getCppType(r.type) + "**";
			}
			else
			{
				if(r.isValueType() || r.IsBuiltType())
					return std::string("pwutils::KvormArray< ") + getCppType(r.type) + " >";
				else
					return std::string("pwutils::KvormObjectArray< ") + getCppType(r.type) + "* >";
			}
		}

		if(r.isHashmap())
		{
			if(r.isValueType() || r.IsBuiltType())
			{
				return std::string("pwutils::KvormHashmap< ") + getCppType(r.findAttrValue("hashmap")) + "," + getCppType(r.type) + " >";
			}
			else
			{
				return std::string("pwutils::KvormObjectHashmap< ") + getCppType(r.findAttrValue("hashmap")) + "," + getCppType(r.type) + "* >";
			}
		}
        return "ERROR_" + r.lowername + __FUNCTION__;
    }

    std::string TableGenerator::getGetterTypeName(Field& r)
    {
        if(r.type == "string")
        {
			return "const char*";
        }
        if(r.type == "bytes")
            return "pwutils::KvormBuffer";
		
		return r.type;
    }

	
    std::string TableGenerator::getSetterTypeName(Field& r)
    {
		if(!r.IsRawBaseType())
			return "ERROR_" + r.lowername;

		if(r.type == "string")
		{
			return "const char*";
		}
		if(r.type == "bytes")
			return "const pwutils::KvormBuffer&";

		return r.type;
    }

    std::string TableGenerator::getTypeNameDefaultValue(Field& r)
    {
        Attrs* defaultAttr = r.find("default");
        if(defaultAttr != NULL && defaultAttr->args.size() == 1)
            return defaultAttr->args[0];

        if(r.type.find("int") != std::string::npos)
            return "0";
        if(r.type.find("float") != std::string::npos)
            return "0.0f";

        if(r.type.find("double") != std::string::npos)
            return "0.0";

		if(r.type == "bool")
			return "false";
		if(r.type == "char")
			return "0";
        return "\"\"";
    }

    int TableGenerator::getBaseType(Field& r)
    {
        if(r.isArray())
            return T_ARRAY;
		if(r.isHashmap())
			return T_HASHMAP;
        if(r.type == "string")
            return T_STR;
        if(r.type == "int32" || r.type == "int16" || r.type == "uint8")
            return T_I32;
        if(r.type == "int64")
            return T_I64;
        if(r.type == "float" || r.type == "double")
            return T_DEC;
        if(r.type == "bytes")
            return T_BUF;
        return T_NIL;
    }

    std::string TableGenerator::getMemberName(Field& r)
    {
// 		if(r.isValueType() || r.IsRawBaseType())
			return std::string("").append(r.lowername);
//         return std::string("m_").append(r.lowername);
    }

    void TableGenerator::genCpp(Table* t,const std::string& outputdir)
    {
        m_lines.clear();
		m_lines.push_back("#include \"kvdb/pw_bsontocpp.h\"");
		m_lines.push_back("#include \"pw_utils.h\"");
		m_lines.push_back("#include \"pw_logger.h\"");
        m_lines.push_back("#include \"kvorm/pw_orm_" + stringToLower(t->name) + ".h\"");

		{
			std::vector<std::string> classes;
			for(size_t i = 0; i < t->fields.size(); ++i)
			{
				Field& r = *t->fields[i];
				if(r.isStruct() && !r.isValueType())
				{
					classes.push_back("\"kvorm/pw_orm_" + stringToLower(r.type) + ".h\"");
				}
			}

			classes.erase(std::unique(classes.begin(),classes.end()),classes.end());
			for(size_t i = 0; i < classes.size(); ++i)
				m_lines.push_back("#include " + classes[i]);
		}

        m_lines.push_back("");
        m_lines.push_back("namespace orm");
        m_lines.push_back("{");
        m_lines.push_back("");
		m_lines.push_back(tabX(1) + "RTTI_TOUCH(" + t->name + ");");
		m_lines.push_back("");

        // default constructor
		{
			m_lines.push_back(tabX(1) + t->name + "::" + t->name + "()");

			size_t num = 0;
			for(size_t i = 0; i < t->fields.size(); ++i)
			{
				Field& r = *t->fields[i];
				std::string defaultValue;

				if(r.IsRawBaseType())
				{
					defaultValue = getTypeNameDefaultValue(r);
				}
				else if(r.isSimpleStruct())
					defaultValue = "NULL";

				if(defaultValue.length() > 0)
				{
					if(num == 0)
						m_lines.push_back(tabX(2) + ": " + getMemberName(r) + "(" + defaultValue + ")");
					else
						m_lines.push_back(tabX(2) + ", " + getMemberName(r) + "(" + defaultValue + ")");
					++num;
				}
			}

			if(num == 0)
				m_lines.push_back(tabX(2) + ": __hash(0)");
			else
				m_lines.push_back(tabX(2) + ", __hash(0)");

			m_lines.push_back(tabX(1) + "{");

			for(size_t i = 0; i < t->fields.size(); ++i)
			{
				Field& r = *t->fields[i];

				std::string vallen;
				r.getLen(vallen);

				if(((!r.isValueType() || r.IsBuiltType()) && !r.isStringType()) && r.isStaticArray())
				{
					m_lines.push_back(tabX(2) + "memset(" + getMemberName(r) + ",0,sizeof(" + getMemberName(r) + "));");
				}
			}


			m_lines.push_back(tabX(1) + "}");
		}

		m_lines.push_back("");

		// copy constructor
		if(!t->isValueType())
		{
			m_lines.push_back(tabX(1) + t->name + "::" + t->name + "(const " + t->name + "& v)");

			size_t num = 0;
			for(size_t i = 0; i < t->fields.size(); ++i)
			{
				Field& r = *t->fields[i];
				std::string defaultValue;

				if(r.IsRawBaseType())
				{
					defaultValue = getTypeNameDefaultValue(r);
				}
				else if(r.isSimpleStruct())
					defaultValue = "NULL";

				if(defaultValue.length() > 0)
				{
					if(num == 0)
						m_lines.push_back(tabX(2) + ": " + getMemberName(r) + "(" + defaultValue + ")");
					else
						m_lines.push_back(tabX(2) + ", " + getMemberName(r) + "(" + defaultValue + ")");
					++num;
				}
			}

			if(num == 0)
				m_lines.push_back(tabX(2) + ": __hash(0)");
			else
				m_lines.push_back(tabX(2) + ", __hash(0)");

			m_lines.push_back(tabX(1) + "{");

			for(size_t i = 0; i < t->fields.size(); ++i)
			{
				Field& r = *t->fields[i];

				std::string vallen;
				r.getLen(vallen);

				if(((!r.isValueType() || r.IsBuiltType()) && !r.isStringType()) && r.isStaticArray())
				{
					m_lines.push_back(tabX(2) + "memset(" + getMemberName(r) + ",0,sizeof(" + getMemberName(r) + "));");
				}
			}

			m_lines.push_back(tabX(2) + "this->from_obj(&v);");
			m_lines.push_back(tabX(1) + "}");
		}

		// default destructor
		m_lines.push_back("");
		
		{
			m_lines.push_back(tabX(1) + t->name + "::~" + t->name + "()");
			m_lines.push_back(tabX(1) + "{");

			for(size_t i = 0; i < t->fields.size(); ++i)
			{
				Field& r = *t->fields[i];

				if(r.isValueType() || r.IsBuiltType())
					continue;

				if(r.isSimpleStruct())
				{
					m_lines.push_back(tabX(2) + "_safe_delete(" + getMemberName(r) + ");");
				}				
				else if(!r.isStaticArray())
				{
					m_lines.push_back(tabX(2) + getMemberName(r) + ".cleanup();");
				}
				else
				{
					std::string lenval;
					r.getLen(lenval);

					m_lines.push_back("");
					m_lines.push_back(tabX(2) + "for(size_t i = 0; i < " + lenval + ";++i)");
					m_lines.push_back(tabX(3) + "_safe_delete(" + getMemberName(r) + "[i]);");
				}
			}

			m_lines.push_back(tabX(1) + "}");
		}

		// ----------------------------------------------
		// key
		// ----------------------------------------------

		m_lines.push_back("");

		{
			std::string name = stringToLower(t->name);
			if(Attrs* attr = t->find("name"))
				name = attr->args[0];

			m_lines.push_back(tabX(1) + "std::string " + t->name + "::rawkey()");
			m_lines.push_back(tabX(1) + "{");
			m_lines.push_back(tabX(2) + "std::string result;");
			m_lines.push_back(tabX(2) + "result.reserve(64);");

			std::vector<std::string> keys;
			for(size_t i = 0; i < t->fields.size(); ++i)
			{
				Field& r = *t->fields[i];
				if(Attrs* attr = r.find("key"))
				{
					if(attr->args.size() == 0)
						keys.push_back("0" + r.name);
					else
						keys.push_back(attr->args[0] + r.name);
				}
			}

			if(keys.size() > 1)
				std::sort(keys.begin(),keys.end());

			for(size_t i = 0; i < keys.size(); ++i)
			{
				Field* r = t->findField(&keys[i][1]);
				if(r != NULL)
				{
					m_lines.push_back("");
					if(i != 0)
						m_lines.push_back(tabX(2) + "result.append(\".\");");
					if(r->isIntegerType())
					{
						m_lines.push_back(tabX(2) + "{");
						m_lines.push_back(tabX(3) + "char tmpbuf[64] = \"\";");
						m_lines.push_back(tabX(3) + "pwutils::itoa(tmpbuf,(int64)" + this->getMemberName(*r) + ");");
						m_lines.push_back(tabX(3) + "result.append(tmpbuf);");
						m_lines.push_back(tabX(2) + "}");
					}
					else if(r->isStringType())
					{
						m_lines.push_back(tabX(2) + "result.append(" + this->getMemberName(*r) + ".c_str());");
					}
				}
			}
			m_lines.push_back(tabX(2) + "return result;");
			m_lines.push_back(tabX(1) + "}");
		}

		m_lines.push_back("");

		{
			Field* f = t->findFiedHasAttr("masterid");

			m_lines.push_back(tabX(1) + "std::string " + t->name + "::getkey()");
			m_lines.push_back(tabX(1) + "{");

			if(f == NULL || t->find("slave") == NULL)
			{
				m_lines.push_back(tabX(2) + "return this->rawkey();");
			}
			else
			{
				m_lines.push_back(tabX(2) + "std::string result;");
				m_lines.push_back(tabX(2) + "result.reserve(64);");

				if(f->isIntegerType())
				{
					m_lines.push_back(tabX(2) + "{");
					m_lines.push_back(tabX(3) + "char tmpbuf[64] = \"\";");
					m_lines.push_back(tabX(3) + "pwutils::itoa(tmpbuf,(int64)" + this->getMemberName(*f) + ");");
					m_lines.push_back(tabX(3) + "result.append(tmpbuf);");
					m_lines.push_back(tabX(2) + "}");
				}
				else if(f->isStringType())
				{
					m_lines.push_back(tabX(2) + "result.append(" + this->getMemberName(*f) + ".c_str());");
				}
				m_lines.push_back(tabX(2) + "return result;");
			}
			m_lines.push_back(tabX(1) + "}");
		}

		m_lines.push_back("");

		{
			Field* f = t->findFiedHasAttr("masterid");

			m_lines.push_back(tabX(1) + "std::string " + t->name + "::getmeta()");
			m_lines.push_back(tabX(1) + "{");
			if(f == NULL || !t->isSlaveTable())
			{
				m_lines.push_back(tabX(2) + "return " + t->name + "::meta();");
			}
			else
			{
				m_lines.push_back(tabX(2) + "std::string result;");
				m_lines.push_back(tabX(2) + "result.reserve(64);");
				m_lines.push_back(tabX(2) + "result.append(meta());");
				m_lines.push_back(tabX(2) + "result.append(\".\");");

				if(f->isIntegerType())
				{
					m_lines.push_back(tabX(2) + "{");
					m_lines.push_back(tabX(3) + "char tmpbuf[64] = \"\";");
					m_lines.push_back(tabX(3) + "pwutils::itoa(tmpbuf,(int64)" + this->getMemberName(*f) + ");");
					m_lines.push_back(tabX(3) + "result.append(tmpbuf);");
					m_lines.push_back(tabX(2) + "}");
				}
				else if(f->isStringType())
				{
					m_lines.push_back(tabX(2) + "result.append(" + this->getMemberName(*f) + ".c_str());");
				}

				m_lines.push_back(tabX(2) + "return result;");
			}
			m_lines.push_back(tabX(1) + "}");
		}

		// ----------------------------------------------

        m_lines.push_back("");
		{
			this->genCppFieldsBsonOpers(t);
			this->genCppFieldsGetterSetter(t);
		}
		// ----------------------------------------------

		m_lines.push_back("");
		
		{
			m_lines.push_back(tabX(1) + "bool " + t->name + "::is_default_value() const");
			m_lines.push_back(tabX(1) + "{");

			for(size_t i = 0; i < t->fields.size(); ++i)
			{
				Field& r = *t->fields[i];

				if(r.IsRawBaseType())
				{
					if(r.type == "string" || r.type == "bytes")
					{
						m_lines.push_back(tabX(2) + "if(" + getMemberName(r) + ".length() != 0)");
						m_lines.push_back(tabX(3) + "return false;");
						m_lines.push_back("");
					}
					else
					{
						m_lines.push_back(tabX(2) + "if(" + getMemberName(r) + " != " + getTypeNameDefaultValue(r) + ")");
						m_lines.push_back(tabX(3) + "return false;");
						m_lines.push_back("");
					}
				}
				else if(r.isSimpleStruct())
				{
					m_lines.push_back(tabX(2) + "if(" +  getMemberName(r) + " != NULL && !" + getMemberName(r) + "->is_default_value())");
					m_lines.push_back(tabX(3) + "return false;");
					m_lines.push_back("");
				}
				else if(r.isValueType())
				{
					std::string vallen;
					r.getLen(vallen);

					if(r.isStaticArray())
					{
						if(r.isStruct())
						{
							m_lines.push_back(tabX(2) + "for(size_t i = 0; i < " + vallen + "; ++i)");
							m_lines.push_back(tabX(3) + "if(!" + getMemberName(r) + "[i].is_default_value())");
							m_lines.push_back(tabX(4) + "return false;");
						}
						else
						{
							if(r.type == "char" && r.isBinary())
							{
								m_lines.push_back(tabX(2) + "if(!pwutils::is_default_value_binary("
									+ getMemberName(r) + "," + vallen + "," + getTypeNameDefaultValue(r) + "))");
								m_lines.push_back(tabX(3) + "return false;");
							}
							else
							{
								m_lines.push_back(tabX(2) + "if(!pwutils::is_default_value("
									+ getMemberName(r) + "," + vallen + "," + getTypeNameDefaultValue(r) + "))");
								m_lines.push_back(tabX(3) + "return false;");
							}
						}
					}
					else
					{
						m_lines.push_back(tabX(2) + "if(!" + getMemberName(r) + ".is_default_value())");
						m_lines.push_back(tabX(3) + "return false;");
					}
					m_lines.push_back("");
				}
				else if(!r.isValueType() && r.isStaticArray())
				{
					std::string vallen;
					r.getLen(vallen);
					if(r.isStruct())
					{
						m_lines.push_back(tabX(2) + "for(size_t i = 0; i < " + vallen + "; ++i)");
						m_lines.push_back(tabX(3) + "if(" + getMemberName(r) + "[i] != NULL && !" + getMemberName(r) + "[i]->is_default_value())");
						m_lines.push_back(tabX(4) + "return false;");
					}
					else
					{
						m_lines.push_back(tabX(2) + "for(size_t i = 0; i < " + vallen + "; ++i)");
						m_lines.push_back(tabX(3) + "if(" + getMemberName(r) + "[i] != " + getTypeNameDefaultValue(r) + ")");
						m_lines.push_back(tabX(4) + "return false;");
					}
					m_lines.push_back("");
				}
				else
				{
					m_lines.push_back(tabX(2) + "if(!" + getMemberName(r) + ".is_default_value())");
					m_lines.push_back(tabX(3) + "return false;");
					m_lines.push_back("");
				}
			}
			

			m_lines.push_back(tabX(2) + "return true;");
			m_lines.push_back(tabX(1) + "}");
		}
		m_lines.push_back("");

		// ----------------------------------------------

		{
// 			m_lines.push_back(tabX(1) + "bool " + t->name + "::is_default_value()");
// 			m_lines.push_back(tabX(1) + "{");
// 			m_lines.push_back(tabX(2) + "");
//			m_lines.push_back(tabX(1) + "}");

		}


		//////////////////////////////////////////////////////////////////////

        m_lines.push_back("}");

        this->writeLinesToFile(outputdir + "/pw_orm_" + stringToLower(t->name) + ".cpp");
    }


	struct SLightWeightFieldSorter
	{
		bool operator()(Field* r1,Field* r2)
		{
			int index1 = r1->findAsInteger("index",-1);
			int index2 = r1->findAsInteger("index",-1);

			if(index1 < 0 || index2 < 0)
				return index1 < index2;

			return index1 < index2;
		}
	};
	void TableGenerator::genCpp_ToBsonLightWeight(Table* t)
	{
		m_lines.push_back(tabX(1) + "void " + t->name + "::to_bson(bson::bo& __obj) const");
		m_lines.push_back(tabX(1) + "{");
		m_lines.push_back(tabX(2) + "int count = 0;");
		m_lines.push_back(tabX(2) + "mongo::BSONArrayBuilder __builder;");

		std::vector<Field*> sortedFields = t->fields;
		std::sort(sortedFields.begin(),sortedFields.end(),SLightWeightFieldSorter());
		
		for(size_t i = 0; i < t->fields.size(); ++i)
		{
			Field& r = *t->fields[i];
			std::string lowname = r.lowername;

			if(!r.IsRawBaseType())
			{
				std::cerr << __FUNCTION__ << " 轻量级对象,只支持原始内建&&非容器类型, 表:" << t->name << " 字段:" << r.name << std::endl;
				exit(1);
			}

			int index = r.findAsInteger("index",-1);
			if(index < 0)
			{
				std::cerr << __FUNCTION__ << " 轻量级对象, 表:" << t->name << " 字段:" << r.name << " 缺少index属性" << std::endl;
				exit(1);
			}
			std::string strindex = r.find("index")->args[0];

			m_lines.push_back("");
			m_lines.push_back(tabX(2) + "while(count < " + strindex + ") { ++count; __builder.appendNull(); }");
			m_lines.push_back(tabX(2) + "__builder.append(" + getMemberName(r) + ");");			
			m_lines.push_back(tabX(2) + "++count;");
		}
		m_lines.push_back("");
		m_lines.push_back(tabX(2) + "__obj = __builder.obj();");
		m_lines.push_back(tabX(1) + "}");
	}

	void TableGenerator::genCpp_FromBsonLightWeight(Table* t)
	{
		m_lines.push_back(tabX(1) + "void " + t->name + "::from_bson(const bson::bo& __obj)");
		m_lines.push_back(tabX(1) + "{");
		m_lines.push_back(tabX(2) + "mongo::BSONObjIterator iter(__obj);");
		m_lines.push_back(tabX(2) + "while(iter.more())");
		m_lines.push_back(tabX(2) + "{");
		m_lines.push_back(tabX(3) + "mongo::BSONElement __be = iter.next();");
		m_lines.push_back(tabX(3) + "int64 index = pwutils::atoi(__be.fieldName());");
		
		m_lines.push_back(tabX(3) + "switch(index)");
		m_lines.push_back(tabX(3) + "{");

		std::vector<Field*> sortedFields = t->fields;
		std::sort(sortedFields.begin(),sortedFields.end(),SLightWeightFieldSorter());

		for(size_t i = 0; i < t->fields.size(); ++i)
		{
			Field& r = *t->fields[i];
			std::string lowname = r.lowername;

			if(!r.IsRawBaseType())
			{
				std::cerr << __FUNCTION__ << " 轻量级对象,只支持原始内建&&非容器类型, 表:" << t->name << " 字段:" << r.name << std::endl;
				exit(1);
			}

			int index = r.findAsInteger("index",-1);
			if(index < 0)
			{
				std::cerr << __FUNCTION__ << " 轻量级对象, 表:" << t->name << " 字段:" << r.name << " 缺少index属性" << std::endl;
				exit(1);
			}
			std::string strindex = r.find("index")->args[0];

			m_lines.push_back(tabX(3) + "case " + strindex + ":");
			m_lines.push_back(tabX(4) + "{");
			m_lines.push_back(tabX(5) + "pwutils::bsonToCppVariable("+ getMemberName(r) + ",__be);");
			m_lines.push_back(tabX(4) + "}");
			m_lines.push_back(tabX(4) + "break;");
		}
		
		m_lines.push_back(tabX(3) + "}");

		m_lines.push_back(tabX(2) + "}");
		m_lines.push_back(tabX(2) + "__hash = hash_make(0);");
		m_lines.push_back(tabX(1) + "}");
	}

	void TableGenerator::genCpp_ToBson(Table* t)
	{
		m_lines.push_back(tabX(1) + "void " + t->name + "::to_bson(bson::bo& __obj) const");
		m_lines.push_back(tabX(1) + "{");
		m_lines.push_back(tabX(2) + "mongo::BSONObjBuilder __builder;");
		m_lines.push_back(tabX(2) + "__builder.append(\"_T\",meta());");
		for(size_t i = 0; i < t->fields.size(); ++i)
		{
			Field& r = *t->fields[i];
			std::string lowname = r.lowername;

			if(r.IsRawBaseType())
			{
				if(r.type == "bytes")
				{
					m_lines.push_back(tabX(2) + "if(" + getMemberName(r) + ".length() > 0)");
					m_lines.push_back(tabX(3) + "__builder.appendBinData(\"" + lowname + +"\"," + getMemberName(r) + ".length(),mongo::bdtCustom," + getMemberName(r) + ".c_str());");
				}
				else
				{
					m_lines.push_back(tabX(2) + "if(" + getMemberName(r) + " != " + getTypeNameDefaultValue(r) + ")");
					m_lines.push_back(tabX(3) + "__builder.append(\"" + lowname + +"\"," + getMemberName(r) + ");");
				}
			}
			else if(r.isStaticArray())
			{
				std::string varname(lowname + "_builder");

				std::string lenval;
				r.getLen(lenval);

				assert(lenval.length() > 0);

				if(!r.isStruct())
				{
					m_lines.push_back("");


					if(r.type == "char" && r.isBinary())
					{
						m_lines.push_back(tabX(2) + "if(!pwutils::is_default_value_binary(" 
							+ getMemberName(r) + "," +lenval+ "," + getTypeNameDefaultValue(r) + "))");

						m_lines.push_back(tabX(3) + "__builder.appendBinData(\"" + lowname + +"\",sizeof(" + getMemberName(r) + "),mongo::bdtCustom," + getMemberName(r) + ");");
					}
					else if(r.type == "char")
					{
						m_lines.push_back(tabX(2) + "if(!pwutils::is_default_value(" 
							+ getMemberName(r) + "," +lenval+ "," + getTypeNameDefaultValue(r) + "))");

						m_lines.push_back(tabX(3) + "__builder.append(\"" + lowname + +"\"," + getMemberName(r) + ");");
					}
					else
					{
						m_lines.push_back(tabX(2) + "if(!pwutils::is_default_value(" 
							+ getMemberName(r) + "," +lenval+ "," + getTypeNameDefaultValue(r) + "))");

						m_lines.push_back(tabX(2) + "{");
						m_lines.push_back(tabX(3) + "mongo::BSONArrayBuilder " + varname + ";");
						m_lines.push_back(tabX(3) + "for(size_t i = 0; i < " + lenval + "; ++i)");
						m_lines.push_back(tabX(3) + "{");

						if(r.isValueType())
							m_lines.push_back(tabX(4) + varname + ".append(" + getMemberName(r) + "[i]);");
						else
							m_lines.push_back(tabX(4) + varname + ".append(" + getMemberName(r) + "[i]);");

						m_lines.push_back(tabX(3) + "}");
						m_lines.push_back(tabX(3) + "__builder.appendArray(\"" + lowname + +"\"," + varname + ".obj());");
						m_lines.push_back(tabX(2) + "}");
					}
					m_lines.push_back("");
				}
				else
				{
					m_lines.push_back("");

					if(!r.isValueType() && !r.isStruct())
						m_lines.push_back(tabX(2) + "if(!" + getMemberName(r) + "->is_default_value())");

					m_lines.push_back(tabX(2) + "{");
					m_lines.push_back(tabX(3) + "mongo::BSONArrayBuilder " + varname + ";");
					m_lines.push_back(tabX(3) + "for(size_t i = 0; i < " + lenval + "; ++i)");
					m_lines.push_back(tabX(3) + "{");

					if(r.isValueType())
					{
						m_lines.push_back(tabX(4) + "bson::bo __tmpobj;");
						m_lines.push_back(tabX(4) + "if(!" + getMemberName(r) + "[i].is_default_value())");
						m_lines.push_back(tabX(4) + "{");
						m_lines.push_back(tabX(5) + getMemberName(r) + "[i].to_bson(__tmpobj);");

						if(IsLightWeightStruct(r.type))
							m_lines.push_back(tabX(5) + varname + ".appendArray(__tmpobj);");
						else
							m_lines.push_back(tabX(5) + varname + ".append(__tmpobj);");
						m_lines.push_back(tabX(4) + "}");
					}
					else
					{
						m_lines.push_back(tabX(4) + "bson::bo __tmpobj;");
						m_lines.push_back(tabX(4) + "if(" + getMemberName(r) + "[i] != NULL && !" + getMemberName(r) + "[i]->is_default_value())");
						m_lines.push_back(tabX(4) + "{");
						m_lines.push_back(tabX(5) + getMemberName(r) + "[i]->to_bson(__tmpobj);");
						if(IsLightWeightStruct(r.type))
							m_lines.push_back(tabX(5) + varname + ".appendArray(__tmpobj);");
						else
							m_lines.push_back(tabX(5) + varname + ".append(__tmpobj);");
						m_lines.push_back(tabX(4) + "}");
					}
					m_lines.push_back(tabX(4) + "else");
					m_lines.push_back(tabX(4) + "{");
					m_lines.push_back(tabX(5) + varname + ".appendNull();");
					m_lines.push_back(tabX(4) + "}");

					m_lines.push_back(tabX(3) + "}");
					m_lines.push_back(tabX(3) + "__builder.appendArray(\"" + lowname + +"\"," + varname + ".obj());");
					m_lines.push_back(tabX(2) + "}");
					m_lines.push_back("");
				}
			}
			else if(r.isStruct() && r.isValueType() && !r.IsContainer())
			{
				m_lines.push_back(tabX(2) + "if(!" + getMemberName(r) + ".is_default_value())");
				m_lines.push_back(tabX(2) + "{");
				m_lines.push_back(tabX(3) + "bson::bo __tmpobj;");
				m_lines.push_back(tabX(3) + getMemberName(r) + ".to_bson(__tmpobj);");

				if(IsLightWeightStruct(r.type))
					m_lines.push_back(tabX(3) + "__builder.appendArray(\"" + lowname + +"\",__tmpobj);");
				else
					m_lines.push_back(tabX(3) + "__builder.append(\"" + lowname + +"\",__tmpobj);");
				m_lines.push_back(tabX(2) + "}");
			}
			else if(r.isSimpleStruct())
			{
				m_lines.push_back(tabX(2) + "if(" + getMemberName(r) + "!= NULL && !" + getMemberName(r) + "->is_default_value())");
				m_lines.push_back(tabX(2) + "{");
				m_lines.push_back(tabX(3) + "bson::bo __tmpobj;");
				m_lines.push_back(tabX(3) + getMemberName(r) + "->to_bson(__tmpobj);");
				m_lines.push_back(tabX(3) + "__builder.append(\"" + lowname + +"\",__tmpobj);");
				m_lines.push_back(tabX(2) + "}");
			}

			else if(r.isArray())
			{
				std::string varname(lowname + "_builder");

				std::string lenval;
				r.getLen(lenval);

				if(!r.isStruct())
				{
					m_lines.push_back("");
					m_lines.push_back(tabX(2) + "if(!" + getMemberName(r) + ".is_default_value())");
					m_lines.push_back(tabX(2) + "{");
					m_lines.push_back(tabX(3) + "mongo::BSONArrayBuilder " + varname + ";");
					m_lines.push_back(tabX(3) + "for(size_t i = 0; i < " + getMemberName(r) + ".size(); ++i)");
					m_lines.push_back(tabX(3) + "{");
					m_lines.push_back(tabX(4) + varname + ".append(" + getMemberName(r) + "[i]);");
					m_lines.push_back(tabX(3) + "}");
					m_lines.push_back(tabX(3) + "__builder.appendArray(\"" + lowname + +"\"," + varname + ".obj());");
					m_lines.push_back(tabX(2) + "}");
					m_lines.push_back("");
				}
				else
				{
					m_lines.push_back("");
					m_lines.push_back(tabX(2) + "if(!" + getMemberName(r) + ".is_default_value())");
					m_lines.push_back(tabX(2) + "{");
					m_lines.push_back(tabX(3) + "mongo::BSONArrayBuilder " + varname + ";");
					m_lines.push_back(tabX(3) + "for(size_t i = 0; i < " + getMemberName(r) + ".size(); ++i)");
					m_lines.push_back(tabX(3) + "{");

					m_lines.push_back(tabX(4) + "bson::bo __tmpobj;");

					if(r.isValueType())
						m_lines.push_back(tabX(4) + getMemberName(r) + "[i].to_bson(__tmpobj);");
					else
						m_lines.push_back(tabX(4) + getMemberName(r) + "[i]->to_bson(__tmpobj);");

					if(IsLightWeightStruct(r.type))
						m_lines.push_back(tabX(4) + varname + ".appendArray(__tmpobj);");
					else
						m_lines.push_back(tabX(4) + varname + ".append(__tmpobj);");
					m_lines.push_back(tabX(3) + "}");
					m_lines.push_back(tabX(3) + "__builder.appendArray(\"" + lowname + +"\"," + varname + ".obj());");
					m_lines.push_back(tabX(2) + "}");
				}						
				m_lines.push_back("");
			}				
			else if(r.isHashmap())
			{
				std::string varname(lowname + "_builder");

				if(!r.isStruct())
				{
					std::string iterateContype = getStoreTypeName(r);

					m_lines.push_back("");
					m_lines.push_back(tabX(2) + "if(!" + getMemberName(r) + ".is_default_value())");
					m_lines.push_back(tabX(2) + "{");
					m_lines.push_back(tabX(3) + "mongo::BSONObjBuilder " + varname + ";");
					m_lines.push_back(tabX(3) + "for(" + iterateContype + "::const_iterator iter = " + getMemberName(r) + ".begin(); iter != " + getMemberName(r) + ".end(); ++iter)");
					m_lines.push_back(tabX(3) + "{");

					if(r.isHashmapIntegerKey())
					{
						m_lines.push_back(tabX(4) + "char intbuf[64] = \"\";");
						m_lines.push_back(tabX(4) + "pwutils::itoa(intbuf,iter->first);");
						m_lines.push_back(tabX(4) + varname + ".append(intbuf,iter->second);");
					}
					else
					{
						m_lines.push_back(tabX(4) + varname + ".append(iter->first,iter->second);");
					}
					m_lines.push_back(tabX(3) + "}");
					m_lines.push_back(tabX(3) + "__builder.append(\"" + lowname + +"\"," + varname + ".obj());");
					m_lines.push_back(tabX(2) + "}");
					m_lines.push_back("");
				}
				else
				{
					std::string iterateContype = getStoreTypeName(r);

					m_lines.push_back("");
					m_lines.push_back(tabX(2) + "if(!" + getMemberName(r) + ".is_default_value())");
					m_lines.push_back(tabX(2) + "{");
					m_lines.push_back(tabX(3) + "mongo::BSONObjBuilder " + varname + ";");
					m_lines.push_back(tabX(3) + "for(" + iterateContype + "::const_iterator iter = " + getMemberName(r) + ".begin(); iter != " + getMemberName(r) + ".end(); ++iter)");
					m_lines.push_back(tabX(3) + "{");
					m_lines.push_back(tabX(4) + "bson::bo __tmpobj;");

					if(r.isValueType())
						m_lines.push_back(tabX(4) + "iter->second.to_bson(__tmpobj);");
					else
						m_lines.push_back(tabX(4) + "iter->second->to_bson(__tmpobj);");

					if(r.isHashmapIntegerKey())
					{
						m_lines.push_back(tabX(4) + "char intbuf[64] = \"\";");
						m_lines.push_back(tabX(4) + "pwutils::itoa(intbuf,iter->first);");
						if(IsLightWeightStruct(r.type))
							m_lines.push_back(tabX(4) + varname + ".appendArray(intbuf,__tmpobj);");
						else
							m_lines.push_back(tabX(4) + varname + ".append(intbuf,__tmpobj);");
					}
					else
					{
						m_lines.push_back(tabX(4) + varname + ".append(iter->first,__tmpobj);");
					}
					m_lines.push_back(tabX(3) + "}");
					m_lines.push_back(tabX(3) + "__builder.append(\"" + lowname + +"\"," + varname + ".obj());");
					m_lines.push_back(tabX(2) + "}");
					m_lines.push_back("");
				}
			}
		}
		m_lines.push_back(tabX(2) + "__obj = __builder.obj();");
		m_lines.push_back(tabX(1) + "}");
	}

	void TableGenerator::genCpp_FromBson(Table* t)
	{
		m_lines.push_back(tabX(1) + "void " + t->name + "::from_bson(const bson::bo& __obj)");
		m_lines.push_back(tabX(1) + "{");
		m_lines.push_back(tabX(2) + "mongo::BSONObjIterator iter(__obj);");
		m_lines.push_back(tabX(2) + "while(iter.more())");
		m_lines.push_back(tabX(2) + "{");
		m_lines.push_back(tabX(3) + "mongo::BSONElement __be = iter.next();");
		m_lines.push_back(tabX(3) + "const char* fieldName = __be.fieldName();");
		m_lines.push_back(tabX(3) + "int64 hash = pwutils::bkdr_hash_and_sum(fieldName);");
		m_lines.push_back(tabX(3) + "switch(hash)");
		m_lines.push_back(tabX(3) + "{");

		// ----meta
		{
			char hashbuf[1000] = "";
			INT64 hash = bkdr_hash_and_sum("_T");
			::_i64toa(hash,hashbuf,10);
			m_lines.push_back(tabX(3) + "case " + hashbuf + ": // _T");
			m_lines.push_back(tabX(4) + "{");
			m_lines.push_back(tabX(5) + "pwasserte(pwutils::strcmp(__be.valuestr(),meta()) == 0);");
			m_lines.push_back(tabX(4) + "}");
			m_lines.push_back(tabX(4) + "break;");
		}

		char hashbuf[1000] = "";

		for(size_t i = 0; i < t->fields.size(); ++i)
		{
			Field& r = *t->fields[i];
			std::string lowname = r.lowername;
			INT64 hash = bkdr_hash_and_sum(lowname.c_str());
			::_i64toa(hash,hashbuf,10);

			m_lines.push_back(tabX(3) + "case " + hashbuf + ": // " + lowname + " type: " + r.type);

			std::vector<std::string> oldnames = r.getOldNames();
			for(size_t k = 0; k < oldnames.size(); ++k)
			{
				std::string oldname(stringToLower(oldnames[k]));
				INT64 hash = bkdr_hash_and_sum(oldname.c_str());
				::_i64toa(hash,hashbuf,10);
				m_lines.push_back(tabX(3) + "case " + hashbuf + ": // " + oldname);
			}

			m_lines.push_back(tabX(4) + "{");
			{
				if(r.IsRawBaseType())
				{
					m_lines.push_back(tabX(5) + "pwutils::bsonToCppVariable(" + getMemberName(r) + ",__be);");
				}
				else if(r.isSimpleStruct())
				{
					m_lines.push_back(tabX(5) + "if(" + getMemberName(r) + " == NULL)");
					m_lines.push_back(tabX(6) + getMemberName(r) + " = new " + getCppType(r.type) + "();");
					m_lines.push_back(tabX(5) + "bson::bo __obj = __be.Obj();");
					m_lines.push_back(tabX(5) + getMemberName(r) + "->from_bson(__obj);");

				}
				else if(r.isValueType() && r.isStruct() && !r.IsContainer())
				{
					m_lines.push_back(tabX(5) + "bson::bo __obj = __be.Obj();");
					m_lines.push_back(tabX(5) + getMemberName(r) +  + ".from_bson(__obj);");
				}
				else if(r.isStaticArray())
				{
					std::string lenval;
					r.getLen(lenval);

					if(!r.isValueType() && !r.IsBuiltType())
					{
						m_lines.push_back(tabX(5) + "for(size_t i = 0; i < " + lenval + "; ++i)");
						m_lines.push_back(tabX(6) + "_safe_delete(" + getMemberName(r) + "[i]);");
					}

					if(r.type == "char" && r.isBinary())
					{
						m_lines.push_back(tabX(5) + "memcpy(" + getMemberName(r) + ",__be.value(),__min(__be.valuesize(),sizeof(" + getMemberName(r) + ")));");
					}
					else if(r.type == "char")
					{
						m_lines.push_back(tabX(5) + "pwutils::strncpy(" + getMemberName(r) + ",__be.valuestrsafe(),_countof(" + getMemberName(r) + "));");
					}
					else
					{
						m_lines.push_back("");
						m_lines.push_back(tabX(5) + "mongo::BSONObj aobj = __be.Obj();");
						m_lines.push_back(tabX(5) + "mongo::BSONObjIterator aiter(aobj);");
						m_lines.push_back(tabX(5) + "size_t count = 0;");
						m_lines.push_back(tabX(5) + "while(aiter.more())");
						m_lines.push_back(tabX(5) + "{");
						m_lines.push_back(tabX(6) + "mongo::BSONElement ae = aiter.next();");
						m_lines.push_back(tabX(6) + "pwassertop(count < " + lenval + ",continue);");


						if(r.isStruct())
						{
							m_lines.push_back(tabX(6) + "if(!ae.isNull())");
							m_lines.push_back(tabX(6) + "{");

							if(r.isValueType())
							{
								m_lines.push_back(tabX(7) + "bson::bo tmp = ae.Obj();");
								m_lines.push_back(tabX(7) + getMemberName(r) + "[count].from_bson(tmp);");
							}
							else
							{
								m_lines.push_back(tabX(7) + getStoreElementTypeName(r) + " tmpvar = new " + r.type + "();");
								m_lines.push_back(tabX(7) + "bson::bo tmp = ae.Obj();");
								m_lines.push_back(tabX(7) + "tmpvar->from_bson(tmp);");
								m_lines.push_back(tabX(7) + getMemberName(r) + "[count] = tmpvar;");
							}

							m_lines.push_back(tabX(6) + "}");
						}
						else
						{
							if(r.isValueType())
							{
								m_lines.push_back(tabX(6) + "pwutils::bsonToCppVariable(" + getMemberName(r) + "[count],ae);");
							}
							else
							{
								m_lines.push_back(tabX(6) + getStoreElementTypeName(r) + " tmpvar;");
								m_lines.push_back(tabX(6) + "pwutils::bsonToCppVariable(tmpvar,ae);");
								m_lines.push_back(tabX(6) + getMemberName(r) + "[count] = tmpvar;");
							}
						}

						m_lines.push_back(tabX(6) + "++count;");

						m_lines.push_back(tabX(5) + "}");
					}
				}
				else if(r.isArray())
				{
					m_lines.push_back(tabX(5) + getMemberName(r) + ".cleanup();");
					m_lines.push_back(tabX(5) + "mongo::BSONObj aobj = __be.Obj();");
					m_lines.push_back(tabX(5) + "mongo::BSONObjIterator aiter(aobj);");
					m_lines.push_back(tabX(5) + "while(aiter.more())");
					m_lines.push_back(tabX(5) + "{");
					m_lines.push_back(tabX(6) + "mongo::BSONElement ae = aiter.next();");

					if(r.isStruct())
					{
						if(r.isValueType())
						{
							m_lines.push_back(tabX(6) + getStoreElementTypeName(r) + " tmpvar;");
							m_lines.push_back(tabX(6) + "bson::bo tmp = ae.Obj();");
							m_lines.push_back(tabX(6) + "tmpvar.from_bson(tmp);");
						}
						else
						{
							m_lines.push_back(tabX(6) + getStoreElementTypeName(r) + " tmpvar = new " + getCppType(r.type) + "();");
							m_lines.push_back(tabX(6) + "bson::bo tmp = ae.Obj();");
							m_lines.push_back(tabX(6) + "tmpvar->from_bson(tmp);");
						}
					}
					else
					{
						if(r.isValueType() || r.IsBuiltType())
						{
							m_lines.push_back(tabX(6) + getStoreElementTypeName(r) + " tmpvar;");
							m_lines.push_back(tabX(6) + "pwutils::bsonToCppVariable(tmpvar,ae);");
						}
						else
						{
							m_lines.push_back(tabX(6) + getStoreElementTypeName(r) + "* tmpvar = new " + getCppType(r.type) + "();");
							m_lines.push_back(tabX(6) + "pwutils::bsonToCppVariable(*tmpvar,ae);");
						}
					}
					m_lines.push_back(tabX(6) + getMemberName(r) + ".push_back(tmpvar);");
					m_lines.push_back(tabX(5) + "}");
				}
				else if(r.isHashmap())
				{
					m_lines.push_back(tabX(5) + getMemberName(r) + ".cleanup();");
					m_lines.push_back(tabX(5) + "mongo::BSONObj aobj = __be.Obj();");
					m_lines.push_back(tabX(5) + "mongo::BSONObjIterator aiter(aobj);");
					m_lines.push_back(tabX(5) + "while(aiter.more())");
					m_lines.push_back(tabX(5) + "{");
					m_lines.push_back(tabX(6) + "mongo::BSONElement ae = aiter.next();");

					if(r.isStruct())
					{
						if(r.isValueType())
						{
							m_lines.push_back(tabX(6) + getStoreElementTypeName(r) + " tmpvar;");
							m_lines.push_back(tabX(6) + "bson::bo tmp = ae.Obj();");
							m_lines.push_back(tabX(6) + "tmpvar.from_bson(tmp);");
						}
						else
						{
							m_lines.push_back(tabX(6) + getStoreElementTypeName(r) + " tmpvar = new " + r.type + "();");
							m_lines.push_back(tabX(6) + "bson::bo tmp = ae.Obj();");
							m_lines.push_back(tabX(6) + "tmpvar->from_bson(tmp);");
						}
					}
					else
					{
						m_lines.push_back(tabX(6) + getStoreElementTypeName(r) + " tmpvar;");
						m_lines.push_back(tabX(6) + "pwutils::bsonToCppVariable(tmpvar,ae);");
					}

					if(r.isHashmapIntegerKey())
					{
						m_lines.push_back(tabX(6) + "int64 key = pwutils::atoi(ae.fieldName());");
						m_lines.push_back(tabX(6) + getMemberName(r) + ".insert(std::make_pair(key,tmpvar));");
					}
					else
					{
						m_lines.push_back(tabX(6) + getMemberName(r) + ".insert(std::make_pair(ae.fieldName(),tmpvar));");
					}
					m_lines.push_back(tabX(5) + "}");
				}
				m_lines.push_back(tabX(4) + "}");
				m_lines.push_back(tabX(4) + "break;");
			}
		}
		m_lines.push_back(tabX(3) + "}");

		m_lines.push_back(tabX(2) + "}");
		m_lines.push_back(tabX(2) + "__hash = hash_make(0);");
		m_lines.push_back(tabX(1) + "}");
	}

	void TableGenerator::genCppFieldsBsonOpers(Table* t)
    {
		// ----------------------------------------set_autoincr -----------------------------------
		
		m_lines.push_back(tabX(1) + "void " + t->name + "::set_autoincr(int64 key)");	
		m_lines.push_back(tabX(1) + "{");
		if(Field* autofield = t->findAutoIncrField())
		{
			m_lines.push_back(tabX(2) + getMemberName(*autofield) + " = key;");
		}
		else
		{
			m_lines.push_back(tabX(2) + "pwassert(false);");
		}
		m_lines.push_back(tabX(1) + "}");
		m_lines.push_back("");

		// ----------------------------------------clone -----------------------------------
		{
			m_lines.push_back(tabX(1) + t->name + "* " + t->name + "::clone() const");
			m_lines.push_back(tabX(1) + "{");
			m_lines.push_back(tabX(2) + "bson::bo __obj;");
			m_lines.push_back(tabX(2) + "to_bson(__obj);");
			m_lines.push_back(tabX(2) + t->name + "* tmp = new " + t->name + "();");
			m_lines.push_back(tabX(2) + "tmp->from_bson(__obj);");
			m_lines.push_back(tabX(2) + "return tmp;");
			m_lines.push_back(tabX(1) + "}");
			m_lines.push_back("");
		}

        // ----------------------------------------to_bson -----------------------------------
		{
			m_lines.push_back(tabX(1) + "void " + t->name + "::to_snappy_buffer(std::string& __buf) const");
			m_lines.push_back(tabX(1) + "{");
			m_lines.push_back(tabX(2) + "bson::bo __obj;");
			m_lines.push_back(tabX(2) + "to_bson(__obj);");
			m_lines.push_back(tabX(2) + "snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);");
			m_lines.push_back(tabX(1) + "}");
			m_lines.push_back("");
			

			m_lines.push_back(tabX(1) + "void " + t->name + "::to_bson(std::string& __buf) const");
			m_lines.push_back(tabX(1) + "{");
			m_lines.push_back(tabX(2) + "bson::bo __obj;");
			m_lines.push_back(tabX(2) + "to_bson(__obj);");
			m_lines.push_back(tabX(2) + "__buf = std::string(__obj.objdata(),__obj.objsize());");
			m_lines.push_back(tabX(1) + "}");
			m_lines.push_back("");

			if(t->find("lightweight") != NULL)
				this->genCpp_ToBsonLightWeight(t);
			else
				this->genCpp_ToBson(t);
		}

        // -------------------------------------from_bson---------------------------------------

        m_lines.push_back("");

		{
			m_lines.push_back(tabX(1) + "void " + t->name + "::from_snappy_buffer(const std::string& __inbuf)");
			m_lines.push_back(tabX(1) + "{");
			m_lines.push_back(tabX(2) + "std::string tmpbuf;");
			m_lines.push_back(tabX(2) + "snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);");
			m_lines.push_back(tabX(2) + "bson::bo __obj(tmpbuf.c_str());");
			m_lines.push_back(tabX(2) + "pwassert(__obj.objsize() == tmpbuf.length());");
			m_lines.push_back(tabX(2) + "from_bson(__obj);");
			m_lines.push_back(tabX(1) + "}");
			m_lines.push_back("");

			m_lines.push_back(tabX(1) + "void " + t->name + "::from_snappy_buffer(const char* __data,size_t __size)");
			m_lines.push_back(tabX(1) + "{");
			m_lines.push_back(tabX(2) + "std::string tmpbuf;");
			m_lines.push_back(tabX(2) + "snappy::Uncompress(__data,__size,&tmpbuf);");
			m_lines.push_back(tabX(2) + "bson::bo __obj(tmpbuf.c_str());");
			m_lines.push_back(tabX(2) + "pwassert(__obj.objsize() == tmpbuf.length());");
			m_lines.push_back(tabX(2) + "from_bson(__obj);");
			m_lines.push_back(tabX(1) + "}");
			m_lines.push_back("");

			m_lines.push_back(tabX(1) + "void " + t->name + "::from_bson(const char* __data,size_t __size)");
			m_lines.push_back(tabX(1) + "{");
			m_lines.push_back(tabX(2) + "pwassert(__data != 0);");
			m_lines.push_back(tabX(2) + "pwassert(__size >= sizeof(int));");
			m_lines.push_back(tabX(2) + "try");
			m_lines.push_back(tabX(2) + "{");			
			m_lines.push_back(tabX(3) + "bson::bo __obj(__data);");
			m_lines.push_back(tabX(3) + "pwassert(__obj.objsize() == __size);");
			m_lines.push_back(tabX(3) + "from_bson(__obj);");
			m_lines.push_back(tabX(2) + "}");
			m_lines.push_back(tabX(2) + "catch(const bson::assertion&)");
			m_lines.push_back(tabX(2) + "{");
			m_lines.push_back(tabX(3) + "pwreportvars(false && \"invalid bson_data\",__size);");
			m_lines.push_back(tabX(3) + "pwassert(false && \"invalid bson_data\");");
			m_lines.push_back(tabX(2) + "}");
			m_lines.push_back(tabX(1) + "}");
			m_lines.push_back("");

			if(t->find("lightweight") != NULL)
				genCpp_FromBsonLightWeight(t);
			else
				genCpp_FromBson(t);
		}

        m_lines.push_back("");

        // -------------------------------------------------------------------------
		// hash

		m_lines.push_back("");

		{
			m_lines.push_back(tabX(1) + "int64 " + t->name + "::hash_make(int64 seed)");
			m_lines.push_back(tabX(1) + "{");
			m_lines.push_back(tabX(2) + "int64 _result = seed;");

			for(size_t i = 0; i < t->fields.size(); ++i)
			{
				Field& r = *t->fields[i];
				std::string lowname = r.lowername;

				if(r.IsRawBaseType())
				{
					m_lines.push_back(tabX(2) + "_result = pwutils::city_hash(" + getMemberDataStr(r) + "," + getMemberSizeStr(r) + ",_result);");
				}
				else if(r.isSimpleStruct())
				{
					m_lines.push_back(tabX(2) + "if(" + getMemberName(r) + " != NULL)");
					m_lines.push_back(tabX(3) + "_result = " + getMemberName(r) + "->hash_make(_result);");
				}
				else if(r.isValueType() && r.isStruct() && !r.IsContainer())
				{
					m_lines.push_back(tabX(2) + "_result = " + getMemberName(r) + ".hash_make(_result);");
				}
				else if(r.isStaticArray())
				{
					std::string lenval;
					r.getLen(lenval);

					if(r.type == "char" && r.isBinary())
					{
						m_lines.push_back(tabX(2) + "_result = pwutils::city_hash(" + getMemberDataStr(r) + "," + getMemberSizeStr(r) + ",_result);");
					}
					else if(r.type == "char")
					{
						m_lines.push_back(tabX(2) + "_result = pwutils::city_hash(" + getMemberName(r) + ",strlen(" + getMemberName(r) + "),_result);");
					}
					else if(r.type == "string" || r.type == "bytes")
					{

						m_lines.push_back(tabX(2) + "for(size_t i = 0; i < " + lenval + ";++i)");
						m_lines.push_back(tabX(2) + "{");
						m_lines.push_back(tabX(3) + "_result = pwutils::city_hash(&i,sizeof(i),_result);");
						m_lines.push_back(tabX(3) + "_result = pwutils::city_hash(" + getMemberName(r) + "[i].c_str()," + getMemberName(r) + "[i].length(),_result);");
						m_lines.push_back(tabX(2) + "}");
					}
					else if(r.isStruct())
					{
						m_lines.push_back(tabX(2) + "for(size_t i = 0; i < " + lenval + ";++i)");
						m_lines.push_back(tabX(2) + "{");
						m_lines.push_back(tabX(3) + "_result = pwutils::city_hash(&i,sizeof(i),_result);");

						if(r.isValueType())
						{
							m_lines.push_back(tabX(3) + "_result = " + getMemberName(r) + "[i].hash_make(_result);");
						}
						else
						{
							m_lines.push_back(tabX(3) + "if(" + getMemberName(r) + "[i] != NULL)");
							m_lines.push_back(tabX(4) + "_result = " + getMemberName(r) + "[i]->hash_make(_result);");
						}
						m_lines.push_back(tabX(2) + "}");
					}
					else
					{
						m_lines.push_back(tabX(2) + "for(size_t i = 0; i < " + lenval + ";++i)");
						m_lines.push_back(tabX(2) + "{");
						m_lines.push_back(tabX(3) + "_result = pwutils::city_hash(&i,sizeof(i),_result);");

						if(r.isValueType() || r.IsBuiltType())
						{
							m_lines.push_back(tabX(3) + "_result = pwutils::city_hash(&" + getMemberName(r) + "[i]," + "sizeof(" + getMemberName(r) + "[i]),_result);");
						}
						else
						{
							m_lines.push_back(tabX(3) + "if(" + getMemberName(r) + "[i] != NULL)");
							m_lines.push_back(tabX(4) + "_result = pwutils::city_hash(" + getMemberName(r) + "[i]," + "sizeof(*" + getMemberName(r) + "[i]),_result);");

						}
						m_lines.push_back(tabX(2) + "}");
					}
				}
				else if(r.isArray())
				{
					m_lines.push_back(tabX(2) + "_result = " + getMemberName(r) + ".hash_make(_result);");
				}
				else if(r.isHashmap())
				{
					m_lines.push_back(tabX(2) + "_result = " + getMemberName(r) + ".hash_make(_result);");
				}

				m_lines.push_back("");
			}

			m_lines.push_back(tabX(2) + "return _result;");
			m_lines.push_back(tabX(1) + "}");
		}
		m_lines.push_back("");
      

        // -------------------------------------------------------------------------
    }

    void TableGenerator::genCppFieldsGetterSetter(Table* t)
    {
        for(size_t i = 0; i < t->fields.size(); ++i)
        {
            Field& r = *t->fields[i];

			char indexbuf[100] = "";
			_i64toa(i,indexbuf,10);

			
			if(r.IsContainer())
				continue;

			if(r.type == "bytes")
			{
				m_lines.push_back(tabX(1) + "void " + t->name + "::set_" + stringToLower(r.name) + "(const void* __buf,size_t __len)");
				m_lines.push_back(tabX(1) + "{");
				m_lines.push_back(tabX(2) + "this->" + getMemberName(r) + ".clear();");
				m_lines.push_back(tabX(2) + "this->" + getMemberName(r) + ".append((const char*)__buf,__len);");
				m_lines.push_back(tabX(1) + "}");
				m_lines.push_back("");

				m_lines.push_back(tabX(1) + getGetterTypeName(r) + " " + t->name + "::get_" + stringToLower(r.name) + "() const");
				m_lines.push_back(tabX(1) + "{");
				m_lines.push_back(tabX(2) + "return pwutils::KvormBuffer((char*)" + getMemberName(r) + ".c_str()," + getMemberName(r) + ".length());");
				m_lines.push_back(tabX(1) + "}");
				m_lines.push_back("");

				m_lines.push_back(tabX(1) + "void " + t->name + "::set_" + stringToLower(r.name) + "(" + this->getSetterTypeName(r) + " value)");
				m_lines.push_back(tabX(1) + "{");
				m_lines.push_back(tabX(2) + "this->" + getMemberName(r) + ".clear();");
				m_lines.push_back(tabX(2) + "this->" + getMemberName(r) + ".append(value.buf,value.len);");
				m_lines.push_back(tabX(1) + "}");
				m_lines.push_back("");
			}
			else if(r.type == "string")
			{
				m_lines.push_back(tabX(1) + getGetterTypeName(r) + " " + t->name + "::get_" + stringToLower(r.name) + "() const");
				m_lines.push_back(tabX(1) + "{");
				m_lines.push_back(tabX(2) + "return " + getMemberName(r) + ".c_str();");
				m_lines.push_back(tabX(1) + "}");
				m_lines.push_back("");

				m_lines.push_back(tabX(1) + "void " + t->name + "::set_" + stringToLower(r.name) + "(const char* value)");
				m_lines.push_back(tabX(1) + "{");
				m_lines.push_back(tabX(2) + "this->" + getMemberName(r) + " = value;");
				m_lines.push_back(tabX(1) + "}");
				m_lines.push_back("");
			}
			else if(r.IsRawBaseType())
			{
				m_lines.push_back(tabX(1) + getGetterTypeName(r) + " " + t->name + "::get_" + stringToLower(r.name) + "() const");
				m_lines.push_back(tabX(1) + "{");
				m_lines.push_back(tabX(2) + "return " + getMemberName(r) + ";");
				m_lines.push_back(tabX(1) + "}");
				m_lines.push_back("");

				m_lines.push_back(tabX(1) + "void " + t->name + "::set_" + stringToLower(r.name) + "(" + this->getSetterTypeName(r) + " value)");
				m_lines.push_back(tabX(1) + "{");
				m_lines.push_back(tabX(2) + "this->" + getMemberName(r) + " = value;");
				m_lines.push_back(tabX(1) + "}");
				m_lines.push_back("");
			}
			else if(r.isSimpleStruct())
			{
				m_lines.push_back(tabX(1) + getCppType(r) + "* " + t->name + "::mutable_" + stringToLower(r.name) + "()");
				m_lines.push_back(tabX(1) + "{");
				m_lines.push_back(tabX(2) + "if(" + "this->" + getMemberName(r) + " == NULL)");
				m_lines.push_back(tabX(3) + "this->" + getMemberName(r) + " = new " + getCppType(r) + "();");
				m_lines.push_back(tabX(2) + "return " + "this->" + getMemberName(r) + ";");
				m_lines.push_back(tabX(1) + "}");
				m_lines.push_back("");
			}
        }
    }

	std::string TableGenerator::getCppType(const std::string& type)
	{
		if(type == "bytes" || type == "string")
			return "std::string";
		return type;
	}
	std::string TableGenerator::getCppType( Field& r )
	{
		if(r.type == "bytes")
			return "std::string";
		
		std::string lenval;
		r.getLen(lenval);

		if(r.type ==  "string")
			if(lenval.length() > 0)
				return "pwutils::fixed_string<" + lenval + ">";
			else
				return "std::string";
		return r.type;
	}


	void ReflectionGenerator::genIncludeFile( std::vector<Table*>& tables,const std::string& outputdir )
	{
		m_lines.clear();
		m_lines.push_back("#ifndef _pw_orm_include_def_");
		m_lines.push_back("#define _pw_orm_include_def_");
	
		m_lines.push_back("");

		for(size_t i = 0; i < tables.size(); ++i)
		{
			Table* t = tables[i];
			m_lines.push_back("#include \"kvorm/pw_orm_" + stringToLower(t->name) + ".h\"");
		}

		m_lines.push_back("");
		m_lines.push_back("#endif // _pw_orm_include_def_");

		this->writeLinesToFile(outputdir + "/pw_orm_include.h");

		m_lines.clear();
	}

	void ReflectionGenerator::gen(std::vector<Table*>& tables,const std::string& outputdir)
	{
		std::set<std::string> masters;
		std::set<std::string> tablemasters;

		for(size_t i = 0; i < tables.size(); ++i)
		{
			Table* t = tables[i];
			Attrs* attr = t->find("slave");
			if( attr != NULL && !t->isIgnoreCollection())
			{
				if(attr->args.size() <= 0)
				{
					
					std::cout << "Error: slave attr need masterName" << t->name << std::endl;
					return ;
				}
				masters.insert(attr->args[0]);
			}

			attr = t->find("slave_table");
			if(attr != NULL && !t->isIgnoreCollection())
			{
				if(attr->args.size() <= 0)
				{
					std::cout << "Error: slave_table attr need masterName" << t->name << std::endl;
					return ;
				}
				tablemasters.insert(attr->args[0]);
			}
		}

		{
			m_lines.clear();
			m_lines.push_back("#ifndef __pw_orm_reflection__");
			m_lines.push_back("#define __pw_orm_reflection__");
			m_lines.push_back("");
			m_lines.push_back("#include \"kvdb/pw_kvorm.h\"");
			m_lines.push_back("");
			m_lines.push_back("namespace orm");
			m_lines.push_back("{");
			m_lines.push_back("");

			// slaveof
			for(std::set<std::string>::iterator iter = masters.begin(); iter != masters.end(); ++iter)
			{
				std::string& name = *iter;
				m_lines.push_back(tabX(1) + "extern const char* cst_slaves_of_" + name + "[];");
				m_lines.push_back(tabX(1) + "extern int64 cst_slaves_hash_of_" + name + "[];");
			}
			for(std::set<std::string>::iterator iter = tablemasters.begin(); iter != tablemasters.end(); ++iter)
			{
				std::string& name = *iter;
				m_lines.push_back(tabX(1) + "extern const char* cst_slave_tables_of_" + name + "[];");
				m_lines.push_back(tabX(1) + "extern int64 cst_slave_tables_hash_of_" + name + "[];");
			}

			m_lines.push_back("");

			m_lines.push_back(tabX(1) + "extern pwutils::KvormBase* createObject(bson::bo& __obj);");
			m_lines.push_back(tabX(1) + "extern pwutils::KvormBase* createObject(const char* __data,size_t __size);");
			m_lines.push_back("}");
			m_lines.push_back("");
			m_lines.push_back("#endif //__pw_orm_reflection__");

			this->writeLinesToFile(outputdir + "/pw_orm_reflection.h");
		}

		
		std::vector<std::string> slaves_lines;

		{
			m_lines.clear();
			m_lines.push_back("#include \"pw_utils.h\"");
			m_lines.push_back("#include \"pw_logger.h\"");
			m_lines.push_back("#include \"kvorm/pw_orm_reflection.h\"");
			for(size_t i = 0; i < tables.size(); ++i)
			{
				Table* t = tables[i];
				m_lines.push_back("#include \"kvorm/pw_orm_" + stringToLower(t->name) + ".h\"");
			}

			m_lines.push_back("");
			m_lines.push_back("namespace orm");
			m_lines.push_back("{");
			m_lines.push_back("");

			// slave of human
			for(std::set<std::string>::iterator iter = masters.begin(); iter != masters.end(); ++iter)
			{
				std::string& mname = *iter;

				int slavecount = 0;
				slaves_lines.clear();
				slaves_lines.push_back("__slave_of_" + stringToLower(mname) + "=[");

				m_lines.push_back(tabX(1) + "const char* cst_slaves_of_" + mname + "[] = {");
				for(size_t i = 0; i < tables.size(); ++i)
				{
					Table* t = tables[i];
					if(t->findAttrAndValue("slave",mname) && !t->isIgnoreReflectionDefine())
					{
						std::string name = stringToLower(t->name);
						if(Attrs* attr = t->find("name"))
							name = attr->args[0];

						m_lines.push_back(tabX(2) + "\"" + name + "\",");

						if(slavecount > 0)
							slaves_lines.push_back(",'" + name + "'");
						else
							slaves_lines.push_back("'" + name + "'");
						++slavecount;
					}
				}
				slaves_lines.push_back("]");
				writeLinesToFile("./orm_slave_" + stringToLower(mname) + ".js",&slaves_lines);

				m_lines.push_back(tabX(2) + "NULL");
				m_lines.push_back(tabX(1) + "};");
			}

			// slave hash of human
			for(std::set<std::string>::iterator iter = masters.begin(); iter != masters.end(); ++iter)
			{
				std::string& mname = *iter;

				m_lines.push_back(tabX(1) + "int64 cst_slaves_hash_of_" + mname + "[] = {");
				for(size_t i = 0; i < tables.size(); ++i)
				{
					Table* t = tables[i];
					if(t->findAttrAndValue("slave",mname) && !t->isIgnoreReflectionDefine())
					{
						std::string name = stringToLower(t->name);
						if(Attrs* attr = t->find("name"))
							name = attr->args[0];

						char hashbuf[1000] = "";
						INT64 hash = bkdr_hash_and_sum(name.c_str());
						::_i64toa(hash,hashbuf,10);

						m_lines.push_back(tabX(2) + "" + hashbuf + ",");
					}
				}
				m_lines.push_back(tabX(2) + "0LL");
				m_lines.push_back(tabX(1) + "};");
			}

			// slave of human table
			for(std::set<std::string>::iterator iter = tablemasters.begin(); iter != tablemasters.end(); ++iter)
			{
				std::string& mname = *iter;
				int slavecount = 0;

				slaves_lines.clear();
				slaves_lines.push_back("__slavetable_of_" + stringToLower(mname) + "=[");

				m_lines.push_back(tabX(1) + "const char* cst_slave_tables_of_" + mname + "[] = {");
				for(size_t i = 0; i < tables.size(); ++i)
				{
					Table* t = tables[i];
					if(t->findAttrAndValue("slave_table",mname) && !t->isIgnoreCollection())
					{
						std::string name = stringToLower(t->name);
						if(Attrs* attr = t->find("name"))
							name = attr->args[0];

						m_lines.push_back(tabX(2) + "\"" + name + "\",");
						if(slavecount > 0)
							slaves_lines.push_back(",'" + name + "'");
						else
							slaves_lines.push_back("'" + name + "'");
						++slavecount;
					}
				}
				slaves_lines.push_back("]");
				writeLinesToFile("./orm_slavetable_" + stringToLower(mname) + ".js",&slaves_lines);

				m_lines.push_back(tabX(2) + "NULL");
				m_lines.push_back(tabX(1) + "};");
			}

			// slave of human table hashs
			for(std::set<std::string>::iterator iter = tablemasters.begin(); iter != tablemasters.end(); ++iter)
			{
				std::string& mname = *iter;

				m_lines.push_back(tabX(1) + "int64 cst_slave_tables_hash_of_" + mname + "[] = {");
				for(size_t i = 0; i < tables.size(); ++i)
				{
					Table* t = tables[i];
					if(t->findAttrAndValue("slave_table",mname) && !t->isIgnoreCollection())
					{
						std::string name = stringToLower(t->name);
						if(Attrs* attr = t->find("name"))
							name = attr->args[0];

						char hashbuf[1000] = "";
						INT64 hash = bkdr_hash_and_sum(name.c_str());
						::_i64toa(hash,hashbuf,10);

						m_lines.push_back(tabX(2) + "" + hashbuf + ",");
					}
				}
				m_lines.push_back(tabX(2) + "NULL");
				m_lines.push_back(tabX(1) + "};");
			}

			m_lines.push_back("");
			m_lines.push_back(tabX(1) + "extern pwutils::KvormBase* createObject(const char* __data,size_t __size)");
			m_lines.push_back(tabX(1) + "{");
			m_lines.push_back(tabX(2) + "mongo::BSONObj __obj(__data);");
			m_lines.push_back(tabX(2) + "pwassertn(__obj.objsize() == __size);");
			m_lines.push_back(tabX(2) + "return createObject(__obj);");
			m_lines.push_back(tabX(1) + "}");

			m_lines.push_back(tabX(1) + "extern pwutils::KvormBase* createObject(bson::bo& __obj)");
			m_lines.push_back(tabX(1) + "{");
				m_lines.push_back(tabX(2) + "std::string metaname;");
				m_lines.push_back(tabX(2) + "mongo::BSONObjIterator iter(__obj);");
				m_lines.push_back(tabX(2) + "while(iter.more())");
				m_lines.push_back(tabX(2) + "{");
					m_lines.push_back(tabX(3) + "mongo::BSONElement __be = iter.next();");
					m_lines.push_back(tabX(3) + "if(pwutils::strcmp(__be.fieldName(),\"_T\") == 0)");
					m_lines.push_back(tabX(3) + "{");
						m_lines.push_back(tabX(4) + "metaname = __be.str();");
						m_lines.push_back(tabX(4) + "break;");
					m_lines.push_back(tabX(3) + "}");
				m_lines.push_back(tabX(2) + "}");
				m_lines.push_back(tabX(2) + "pwutils::KvormBase* result = NULL;");
				m_lines.push_back(tabX(2) + "int64 hash = pwutils::bkdr_hash_and_sum(metaname.c_str());");
				m_lines.push_back(tabX(2) + "switch(hash)");
				m_lines.push_back(tabX(2) + "{");

				for(size_t i = 0; i < tables.size(); ++i)
				{
					Table* t = tables[i];
					m_lines.push_back(tabX(2) + "case orm::" + t->name + "::meta_hash:");
					m_lines.push_back(tabX(3) + "result = new orm::" + t->name + "();");
					m_lines.push_back(tabX(3) + "break;");
				}
				
				m_lines.push_back(tabX(2) + "}");
				m_lines.push_back(tabX(2) + "if(result != NULL)");
				m_lines.push_back(tabX(3) + "result->from_bson(__obj);");
				m_lines.push_back(tabX(2) + "return result;");
			m_lines.push_back(tabX(1) + "}");
			m_lines.push_back("}");
			m_lines.push_back("");

			this->writeLinesToFile(outputdir + "/pw_orm_reflection.cpp");
		}
	}

	void ReflectionGenerator::writeLinesToFile(const std::string& filename,std::vector<std::string>* lines)
	{
		if(lines == NULL)
			lines = &m_lines;

		if(isSameLines(filename,*lines))
			return ;
		std::fstream f;
		f.open(filename.c_str(),std::ios_base::out | std::ios_base::trunc);

		for(size_t i = 0; i < lines->size(); ++i)
		{
			std::string& r = lines->at(i);
			f << r << std::endl;
		}
		f.flush();
	}

	void ReflectionGenerator::genCollection( std::vector<Table*>& tables,const std::string& outputdir )
	{
		m_lines.clear();

		std::set<std::string> masters;

		for(size_t i = 0; i < tables.size(); ++i)
		{
			Table* t = tables[i];
			Attrs* attr = NULL;

			attr = t->find("slave");
			if( attr != NULL && !t->isIgnoreCollection())
			{
				if(attr->args.size() <= 0)
				{

					std::cout << "Error: slave attr need masterName" << t->name << std::endl;
					return ;
				}
				masters.insert(attr->args[0]);

				if(t->findFiedHasAttr("masterid") == NULL)
				{
					std::cout << "Error: slave miss masterid field " << t->name << std::endl;
				}
			}

			attr = t->find("slave_table");
			if( attr != NULL && !t->isIgnoreCollection())
			{
				if(attr->args.size() <= 0)
				{
					std::cout << "Error: slave_table attr need masterName" << t->name << std::endl;
					return ;
				}
				masters.insert(attr->args[0]);

				if(t->findFiedHasAttr("masterid") == NULL)
				{
					std::cout << "Error: slave miss masterid field " << t->name << std::endl;
				}
				if(t->findFiedHasAttr("key") == NULL)
				{
					std::cout << "Error: slave miss key field " << t->name << std::endl;
				}

			}
		}

		for(std::set<std::string>::iterator iter = masters.begin();iter != masters.end(); ++iter)
		{
			std::string& m = *iter;
			genCollection(m,tables,outputdir);
		}
	}

	void ReflectionGenerator::genCollection( const std::string& master,std::vector<Table*>& tables,const std::string& outputdir )
	{
		std::string lmaster = stringToLower(master);
		std::string Wmaster = stringToLower(master);

		Table* tmaster = getTable(tables,master);
		assert(tmaster);

		Field* keyfield = tmaster->findFiedHasAttr("key");
		assert(keyfield);

		Wmaster[0] = std::toupper(Wmaster[0],std::locale());

		std::set<std::string> slaves;
		std::set<std::string> slavetables;
		
		//**************************************************************************************
		// hpp
		//**************************************************************************************
		{
			m_lines.push_back("#ifndef _pw_orm_collection_" + lmaster + "_");
			m_lines.push_back("#define _pw_orm_collection_" + lmaster + "_");
			m_lines.push_back("");
			m_lines.push_back("#include \"kvdb/pw_kvorm.h\"");
			m_lines.push_back("#include \"kvdb/pw_kvorm_array.h\"");
			m_lines.push_back("");
			m_lines.push_back("namespace orm");
			m_lines.push_back("{");
			m_lines.push_back("");

			// 插入自已
			slaves.insert(master);

			for(size_t i = 0; i < tables.size(); ++i)
			{
				Table* t = tables[i];
				if(t->findAttrAndValue("slave",master) && !t->isIgnoreCollection())
				{
					slaves.insert(t->name);
				}
				else if(t->findAttrAndValue("slave_table",master) && !t->isIgnoreCollection())
				{
					slavetables.insert(t->name);
				}
			}

			for(std::set<std::string>::iterator iter = slaves.begin();iter != slaves.end(); ++iter)
				m_lines.push_back(tabX(1) + "class " + *iter + ";");
			for(std::set<std::string>::iterator iter = slavetables.begin();iter != slavetables.end(); ++iter)
				m_lines.push_back(tabX(1) + "class " + *iter + ";");
			m_lines.push_back("");

			if(keyfield->isIntegerType())
				m_lines.push_back(tabX(1) + "class " + getClassName(Wmaster) + " : public pwutils::KvormCollectionInteger");
			else if(keyfield->isStringType())
				m_lines.push_back(tabX(1) + "class " + getClassName(Wmaster) + " : public pwutils::KvormCollectionString");

			m_lines.push_back(tabX(1) + "{");
			m_lines.push_back(tabX(1) + "public:");
			m_lines.push_back(tabX(2) + getClassName(Wmaster) + "();");
			m_lines.push_back(tabX(2) + "~" + getClassName(Wmaster) + "();");

			m_lines.push_back(tabX(1) + "public:");
			m_lines.push_back(tabX(2) + "void load(const char* __buf,size_t __len);");
			m_lines.push_back(tabX(2) + "void load(std::string& compressedBuf);");
			m_lines.push_back(tabX(2) + "void save(std::string& compressedBuf,size_t builderInitSize = 1*1024*1024);");
			m_lines.push_back(tabX(2) + "void save(mongo::BSONObjBuilder& __builder);");

			// visitor
			{
				m_lines.push_back(tabX(1) + "public:");
				m_lines.push_back(tabX(2) + "template<class VISITOR,class PARAM> void visit(VISITOR visitor,PARAM& param)");
				m_lines.push_back(tabX(2) + "{");
				
				for(std::set<std::string>::iterator iter = slaves.begin();iter != slaves.end(); ++iter)
				{					
					m_lines.push_back(tabX(3) + "if(!visitor(" + getMemberName(*iter,false) + ",param))" );
					m_lines.push_back(tabX(4) + "return ;" );
				}

				m_lines.push_back("");

				for(std::set<std::string>::iterator iter = slavetables.begin();iter != slavetables.end(); ++iter)
				{
					m_lines.push_back(tabX(3) + "for(pwutils::KvormObjectArray<" + *iter + "*>::iterator iter = "
						+ getMemberName(*iter,true) + ".begin(); iter != " + getMemberName(*iter,true) + ".end(); ++iter)");
					m_lines.push_back(tabX(3) + "{");
					m_lines.push_back(tabX(4) + "if(!visitor(*iter,param))");
					m_lines.push_back(tabX(5) + "return;");
					m_lines.push_back(tabX(3) + "}");
				}

				m_lines.push_back(tabX(2) + "}");
			}

			m_lines.push_back(tabX(1) + "public:");
			for(std::set<std::string>::iterator iter = slaves.begin();iter != slaves.end(); ++iter)
			{
				m_lines.push_back(tabX(2) + "" + *iter + "* " + stringToLower(*iter) + "() { return " + getMemberName(*iter,false) + "; }");
				m_lines.push_back(tabX(2) + "" + *iter + "* mutable_" + stringToLower(*iter) + "();");
				m_lines.push_back(tabX(2) + "void cleanup_" + stringToLower(*iter) + "();");
				m_lines.push_back("");
			}

			m_lines.push_back(tabX(1) + "public:");
			for(std::set<std::string>::iterator iter = slavetables.begin();iter != slavetables.end(); ++iter)
				m_lines.push_back(tabX(2) + "inline " + "pwutils::KvormObjectArray< " + *iter + "* >& " + stringToLower(*iter) + "() { return " + getMemberName(*iter,true) + "; }");

			m_lines.push_back(tabX(1) + "public:");
			for(std::set<std::string>::iterator iter = slavetables.begin();iter != slavetables.end(); ++iter)
			{
				m_lines.push_back(tabX(2) + "" + *iter + "* new_" + stringToLower(*iter) + "(bool manager = true);");
				m_lines.push_back(tabX(2) + "bool del_" + stringToLower(*iter) + "("+ *iter + "* value,bool freeIt = false);");
				m_lines.push_back(tabX(2) + "void load_" + stringToLower(*iter) + "(mongo::BSONObj& __obj);");
				m_lines.push_back(tabX(2) + "void save_" + stringToLower(*iter) + "(mongo::BSONArrayBuilder& __tmpbuilder);");
				m_lines.push_back("");
			}			
			
			m_lines.push_back(tabX(1) + "private:");
			for(std::set<std::string>::iterator iter = slaves.begin();iter != slaves.end(); ++iter)
				m_lines.push_back(tabX(2) + "" + *iter + "* " + getMemberName(*iter,false) + ";");

			m_lines.push_back(tabX(1) + "private:");
			for(std::set<std::string>::iterator iter = slavetables.begin();iter != slavetables.end(); ++iter)
				m_lines.push_back(tabX(2) + "pwutils::KvormObjectArray<" + *iter + "* > " + getMemberName(*iter,true) + ";");

			m_lines.push_back(tabX(1) + "};");

			m_lines.push_back("}");
			m_lines.push_back("");
			m_lines.push_back("#endif // _pw_orm_collection_" + lmaster + "_");
		}

		this->writeLinesToFile(outputdir + "/pw_orm_collection_" + lmaster + ".h");

		//**************************************************************************************

		m_lines.clear();

		//**************************************************************************************
		//**************************************************************************************
		// cpp
		//**************************************************************************************
		{
			m_lines.push_back("#include \"kvorm/pw_orm_collection_" + lmaster + ".h\"");
			m_lines.push_back("#include \"pw_logger.h\"");
			m_lines.push_back("#include \"pw_utils.h\"");
			m_lines.push_back("#include \"snappy/snappy.h\"");
			m_lines.push_back("");

			for(std::set<std::string>::iterator iter = slaves.begin();iter != slaves.end(); ++iter)
				m_lines.push_back("#include \"kvorm/pw_orm_" + stringToLower(*iter) + ".h\"");
			for(std::set<std::string>::iterator iter = slavetables.begin();iter != slavetables.end(); ++iter)
				m_lines.push_back("#include \"kvorm/pw_orm_" + stringToLower(*iter) + ".h\"");

			m_lines.push_back("");
			m_lines.push_back("namespace orm");
			m_lines.push_back("{");
			m_lines.push_back("");

			// 	m_lines.push_back(tabX(2) + "void load(const char* __buf,size_t len);");
			//	m_lines.push_back(tabX(2) + "void load(std::string& compressedBuf);");
			//	m_lines.push_back(tabX(2) + "void save(std::string& compressedBuf);");
			{
				m_lines.push_back(tabX(1) + "void " + getClassName(Wmaster) + "::load(std::string& compressedBuf)");
				m_lines.push_back(tabX(1) + "{");
				m_lines.push_back(tabX(2) + "std::string tmpbuf;");
				m_lines.push_back(tabX(2) + "snappy::Uncompress(compressedBuf.c_str(),compressedBuf.length(),&tmpbuf);");
				m_lines.push_back(tabX(2) + "this->load(tmpbuf.c_str(),tmpbuf.length());");
				m_lines.push_back(tabX(1) + "}");
				m_lines.push_back("");

				// --------------------------------------------------------------------------

				m_lines.push_back(tabX(1) + "void " + getClassName(Wmaster) + "::load(const char* __buf,size_t __len)");
				m_lines.push_back(tabX(1) + "{");

				m_lines.push_back(tabX(2) + "mongo::BSONObj __obj(__buf);");
				m_lines.push_back(tabX(2) + "pwassert(__obj.objsize() == __len);");
				m_lines.push_back("");

				m_lines.push_back(tabX(2) + "mongo::BSONObjIterator iter(__obj);");
				m_lines.push_back(tabX(2) + "while(iter.more())");
				m_lines.push_back(tabX(2) + "{");
					m_lines.push_back(tabX(3) + "mongo::BSONElement __be = iter.next();");
					m_lines.push_back(tabX(3) + "pwassertop(__be.isABSONObj(),continue);");
					m_lines.push_back(tabX(3) + "mongo::BSONObj __tmpobj = __be.Obj();");

					m_lines.push_back(tabX(3) + "int64 hash = pwutils::bkdr_hash_and_sum(__be.fieldName());");
					m_lines.push_back(tabX(3) + "switch(hash)");
					m_lines.push_back(tabX(3) + "{");

					for(std::set<std::string>::iterator iter = slaves.begin();iter != slaves.end(); ++iter)
					{
						std::string& sname = *iter;
						std::string lowname = stringToLower(*iter);
						char hashbuf[1000] = "";
						INT64 hash = bkdr_hash_and_sum(lowname.c_str());
						::_i64toa(hash,hashbuf,10);

						m_lines.push_back(tabX(3) + "case " + hashbuf + ": // " + sname);
						m_lines.push_back(tabX(4) + "{");
						m_lines.push_back(tabX(5) + "mutable_" + stringToLower(sname) + "()->from_bson(__tmpobj);");
						m_lines.push_back(tabX(4) + "}");
						m_lines.push_back(tabX(4) + "break;");
					}

					for(std::set<std::string>::iterator iter = slavetables.begin();iter != slavetables.end(); ++iter)
					{
						std::string& sname = *iter;
						std::string lowname = stringToLower(*iter);
						char hashbuf[1000] = "";
						INT64 hash = bkdr_hash_and_sum(lowname.c_str());
						::_i64toa(hash,hashbuf,10);

						m_lines.push_back(tabX(3) + "case " + hashbuf + ": // " + sname);
						m_lines.push_back(tabX(4) + "{");
						m_lines.push_back(tabX(5) + "load_" + stringToLower(sname) + "(__tmpobj);");
						m_lines.push_back(tabX(4) + "}");
						m_lines.push_back(tabX(4) + "break;");
					}

					// default
					m_lines.push_back(tabX(3) + "default:");
					m_lines.push_back(tabX(4) + "{");
					m_lines.push_back(tabX(5) + "pwasserte(false && \"invalid metahash\");");
					m_lines.push_back(tabX(4) + "}");
					m_lines.push_back(tabX(4) + "break;");

					m_lines.push_back(tabX(3) + "}");
				m_lines.push_back(tabX(2) + "}");
				m_lines.push_back(tabX(1) + "}");
				m_lines.push_back("");


				m_lines.push_back(tabX(1) + "void " + getClassName(Wmaster) + "::save(std::string& compressedBuf,size_t builderInitSize)");
				m_lines.push_back(tabX(1) + "{");
				m_lines.push_back(tabX(2) + "mongo::BSONObjBuilder __builder(builderInitSize);");
				m_lines.push_back(tabX(2) + "save(__builder);");
				m_lines.push_back(tabX(2) + "mongo::BSONObj __tmpobj = __builder.obj();");
				m_lines.push_back(tabX(2) + "snappy::Compress(__tmpobj.objdata(),__tmpobj.objsize(),&compressedBuf);");
				m_lines.push_back(tabX(1) + "}");
				m_lines.push_back("");

				// --------------------------------------------------------------------------

				m_lines.push_back(tabX(1) + "void " + getClassName(Wmaster) + "::save(mongo::BSONObjBuilder& __builder)");
				m_lines.push_back(tabX(1) + "{");

				for(std::set<std::string>::iterator iter = slaves.begin();iter != slaves.end(); ++iter)
				{
					std::string& sname = *iter;
					m_lines.push_back(tabX(2) + "if(" + getMemberName(sname,false) + " != NULL)");
					m_lines.push_back(tabX(2) + "{");
					
					m_lines.push_back(tabX(3) + "mongo::BSONObj __tmpobj;");
					m_lines.push_back(tabX(3) + getMemberName(sname,false) + "->to_bson(__tmpobj);");
					m_lines.push_back(tabX(3) + "__builder.append(" + sname + "::meta(),__tmpobj);");

					m_lines.push_back(tabX(2) + "}");
					m_lines.push_back("");
				}

				for(std::set<std::string>::iterator iter = slavetables.begin();iter != slavetables.end(); ++iter)
				{
					std::string& sname = *iter;
					
					m_lines.push_back(tabX(2) + "{");
					m_lines.push_back(tabX(3) + "mongo::BSONArrayBuilder __tmpbuilder;");
					m_lines.push_back(tabX(3) + "this->save_" + stringToLower(sname) + "(__tmpbuilder);");
					m_lines.push_back(tabX(3) + "__builder.append(" + sname + "::meta(),__tmpbuilder.obj());");

					m_lines.push_back(tabX(2) + "}");
					m_lines.push_back("");
				}

				m_lines.push_back(tabX(1) + "}");
			}

			m_lines.push_back("");
			
			m_lines.push_back(tabX(1) + getClassName(Wmaster) + "::" + getClassName(Wmaster) + "()");
			m_lines.push_back(tabX(1) + "{");

			for(std::set<std::string>::iterator iter = slaves.begin();iter != slaves.end(); ++iter)
				m_lines.push_back(tabX(2) + getMemberName(*iter,false) + " = NULL;");

			m_lines.push_back(tabX(1) + "}");
			m_lines.push_back("");

			// -----------------------------------------------------------------

			m_lines.push_back(tabX(1) + getClassName(Wmaster) + "::~" + getClassName(Wmaster) + "()");
			m_lines.push_back(tabX(1) + "{");

			for(std::set<std::string>::iterator iter = slaves.begin();iter != slaves.end(); ++iter)
				m_lines.push_back(tabX(2) + "_safe_delete(" + getMemberName(*iter,false) + ");");
				// m_lines.push_back(tabX(2) + "_safe_unref(" + getMemberName(*iter,false) + ");");

			m_lines.push_back(tabX(1) + "}");
			m_lines.push_back("");

			// ---------------------------------------------------------------------

			for(std::set<std::string>::iterator iter = slaves.begin();iter != slaves.end(); ++iter)
			{
				m_lines.push_back(tabX(1) + "" + *iter + "* " + getClassName(Wmaster) + "::mutable_" + stringToLower(*iter) + "()");
				m_lines.push_back(tabX(1) + "{");
				m_lines.push_back(tabX(2) + "if(" + getMemberName(*iter,false) + " == NULL)");
				m_lines.push_back(tabX(2) + "{");
				m_lines.push_back(tabX(3) + getMemberName(*iter,false) + " = new " + *iter + "();");
				//m_lines.push_back(tabX(3) + getMemberName(*iter,false) + "->doref();");

				m_lines.push_back(tabX(3) + getMemberName(*iter,false) + "->set_masterid(" + getMasterKeyName(keyfield) + ");");
				m_lines.push_back(tabX(2) + "}");
				m_lines.push_back(tabX(2) + "return " + getMemberName(*iter,false) + ";");
				m_lines.push_back(tabX(1) + "}");
				m_lines.push_back("");
			}

			for(std::set<std::string>::iterator iter = slaves.begin();iter != slaves.end(); ++iter)
			{
				m_lines.push_back(tabX(1) + "void " + getClassName(Wmaster) + "::cleanup_" + stringToLower(*iter) + "()");
				m_lines.push_back(tabX(1) + "{");
				m_lines.push_back(tabX(2) + "_safe_delete(" + getMemberName(*iter,false) + ");");
				// m_lines.push_back(tabX(2) + "_safe_unref(" + getMemberName(*iter,false) + ");");
				m_lines.push_back(tabX(1) + "}");
				m_lines.push_back("");
			}

			for(std::set<std::string>::iterator iter = slavetables.begin();iter != slavetables.end(); ++iter)
			{
				m_lines.push_back(tabX(1) + "" + *iter + "* " + getClassName(Wmaster) + "::new_" + stringToLower(*iter) + "(bool manager)");
				m_lines.push_back(tabX(1) + "{");
				m_lines.push_back(tabX(2) + *iter + "* tmp = new " + *iter + "();");
				//m_lines.push_back(tabX(2) + "tmp->doref();");
				m_lines.push_back(tabX(2) + "tmp->set_masterid(" + getMasterKeyName(keyfield) + ");");
				m_lines.push_back(tabX(2) + "if(manager)");
				m_lines.push_back(tabX(3) + getMemberName(*iter,true) + ".push_back(tmp);");
				m_lines.push_back(tabX(2) + "return tmp;");
				m_lines.push_back(tabX(1) + "}");
				m_lines.push_back("");

				m_lines.push_back(tabX(1) + "bool " + getClassName(Wmaster) + "::del_" + stringToLower(*iter) + "("+ *iter + "* value,bool freeIt)");
				m_lines.push_back(tabX(1) + "{");
				m_lines.push_back(tabX(2) + "return " + getMemberName(*iter,true) + ".remove(value,freeIt);");
				m_lines.push_back(tabX(1) + "}");
				m_lines.push_back("");

				m_lines.push_back(tabX(1) + "void " + getClassName(Wmaster) + "::load_" + stringToLower(*iter) + "(mongo::BSONObj& __obj)");
				m_lines.push_back(tabX(1) + "{");
				m_lines.push_back(tabX(2) + getMemberName(*iter,true) + ".cleanup();");
				m_lines.push_back(tabX(2) + "mongo::BSONObjIterator iter(__obj);");
				m_lines.push_back(tabX(2) + "while(iter.more())");
				m_lines.push_back(tabX(2) + "{");
					m_lines.push_back(tabX(3) + "mongo::BSONElement __be = iter.next();");
					m_lines.push_back(tabX(3) + "pwassertop(__be.isABSONObj(),continue);");

					m_lines.push_back(tabX(3) + *iter + "* tmp = new_" + stringToLower(*iter) + "(true);");
					m_lines.push_back(tabX(3) + "tmp->from_bson(__be.Obj());");
				m_lines.push_back(tabX(2) + "}");

				m_lines.push_back(tabX(1) + "}");
				m_lines.push_back("");

				m_lines.push_back(tabX(1) + "void " + getClassName(Wmaster) + "::save_" + stringToLower(*iter) + "(mongo::BSONArrayBuilder& __tmpbuilder)");
				m_lines.push_back(tabX(1) + "{");
				m_lines.push_back(tabX(2) + "for(size_t i = 0; i < " + getMemberName(*iter,true) + ".size(); ++i)");
				m_lines.push_back(tabX(2) + "{");
				m_lines.push_back(tabX(3) + "mongo::BSONObj __tmpobj;");
				m_lines.push_back(tabX(3) + *iter + "* tmp = " + getMemberName(*iter,true) + "[i];");
				m_lines.push_back(tabX(3) + "tmp->to_bson(__tmpobj);");
				m_lines.push_back(tabX(3) + "__tmpbuilder.append(__tmpobj);");
				m_lines.push_back(tabX(2) + "}");
				m_lines.push_back(tabX(1) + "}");
				m_lines.push_back("");
			}

		}
		m_lines.push_back("}");

		this->writeLinesToFile(outputdir + "/pw_orm_collection_" + lmaster + ".cpp");
		m_lines.clear();
	}

	std::string TableGenerator::getMemberDataStr( Field& r )
	{
		std::string lenval;
		r.getLen(lenval);

		if(r.isStringType() && lenval.length() == 0)
			return getMemberName(r) + ".c_str()";
		return "&" + getMemberName(r);
	}

	std::string TableGenerator::getMemberSizeStr( Field& r )
	{
		std::string lenval;
		r.getLen(lenval);

		if(r.isStringType() && lenval.length() == 0)
			return getMemberName(r) + ".length()";

		if(lenval.length() > 0)
			return "sizeof(" + getMemberName(r) + ")";

		return "sizeof(" + getMemberName(r) + ")";
	}


}