#pragma once
#include "ECS_Defines.h"

// STL:
#include <unordered_map>
#include <vector>

namespace Libero
{
	class IEvent;
	class ISystem;
	class ECS_ComponentMaster;
	class LibLinearAllocator;

	class ECS_SystemMaster final
	{
	public:
		ECS_SystemMaster();
		~ECS_SystemMaster();

		void Start();
		void Update(float dt);
		void OnEvent(IEvent* e);
		void Draw() const;

		template <class SysType, class... Args>
		SysType* AddSystem(ECS_ComponentMaster* pCompMaster, Args&&... sysArgs);

	private:
		using SystemMap = std::unordered_map<SysID, ISystem*>;
		LibLinearAllocator* m_pSystemAlloc;
		SystemMap m_Systems;
		std::vector<ISystem*> m_pSystemsToWork;

	public:
		ECS_SystemMaster(const ECS_SystemMaster&) = delete;
		ECS_SystemMaster(ECS_SystemMaster&&) = delete;
		ECS_SystemMaster& operator=(const ECS_SystemMaster&) = delete;
		ECS_SystemMaster& operator=(ECS_SystemMaster&&) = delete;
	};
}


#include "LiberoECS_SystemMaster.inl"
