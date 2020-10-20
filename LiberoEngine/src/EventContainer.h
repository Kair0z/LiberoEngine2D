#pragma once

#include "LiberoMemory.h"
#include <vector>
#include "IEvent.h"

namespace Libero
{
	class IEventContainer
	{
	public:
		virtual ~IEventContainer() = default;
		virtual void DestroyEvent(IEvent*& pEvent) = 0;
	};
}

namespace Libero
{
	template <class EventType>
	class EventContainer :
		public LibMemoryChunkAllocator<EventType, EVENT_T_CHUNK_SIZE>, // Has all the creating & destroying functionality
		public IEventContainer
	{
	public:
		virtual ~EventContainer() = default;

		virtual void DestroyEvent(IEvent*& pEvent) override
		{
			pEvent->~IEvent();
			this->DestroyObject(pEvent);
			pEvent = nullptr;
		}
	};
}

