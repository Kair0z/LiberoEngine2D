#include "PCH.h"
#include "ContentMaster.h"

namespace Libero
{
	ContentMaster::ContentMaster()
		: m_IsInitialized{false}
	{
	}

	void ContentMaster::Initialize()
	{
		if (m_IsInitialized) return;

		m_IsInitialized = true;
	}
}

