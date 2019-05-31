
#ifndef _pw_dist_lexer_
#define _pw_dist_lexer_


extern void on_attr(const char* attr,const char* value);
extern void on_namespace_began(const char* name);
extern void on_namespace_ended();

extern void on_object_began(const char* name,const char* parent);
extern void on_object_ended();

extern void on_method_began(const char* name);
extern void on_method_ended();

extern void on_method_param(int type,const char* name,int return_params,int optional);

extern void generate();

#endif 
