#pragma once
#include <functional>
#include "IEvent.h"



namespace Libero
{
#define EVDISP_MEMBER_BIND(Func) std::bind(&##Func, this, std::placeholders::_1)

	class EventDispatcher 
	{
		template <class E>
		using EventFunc = std::function<bool(E*)>;
		// Defines a function that returns a boolean & takes in a pointer to an event as parameter

	public:
		EventDispatcher(IEvent* pE) : m_pEvent{pE}{}

		template <class E>
		bool Dispatch(EventFunc<E> handler)
		{
			if (!m_pEvent) return false;
			if (m_pEvent->IsHandled()) return false;
			if (m_pEvent->GetStaticTypeID() != E::Static_GetStaticTypeID()) return false;

			// Pass a dereferenced, [casted to E::type] event to the handler function
			if (handler((E*)m_pEvent))
			{
				m_pEvent->SetHandled();
				return true;
			}
			return false;
		}

	private:
		IEvent* m_pEvent;
	};

	// Calls the <void(IEvent*)> Function and automatically sets the event handled
#define EVDISP_FINAL_MEMBER_BIND(Func) std::bind(&##Func, this, std::placeholders::_1)
	class EventFinalDispatcher 
	{
		template <class E>
		using EventFunc = std::function<void(E*)>;
	public:
		EventFinalDispatcher(IEvent* pE) : m_pEvent{pE}{}

		template <class E>
		bool Dispatch(EventFunc<E> handler)
		{
			if (!m_pEvent) return false;
			if (m_pEvent->IsHandled()) return false;
			if (m_pEvent->GetStaticTypeID() != E::Static_GetStaticTypeID()) return false;

			handler((E*)m_pEvent);
			m_pEvent->SetHandled();
			return true;
		}

	private:
		IEvent* m_pEvent;
	}; 

	// Just calls the function <void()> On specific event
#define EVDISP_SIGNAL_MEMBER_BIND(Func) std::bind(&##Func, this)
	class EventSignalDispatcher
	{
		template<class E>
		using EventFunc = std::function<void()>;
	public:
		EventSignalDispatcher(IEvent* pE) : m_pEvent{pE}{}

		template <class E>
		bool Dispatch(EventFunc<E> handler, bool consume = true)
		{
			if (!m_pEvent) return false;
			if (m_pEvent->IsHandled()) return false;
			if (m_pEvent->GetStaticTypeID() != E::Static_GetStaticTypeID()) return false;

			handler();
			if (consume) m_pEvent->SetHandled();
			return true;
		}

	private:
		IEvent* m_pEvent;
	};
}


