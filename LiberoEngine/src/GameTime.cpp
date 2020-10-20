#include "PCH.h"
#include "GameTime.h"

using namespace std::chrono;

namespace Libero
{
	Libero::GameTime::GameTime()
		: m_TotalTime{}
		, m_Start{ steady_clock::now() }
		, m_LastTick{steady_clock::now()}
		, m_ElapsedSeconds{}
	{

	}

	Libero::GameTime::~GameTime()
	{

	}

	void Libero::GameTime::Tick()
	{
		m_ElapsedSeconds = std::chrono::duration<double>(steady_clock::now() - m_LastTick).count();
		m_TotalTime = std::chrono::duration<double>(steady_clock::now() - m_Start).count();

		m_LastTick = steady_clock::now();
	}

	double Libero::GameTime::GetElapsedSec() const
	{
		return m_ElapsedSeconds;
	}

	double Libero::GameTime::GetTotalTime() const
	{
		return m_TotalTime;
	}

	Libero::GameTime::Timepoint Libero::GameTime::LastTick() const
	{
		return m_LastTick;
	}

	Libero::GameTime::Timepoint Libero::GameTime::Now() const
	{
		return steady_clock::now();
	}
}
