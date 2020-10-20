#pragma once
#include "LiberoMacros.h"
#include "ILiberoLocator.h"
#include <unordered_map>
#include "IObserver.h"
#include <list>

namespace Libero
{
	class SubjectMaster
	{
	public:
		enum class Category
		{
			Physics,
			Score,
			Levels
		};

	public:
		SubjectMaster() = default;
		ROFDEL(SubjectMaster);

		void Notify(Category cat);
		void NotifyPhysics();
		void NotifyScore();
		void NotifyLevels();

		void SubToSubject(Category cat, IObserver* pObserver);
		void UnsubFromSubject(Category cat, IObserver* pObserver);

		void Initialize();

	private:
		using ObserverMap = std::unordered_map<Category, std::list<IObserver*>>;

		ObserverMap m_ObserverMap;
	};

	class SubjectMasterLocator : public ILiberoLocator<SubjectMaster>{};
}


