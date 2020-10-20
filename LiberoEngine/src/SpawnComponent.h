#pragma once
#include "Component.h"
#include <queue>
#include "GameObject.h"

namespace Libero
{
	class SpawnComponent : public Component<SpawnComponent>
	{
	public:
		SpawnComponent() = default;
		virtual ~SpawnComponent() = default;

		GameObject* SpawnGameObject();
	};
}


