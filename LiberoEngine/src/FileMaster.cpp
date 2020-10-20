#include "PCH.h"
#include "FileMaster.h"
#include "LiberoScene.h"
#include "GameObject.h"

namespace Libero
{
	void FileMaster::Initialize()
	{
		m_IsInitialized = true;
	}

	void FileMaster::SaveScene(LiberoScene* pScene)
	{
		if (!m_IsInitialized) return;

		m_OFS.open("../Resources/Scenes/" + pScene->GetName() + ".libsc");

		if (m_OFS.is_open())
		{
			m_OFS << pScene;
		}

		m_OFS.close();
	}

	void FileMaster::LoadScene(const std::string& sceneName)
	{
		if (!m_IsInitialized) return;

		std::string filepath = "../Resources/Scenes/" + sceneName + ".libsc";
		m_IFS.open(filepath);

		if (m_IFS.is_open())
		{
			// Parse file:
		}
		else
		{
			LoggerLocator::Locate()->LogInfo("Couldn't open scene with name " + sceneName + " at [" + filepath + "]");
		}

		m_IFS.close();
	}

#pragma region ToFile
	std::ofstream& operator<<(std::ofstream& ofs, const LiberoScene* pScene)
	{
		// 0: Header:
		ofs << "-----------------------------------------------------------------\n";
		ofs << " -- LiberoScene: " << pScene->GetName() << " -- \n";
		ofs << "-----------------------------------------------------------------\n";
		ofs << "\n";

		// 1: General settings:
		ofs << "-- General Settings --\n";
		ofs << " ... \n";
		ofs << "\n\n";

		// 2: Gameobjects:
		ofs << "-- GameObjects --\n";
		for (GameObject* pGameObject : pScene->GetObjects())
		{
			ofs << pGameObject << "\n";
		}

		return ofs;
	}

	std::ofstream& operator<<(std::ofstream& ofs, const GameObject* pGameObject)
	{
		ofs << "--- GameObject: " << pGameObject->Getname() << "--- \n";

		auto components = pGameObject->GetComponents();

		for (IComponent* pComponent : components)
		{
			ofs << pComponent;
		}

		ofs << "\n";

		return ofs;
	}

	std::ofstream& operator<<(std::ofstream& ofs, const IComponent* pComponent)
	{
		return pComponent->ToFile(ofs);
	}
#pragma endregion
}

