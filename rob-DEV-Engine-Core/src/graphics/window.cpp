#include "window.h"
#include <iostream>

namespace Engine {	namespace Core {  namespace Graphics {
	Window::Window(const char* title, int width, int height)
	{
		m_Title = title;
		m_Width = width;
		m_Height = height;

		if (!init(false)) {
			glfwTerminate();
		}
	}


	Window::~Window()
	{
	}


	bool Window::init(bool resizeable)
	{
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW!\n";
			return false;
		}

		if (!resizeable)
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window)
		{
			glfwTerminate();
			std::cout << "Failed to create: " << m_Title << "\n";
			return false;
		}
		
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowSizeCallback(m_Window, Engine::Core::Input::Input::getInputInstance()->window_resize_callback_handle);
		glfwSetKeyCallback(m_Window, Engine::Core::Input::Input::getInputInstance()->key_callback_handle);
		glfwSetMouseButtonCallback(m_Window, Engine::Core::Input::Input::getInputInstance()->mouse_button_callback_handle);
		glfwSetCursorPosCallback(m_Window, Engine::Core::Input::Input::getInputInstance()->cursor_position_callback_handle);

		glfwSetWindowUserPointer(m_Window, this);
		glfwSwapInterval(0);
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initalize GLEW\n";
			return false;
		}

		

		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);

		std::cout << "Open GL Version: " << glGetString(GL_VERSION) << "\n";

		return true;
	}

	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_Window) == 1;
	}

	void Window::update()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}


}	}	}