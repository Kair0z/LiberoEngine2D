#pragma once
#include "Event.h"

namespace Libero
{
	class GamePlayEvent : public Event<GamePlayEvent>
	{
	public:
		std::string ToString() const
		{
			std::stringstream ss;
			ss << "Play Game Event! \n";

			return ss.str();
		}
	};

	class GameStopEvent : public Event<GameStopEvent>
	{
	public:
		std::string ToString() const
		{
			std::stringstream ss;
			ss << "Stop Game Event! \n";

			return ss.str();
		}
	};

	class NextSceneEvent : public Event<NextSceneEvent>
	{
	public:
		NextSceneEvent(size_t nextIdx) : m_NextIdx{nextIdx}{}
		std::string ToString() const
		{
			return "Next Scene Event!\n";
		}

		size_t GetNextIdx() const { return m_NextIdx; }

	private:
		size_t m_NextIdx{};
	};

	class ExitEvent : public Event<ExitEvent>
	{
	public:
		std::string ToString() const
		{
			std::stringstream ss;
			ss << "!EXIT! \n";

			return ss.str();
		}
	};
}


