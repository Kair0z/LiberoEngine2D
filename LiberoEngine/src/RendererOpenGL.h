#pragma once
#include "LiberoRenderer.h"

struct GLFWwindow;

namespace Libero
{
	class LiberoSceneMaster;
	class Texture2DComponent;

	class RendererOpenGL final : public LiberoRenderer
	{
	public:
		struct GLContext
		{
			GLFWwindow* m_pWindow = nullptr;
		};

	public:
		RendererOpenGL();
		~RendererOpenGL();

		void Initialize(GLFWwindow* pWindow);
		bool IsInitialized() const;

		virtual void Open() const override final;
		virtual void Present() const override final;

	private:
		bool m_IsInitialized;

		GLContext m_Context;

		void InitContext(GLFWwindow* pWindow);
	};
}

