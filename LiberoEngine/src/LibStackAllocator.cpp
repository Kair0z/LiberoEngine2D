#include "PCH.h"
#include "LibStackAllocator.h"

namespace Libero
{
	LibStackAllocator::LibStackAllocator(const size_t size, const void* pBase)
		: ILibAllocator(size, pBase)
	{

	}

	LibStackAllocator::~LibStackAllocator() { Clear(); }

	void* LibStackAllocator::Allocate(const size_t size)
	{
		assert(size > 0);

		union 
		{
			void* asVoidPtr;
			char* asCharPtr;
		};

		// The top of the stack:
		asVoidPtr = (void*)m_pBase;
		asCharPtr += m_MemoryUsed;

		// TODO: Dealing with this case (logging?)
		if (m_MemoryUsed + size > m_Size) return nullptr;

		m_MemoryUsed += size;

		return asVoidPtr;
	}

	void LibStackAllocator::Free(void* address)
	{
		union
		{
			void* asVoidPtr;
			char* asCharPtr;
		};

		asVoidPtr = address;
		
		size_t amountOfMemory = ((char*)m_pBase + m_MemoryUsed) - (char*)address;
		m_MemoryUsed -= amountOfMemory;
	}

	void LibStackAllocator::Clear()
	{
		m_MemoryUsed = 0;
	}
}

