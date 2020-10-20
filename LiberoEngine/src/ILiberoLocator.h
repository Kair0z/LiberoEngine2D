#pragma once

namespace Libero
{
	// If no NullService is provided, the locator will return the service anyway!
	template <class Service, class NullService = Service>
	class ILiberoLocator
	{
	public:
		static Service* Locate()
		{
			if (!m_pService) return &m_Null;

			return m_pService;
		}
		static void Provide(Service* pService)
		{
			m_pService = pService;
		}

	private:
		static Service* m_pService;
		static NullService m_Null;
	};

	template <class Service, class NullService>
	Service* ILiberoLocator<Service, NullService>::m_pService = nullptr;

	template <class Service, class NullService>
	NullService ILiberoLocator<Service, NullService>::m_Null{};
}

#include "ILiberoLocator.h"
