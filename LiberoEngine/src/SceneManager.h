#pragma once
#include "LiberoMacros.h"
#include "ILiberoLocator.h"
#include "Logger.h"
#include "LiberoScene.h"
#include <vector>

#define SCENEMANAGER_MAX_AMOUNT_SCENES 150

namespace Libero
{
	class IEvent;
	class LiberoScene;
	class LiberoSceneMaster
	{
	public:
		LiberoSceneMaster();
		~LiberoSceneMaster();

		void Initialize();
		void Start();
		void Stop();
		void HandleEvent(IEvent*);

		template<class Scene, class ...Args>
		void AddScene(Args&& ...args)
		{
			if (m_pScenes.size() >= SCENEMANAGER_MAX_AMOUNT_SCENES)
			{
				LoggerLocator::Locate()->Log(Logger::LogType::Warning, "SceneManager::AddScene >> Tried to add over the max amount of Scenes!");
				return;
			}

			m_pScenes.emplace_back(new Scene(std::forward<Args>(args)...) );
			m_pOriginalScenes.emplace_back(new Scene( std::forward<Args>(args)... ));
		}

		void SetActiveScene(const size_t idx);
		void IncrementActiveScene();
		void ToggleActiveScene();
		LiberoScene* GetActiveScene() const;
		size_t GetActiveSceneIdx() const;

		bool IsEmpty() const;
		void RenderActiveScene() const;

	private:
		std::vector<LiberoScene*> m_pScenes;
		std::vector<LiberoScene*> m_pOriginalScenes;
		size_t m_ActiveSceneIdx;
		size_t m_StartSceneIdx;

	public:
		ROFDEL(LiberoSceneMaster)
	};

	class SceneMasterLocator : public ILiberoLocator<LiberoSceneMaster>{};
}


