#include "PCH.h"
#include "ILibAllocator.h"

size_t Libero::ILibAllocator::GetMemorySize() const
{
	return m_Size;
}

size_t Libero::ILibAllocator::GetUsedMemory() const
{
	return m_MemoryUsed;
}

const void* Libero::ILibAllocator::GetBaseAdress() const
{
	return m_pBase;
}

Libero::ILibAllocator::ILibAllocator(const size_t size, const void* pBase)
	: m_pBase{pBase}
	, m_Size{size}
{
}
