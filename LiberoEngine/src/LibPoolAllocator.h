#pragma once
#include "ILibAllocator.h"

namespace Libero
{
	class LibPoolAllocator : public ILibAllocator
	{
	public:
		LibPoolAllocator(const size_t size, const void* pBase, const size_t objSize);
		virtual ~LibPoolAllocator();

		virtual void* Allocate(const size_t size) override;
		virtual void Free(void*) override;
		virtual void Clear() override;

	private:
		const size_t m_ObjectSize;
		void** m_pFreeList; 
		// Pointer to an array of void* addresses of free objects
	};
}

