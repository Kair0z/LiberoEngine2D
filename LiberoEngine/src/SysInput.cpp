#include "PCH.h"
#include "SysInput.h"
#include "InputComponent.h"
#include "Logger.h"
#include "EventDispatcher.h"
#include "Logger.h"

namespace Libero
{
	SysInput::SysInput()
	{
		m_UpdateInterval = 0.1f;
	}

	void SysInput::Update(float dt)
	{
		dt;
		ForEachComponent<InputComponent>([](InputComponent* pComponent)
			{
				//pComponent->ResetKeys();
				pComponent->SetMouseDown(false);
				pComponent->SetMouseUp(true);
			});
	}

	void SysInput::OnEvent(IEvent* pE)
	{
		EventDispatcher dispatch{ pE };
		dispatch.Dispatch<MouseUpEvent>(EVDISP_MEMBER_BIND(SysInput::OnMouseUp));
		dispatch.Dispatch<MouseDownEvent>(EVDISP_MEMBER_BIND(SysInput::OnMouseDown));
		dispatch.Dispatch<MouseMoveEvent>(EVDISP_MEMBER_BIND(SysInput::OnMouseMove));
		dispatch.Dispatch<KeyUpEvent>(EVDISP_MEMBER_BIND(SysInput::OnKeyUp));
		dispatch.Dispatch<KeyDownEvent>(EVDISP_MEMBER_BIND(SysInput::OnKeyDown));
	}

	bool SysInput::OnMouseDown(MouseDownEvent*)
	{
		for (auto it = m_pComponentMasterRef->Begin<InputComponent>(); it != m_pComponentMasterRef->End<InputComponent>(); ++it)
		{
			it->SetMouseDown(true);
			it->SetMouseUp(false);
		}

		return true;
	}

	bool SysInput::OnMouseUp(MouseUpEvent*)
	{
		for (auto it = m_pComponentMasterRef->Begin<InputComponent>(); it != m_pComponentMasterRef->End<InputComponent>(); ++it)
		{
			it->SetMouseDown(false);
			it->SetMouseUp(true);
		}

		return true;
	}

	bool SysInput::OnMouseMove(MouseMoveEvent*)
	{
		return false;
	}

	bool SysInput::OnKeyUp(KeyUpEvent* pE)
	{
		for (auto it = m_pComponentMasterRef->Begin<InputComponent>(); it != m_pComponentMasterRef->End<InputComponent>(); ++it)
		{
			it->SetKeyState(pE->GetKey(), InputComponent::KeyState::UP);
		}

		return true;
	}

	bool SysInput::OnKeyDown(KeyDownEvent* pE)
	{
		for (auto it = m_pComponentMasterRef->Begin<InputComponent>(); it != m_pComponentMasterRef->End<InputComponent>(); ++it)
		{
			it->SetKeyState(pE->GetKey(), InputComponent::KeyState::DOWN);
		}

		return true;
	}
}