#pragma once
#include "LiberoECS_ComponentMaster.h"
#include "LiberoECS_EntityMaster.h"
#include "LiberoECS_SystemMaster.h"

namespace Libero
{
	class IEntity;
	class IEvent;

	class ECS_Engine
	{
	public:
		ECS_Engine();
		~ECS_Engine();

		void Initialize();
		bool IsInitialized() const;

		// Main loops
		void Start();
		void Update(float dt);
		void OnEvent(IEvent* pE);
		void Draw() const;

		// EntityMaster functionality:
		template<class Type, typename ...creationArgs>
		inline IEntity* NewEntity(creationArgs&&... constructionParams);

		template<class Type, typename ...creationArgs>
		inline Type* NewEntityAs(creationArgs&&... constructionParams);

		inline void DestroyEntity(const EntityID id);

		// SystemMaster functionality:
		template<class SysType, typename ...creationArgs>
		void CreateSystem(creationArgs&&... sysParams);

		// ComponentMaster functionality:
		template<class CompType>
		std::vector<CompType*> GetAllComponents();


	private:
		ECS_SystemMaster* m_pSystemMaster;
		ECS_ComponentMaster* m_pComponentMaster;
		ECS_EntityMaster* m_pEntityMaster;

		bool m_IsInitialized;
	};
}

#include "ILiberoLocator.h"

namespace Libero
{
	class ECSLocator : public ILiberoLocator<ECS_Engine>{};
}

#include "ECS_Engine.inl"

