#pragma once

namespace Libero
{
	template <typename T>
	class INote
	{};

	class NextLevelNote : public INote<NextLevelNote>
	{};
}


