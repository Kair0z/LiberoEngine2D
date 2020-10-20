#pragma once
#include "LiberoMacros.h"
#include <chrono>

namespace Libero
{
	class GameTime
	{
	public:
		using Timepoint = std::chrono::time_point<std::chrono::steady_clock>;

		GameTime();
		~GameTime();

		void Tick();

		double GetElapsedSec() const;
		double GetTotalTime() const;
		Timepoint LastTick() const;
		Timepoint Now() const;

	private:
		double m_TotalTime{};
		double m_ElapsedSeconds{};
		
		const Timepoint m_Start{};
		Timepoint m_LastTick{};

	public:
		ROFDEL(GameTime)
	};
}


