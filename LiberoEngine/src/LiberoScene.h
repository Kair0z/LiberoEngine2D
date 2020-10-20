#pragma once
#include "LiberoMacros.h"
#include <string>
#include <vector>

#define LIBEROSCENE(SceneType) \
	public: \
		SceneType* Clone() const override \
		{ \
			return new SceneType(*this); \
		} \

namespace Libero
{
	class GameObject;
	class IEvent;

	class LiberoScene
	{
	public:
		LiberoScene(const std::string& name = "DefaultEmptyScene");
		virtual ~LiberoScene();
#pragma region ROF
		LiberoScene(const LiberoScene& other);
		LiberoScene(LiberoScene&& other) = delete;
		LiberoScene& operator=(const LiberoScene& other);
		LiberoScene& operator=(LiberoScene&& other) = delete;
#pragma endregion

		virtual void Initialize() = 0;
		virtual void Start() {};
		virtual void Update(float) {};
		virtual void Render() const {};
		virtual void OnEvent(IEvent*) {};

		virtual LiberoScene* Clone() const = 0;

		GameObject* AddGameObject();
		void DestroyGameObject(GameObject* pObj);

		template<class SysType, typename ...creationArgs>
		void CreateSystem(creationArgs&& ...sysParams);

		const std::vector<GameObject*>& GetObjects() const;

		const std::string& GetName() const;

	private:
		std::string m_Name;
		std::vector<GameObject*> m_pObjects; // Doesn't get made!
	};
}

#include "LiberoScene.inl"

