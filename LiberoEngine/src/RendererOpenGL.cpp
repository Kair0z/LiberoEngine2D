#include "PCH.h"
#include "RendererOpenGL.h"

namespace Libero
{
	RendererOpenGL::RendererOpenGL()
		: m_IsInitialized{false}
		, m_Context{}
	{
		
	}

	RendererOpenGL::~RendererOpenGL()
	{

	}

	void RendererOpenGL::Initialize(GLFWwindow* pWindow)
	{
		InitContext(pWindow);

		m_IsInitialized = true;
	}

	bool RendererOpenGL::IsInitialized() const
	{
		return m_IsInitialized;
	}

	void RendererOpenGL::InitContext(GLFWwindow* pWindow)
	{
		m_Context.m_pWindow = pWindow;
	}

	void RendererOpenGL::Open() const
	{
		if (!m_IsInitialized) return;
		
		
	}

	void RendererOpenGL::Present() const
	{
		if (!m_IsInitialized) return;
	}
}