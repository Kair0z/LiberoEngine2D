#include "PCH.h"
#include "IEvent.h"

namespace Libero
{
	bool IEvent::IsHandled() const
	{
		return m_IsHandled;
	}

	void IEvent::SetHandled()
	{
		m_IsHandled = true;
	}
}

