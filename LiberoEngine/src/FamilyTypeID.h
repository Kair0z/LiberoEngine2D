#pragma once

template <class T>
class FamilyTypeID
{
public:
	template <class U>
	inline static const unsigned int Get();

	inline static const unsigned int Get();

private:
	static unsigned int m_Stat_Count;
};


template<class T>
template<class U>
inline const unsigned int FamilyTypeID<T>::Get()
{
	static const unsigned int value = m_Stat_Count++;
	return value;
}

template<class T>
inline const unsigned int FamilyTypeID<T>::Get()
{
	static const unsigned int value = m_Stat_Count;
	return value;
}