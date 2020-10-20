#pragma once
#include <LiberoScene.h>
#include <GridComponent.h>
#include "BB_LevelParser.h"
#include "LiberoMath.h"
#include "GameObject.h"
#include "IEvent.h"

using namespace Libero;

class BBLevel final : public Libero::LiberoScene
{
public:
	LIBEROSCENE(BBLevel);

	BBLevel(size_t level, const BB_EnviromentLoader& enviromentLoader);

	void Initialize() override;

private:
	const Vector2ui m_EnviromentDimensions;
	const size_t m_Level;
	const BB_EnviromentLoader& m_EnviromentLoader;

	GameObject* m_pGrid;
	Grid2DComponent* m_pGridComponent;
	std::vector<GameObject*> m_pEnviroment;

private:
	void InitializeGrid();
	void InitializePlayer();
	void InitializeEnemy();
	void InitializeEnviroment();
	void InitializeFPS();
};
