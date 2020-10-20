#include "PCH.h"
#include "SubjectMaster.h"

namespace Libero
{
	void SubjectMaster::Initialize()
	{

	}

	void SubjectMaster::Notify(Category cat)
	{
		for (IObserver* pObserver : m_ObserverMap[cat])
			pObserver->OnNotify();
	}

	void SubjectMaster::NotifyPhysics()
	{
		Notify(Category::Physics);
	}

	void SubjectMaster::NotifyScore()
	{
		Notify(Category::Score);
	}

	void SubjectMaster::NotifyLevels()
	{
		Notify(Category::Levels);
	}

	void SubjectMaster::SubToSubject(Category cat, IObserver* pObserver)
	{
		if (!pObserver) return;

		m_ObserverMap[cat].push_back(pObserver);
	}

	void SubjectMaster::UnsubFromSubject(Category cat, IObserver* pObserver)
	{
		if (!pObserver) return;

		m_ObserverMap[cat].remove(pObserver);
	}
}

