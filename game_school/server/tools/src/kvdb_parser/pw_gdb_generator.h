#ifndef PW_GDB_GENERATOR_H
#define PW_GDB_GENERATOR_H

#include "pw_gdb_idl.h"

namespace gdb
{
    class TableGenerator
    {
        enum
        {
            T_NIL,T_I32,T_I64,T_STR,T_BUF,T_DEC,T_ARRAY,T_HASHMAP,
        };
    public:
        void gen(Table* t,const std::string& outputdir);
    protected:
        void genHpp(Table* t,const std::string& outputdir);
        void genHppFields(Table* t);
        void genHppFieldsGetterSetter(Table* t);
    protected:
        void genCpp(Table* t,const std::string& outputdir);
        void genCppFieldsBsonOpers(Table* t);

		void genCpp_ToBsonLightWeight(Table* t);
		void genCpp_FromBsonLightWeight(Table* t);

		void genCpp_ToBson(Table* t);
		void genCpp_FromBson(Table* t);
        void genCppFieldsGetterSetter(Table* t);
    protected:
		std::string getMemberAndType(Field& r);

		std::string getCppType(Field& r);
		std::string getCppType(const std::string& type);

		std::string getStoreTypeName(Field& r);
// 
        std::string getStoreElementTypeName(Field& r);
        std::string getGetterTypeName(Field& r);

        std::string getSetterTypeName(Field& r);
        std::string getTypeNameDefaultValue(Field& r);
        std::string getMemberName(Field& r);
		std::string getMemberDataStr(Field& r);
		std::string getMemberSizeStr(Field& r);
        int getBaseType(Field& r);
    protected:
        void writeLinesToFile(const std::string& filename);
    protected:
        std::vector<std::string> m_lines;
    };

	class ReflectionGenerator
	{
	public:
		void gen(std::vector<Table*>& tables,const std::string& outputdir);
		void genIncludeFile(std::vector<Table*>& tables,const std::string& outputdir);

		void writeLinesToFile(const std::string& filename,std::vector<std::string>* lines = NULL);
		void genCollection(std::vector<Table*>& tables,const std::string& outputdir);
		void genCollection(const std::string& master,std::vector<Table*>& tables,const std::string& outputdir);

		std::string getClassName(const std::string& v)
		{
			return v + "Collection";
		}
		std::string getMemberName(const std::string& v,bool slavetables) 
		{ 
			if(slavetables)
				return std::string("m_v") + v; 
			return std::string("m_p") + v; 
		}

		Table* getTable(std::vector<Table*>& tables,const std::string& name)
		{
			for(size_t i = 0; i < tables.size(); ++i)
			{
				if(tables[i]->name == name)
					return tables[i];
			}
			return NULL;
		}

		std::string getMasterKeyName(Field* keyfield)
		{
			if(keyfield->isStringType())
				return "m_vMasterId.c_str()";
			return "m_vMasterId";
		}
	protected:
		std::vector<std::string> m_lines;
	};

	extern std::vector<Table*> g_objAllTables;
}
#endif // PW_GDB_GENERATOR_H
