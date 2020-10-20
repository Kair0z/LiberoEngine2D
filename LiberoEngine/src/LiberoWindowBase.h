#pragma once
#include "LiberoMacros.h"
#include "LiberoMath.h"

//***********************************************
// Libero Window wrapper of the SDL_Window class
//***********************************************

// Forward declarations:
struct SDL_Window;
struct GLFWwindow;

namespace Libero
{
	class LiberoWindowBase
	{
	public:
		LiberoWindowBase() = default;
		~LiberoWindowBase() = default;
			
		virtual void Initialize(const std::string& name, const Vector2ui dim) = 0;
		virtual void Initialize(const std::string& name, const size_t w, const size_t h)
		{
			Initialize(name, Vector2ui{ (uint32_t)w, (uint32_t)h });
		}

	public:
		ROFDEL(LiberoWindowBase)
	};

	// OpenGL Window
	class OpenGLWindow final : public LiberoWindowBase
	{
	public:
		virtual ~OpenGLWindow();
		virtual void Initialize(const std::string& name, const Vector2ui dim) override;
		GLFWwindow* GetGLWindow() const;

	private:
		GLFWwindow* m_pGLWindow;
	};

	// SDL Window
	class LiberoWindow_SDL final : public LiberoWindowBase
	{
	public:
		virtual ~LiberoWindow_SDL();
		virtual void Initialize(const std::string& name, const Vector2ui dim) override;
		SDL_Window* GetSDLWindow() const;

	private:
		SDL_Window* m_pSDLWindow;
	};
}


