#pragma once
#include "ILiberoLocator.h"
#include "Loader.h"
#include <unordered_map>
#include <string>
#include <vector>

namespace Libero
{
	class ContentMaster
	{
	public:
		ContentMaster();
		void Initialize();

	private:
		bool m_IsInitialized;
		
	};

	class ContentMasterLocator : public ILiberoLocator<ContentMaster>{};
}
