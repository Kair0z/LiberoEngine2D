#pragma once
#include "ECS_Defines.h"

namespace Libero
{
	class IEvent
	{
	public:
		virtual const EventTypeID GetStaticTypeID() const = 0;

		bool IsHandled() const;
		void SetHandled();

	private:
		bool m_IsHandled;
		friend class EventMaster;
	};
}


