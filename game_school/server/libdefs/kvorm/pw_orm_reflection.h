#ifndef __pw_orm_reflection__
#define __pw_orm_reflection__

#include "kvdb/pw_kvorm.h"

namespace orm
{

	extern const char* cst_slaves_of_Passport[];
	extern int64 cst_slaves_hash_of_Passport[];
	extern const char* cst_slave_tables_of_Passport[];
	extern int64 cst_slave_tables_hash_of_Passport[];

	extern pwutils::KvormBase* createObject(bson::bo& __obj);
	extern pwutils::KvormBase* createObject(const char* __data,size_t __size);
}

#endif //__pw_orm_reflection__
