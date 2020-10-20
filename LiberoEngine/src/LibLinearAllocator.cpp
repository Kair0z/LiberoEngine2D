#include "PCH.h"
#include "LibLinearAllocator.h"

namespace Libero
{
	LibLinearAllocator::~LibLinearAllocator()
	{
		Clear();
	}

	void* LibLinearAllocator::Allocate(const size_t size)
	{
		assert(size > 0);

		union
		{
			void* asVoidPtr;
			char* asCharPtr;
		};

		asVoidPtr = (void*)m_pBase;
		asCharPtr += m_MemoryUsed;

		// TODO: Catch this case
		if (m_MemoryUsed + size > m_Size) return nullptr;

		m_MemoryUsed += size;
		return asVoidPtr;
	}

	void LibLinearAllocator::Free(void* p)
	{
		// TODO: do something cleaner with this
		// Linear allocators cannot free memory, must clear()
		p;
		assert(false);
	}

	void LibLinearAllocator::Clear()
	{
		m_MemoryUsed = 0;
	}
}

