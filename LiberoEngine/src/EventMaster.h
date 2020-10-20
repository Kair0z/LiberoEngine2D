#pragma once
#include <vector>
#include <unordered_map>

#include "ECS_Defines.h"
#include "EventContainer.h"
#include "ILiberoLocator.h"

namespace Libero
{
	class IEvent;
	class EventMaster
	{
	public:
		EventMaster();
		~EventMaster();

		void Initialize();
		bool IsInitialized() const;

		template<class EvType, class ...Args>
		void AddToQueue(Args&&... args);

		std::vector<IEvent*>& GetQueue();

		void Update(float dt);
		void FlushUsed();
		void FlushFull();

	private:
		using EventMap = std::unordered_map<EventTypeID, IEventContainer*>;

		EventMap m_EventMap;
		std::vector<IEvent*> m_EventLookUp;

		bool m_IsInitialized;
		float m_FlushInterval = 1.f;
		float m_FlushTimer = 0.0f;

	private:
		template <class EvType>
		EventContainer<EvType>* GetContainer();

		void DestroyEvent(IEvent*& pEvent);

	public:
		ROFDEL(EventMaster)
	};

	class EventMasterLocator : public ILiberoLocator<EventMaster>{};
}

#include "EventMaster.inl"

