#ifndef _pw_linked_object_
#define _pw_linked_object_

#include "pw_def.h"
#include <string.h>

namespace pwutils
{
	class linked_object;

	class linked_object_master
	{
	public:
		linked_object_master()
			: m_head(0)
		{			
		}

		virtual ~linked_object_master();		
	public:
		bool attach(linked_object* ptr);
		bool detach(linked_object* ptr);
	public:
		linked_object_master(const linked_object_master&) : m_head(0) { this->detach_all(); }
		const linked_object_master& operator=(const linked_object_master&) { this->detach_all(); return *this; }
	protected:
		void detach_all();
	protected:
		linked_object* m_head;
	};

	class linked_object
	{
	public:
		linked_object()
			: master(0)
			, next(0)
		{
		}

		void init(linked_object_master* m)
		{
			master = m;
			if(master)
				master->attach(this);
		}
		virtual ~linked_object()
		{
			if(master != 0)
			{
				master->detach(this);
				master = 0;
			}
		}
	public:
		virtual void detach()
		{
			// dont clear member next
			this->master = 0;
		}
	public:
		linked_object_master* master;
		linked_object* next;
	};
}

#endif // _pw_linked_object_