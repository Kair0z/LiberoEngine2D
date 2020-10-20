#include "BBLevel.h"

// Component includes:
#include "TransformComponent.h"
#include "InputComponent.h"
#include "PlayerState.h"
#include "SpriteComponent.h"
#include "TextureComponent.h"
#include "RigidbodyComponent.h"
#include "ColliderComponent.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "EnemyState.h"
#include "SpawnComponent.h"

#include "MySprites.h"

// System includes:
#include "Sys_PlayerBehaviour.h"
#include "Sys_FPSCounter.h"
#include "Sys_EnemyBehaviour.h"
#include "Sys_BubbleBehaviour.h"
#include "Sys_LevelSwitch.h"
#include "Sys_CharacterSaver.h"
#include "Sys_ScoreLogger.h"

using namespace Libero;

BBLevel::BBLevel(size_t level, const BB_EnviromentLoader& enviromentLoader)
	: LiberoScene("BubbleBobble [Level " + std::to_string(level) + "]")
	, m_Level{level}
	, m_EnviromentLoader{enviromentLoader}
	, m_EnviromentDimensions{ 32, 25 }
{

}

void BBLevel::Initialize()
{
	CreateSystem<Sys_LevelSwitch>();
	CreateSystem<Sys_CharacterSaver>();
	CreateSystem<Sys_ScoreLogger>();

	InitializePlayer();
	InitializeEnemy();
	InitializeGrid();
	InitializeEnviroment();
	InitializeFPS();
}

void BBLevel::InitializeGrid()
{
	m_pGrid = AddGameObject();
	m_pGrid->SetName("Grid");
	m_pGrid->GetTransform()->SetPosition({ -360.f, -320.f });

	GridCell cell{};
	cell.m_H = 60.f;
	cell.m_W = 60.f;
	m_pGridComponent = m_pGrid->AddComponent<Grid2DComponent>(Grid2DComponent(720.f, 640.f, m_EnviromentDimensions.x, m_EnviromentDimensions.y));
}

void BBLevel::InitializePlayer()
{
	CreateSystem<Sys_PlayerBehaviour>();
	CreateSystem<Sys_BubbleBehaviour>();

	GameObject* pObj = AddGameObject();
	pObj->SetName("Player");

	Rectf dest2{};
	dest2.m_W = 32.f;
	dest2.m_H = 32.f;
	pObj->AddComponent<SpriteComponent>(MySprites::MainCharLeftSprite(dest2));
	pObj->AddComponent<InputComponent>(); // Catches input for the character
	pObj->AddComponent<BoxCollider2DComponent>(dest2.m_W / 2.f, dest2.m_H / 2.f);
	RigidbodyComponent* pRB = pObj->AddComponent<RigidbodyComponent>(RigidbodyComponent::BodyType::Dynamic);
	pRB->SetWeight(5.f);

	PlayerComponent* pPlayer = pObj->AddComponent<PlayerComponent>();
	CharacterComponent* pCharacter = pObj->AddComponent<CharacterComponent>(900.f); // Uses input for movement
	pCharacter->SetEnableGravity(true);
	pCharacter->SetGravityScale(250.f);
	pCharacter->SetDrag(30.f);
	pCharacter->SetMaxSpeed(700.f);
	pObj->AddComponent<SpawnComponent>();
}

void BBLevel::InitializeEnemy()
{
	CreateSystem<Sys_EnemyBehaviour>();

	GameObject* enemies[3]{ nullptr, nullptr, nullptr };
	for (size_t i{}; i < 3; ++i)
	{
		GameObject* pObj = AddGameObject();
		pObj->GetTransform()->Translate({ 100.f, -300.f });
		pObj->SetName("Enemy");
		Rectf dest{};
		dest.m_W = 32.f;
		dest.m_H = 32.f;
		pObj->AddComponent<SpriteComponent>(MySprites::EnemyLeftSprite(dest));
		pObj->AddComponent<BoxCollider2DComponent>(dest.m_W / 2.f, dest.m_H / 2.f);
		RigidbodyComponent* pRB = pObj->AddComponent<RigidbodyComponent>(RigidbodyComponent::BodyType::Dynamic);
		pRB->SetWeight(14.f);

		Rectf enemyBounds{};
		enemyBounds.m_LeftTop = { -320.f, -200.f };
		enemyBounds.m_W = 600.f;
		enemyBounds.m_H = 100.f;
		pObj->AddComponent<EnemyComponent>(enemyBounds);

		CharacterComponent* pCharacter = pObj->AddComponent<CharacterComponent>(500.f);
		pCharacter->SetEnableGravity(false);
		pCharacter->SetGravityScale(80.f);
		pCharacter->SetMaxSpeed(400.f);

		enemies[i] = pObj;
	}

	enemies[1]->GetTransform()->SetPosition({ 100.f, 200.f });
	enemies[2]->GetTransform()->SetPosition({ -100.f, 200.f });
	
}

void BBLevel::InitializeEnviroment()
{
	for (size_t y{}; y < m_EnviromentDimensions.y + 1; ++y)
		for (size_t x{}; x < m_EnviromentDimensions.x; ++x)
		{
			// Get the gridcell
			Libero::GridCell cell = m_pGridComponent->GetCell((int)x, int(y - 1));

			// Load the block
			size_t parserIdx = (x + ((m_EnviromentDimensions.y - y) * m_EnviromentDimensions.x)) + (25 * 32 * m_Level);
			GameObject* pBlock = m_EnviromentLoader.LoadBlock(this, (int)parserIdx, cell.m_W, cell.m_H);
			if (!pBlock) continue;

			// Move it to cell pos
			pBlock->GetTransform()->SetPosition(cell.GetMid() + m_pGrid->GetTransform()->GetPosition());

			// Add physics
			pBlock->AddComponent<BoxCollider2DComponent>(cell.m_W / 2.f, cell.m_H / 2.f);
			pBlock->AddComponent<RigidbodyComponent>(RigidbodyComponent::BodyType::Static);

			// Add it to enviroment vector
			m_pEnviroment.push_back(pBlock);
		}
}

void BBLevel::InitializeFPS()
{
	CreateSystem<Sys_FPSCounter>();

	GameObject* pObj = AddGameObject();
	pObj->SetName("FPS");

	pObj->AddComponent<TextComponent>(TextComponent("00000"));
	pObj->AddComponent<FPSComponent>();
}
