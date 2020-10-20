#pragma once
#include "LiberoMacros.h"
#include "ILiberoLocator.h"
#include <string>
#include <fstream>

namespace Libero
{
	class LiberoScene;
	class GameObject;
	class IComponent;

	class FileMaster
	{
	public:
		FileMaster() = default;
		virtual ~FileMaster() = default;

		void Initialize();

		void SaveScene(LiberoScene* pScene);
		void LoadScene(const std::string& filename);
		
	private:
		std::ofstream m_OFS;
		std::ifstream m_IFS;

		bool m_IsInitialized;

		ROFDEL(FileMaster)
	};

	class FileMasterLocator : public ILiberoLocator<FileMaster>{};

#pragma region ToFile
	std::ofstream& operator<<(std::ofstream& ofs, const LiberoScene* pScene);
	std::ofstream& operator<<(std::ofstream& ofs, const GameObject* pGameObject);
	std::ofstream& operator<<(std::ofstream& ofs, const IComponent* pComponent);
#pragma endregion
}


