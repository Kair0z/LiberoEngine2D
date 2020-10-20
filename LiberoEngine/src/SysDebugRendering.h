#pragma once
#include "System.h"
#include "Event.h"

namespace Libero
{
	class SysDebugRendering : public System<SysDebugRendering>
	{
	public:
		virtual void PostDraw() const override;

	private:
		void DrawTransforms() const;
		void DrawGrids() const;
		void DrawPhysics() const;
		void DrawMovement() const;
	};
}