#include "pwdist_lexer.h"
#include "pwdist.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define OUT_PATH "../../server/"
//#define OUT_PATH "./out/"

const int cst_max_attr_num = 100;

struct s_attribute
{
	char name[50];
	char value[100];
};

struct s_method_parameter
{
	int type;
	char name[100];
	int is_result;
	int is_optional;
};

struct s_method
{
	char name[100];
	struct s_method_parameter params[10];
	long num_params;
};

struct s_object
{
	char name[100];
	char parent[100];

	struct s_method methods[200];
	long num_method;

	struct s_attribute attrs[10];
	long num_attr;
};

struct s_namespace
{
	char name[100];

	struct s_attribute attrs[10];
	long num_attr;

	struct s_object objects[100];
	long num_object;
};

struct s_global
{
	struct s_namespace* nm[20];
	long num_nm;
};


static struct s_global global = {0};
static struct s_attribute* g_curr_attrs = 0;
static int g_attr_num = 0;


void strreplace(char* buf,const char* tofind,const char* toreplace);

struct s_namespace* curr_nm()
{
	return global.nm[global.num_nm - 1];
}

struct s_object* curr_obj()
{
	struct s_namespace* nm = curr_nm();
	return &nm->objects[nm->num_object - 1];
}

struct s_method* curr_method()
{
	struct s_object* obj = curr_obj();
	return &obj->methods[obj->num_method - 1];
}
// ----------------------------------------

int strsum(const char* name)
{
	int result = 0;
	while(*name != 0)
	{
		result += *name;
		++name;
	}
	return result;
}

const char* get_method_real_name(struct s_object* obj,struct s_method* method)
{
	static char s_name[1024] = "";
	
	s_name[0] = 0;

	sprintf(s_name,"%s@%d",method->name,strsum(obj->name));

	return s_name;
}
// ----------------------------------------

void init_attr()
{
	if(g_curr_attrs == 0)
		g_curr_attrs = (struct s_attribute*)calloc(sizeof(struct s_attribute), cst_max_attr_num);
}

void exit_attr()
{
	g_attr_num = 0;
}

void on_attr(const char* name,const char* value)
{
	struct s_attribute* cur = 0;
	init_attr();

	cur = &g_curr_attrs[g_attr_num];
	g_attr_num++;

	strcpy(cur->name,name);
	strcpy(cur->value,value);
	strreplace(cur->value,"\"","");
//	printf("attr name=%s value=%s\n",name,value);
}


void on_namespace_began(const char* name)
{
	struct s_namespace* nm = (struct s_namespace*)calloc(1,sizeof(struct s_namespace));
	strcpy(nm->name,name);

	nm->num_attr = g_attr_num;
	memcpy(nm->attrs,g_curr_attrs,sizeof(struct s_attribute) * g_attr_num);
	exit_attr();

	global.nm[global.num_nm] = nm;
	global.num_nm++;
	
//	printf("namespace began=%s\n",name);
}

void on_namespace_ended()
{
//	printf("namespace ended\n");
}

void on_object_began(const char* name,const char* parent)
{
	struct s_namespace* nm = 0;
	struct s_object* obj = 0;

	nm = curr_nm();
	nm->num_object ++;

	obj = curr_obj();	
	
	strcpy(obj->name,name);
	strcpy(obj->parent,parent);

	obj->num_attr = g_attr_num;
	memcpy(obj->attrs,g_curr_attrs,sizeof(struct s_attribute) * g_attr_num);
	exit_attr();

//	printf("\tobject began=%s\n",name);
}

void on_object_ended()
{
//	printf("\tobject ended\n");
}

void on_method_began(const char* name)
{
	struct s_object* obj = 0;
	struct s_method* m = 0;

	obj = curr_obj();
	obj->num_method++;
	m = curr_method();

	strcpy(m->name,name);

// 	printf("\t\tmethod began %s\n",name);
}

void on_method_ended()
{
// 	printf("\t\tmethod ended\n");
}

void on_method_param(int type,const char* name,int return_params,int optional)
{
	struct s_method* m = curr_method();
	struct s_method_parameter* p = &m->params[m->num_params];
	m->num_params ++;

	p->type = type;
	strcpy(p->name,name);
	p->is_result = return_params;
	p->is_optional = optional;
	
// 	if(!return_params)
// 	{
// 		printf("\t\t\t params type=%d name=%s optional=%d\n",type,name,optional);	
// 	}
// 	else
// 	{
// 		printf("\t\t\t return type=%d name=%s optional=%d\n",type,name,optional);	
// 	}
	
}

void print_method(struct s_method* method)
{
	int i = 0;
	printf("\t\tmethod %s\n",method->name);
	for(i = 0; i < method->num_params; ++i)
	{
		struct s_method_parameter* p = &method->params[i];
		printf("\t\t\t %s type=%d name=%s optional=%d \n",
			p->is_result ? "return" : "params",
			p->type,p->name,p->is_optional);
	}
}

void print_object(struct s_object* obj)
{
	int i = 0;

	for(i = 0; i < obj->num_attr; ++i)
	{
		printf("\tattr %s=%s\n",obj->attrs[i].name,obj->attrs[i].value);
	}
	printf("\tobject %s \n",obj->name);
	for(i = 0; i < obj->num_method; ++i)
	{
		print_method(&obj->methods[i]);
	}
	printf("\tobject end \n");
	
}

void print_namespace(struct s_namespace* nm)
{
	int i = 0;
		
	for(i = 0; i < nm->num_attr; ++i)
	{
		printf("attr %s=%s\n",nm->attrs[i].name,nm->attrs[i].value);
	}
	printf("namespace beg %s\n",nm->name);
	for(i = 0; i < nm->num_object; ++i)
	{
		print_object(&nm->objects[i]);
	}
	printf("namespace end\n",nm->name);
}

// --------------------------------------------------------------------------------------------------------

void gen_rpc_names2(struct s_namespace* nm,FILE* f)
{
	int i = 0;
	int j = 0;
	int k = 0;
	struct s_object* obj = 0;
	struct s_method* method = 0;
	struct s_method_parameter* param = 0;

	fprintf(f,"\tnamespace %s\n",nm->name);
	fprintf(f,"\t{\n");

	for(i = 0; i < nm->num_object; ++i)
	{
		obj = &nm->objects[i];
		fprintf(f,"\t\t namespace %s\n",obj->name);
		fprintf(f,"\t\t {\n");
		for(j = 0; j < obj->num_method; ++j)
		{
			method = &obj->methods[j];
			fprintf(f,"\t\t\t const char %s[] = \"%s\";\n",method->name,get_method_real_name(obj,method));
		}
		fprintf(f,"\t\t }\n");
	}
	fprintf(f,"\t}\n");
}

void gen_rpc_names_keywords_lua(struct s_namespace* nm,FILE* f)
{
	int i = 0;
	int j = 0;
	int k = 0;
	struct s_object* obj = 0;
	struct s_method* method = 0;
	struct s_method_parameter* param = 0;
	char tmpname[200] = "";

	for(i = 0; i < nm->num_object; ++i)
	{
		obj = &nm->objects[i];

		for(j = 0; j < obj->num_method; ++j)
		{
			method = &obj->methods[j];
			strcpy(tmpname,method->name);
			strreplace(tmpname,"_rpc_call_","");
			fprintf(f,"pwngs_rpcnames.%s.%s.%s\n",nm->name,obj->name,tmpname);
		}
	}
}

void gen_rpc_names_lua(struct s_namespace* nm,FILE* f)
{
	int i = 0;
	int j = 0;
	int k = 0;
	struct s_object* obj = 0;
	struct s_method* method = 0;
	struct s_method_parameter* param = 0;
	char tmpname[200] = "";

	fprintf(f,"\n");
	fprintf(f,"pwngs_rpcnames.%s = {}\n",nm->name);
	
	for(i = 0; i < nm->num_object; ++i)
	{
		obj = &nm->objects[i];

		fprintf(f,"\n");
		fprintf(f,"pwngs_rpcnames.%s.%s = {}\n",nm->name,obj->name);
		for(j = 0; j < obj->num_method; ++j)
		{
			method = &obj->methods[j];
			strcpy(tmpname,method->name);
			strreplace(tmpname,"_rpc_call_","");
			fprintf(f,"pwngs_rpcnames.%s.%s.%s = '%s'\n",nm->name,obj->name,tmpname,get_method_real_name(obj,method));
		}
	}
}

void gen_rpc_names()
{
	int i = 0;
	FILE* f = fopen(OUT_PATH"libdefs/pw_rpc_names.h","w+");
	assert(f && "open file error");
	fprintf(f,"#ifndef _pw_rpc_names_\n");
	fprintf(f,"#define _pw_rpc_names_\n");
	fprintf(f,"\n\n");
	fprintf(f,"namespace rpcnames\n");
	fprintf(f,"{\n");
	for(i = 0; i < global.num_nm; ++i)
		gen_rpc_names2(global.nm[i],f);
	fprintf(f,"}\n");
	fprintf(f,"#endif //_pw_rpc_names_");
	fclose(f);



	f = fopen(OUT_PATH"bin/Lua/pwdist_rpcnames.lua","w+");
	assert(f && "open file error");
	fprintf(f,"pwngs_rpcnames = {}\n");
	for(i = 0; i < global.num_nm; ++i)
		gen_rpc_names_lua(global.nm[i],f);
	fclose(f);

	f = fopen(OUT_PATH"bin/Lua/pwdist_keywords.txt","w+");
	assert(f && "open file error");
	for(i = 0; i < global.num_nm; ++i)
		gen_rpc_names_keywords_lua(global.nm[i],f);
	fclose(f);
}

// --------------------------------------------------------------------------------------------------------

int get_attr(struct s_attribute* attrs,long num,const char* attr,char* result)
{
	int i;
	for(i = 0; i < num; ++i)
	{
		if(strcmp(attrs[i].name,attr) == 0)
		{
			strcpy(result,attrs[i].value);
			return 0;
		}
	}
	return -1;
}

// --------------------------------------------------------------------------------------------------------


void strreplace(char* buf,const char* tofind,const char* toreplace)
{
	int n = 0;
	int len = 0;
	int len2 = 0;
	char tmpbuf[10000] = {0};
	char* bufo = buf;
	char* find = 0;
	int len3 = strlen(buf);

	len = strlen(toreplace);
	len2 = strlen(tofind);

	while(1)
	{
		find = strstr(bufo,tofind);
		if(find == 0)
		{
			strcat(tmpbuf,bufo);
			break;
		}
		memcpy(&tmpbuf[n],bufo,find - bufo);
		n += find - bufo;
		memcpy(&tmpbuf[n],toreplace,len);
		n += len;

		bufo = find + len2;
	}
	
	buf[0] = 0;
	strcpy(buf,tmpbuf);
}

// --------------------------------------------------------------------------------------------------------

void strtolower(char* buf)
{
	int i;
	int k = strlen(buf);
	for(i = 0; i < k; ++i)
		buf[i] = tolower(buf[i]);
}

void gen_rpc_init2(struct s_namespace* nm)
{
	int i = 0;
	int j = 0;
	int k = 0;
	FILE* f = 0;
	char filename[200] = "";
	struct s_object* obj = 0;
	struct s_method* method = 0;
	struct s_method_parameter* param = 0;
	char attr_value[200] = "";
	char objname[100] = "";



	for(i = 0; i < nm->num_object; ++i)
	{
		obj = &nm->objects[i];
		strcpy(objname,obj->name);
		strtolower(objname);

		// ---------------------------------------------------------

		if(get_attr(nm->attrs,nm->num_attr,"file_initial",attr_value) == 0)
		{
			strreplace(attr_value,"{objname}",objname);
			strcpy(filename,attr_value);
		}
		else
		{
			sprintf(filename,"./pw_rpcs_impl_%s.cpp",obj->name);
		}

		f = fopen(filename,"w+");
		assert(f && "open file error");

		fprintf(f,"#include \"pwdist_port_generic.h\"\n");
		fprintf(f,"#include \"pw_rpc_names.h\"\n");

		// ---------------------------------------------------------

		if(get_attr(obj->attrs,obj->num_attr,"file_initial_include",attr_value) == 0)
		{
			fprintf(f,"#include \"%s\"\n",attr_value);
		}

		// ---------------------------------------------------------

		if(get_attr(obj->attrs,obj->num_attr,"ns",attr_value) == 0)
		{
			fprintf(f,"\n\n");
			fprintf(f,"namespace %s\n",attr_value);
			fprintf(f,"{\n");
		}
		else
		{
			fprintf(f,"\n\n");
			fprintf(f,"namespace pwngs\n");
			fprintf(f,"{\n");
		}

		// ---------------------------------------------------------


		// ---------------------------------------------------------

		fprintf(f,"\tint %s::InitialRpcs(pwdist::Port* port)\n",obj->name);
		fprintf(f,"\t{\n");

		for(j = 0; j < obj->num_method; ++j)
		{
			method = &obj->methods[j];
			fprintf(f,"\t\tport->Impl<%s>(rpcnames::%s::%s::%s,&%s::%s);\n",obj->name,nm->name,obj->name,method->name,obj->name,method->name);
		}
		fprintf(f,"\t\treturn 0;\n");
		fprintf(f,"\t}\n");
		fprintf(f,"}\n");
		fclose(f);
	}
	fprintf(f,"\t}\n");
}

// --------------------------------------------------------------------------------------------------------

void gen_rpc_init()
{
	int i = 0;

	for(; i < global.num_nm; ++i)
	{
		gen_rpc_init2(global.nm[i]);
	}
}

// --------------------------------------------------------------------------------------------------------

enum EParamsFlags
{
	PARAM_FLAGS_NORMAL = 0x01,
	PARAM_FLAGS_RESULT_REQ = 0x02,
	PARAM_FLAGS_RESULT_OPT = 0x04,
	PARAM_FLAGS_ALL = 0xff,
};

const char* get_param_type_name(int type)
{
	static char buf[100] = "";

	switch(type)
	{
	case K_TYPE_I32:
		strcpy(buf,"int32");
		break;
	case K_TYPE_I64:
		strcpy(buf,"int64");
		break;
	case K_TYPE_DEC:
		strcpy(buf,"double");
		break;
	case K_TYPE_STR:
		strcpy(buf,"const char*");
		break;
	case K_TYPE_BUF:
		strcpy(buf,"pwdist::Chunk");
		break;
	case K_TYPE_CHAR:
		strcpy(buf,"char");
		break;
	case K_TYPE_SHORT:
		strcpy(buf,"short");
		break;
	case K_TYPE_BOOL:
		strcpy(buf,"bool");
		break;
	case K_TYPE_STDSTR:
		strcpy(buf,"const std::string&");
		break;
	}
	return buf;
}

void gen_params_all(struct s_method* m, char* out,int flags)
{
	int i;
	struct s_method_parameter* param = 0;
	char buf[1000] = "";

	out[0] = '\0';
	for(i = 0; i < m->num_params; ++i)
	{
		param = &m->params[i];

		if(param->is_result)
		{

			if(param->is_optional)
			{
				if((flags & PARAM_FLAGS_RESULT_OPT) == 0)
					continue;
			}
			else if ((flags & PARAM_FLAGS_RESULT_REQ) == 0)
			{
				continue;	
			}
		}
		else
		{
			if((flags & PARAM_FLAGS_NORMAL) == 0)
				continue;
		}

		
		sprintf(buf,",%s %s",get_param_type_name(param->type),param->name);

		strcat(out,buf);
	}
}

int get_params_num(struct s_method* m, int flags)
{
	int i;
	int r = 0;
	struct s_method_parameter* param = 0;

	for(i = 0; i < m->num_params; ++i)
	{
		param = &m->params[i];

		if(param->is_result)
		{
			if(param->is_optional)
			{
				if((flags & PARAM_FLAGS_RESULT_OPT) == 0)
					continue;
			}
			else if ((flags & PARAM_FLAGS_RESULT_REQ) == 0)
			{
				continue;						}
		}
		else
		{
			if((flags & PARAM_FLAGS_NORMAL) == 0)
				continue;
		}

		++r;
	}
	return r;
}

void gen_params_val(struct s_method* m, char* out,int flags)
{
	int i;
	struct s_method_parameter* param = 0;
	char buf[1000] = "";

	out[0] = '\0';
	for(i = 0; i < m->num_params; ++i)
	{
		param = &m->params[i];
		
		if(param->is_result)
		{
			if(param->is_optional)
			{
				if((flags & PARAM_FLAGS_RESULT_OPT) == 0)
					continue;
			}
			else if ((flags & PARAM_FLAGS_RESULT_REQ) == 0)
			{
				continue;						}
			}
		else
		{
			if((flags & PARAM_FLAGS_NORMAL) == 0)
				continue;
		}

		sprintf(buf,",%s",param->name);
		strcat(out,buf);
	}
}

void gen_result_desc(struct s_method* m, char* out,int ctab)
{
	int i,j = 0;
	struct s_method_parameter* param = 0;
	char buf[1000] = "";
	char tab[20] = "";
	const char* strreq = "required";
	const char* stropt = "optional";

	for(i = 0; i < ctab; ++i)
		strcat(tab,"\t");

	out[0] = '\0';

	sprintf(buf,"%s//@result desc\n",tab);
	strcat(out,buf);

	for(i = 0; i < m->num_params; ++i)
	{
		param = &m->params[i];
		if(!param->is_result)
			continue;
		j++;
		
		sprintf(buf,"%s//@result %d, %s %s [%s]\n",tab,j,get_param_type_name(param->type),param->name,param->is_optional ? stropt : strreq);
		
		strcat(out,buf);
	}
}

// --------------------------------------------------------------------------------------------------------

struct s_object* get_parent(struct s_namespace* nm,struct s_object* obj)
{
	int i;
	if(strlen(obj->parent) <= 0)
		return 0;
	
	for(i = 0; i < nm->num_object; ++i)
	{
		if(strcmp(nm->objects[i].name,obj->parent) == 0)
			return &nm->objects[i];
	}
	return 0;
}

// --------------------------------------------------------------------------------------------------------

void gen_rpc_proxy_cpp(struct s_namespace* nm,FILE* fhpp)
{
	int i,j,k,m;
	struct s_object* obj = 0;
	struct s_method* method = 0;
	struct s_object* parent = 0;
	struct s_method_parameter* param = 0;
	
	char objname[200] = "";
	char conname[200] = "";
	char paramname[100] = "";

	char paramsbuf1[2000] = "";
	char paramsbuf2[2000] = "";
	char paramsbuf3[2000] = "";
	char paramsbuf4[2000] = "";
	char methodname[200] = "";

	fprintf(fhpp,"\t" "namespace %s\n",nm->name);
	fprintf(fhpp,"\t" "{\n\n");

	for(i = 0; i < nm->num_object; ++i)
	{
		obj = &nm->objects[i];

		sprintf(objname,"%sProxy",obj->name);

		parent = get_parent(nm,obj);
		if(parent == 0)
		{
			fprintf(fhpp,"\t\t" "%sProxy::%sProxy(pwdist::Port* port)\n",obj->name,obj->name);
			fprintf(fhpp,"\t\t\t" ":m_pPort(port)\n");
			fprintf(fhpp,"\t\t{\n");
            fprintf(fhpp,"\t\t\t""if(m_pPort == NULL)\n");
            fprintf(fhpp,"\t\t\t\t""m_pPort = pwdist::Port::self();\n");
			fprintf(fhpp,"\t\t}\n");
		}
		else
		{
			fprintf(fhpp,"\t\t" "%sProxy::%sProxy(pwdist::Port* port)\n",obj->name,obj->name);
			fprintf(fhpp,"\t\t\t" ": %sProxy(port)\n",parent->name);
			fprintf(fhpp,"\t\t{\n");
			fprintf(fhpp,"\t\t}\n");
		}

		if(parent == 0)
		{
			fprintf(fhpp,"\t\tint %s::_set_call_target(const char* node,const char* port,int64* specs,int64 nspecs)\n",objname);
			fprintf(fhpp,"\t\t{\n");
			fprintf(fhpp,"\t\t\treturn m_pPort->Prepare(node,port,specs,2);\n");
			fprintf(fhpp,"\t\t}\n");

			fprintf(fhpp,"\t\tint %s::_set_call_target(const std::string& node,const std::string& port,int64* specs,int64 nspecs)\n",objname);
			fprintf(fhpp,"\t\t{\n");
			fprintf(fhpp,"\t\t\treturn _set_call_target(node.c_str(),port.c_str(),specs,nspecs);\n");
			fprintf(fhpp,"\t\t}\n");

			fprintf(fhpp,"\t\tint %s::_set_call_target(const char* node,const char* port,int64 spec1,int64 spec2)\n",objname);
			fprintf(fhpp,"\t\t{\n");
			fprintf(fhpp,"\t\t\treturn m_pPort->Prepare(node,port,spec1,spec2);\n");
			fprintf(fhpp,"\t\t}\n");

			fprintf(fhpp,"\t\tint %s::_set_call_target(const char* node,const char* port,int64 spec1)\n",objname);
			fprintf(fhpp,"\t\t{\n");
			fprintf(fhpp,"\t\t\treturn m_pPort->Prepare2(node,port,spec1);\n");
			fprintf(fhpp,"\t\t}\n");

			fprintf(fhpp,"\t\tint %s::_set_call_target(const std::string& node,const std::string& port,int64 spec1)\n",objname);
			fprintf(fhpp,"\t\t{\n");
			fprintf(fhpp,"\t\t\treturn _set_call_target(node.c_str(),port.c_str(),spec1);\n");
			fprintf(fhpp,"\t\t}\n");

			// 			fprintf(fhpp,"\t\t\tint _set_call_target(const std::string& node,const std::string& port,int64 spec1)\n");
			// 				fprintf(fhpp,"\t\t\t{\n");
			// 					fprintf(fhpp,"\t\t\t\treturn _set_call_target(node.c_str(),port.c_str(),spec1);\n");
			// 				fprintf(fhpp,"\t\t\t}\n");


			fprintf(fhpp,"\t\tint %s::_set_call_target(const std::string& node,const std::string& port,int64 spec1,int64 spec2)\n",objname);
			fprintf(fhpp,"\t\t{\n");
			fprintf(fhpp,"\t\t\treturn _set_call_target(node.c_str(),port.c_str(),spec1,spec2);\n");
			fprintf(fhpp,"\t\t}\n");
		}

		for(j = 0; j < obj->num_method; ++j)
		{
			method = &obj->methods[j];
			gen_result_desc(method,paramsbuf1,3);
			fprintf(fhpp,"\n");
			fprintf(fhpp,"%s",paramsbuf1);

			gen_params_all(method,paramsbuf1,PARAM_FLAGS_NORMAL);
			gen_params_val(method,paramsbuf2,PARAM_FLAGS_NORMAL);
			fprintf(fhpp,"\t\tint %s::%s(pwdist::ICallableObject* caller%s)\n",objname,method->name,paramsbuf1);
			fprintf(fhpp,"\t\t{\n");
			fprintf(fhpp,"\t\t\tif(caller == 0)\n");
			fprintf(fhpp,"\t\t\t\tcaller = m_pPort;\n");
			fprintf(fhpp,"\t\t\treturn m_pPort->Call(caller,rpcnames::%s::%s::%s%s);\n",
				nm->name,obj->name,method->name,paramsbuf2);
			fprintf(fhpp,"\t\t}\n");
		}

		
		for(j = 0; j < obj->num_method; ++j)
		{
			method = &obj->methods[j];
			gen_result_desc(method,paramsbuf1,3);
			fprintf(fhpp,"\n");
			fprintf(fhpp,"%s",paramsbuf1);

			gen_params_all(method,paramsbuf1,PARAM_FLAGS_NORMAL);
			gen_params_val(method,paramsbuf2,PARAM_FLAGS_NORMAL);

			fprintf(fhpp,"\t\tint %s::_make%s(pwdist::MsgCall& call,pwdist::ICallableObject* caller%s)\n",objname,method->name,paramsbuf1);
			fprintf(fhpp,"\t\t{\n");
			fprintf(fhpp,"\t\t\tif(caller == NULL)\n");
			fprintf(fhpp,"\t\t\t\tcaller = m_pPort;\n");
			fprintf(fhpp,"\t\t\tm_pPort->MakeCall(call,caller,rpcnames::%s::%s::%s%s);\n",
				nm->name,obj->name,method->name,paramsbuf2);
			fprintf(fhpp,"\t\t\treturn 0;\n");
			fprintf(fhpp,"\t\t}\n");

			// 				fprintf(fhpp,"\t\t\tint _make%s(pwdist::MsgCall& call,ICallableObject* caller,int64* spec,int num_spec%s)\n",method->name,paramsbuf1);
			// 				fprintf(fhpp,"\t\t\t{\n");
			// 				fprintf(fhpp,"\t\t\t\treturn m_pPort->MakeCall(call,caller,spec,num_spec,rpcnames::%s::%s::%s%s);\n",
			// 					nm->name,obj->name,method->name,paramsbuf2);
			// 				fprintf(fhpp,"\t\t\t}\n");

		}
		
		for(j = 0; j < obj->num_method; ++j)
		{
			method = &obj->methods[j];

			if(get_params_num(method,PARAM_FLAGS_RESULT_REQ | PARAM_FLAGS_RESULT_OPT) == 0)
				continue;

			strcpy(methodname,method->name);
			strreplace(methodname,"_rpc_call","");
			sprintf(conname,"CON%s",methodname);

			fprintf(fhpp,"\t\t" "// -------------------------------------" "\n");
			fprintf(fhpp,"\t\t" "//  %s" "\n",method->name);
			fprintf(fhpp,"\t\t" "// -------------------------------------" "\n");

			fprintf(fhpp,"\t\t" "%s::%s::%s(pwdist::Port* port)" "\n",objname,conname,conname);
			fprintf(fhpp,"\t\t" ": m_pPort(port)" "\n");
			fprintf(fhpp,"\t\t" "{" "\n");
			fprintf(fhpp,"\t\t\t""if(m_pPort == NULL)\n");
			fprintf(fhpp,"\t\t\t\t""m_pPort = pwdist::Port::self();\n");
			fprintf(fhpp,"\t\t" "}" "\n");

			if(get_params_num(method,PARAM_FLAGS_RESULT_REQ) > 0)
			{
				gen_params_all(method,paramsbuf1,PARAM_FLAGS_RESULT_REQ);
				gen_params_val(method,paramsbuf2,PARAM_FLAGS_RESULT_REQ);

				strcpy(paramsbuf3,&paramsbuf1[1]); //
				strcpy(paramsbuf4,&paramsbuf2[1]); //

				fprintf(fhpp,"\t\t" "int %s::%s::Return(%s)" "\n",objname,conname,paramsbuf3);
				fprintf(fhpp,"\t\t" "{" "\n");
				fprintf(fhpp,"\t\t\t" "return m_pPort->Return(%s);" "\n",paramsbuf4);
				fprintf(fhpp,"\t\t" "}" "\n");
				fprintf(fhpp,"\t\t" "" "\n");

				fprintf(fhpp,"\t\t" "int %s::%s::ReturnAsyncEx(int64 pid%s)" "\n",objname,conname,paramsbuf1);
				fprintf(fhpp,"\t\t" "{" "\n");
				fprintf(fhpp,"\t\t\t" "return m_pPort->AsyncReturn(pid%s);" "\n",paramsbuf2);
				fprintf(fhpp,"\t\t" "}" "\n");
				fprintf(fhpp,"\t\t" "" "\n");

				fprintf(fhpp,"\t\t" "int %s::%s::CancelAsyncReturn(int64 pid)" "\n",objname,conname);
				fprintf(fhpp,"\t\t" "{" "\n");
				fprintf(fhpp,"\t\t\t" "return m_pPort->AsyncReturnCancel(pid);" "\n");
				fprintf(fhpp,"\t\t" "}" "\n");
				fprintf(fhpp,"\t\t" "" "\n");
			}

			if(get_params_num(method,PARAM_FLAGS_RESULT_OPT) > 0)
			{
				gen_params_all(method,paramsbuf1,PARAM_FLAGS_RESULT_REQ | PARAM_FLAGS_RESULT_OPT);
				gen_params_val(method,paramsbuf2,PARAM_FLAGS_RESULT_REQ | PARAM_FLAGS_RESULT_OPT);

				strcpy(paramsbuf3,&paramsbuf1[1]); 
				strcpy(paramsbuf4,&paramsbuf2[1]); 

				fprintf(fhpp,"\t\t" "int %s::%s::Return(%s)" "\n",objname,conname,paramsbuf3);
				fprintf(fhpp,"\t\t" "{" "\n");
				fprintf(fhpp,"\t\t\t" "return m_pPort->Return(%s);" "\n",paramsbuf4);
				fprintf(fhpp,"\t\t" "}" "\n");
				fprintf(fhpp,"\t\t" "" "\n");

				fprintf(fhpp,"\t\t" "int %s::%s::ReturnAsyncEx(int64 pid%s)" "\n",objname,conname,paramsbuf1);
				fprintf(fhpp,"\t\t" "{" "\n");
				fprintf(fhpp,"\t\t\t" "return m_pPort->AsyncReturn(pid%s);" "\n",paramsbuf2);
				fprintf(fhpp,"\t\t" "}" "\n");
				fprintf(fhpp,"\t\t" "" "\n");
			}

			m = 0;
			for(k = 0; k < method->num_params; ++k)
			{
				param = &method->params[k];

				if(!param->is_result)
					continue;

				strcpy(paramname,param->name);
				strtolower(paramname);
				paramname[0] = toupper(paramname[0]);

				fprintf(fhpp,"\t\t""%s %s::%s::GetResult%s(pwdist::FutureObject& f)\n",get_param_type_name(param->type),objname,conname,paramname);
				fprintf(fhpp,"\t\t""{\n");
				fprintf(fhpp,"\t\t\t""return f.Get<%s>(%d);\n",get_param_type_name(param->type),m);
				fprintf(fhpp,"\t\t""}\n");

				++m;
			}
			fprintf(fhpp,"\t\t" "" "\n");
		}
		fprintf(fhpp,"\n");
	}

	fprintf(fhpp,"\t}\n");
	fprintf(fhpp,"\n");
}

void gen_rpc_proxy_hpp(struct s_namespace* nm,FILE* fhpp)
{
	int i,j,k,m;
	struct s_object* obj = 0;
	struct s_method* method = 0;
	struct s_object* parent = 0;
	struct s_method_parameter* param = 0;

	char paramname[100] = "";

	char paramsbuf1[2000] = "";
	char paramsbuf2[2000] = "";
	char paramsbuf3[2000] = "";
	char paramsbuf4[2000] = "";
	char methodname[200] = "";

	fprintf(fhpp,"\tnamespace %s\n",nm->name);
	fprintf(fhpp,"\t{\n");


	for(i = 0; i < nm->num_object; ++i)
	{
		obj = &nm->objects[i];
	
		fprintf(fhpp,"\t\t// *********************************\n");
		fprintf(fhpp,"\t\t// rpc ProxyClass %s\n",obj->name);
		fprintf(fhpp,"\t\t// *********************************\n");

		parent = get_parent(nm,obj);
		if(parent == 0)
		{
			fprintf(fhpp,"\t\tclass %sProxy\n",obj->name);
			fprintf(fhpp,"\t\t{\n");
			fprintf(fhpp,"\t\tpublic:\n");
			fprintf(fhpp,"\t\t\t%sProxy(pwdist::Port* port = NULL);\n",obj->name);
		}
		else
		{
			fprintf(fhpp,"\t\tclass %sProxy : public %sProxy\n",obj->name,parent->name);
			fprintf(fhpp,"\t\t{\n");
			fprintf(fhpp,"\t\tpublic:\n");
			fprintf(fhpp,"\t\t\t%sProxy(pwdist::Port* port = NULL);\n",obj->name);
		}

		if(parent == 0)
		{
			fprintf(fhpp,"\t\tpublic:\n");
			fprintf(fhpp,"\t\t\tinline pwdist::Port* port()\n");
			fprintf(fhpp,"\t\t\t{\n");
			fprintf(fhpp,"\t\t\t\t" "return m_pPort;\n");
			fprintf(fhpp,"\t\t\t}\n");
			fprintf(fhpp,"\t\tpublic:\n");

			fprintf(fhpp,"\t\t\tint _set_call_target(const char* node,const char* port,int64* specs,int64 nspecs);\n");
			
			fprintf(fhpp,"\t\t\tint _set_call_target(const std::string& node,const std::string& port,int64* specs,int64 nspecs);\n");

			fprintf(fhpp,"\t\t\tint _set_call_target(const char* node,const char* port,int64 spec1,int64 spec2);\n");

			fprintf(fhpp,"\t\t\tint _set_call_target(const char* node,const char* port,int64 spec1);\n");

			fprintf(fhpp,"\t\t\tint _set_call_target(const std::string& node,const std::string& port,int64 spec1);\n");

// 			fprintf(fhpp,"\t\t\tint _set_call_target(const std::string& node,const std::string& port,int64 spec1)\n");
// 				fprintf(fhpp,"\t\t\t{\n");
// 					fprintf(fhpp,"\t\t\t\treturn _set_call_target(node.c_str(),port.c_str(),spec1);\n");
// 				fprintf(fhpp,"\t\t\t}\n");


			fprintf(fhpp,"\t\t\tint _set_call_target(const std::string& node,const std::string& port,int64 spec1,int64 spec2);\n");
		}

		fprintf(fhpp,"\t\tpublic:\n");
			for(j = 0; j < obj->num_method; ++j)
			{
				method = &obj->methods[j];
				gen_result_desc(method,paramsbuf1,3);
				fprintf(fhpp,"\n");
				fprintf(fhpp,"%s",paramsbuf1);

				gen_params_all(method,paramsbuf1,PARAM_FLAGS_NORMAL);
				gen_params_val(method,paramsbuf2,PARAM_FLAGS_NORMAL);
				fprintf(fhpp,"\t\t\tint %s(pwdist::ICallableObject* caller%s);\n",method->name,paramsbuf1);
			}

		fprintf(fhpp,"\t\tpublic:\n");
			for(j = 0; j < obj->num_method; ++j)
			{
				method = &obj->methods[j];
				gen_result_desc(method,paramsbuf1,3);
				fprintf(fhpp,"\n");
				fprintf(fhpp,"%s",paramsbuf1);

				gen_params_all(method,paramsbuf1,PARAM_FLAGS_NORMAL);
				gen_params_val(method,paramsbuf2,PARAM_FLAGS_NORMAL);

				fprintf(fhpp,"\t\t\tint _make%s(pwdist::MsgCall& call,pwdist::ICallableObject* caller%s);\n",method->name,paramsbuf1);
			}
		fprintf(fhpp,"\t\tpublic:\n");
			for(j = 0; j < obj->num_method; ++j)
			{
				method = &obj->methods[j];

				if(get_params_num(method,PARAM_FLAGS_RESULT_REQ | PARAM_FLAGS_RESULT_OPT) == 0)
					continue;
				
				strcpy(methodname,method->name);
				strreplace(methodname,"_rpc_call","");

				fprintf(fhpp,"\t\t\t" "// -------------------------------------" "\n");
				fprintf(fhpp,"\t\t\t" "//  %s" "\n",method->name);
				fprintf(fhpp,"\t\t\t" "// -------------------------------------" "\n");
				fprintf(fhpp,"\t\t\t" "class CON%s" "\n",methodname);
				fprintf(fhpp,"\t\t\t" "{" "\n");
				fprintf(fhpp,"\t\t\t" "public:" "\n");
				fprintf(fhpp,"\t\t\t\t" "CON%s(pwdist::Port* port = NULL);" "\n",methodname);
				fprintf(fhpp,"\t\t\t" "public:" "\n");

				if(get_params_num(method,PARAM_FLAGS_RESULT_REQ) > 0)
				{
					gen_params_all(method,paramsbuf1,PARAM_FLAGS_RESULT_REQ);
					gen_params_val(method,paramsbuf2,PARAM_FLAGS_RESULT_REQ);

					strcpy(paramsbuf3,&paramsbuf1[1]); //
					strcpy(paramsbuf4,&paramsbuf2[1]); //

					fprintf(fhpp,"\t\t\t\t" "int Return(%s);" "\n",paramsbuf3);

					fprintf(fhpp,"\t\t\t\t" "int ReturnAsyncEx(int64 pid%s);" "\n",paramsbuf1);

					fprintf(fhpp,"\t\t\t\t" "int CancelAsyncReturn(int64 pid);" "\n");
				}

				if(get_params_num(method,PARAM_FLAGS_RESULT_OPT) > 0)
				{
					gen_params_all(method,paramsbuf1,PARAM_FLAGS_RESULT_REQ | PARAM_FLAGS_RESULT_OPT);
					gen_params_val(method,paramsbuf2,PARAM_FLAGS_RESULT_REQ | PARAM_FLAGS_RESULT_OPT);

					strcpy(paramsbuf3,&paramsbuf1[1]); 
					strcpy(paramsbuf4,&paramsbuf2[1]); 
					
					fprintf(fhpp,"\t\t\t\t" "int Return(%s);" "\n",paramsbuf3);

					fprintf(fhpp,"\t\t\t\t" "int ReturnAsyncEx(int64 pid%s);" "\n",paramsbuf1);
					fprintf(fhpp,"\t\t\t\t" "" "\n");
				}

				fprintf(fhpp,"\t\t\t" "public:" "\n");
				
				// \BB\F1ȡ\B7\B5\BB\D8ֵ
				m = 0;
				for(k = 0; k < method->num_params; ++k)
				{
					param = &method->params[k];

					if(!param->is_result)
						continue;

					strcpy(paramname,param->name);
					strtolower(paramname);
					paramname[0] = toupper(paramname[0]);

					fprintf(fhpp,"\t\t\t\t""static %s GetResult%s(pwdist::FutureObject& f);\n",get_param_type_name(param->type),paramname);
					++m;
				}

				fprintf(fhpp,"\t\t\t" "private:" "\n");
				fprintf(fhpp,"\t\t\t\t" "pwdist::Port* m_pPort;" "\n");

				fprintf(fhpp,"\t\t\t" "};" "\n");
				fprintf(fhpp,"\t\t\t" "" "\n");
			}
		if(parent == 0)
		{
			fprintf(fhpp,"\t\tprotected:\n");
			fprintf(fhpp,"\t\t\tpwdist::Port* m_pPort;\n");
		}
		fprintf(fhpp,"\t\t};\n");
		fprintf(fhpp,"\n");
	}
	
	fprintf(fhpp,"\t}\n");
	fprintf(fhpp,"\n");
}

void gen_rpc_proxy()
{
	int i = 0;
	FILE* fcpp = NULL;
	FILE* fhpp = NULL;
	
	fhpp = fopen(OUT_PATH"libdefs/pw_rpc_proxy.h","w+");
	assert(fhpp && "open file error");
	fcpp = fopen(OUT_PATH"libdefs/pw_rpc_proxy.cpp","w+");
	assert(fcpp && "open file error");

	fprintf(fhpp,"#ifndef _pw_rpc_proxies_\n");
	fprintf(fhpp,"#define _pw_rpc_proxies_\n");
	fprintf(fhpp,"\n");
	fprintf(fhpp,"#include \"pw_def.h\"\n");
	fprintf(fhpp,"#include \"pwdist_def.h\"\n");
	fprintf(fhpp,"#include \"pwdist_parameter.h\"\n");
// 	fprintf(fhpp,"#include \"pwdist_port.h\"\n");
// 	fprintf(fhpp,"#include \"pwdist_callable_object.h\"\n");
// 	fprintf(fhpp,"#include \"pw_rpc_names.h\"\n");
	fprintf(fhpp,"\n");
// 	fprintf(fhpp,"namespace pwdist\n");
// 	fprintf(fhpp,"{\n");
// 	fprintf(fhpp,"\t""class Node;\n");
// 	fprintf(fhpp,"\t""class Port;\n");
// 	fprintf(fhpp,"\t""class ICallableObject;\n");
// 	fprintf(fhpp,"\t""class MsgCall;\n");
// 	fprintf(fhpp,"}\n");
	fprintf(fhpp,"namespace pwngs\n");
	fprintf(fhpp,"{\n");
	fprintf(fhpp,"\n");

	
	fprintf(fcpp,"#include \"pw_rpc_proxy.h\"\n");
	fprintf(fcpp,"#include \"pw_rpc_names.h\"\n");
	fprintf(fcpp,"#include \"pwdist_port.h\"\n");
	fprintf(fcpp,"#include \"pwdist_port_generic.h\"\n");
	fprintf(fcpp,"#include \"pwdist_callable_object.h\"\n");
	fprintf(fcpp,"\n");
	fprintf(fcpp,"namespace pwngs\n");
	fprintf(fcpp,"{\n");
	fprintf(fcpp,"\n");

	for(; i < global.num_nm; ++i)
	{
		gen_rpc_proxy_hpp(global.nm[i],fhpp);
		gen_rpc_proxy_cpp(global.nm[i],fcpp);
	}

	fprintf(fhpp,"}\n");
	fprintf(fhpp,"#endif\n");
	fprintf(fcpp,"}\n");
	fclose(fhpp);
	fclose(fcpp);
}

// --------------------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------------------

void generate()
{
// 	int i = 0;
// 	for(i = 0; i < global.num_nm; ++i)
// 	{
// 		print_namespace(global.nm[i]);
// 	}
 	gen_rpc_names();
 	gen_rpc_init();
 	gen_rpc_proxy();
}


int yywrap (void )
{
	return 1;
}
