#pragma once
#include "LiberoMacros.h"
#include <list>
#include <iterator>

// ---------------------------------------------------------------------------------------------------------------------------------*
//  Credits to Tobias Stein's article about an auxiliary allocator class using the base PoolAllocator.
// --> It creates memory chunks when out of capacity. Every memory chunk is managed by a single PoolAllocator
// This article helped me greatly into creating the perfect allocator to manage my ECS-items
// https://github.com/tobias-stein/EntityComponentSystem/blob/master/EntityComponentSystem/include/ECS/Memory/MemoryChunkAllocator.h
// ---------------------------------------------------------------------------------------------------------------------------------*

namespace Libero
{
	class LibPoolAllocator;

	template <class ObjType, size_t MaxChunkObj>
	class LibMemoryChunkAllocator
	{
	public:
		LibMemoryChunkAllocator();
		virtual ~LibMemoryChunkAllocator();

		void* CreateObject();
		void DestroyObject(void* pObj);

		ROFDEL(LibMemoryChunkAllocator);

	private: // Static data
		static const size_t m_MaxObjPerChunk = MaxChunkObj;
		static const size_t m_ChunkAllocationSize = (sizeof(ObjType) + alignof(ObjType)) * MaxChunkObj;

	public: // Nested classes & defines
		using ObjectList = std::list<ObjType*>;
		class MemoryChunk 
		{
		public:
			MemoryChunk(LibPoolAllocator* pAllocator)
				: m_pAllocator{pAllocator}
			{
				m_pStart = (char*)m_pAllocator->GetBaseAdress();

				// Take into account alignement
				size_t plus = (sizeof(ObjType) + alignof(ObjType)) * MaxChunkObj;
				m_pEnd = m_pStart + plus;
				m_pObjects.clear();
			}

			~MemoryChunk()
			{
				// TODO: outside created allocator shouldn't be deleted in here?
				delete m_pAllocator;
				m_pAllocator = nullptr;
			}

			LibPoolAllocator* m_pAllocator;
			ObjectList m_pObjects;

			char* m_pStart;
			char* m_pEnd;
		};

		using ChunkList = std::list<MemoryChunk*>;
		class ChunkIterator : std::iterator<std::forward_iterator_tag, ObjType>
		{
		public:
			ChunkIterator(typename ChunkList::iterator begin,typename ChunkList::iterator end);
			ChunkIterator& operator++()
			{
				// Move to the next obj in the current chunk:
				m_CurrentObj++;

				// If end, move to next chunk:
				if (m_CurrentObj == (*m_CurrentChunk)->m_pObjects.end())
				{
					m_CurrentChunk++;

					if (m_CurrentChunk != m_End)
					{
						// Set object iterator to begin of next chunk list:
						assert((*m_CurrentChunk));
						m_CurrentObj = (*m_CurrentChunk)->m_pObjects.begin();
					}
				}

				return *this;
			}
			ObjType* operator*() const { return *m_CurrentObj; }
			ObjType* operator->() const { return *m_CurrentObj; }

			bool operator==(ChunkIterator& other)
			{
				bool result{};

				result = (m_CurrentChunk == other.m_CurrentChunk) && (m_CurrentObj == other.m_CurrentObj);

				return result;
			}
			bool operator==(const ChunkIterator& other) const
			{
				bool result{};

				result = (m_CurrentChunk == other.m_CurrentChunk) && (m_CurrentObj == other.m_CurrentObj);

				return result;
			}
			bool operator!=(ChunkIterator& other)
			{
				bool result{};

				result = (m_CurrentChunk != other.m_CurrentChunk) && (m_CurrentObj != other.m_CurrentObj);

				return result;
			}
			bool operator!=(const ChunkIterator& other) const
			{
				if (m_CurrentChunk != other.m_CurrentChunk)
				{
					if (m_CurrentObj != other.m_CurrentObj) return true;
				}

				return false;
			}

		private:
			typename ChunkList::iterator m_CurrentChunk;
			typename ChunkList::iterator m_End;

			typename ObjectList::iterator m_CurrentObj;
		};

	protected: // Data:
		ChunkList m_ChunkList{};

	public:
		ChunkIterator Begin()
		{
			return ChunkIterator(m_ChunkList.begin(), m_ChunkList.end());
		}
		ChunkIterator End()
		{
			return ChunkIterator(m_ChunkList.end(), m_ChunkList.end());
		}
	};
}

#pragma region ChunkIterator
namespace Libero
{
	template<class ObjType, size_t MaxChunkObj>
	LibMemoryChunkAllocator<ObjType, MaxChunkObj>::ChunkIterator::ChunkIterator(typename ChunkList::iterator begin, typename ChunkList::iterator end)
		: m_CurrentChunk(begin)
		, m_End{ end }
	{
		// If the iterator is not the enditerator: set current obj to current chunk:
		if (begin != end)
		{
			assert((*m_CurrentChunk));
			m_CurrentObj = (*m_CurrentChunk)->m_pObjects.begin();
		}
		else // Else: current obj == last object in the endChunk
		{
			m_CurrentObj = (*std::prev(end))->m_pObjects.end();
		}
	}
}
#pragma endregion

#include "LibMemoryChunkAllocator.inl"


