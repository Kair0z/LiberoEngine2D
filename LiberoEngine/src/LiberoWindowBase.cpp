#include "PCH.h"
#include "LiberoWindowBase.h"

namespace Libero
{
	//***********************
	// GLFW
	//***********************

	OpenGLWindow::~OpenGLWindow()
	{
		glfwDestroyWindow(m_pGLWindow);
		m_pGLWindow = nullptr;
	}

	void OpenGLWindow::Initialize(const std::string& name, const Vector2ui dim)
	{
		m_pGLWindow = glfwCreateWindow((int)dim[0], (int)dim[1], name.c_str(), NULL, NULL);

		if (!m_pGLWindow)
			throw std::runtime_error(std::string("glfwCreateWindow Error!"));
	}

	GLFWwindow* OpenGLWindow::GetGLWindow() const
	{
		return m_pGLWindow;
	}

	//************************
	// SDL
	//************************

	LiberoWindow_SDL::~LiberoWindow_SDL()
	{
		SDL_DestroyWindow(m_pSDLWindow);
		m_pSDLWindow = nullptr;
	}

	void LiberoWindow_SDL::Initialize(const std::string& name, const Vector2ui dim)
	{
		m_pSDLWindow = SDL_CreateWindow(
			name.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			(int)dim[0],
			(int)dim[1],
			SDL_WINDOW_OPENGL
		);

		if (!m_pSDLWindow)
			throw std::runtime_error(std::string{ "SDL_CreateWindow Error: " } + SDL_GetError());

		SDL_Surface* pIconSurface = IMG_Load("../Resources/Textures/Libero/Logo.png");
		SDL_SetWindowIcon(m_pSDLWindow, pIconSurface);
		SDL_FreeSurface(pIconSurface);
	}

	SDL_Window* LiberoWindow_SDL::GetSDLWindow() const
	{
		return m_pSDLWindow;
	}
}

