#pragma once
#include <string>
#include <sstream>
#include "ECS_Defines.h"
#include "IEvent.h"

namespace Libero
{
	template <class Type>
	class Event : public IEvent
	{
	public:
		virtual ~Event() = default;

		virtual const EventTypeID GetStaticTypeID() const override;
		static const EventTypeID Static_GetStaticTypeID();
		static const EventTypeID m_Stat_Event_TypeID;

		virtual std::string ToString() const { return ""; }

	private:
		void operator delete(void*) = delete;
		void operator delete[](void*) = delete;
	};
}

#include "Event.inl"


