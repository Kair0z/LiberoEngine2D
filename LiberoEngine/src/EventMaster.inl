#include "PCH.h"
#include "EventMaster.h"
#include "FamilyTypeID.h"
#include "IEvent.h"
#include "ECS_Defines.h"
#include "Logger.h"

namespace Libero
{
	inline EventMaster::EventMaster()
	{
		size_t size = EVENTMASTER_MEMORY_SIZE;
		m_EventLookUp.reserve(size);
	}

	inline EventMaster::~EventMaster()
	{
		if (!m_IsInitialized) return;
	
		for (auto container : m_EventMap)
		{
			delete container.second;
			container.second = nullptr;
		}
	}

	template <class Type, class ...Args>
	inline void EventMaster::AddToQueue(Args&&... args)
	{
		if (!m_IsInitialized) return;

		const EventTypeID eTypeID = Type::m_Stat_Event_TypeID;

		EventContainer<Type>* getContainer = GetContainer<Type>();
		void* pObjMem = getContainer->CreateObject();

		// Create the actual object pointer:
		IEvent* pEvent = new (pObjMem)Type(std::forward<Args>(args)...);
		pEvent->m_IsHandled = false;

		// Add it to the lookup
		m_EventLookUp.push_back(pEvent);
	}

	inline std::vector<IEvent*>& EventMaster::GetQueue()
	{
		return m_EventLookUp;
	}

	inline void EventMaster::Update(float dt)
	{
		m_FlushTimer += dt;

		// Only flush used events if fullflush timer doesn't tick
		// else, do a full flush to clean up old events
		if (m_FlushTimer > m_FlushInterval) 
		{ 
			FlushFull(); 
			m_FlushTimer = 0.0f; 
			//LoggerLocator::Locate()->LogInfo("FULL FLUSH!");
		}
		else FlushUsed();
	}

	inline void EventMaster::FlushUsed()
	{
		if (!m_IsInitialized) return;

		for (IEvent*& pEvent : m_EventLookUp)
		{
			if (pEvent != nullptr && pEvent->IsHandled())
			{
				DestroyEvent(pEvent);
				pEvent = pEvent;
			}
		}

		// TODO: remove all nullptr's from lookup [best approach]?
		m_EventLookUp.erase(std::remove_if(m_EventLookUp.begin(), m_EventLookUp.end(),
			[](IEvent* pEvent) {return pEvent == nullptr; })
			, m_EventLookUp.end());
	}

	inline void EventMaster::FlushFull()
	{
		if (!m_IsInitialized) return;

		for (IEvent*& pEvent : m_EventLookUp)
		{
			if (pEvent != nullptr)
			{
				DestroyEvent(pEvent);
				pEvent = pEvent;
			}
		}

		// TODO: remove all nullptr's from lookup [best approach]?
		m_EventLookUp.erase(std::remove_if(m_EventLookUp.begin(), m_EventLookUp.end(),
			[](IEvent* pEvent) {return pEvent == nullptr; })
			, m_EventLookUp.end());
	}

	inline void EventMaster::DestroyEvent(IEvent*& pEvent)
	{
		const EventTypeID eTypeID = pEvent->GetStaticTypeID();

		m_EventMap[eTypeID]->DestroyEvent(pEvent);
	}

	template<class EvType>
	inline EventContainer<EvType>* EventMaster::GetContainer()
	{
		EventTypeID eTypeID = EvType::m_Stat_Event_TypeID;

		auto it = m_EventMap.find(eTypeID);
		EventContainer<EvType>* pContainer = nullptr;

		if (it == m_EventMap.end())
		{
			// Create new eventcontainer:
			pContainer = new EventContainer<EvType>();
			m_EventMap[eTypeID] = pContainer;
		}
		else pContainer = (EventContainer<EvType>*)it->second;

		return pContainer;
	}

	inline void EventMaster::Initialize()
	{
		m_IsInitialized = true;
	}

	inline bool EventMaster::IsInitialized() const
	{
		return m_IsInitialized;
	}
}
