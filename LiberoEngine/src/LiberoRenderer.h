#pragma once
#include "LiberoMacros.h"
#include "LiberoMath.h"
#include "ILiberoLocator.h"

namespace Libero
{
	class LiberoSceneMaster;
	class LiberoRenderer
	{
	public:
		~LiberoRenderer() = default;

		void SetClearColor(const ColorRGBA& color) { m_ClearColor = color; }
		virtual void Open() const = 0;
		virtual void Present() const = 0;

	protected:
		LiberoRenderer() = default;
		ColorRGBA m_ClearColor{ 0.f, 0.f, 0.f, 255.f };

	public:
		ROFDEL(LiberoRenderer)
	};

	class NullRenderer : public LiberoRenderer
	{
	public:
		virtual void Open() const override {};
		virtual void Present() const override {};
	};
	class RendererLocator : public ILiberoLocator<LiberoRenderer, NullRenderer>{};
}


