#include "PCH.h"
#include "LibPoolAllocator.h"

namespace Libero
{
	LibPoolAllocator::LibPoolAllocator(const size_t size, const void* pBase, const size_t objSize)
		: ILibAllocator(size, pBase)
		, m_ObjectSize{objSize}
	{
		Clear();
	}

	LibPoolAllocator::~LibPoolAllocator()
	{
		m_pFreeList = nullptr;
	}

	void* LibPoolAllocator::Allocate(const size_t size)
	{
		assert(size > 0);
		assert(size == m_ObjectSize);

		size;

		// No memory to provide that's free
		if (!m_pFreeList) return nullptr;

		// Get Free slot
		void* p = m_pFreeList;

		// Point to next available slot
		m_pFreeList = (void**)(*m_pFreeList);

		m_MemoryUsed += m_ObjectSize;
		return p;
	}

	void LibPoolAllocator::Free(void* p)
	{
		// Put this slot back to to free list
		*((void**)p) = m_pFreeList;

		m_pFreeList = (void**)p;

		m_MemoryUsed -= m_ObjectSize;
	}

	void LibPoolAllocator::Clear()
	{
		// TODO: understand
		size_t amountOfObjects = (size_t)float(m_Size) / m_ObjectSize;

		union
		{
			void* asVoidPtr;
			char* asCharPtr;
		};

		asVoidPtr = (void*)m_pBase;
		
		m_pFreeList = (void**)asVoidPtr;

		void** p = m_pFreeList;

		for (size_t i{}; i < amountOfObjects - 1; ++i)
		{
			*p = (void*)((char*)p + m_ObjectSize);
			p = (void**)*p;
		}

		*p = nullptr;
	}
}

