#ifndef _pw_orm_helper_
#define _pw_orm_helper_

#include "pw_def.h"
#include "kvdb/pw_kvorm.h"
#include "pw_tick_timer.h"

namespace pwngs
{
	enum
	{
		ORM_SYNC_NOW,		// 立刻
		ORM_SYNC_FRAME,		// 下一帧
		ORM_SYNC_FAST,		// 5秒内
		ORM_SYNC_SLOW,		// 10秒内
		ORM_SYNC_LAZY,		// 30-60秒
		ORM_SYNC_MAX,
	};

	enum
	{
		ORM_HELP_FLAGS_DISABLE = 0x01,
	};

	enum EReturnResult
	{
		EResult_OK = 0,
		EResult_SameHash,	//ÏàÍ¬µÄÊý¾Ý£¬ÎÞÐèOrm
	};

	class OrmHelper
	{
		enum
		{
			OPERATION_INSERT,
			OPERATION_UPDATE,
			OPERATION_DELETE,
			OPERATION_MAX,
		};
	public:
		OrmHelper();
		~OrmHelper();
	public:
		bool OrmInsert(pwutils::KvormBase* obj);
		bool OrmUpdate(pwutils::KvormBase* obj,int level = ORM_SYNC_NOW);
		void OrmDelete(pwutils::KvormBase* obj);
	public:
		static void GOrmInsert(pwutils::KvormBase* obj);
		static int GOrmUpdate(pwutils::KvormBase* obj);
		static void GOrmDelete(pwutils::KvormBase* obj);
	public:
		void Update(int64 tick);
	public:
		inline int IsIncludeFlags(int32 flags)
		{
			return m_nFlags & flags;
		}

		inline void ExcludeFlags(int32 flags)
		{
			m_nFlags &= ~flags;
		}

		inline void IncludeFlags(int32 flags)
		{
			m_nFlags |= flags;
		}
	protected:
		static bool Commit(pwutils::KvormBase* obj,int operation);
	protected:
		unsigned Merge(int16 newop,int16 oldop);
		pwutils::TickTimer m_objTimerLazy;
	private:
		int32 m_nFlags;
	};
}
#endif // _pw_orm_helper_