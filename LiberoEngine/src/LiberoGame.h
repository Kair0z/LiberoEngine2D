#pragma once
#include "LiberoMacros.h"
#include "SceneManager.h"

namespace Libero
{
	class LiberoScene;
	class LiberoGame
	{
		ROFDEL(LiberoGame);

	public:
		LiberoGame();
		virtual ~LiberoGame() = default;

		virtual void Initialize() = 0;

	protected:
		template<class Scene, class ...Args>
		void AddScene(Args&& ...args)
		{
			SceneMasterLocator::Locate()->AddScene<Scene>(args...);
		}

	private:
		bool m_IsInitialized;
	};
}


