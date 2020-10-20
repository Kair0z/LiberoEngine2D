#include "ISystem.h"

namespace Libero
{
	template<class ComponentType, typename Func>
	inline void ISystem::ForEachComponent(Func func)
	{
		for (auto it = m_pComponentMasterRef->Begin<ComponentType>(); it != m_pComponentMasterRef->End<ComponentType>(); ++it)
		{
			if (!(*it)->IsActive()) continue;
			func(*it);
		}
	}

	template<class ComponentType, typename Func>
	inline void ISystem::ForEachComponent(Func func) const
	{
		for (auto it = m_pComponentMasterRef->Begin<ComponentType>(); it != m_pComponentMasterRef->End<ComponentType>(); ++it)
		{
			if (!(*it)->IsActive()) continue;
			func(*it);
		}
	}
}
