#pragma once
#include "ECS_Defines.h"
#include "LiberoECS_ComponentMaster.h"
#include "IEvent.h"

namespace Libero
{
	class ECS_SystemMaster;
	class ECS_ComponentMaster;

	class ISystem
	{
	public:
		inline virtual void Start() {};
		inline virtual void PreUpdate(float) {};
		inline virtual void Update(float) {};
		inline virtual void PostUpdate(float) {};
		inline virtual void OnEvent(IEvent*) {};

		inline virtual void Draw() const {};
		inline virtual void PostDraw() const {};

	protected:
		float m_TimeSinceLastUpdate = 0.0f;
		float m_UpdateInterval = 0.01f;

		bool m_IsEnabled = true;
		bool m_DoesNeedUpdate = true;
		// TODO: System priority variable

		// TODO: This could be cleaner...
		friend class ECS_SystemMaster;
		ECS_SystemMaster* m_pSystemMasterRef;
		ECS_ComponentMaster* m_pComponentMasterRef;

		template<class ComponentType, typename Func = std::function<void(ComponentType*)>>
		void ForEachComponent(Func func); // Helper function that allows Systems to access all components of Type 'ComponentType'

		template<class ComponentType, typename Func = std::function<void(ComponentType*)>>
		void ForEachComponent(Func func) const;
	};
}

#include "ISystem.inl"

