#include "PCH.h"
#include "Event.h"
#include "FamilyTypeID.h"

namespace Libero
{
	template<class Type>
	const EventTypeID Event<Type>::m_Stat_Event_TypeID = FamilyTypeID<IEvent>::Get<Type>();

	template<class Type>
	inline const EventTypeID Event<Type>::GetStaticTypeID() const
	{
		return m_Stat_Event_TypeID;
	}

	template<class Type>
	inline const EventTypeID Event<Type>::Static_GetStaticTypeID()
	{
		return m_Stat_Event_TypeID;
	}
}