#pragma once
#include "System.h"
#include "MouseEvent.h"
#include "KeyEvent.h"

namespace Libero
{
	class SysInput : public System<SysInput>
	{
	public:
		SysInput();
		virtual void Update(float dt) override;
		virtual void OnEvent(IEvent*) override;

	private:
		bool OnMouseDown(MouseDownEvent* e);
		bool OnMouseUp(MouseUpEvent* e);
		bool OnMouseMove(MouseMoveEvent* e);

		bool OnKeyUp(KeyUpEvent* e);
		bool OnKeyDown(KeyDownEvent* e);
	};
}


