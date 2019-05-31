#include "pw_linked_object.h"

namespace pwutils
{
	linked_object_master::~linked_object_master()
	{
		detach_all();
	}

	bool linked_object_master::attach( linked_object* ptr )
	{
		ptr->next = m_head;
		m_head = ptr;
		return true;
	}

	bool linked_object_master::detach( linked_object* ptr )
	{
		if(m_head == 0)
			return false;

		if(m_head == ptr)
		{
			m_head = m_head->next;
			return true;
		}

		linked_object* temp = m_head;
		do
		{
			if(temp->next == ptr)
			{
				temp->next = ptr->next;
				return true;
			}
			temp = temp->next;
		} while(temp);

		return false;
	}

	void linked_object_master::detach_all()
	{
		linked_object* temp = m_head;
		while(temp != 0)
		{
			temp->detach();
			temp = temp->next;
		}
		m_head = 0;
	}

}