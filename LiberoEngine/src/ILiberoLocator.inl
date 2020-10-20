#pragma once
#include "ILiberoLocator.h"

namespace Libero
{
	template<class Service, class NullService = Service>
	Service* ILiberoLocator<Service, NullService>::m_pService = nullptr;
}
