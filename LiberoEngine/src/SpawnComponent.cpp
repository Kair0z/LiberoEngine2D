#include "PCH.h"
#include "SpawnComponent.h"
#include "SceneManager.h"
#include "TransformComponent.h"
#include "PhysicsMaster.h"

namespace Libero
{
	GameObject* SpawnComponent::SpawnGameObject()
	{
		LiberoSceneMaster* pSceneMaster = SceneMasterLocator::Locate();
		if (!pSceneMaster) return nullptr;

		GameObject* pResult = pSceneMaster->GetActiveScene()->AddGameObject();
		pResult->Initialize();

		pResult->GetTransform()->SetPosition(GetOwnerEntity()->GetComponent<Transform2DComponent>()->GetPosition());

		return pResult;
	}
}

