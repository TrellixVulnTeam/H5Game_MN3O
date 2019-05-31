#ifndef PW_GDB_IDL_H
#define PW_GDB_IDL_H

#include <string>
#include <vector>

namespace gdb
{
    class Attrs
    {
    public:
        size_t linenum;
        std::string name;
        std::vector<std::string> args;
    };

    class Field
    {
    public:
        size_t linenum;
		size_t pos;
        std::string type;
        std::string name;
        std::string lowername;
        std::vector<Attrs> attrs;
    public:
		inline bool isValueType()
		{
			return this->find("value_type") != NULL;
		}

		inline bool IsBuiltType()
		{
			return isIntegerType() || isStringType() || isDecimalType() || type == "bytes" || type == "bool" || type == "char";
		}
		inline bool IsRawBaseType()
		{
			return IsBuiltType() && !IsContainer();
		}

		inline bool isBaseType()
		{
			return !this->isStruct() && !this->isHashmap() && !this->isArray() && !isValueType();
		}

		inline bool isKey()
		{
			return this->find("key") != NULL;
		}

		inline bool isIntegerType()
		{
			return this->type.find("int") != std::string::npos;
		}

		inline bool isDecimalType()
		{
			return this->type.find("float") != std::string::npos
			|| this->type.find("double") != std::string::npos;
		}

		inline bool isStringType()
		{
			return this->type.find("string") != std::string::npos;
		}

		inline bool isBinary()
		{
			return this->find("binary") != NULL;
		}
		inline bool isArray()
        {
            return this->find("array") != NULL;
        }

		inline bool isHashmap()
		{
			return this->find("hashmap") != NULL;
		}

		inline bool isStruct()
		{
			return this->find("struct") != NULL;
		}

		inline bool isSimpleStruct()
		{
			return isStruct() && !IsContainer() && !isValueType();
		}

		inline bool IsContainer()
		{
			return this->isArray() || isHashmap();
		}

		inline bool isStaticArray()
		{
			return this->find("array") != NULL && this->find("len") != NULL;
		}

		inline void getLen(std::string& lenval)
		{
			Attrs* b = this->find("len");
			if(b)
				lenval = b->args[0];
		}

		std::string getDefaultMemberName()
		{
// 			if(isValueType() || IsRawBaseType())
				return std::string("").append(lowername);

// 			return "m_" + lowername;
		}
		std::string getDefaultValue()
		{
			if(isIntegerType())
				return "0";
			if(isDecimalType())
				return "0.0f";
			if(isStringType())
				return "\"\"";
			if(type == "bool")
				return "false";
			if(type == "char")
				return "0";
			return "";
		}

        std::vector<std::string>& getOldNames()
        {
            static std::vector<std::string> sv_empty;

            Attrs* a = this->find("oldname");
            if(a != NULL)
                return a->args;
            return sv_empty;
        }
    public:
        Attrs* find(const std::string& name);
		int findAsInteger(const std::string& name,int nullval);
		std::string findAttrValue(const std::string& name,size_t pos = 0,const std::string& errorReturn = "ERROR_findAttrValue");

		bool isHashmapIntegerKey();
    };

    class Table
    {
    public:
        ~Table();
    public:
        std::string name;
        std::vector<Attrs> attrs;
        std::vector<Field*> fields;
	public:
		bool isSlave();
		bool isSlaveTable();
		bool isIgnoreCollection();
		bool isIgnoreReflectionDefine();
	public:
		Attrs* find(const std::string& name);
		Attrs* findAttrAndValue(const std::string& name,const std::string& value);
		Field* findField(const std::string& name);
		Field* findAutoIncrField();
		Field* findFiedHasAttr(const std::string& attr);
		bool isValueType();
    };

}
#endif // PW_GDB_IDL_H
