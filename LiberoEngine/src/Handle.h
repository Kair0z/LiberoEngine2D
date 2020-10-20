#pragma once
#include <limits>
#include <vector>
#include <cstdint>
#include <cassert>
#include <algorithm>

//--------------------------------------------------------------------------------------------------------------------
// Handles > pointers
// --> Opaque identifier that only the system internally knows the meaning of
// https://github.com/tobias-stein/EntityComponentSystem/blob/master/EntityComponentSystem/include/ECS/util/Handle.h
//---------------------------------------------------------------------------------------------------------------------

// using static_assert stops the shift count being negative / too big (line 22)
#pragma warning(disable: 4293)

// nameless struct is needed in this file
#pragma warning(disable: 4201)

template<typename HandleValueType, size_t VersionBits, size_t IndexBits>
union Handle
{
	static_assert(sizeof(HandleValueType)* CHAR_BIT >= (VersionBits + IndexBits), "Invalid Handle layout!");

	using ValueType = HandleValueType;

	static constexpr size_t m_VersionBitAmount{ VersionBits };
	static constexpr size_t m_IndexBitAmount{ IndexBits };

	static constexpr ValueType m_MinVersion{};
	static constexpr ValueType m_MaxVersion{ (1U << m_VersionBitAmount) - 2U };
	static constexpr ValueType m_MaxIndices{ (1U << m_IndexBitAmount) - 2U };

	static constexpr ValueType INVALID{ 100 };

private:
	ValueType m_Value;

public:
	struct
	{
		ValueType m_Idx : m_IndexBitAmount;
		ValueType m_Version : m_VersionBitAmount;
	};

	Handle() = default;
	Handle(ValueType val) : m_Value{val}{}
	Handle(ValueType idx, ValueType version) 
		: m_Idx{idx}, m_Version{version}
	{
	}

	inline operator ValueType() const { return m_Value; }
};


#ifdef _WIN32
// 32bit handle:
using Handle32 = Handle<uint32_t, 12, 20>;
#endif

#ifdef _WIN64
// 64bit handle:
using Handle64 = Handle<uint64_t, 24, 40>;
#endif

template<class T, class HandleType, size_t GrowAmount = 1024>
class HandleTable
{
	using Handle = HandleType;

public:
	HandleTable() { Grow(); }
	~HandleTable() = default;

	Handle AcquireHandle(T* rawObj)
	{
		typename Handle::ValueType ii{};
		for (typename Handle::ValueType i{}; i < m_Table.size(); ++i)
		{
			if (m_Table[i].second == nullptr)
			{
				// this handle is not yet in use:
				m_Table[i].second = rawObj;
				
				if ((m_Table[i].first + 1) > Handle::m_MaxVersion)
					m_Table[i].first = Handle::m_MinVersion;

				else m_Table[i].first = m_Table[i].first + 1;

				return Handle(i, m_Table[i].first);
			}

			ii = i;
		}

		// if we get here, we need to grow the table:
		Grow();

		m_Table[ii].first = 1;
		m_Table[ii].second = rawObj;

		return Handle(ii, m_Table[ii].first);
	}

	void ReleaseHandle(Handle handle)
	{
		assert((handle.m_Idx < m_Table.size() && !IsExpired(handle)));
		m_Table[handle.m_Idx].second = nullptr;
	}

	bool IsExpired(Handle handle) const
	{
		// Is t he intern version == version stored in table
		return m_Table[handle.m_Idx].first != handle.m_Version;
	}
	Handle operator[](typename Handle::ValueType idx) const
	{
		assert(idx < m_Table.size());
		return Handle(idx, m_Table[idx].first);
	}
	T* operator[](Handle handle)
	{
		assert(handle.m_Idx < m_Table.size() && !IsExpired(handle));
		
		if (!IsExpired(handle)) return m_Table[handle.m_Idx].second;
		else return nullptr;
	}

private:
	using TableItem = std::pair<typename Handle::ValueType, T*>;
	std::vector<TableItem> m_Table;

	void Grow()
	{
		size_t oldSize = m_Table.size();

		// TODO: catch this problem!
		assert(oldSize < Handle::m_MaxIndices);

		// Set the new size to either old + growamount, or if that's too big, to maxIndices:
#ifdef _WIN64
		size_t newSize = std::min(oldSize + GrowAmount, Handle64::m_MaxIndices);
#else 
		size_t newSize = std::min(oldSize + GrowAmount, Handle32::m_MaxIndices);
#endif

		m_Table.resize(newSize);

#ifdef _WIN64
		for (typename Handle64::ValueType i{ oldSize }; i < newSize; ++i)
			m_Table[i] = TableItem(Handle64::m_MinVersion, nullptr);
#else
		for (typename Handle32::ValueType i{ oldSize }; i < newSize; ++i)
			m_Table[i] = TableItem(Handle32::m_MinVersion, nullptr);
#endif
		
	}
};