
#ifndef _pw_mytuple_
#define _pw_mytuple_

#include "pw_bsontocpp.h"
#include <string.h>

namespace pwutils
{
	class TupleBase
	{
	public:
		virtual ~TupleBase() {}
		virtual void from_bson(const mongo::BSONObj& bsonobj) = 0;
		virtual void to_bson(mongo::BSONObj& bsonobj) = 0;
	};

	template<class T1> class Tuple1
	{
	public:
		virtual void from_bson(const mongo::BSONObj& bsonobj)
		{
			mongo::BSONObjIterator iter(bsonobj);
			while(iter.more())
			{
				mongo::BSONElement be = iter.next();
				if(strcmp(be.fieldName(),"v1") == 0)
					pwutils::bsonToCppVariable(v1,be);
			}
		}
		virtual void to_bson(mongo::BSONObj& bsonobj)
		{
			mongo::BSONObjBuilder builder;
			builder.append("v1",v1);
			bsonobj = builder.obj();
		}
	public:
		T1 v1;
	};

	template<class T1,class T2> class Tuple2
	{
	public:
		virtual void from_bson(const mongo::BSONObj& bsonobj)
		{
			mongo::BSONObjIterator iter(bsonobj);
			while(iter.more())
			{
				mongo::BSONElement be = iter.next();
				if(strcmp(be.fieldName(),"v1") == 0)
					pwutils::bsonToCppVariable(v1,be);
				else if(strcmp(be.fieldName(),"v2") == 0)
					pwutils::bsonToCppVariable(v2,be);
			}
		}
		virtual void to_bson(mongo::BSONObj& bsonobj)
		{
			mongo::BSONObjBuilder builder;
			builder.append("v1",v1);
			builder.append("v2",v2);
			bsonobj = builder.obj();
		}
	public:
		T1 v1;
		T2 v2;
	};

	template<class T1,class T2,class T3> class Tuple3
	{
	public:
		virtual void from_bson(const mongo::BSONObj& bsonobj)
		{
			mongo::BSONObjIterator iter(bsonobj);
			while(iter.more())
			{
				mongo::BSONElement be = iter.next();
				if(strcmp(be.fieldName(),"v1") == 0)
					pwutils::bsonToCppVariable(v1,be);
				else if(strcmp(be.fieldName(),"v2") == 0)
					pwutils::bsonToCppVariable(v2,be);
				else if(strcmp(be.fieldName(),"v3") == 0)
					pwutils::bsonToCppVariable(v3,be);
			}
		}
		virtual void to_bson(mongo::BSONObj& bsonobj)
		{
			mongo::BSONObjBuilder builder;
			builder.append("v1",v1);
			builder.append("v2",v2);
			builder.append("v3",v3);
			bsonobj = builder.obj();
		}
	public:
		T1 v1;
		T2 v2;
		T3 v3;
	};

	template<class T1,class T2,class T3,class T4> class Tuple4
	{
	public:
		virtual void from_bson(const mongo::BSONObj& bsonobj)
		{
			mongo::BSONObjIterator iter(bsonobj);
			while(iter.more())
			{
				mongo::BSONElement be = iter.next();
				if(strcmp(be.fieldName(),"v1") == 0)
					pwutils::bsonToCppVariable(v1,be);
				else if(strcmp(be.fieldName(),"v2") == 0)
					pwutils::bsonToCppVariable(v2,be);
				else if(strcmp(be.fieldName(),"v3") == 0)
					pwutils::bsonToCppVariable(v3,be);
				else if(strcmp(be.fieldName(),"v4") == 0)
					pwutils::bsonToCppVariable(v4,be);
			}
		}
		virtual void to_bson(mongo::BSONObj& bsonobj)
		{
			mongo::BSONObjBuilder builder;
			builder.append("v1",v1);
			builder.append("v2",v2);
			builder.append("v3",v3);
			builder.append("v4",v4);
			bsonobj = builder.obj();
		}
	public:
		T1 v1;
		T2 v2;
		T3 v3;
		T4 v4;
	};

	template<class T1,class T2,class T3,class T4,class T5> class Tuple5
	{
	public:
		virtual void from_bson(const mongo::BSONObj& bsonobj)
		{
			mongo::BSONObjIterator iter(bsonobj);
			while(iter.more())
			{
				mongo::BSONElement be = iter.next();
				if(strcmp(be.fieldName(),"v1") == 0)
					pwutils::bsonToCppVariable(v1,be);
				else if(strcmp(be.fieldName(),"v2") == 0)
					pwutils::bsonToCppVariable(v2,be);
				else if(strcmp(be.fieldName(),"v3") == 0)
					pwutils::bsonToCppVariable(v3,be);
				else if(strcmp(be.fieldName(),"v4") == 0)
					pwutils::bsonToCppVariable(v4,be);
				else if(strcmp(be.fieldName(),"v5") == 0)
					pwutils::bsonToCppVariable(v5,be);
			}
		}
		virtual void to_bson(mongo::BSONObj& bsonobj)
		{
			mongo::BSONObjBuilder builder;
			builder.append("v1",v1);
			builder.append("v2",v2);
			builder.append("v3",v3);
			builder.append("v4",v4);
			builder.append("v5",v5);
			bsonobj = builder.obj();
		}
	public:
		T1 v1;
		T2 v2;
		T3 v3;
		T4 v4;
		T5 v5;
	};
}


#endif //_pw_mytuple_