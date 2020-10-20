#pragma once
#include "LiberoMacros.h"
#include <cassert>

namespace Libero
{
	class ILibAllocator
	{
	public:
		virtual ~ILibAllocator() = default;

		virtual void* Allocate(const size_t amount) = 0;
		virtual void Free(void*) = 0;
		virtual void Clear() = 0;

		size_t GetMemorySize() const;
		size_t GetUsedMemory() const;
		const void* GetBaseAdress() const;

	protected:
		ILibAllocator(const size_t size, const void* pBase);

		const size_t m_Size;
		const void* m_pBase;
		size_t m_MemoryUsed;

	public: // ROF
		ROFDEL(ILibAllocator)
	};
}


