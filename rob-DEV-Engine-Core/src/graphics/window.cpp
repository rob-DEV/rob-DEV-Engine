#include "window.h"

#include <iostream>
#include "../include/EngineConfig.h"


namespace Engine {	namespace Core {  namespace Graphics {
	Window::Window(const char* title, int width, int height)
	{
		m_Title = title;
		m_Width = width;
		m_Height = height;

		#if ENGINE_RENDERER_OPENGL
		init_opengl(false);
		#endif

		#if ENGINE_RENDERER_VULKAN
		//ADD VULKAN
		init_vulkan(false);
		#endif
	}

	Window::~Window()
	{
	}

	bool Window::init_opengl(bool resizeable)
	{
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW!\n";
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
		glfwSetWindowSizeCallback(m_Window, Engine::Core::Input::Input::getInstance()->window_resize_callback_handle);
		glfwSetKeyCallback(m_Window, Engine::Core::Input::Input::getInstance()->key_callback_handle);
		glfwSetMouseButtonCallback(m_Window, Engine::Core::Input::Input::getInstance()->mouse_button_callback_handle);
		glfwSetCursorPosCallback(m_Window, Engine::Core::Input::Input::getInstance()->cursor_position_callback_handle);

		glfwSetWindowUserPointer(m_Window, this);
		glfwSwapInterval(0);
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initalize GLEW\n";
			return false;
		}

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		std::cout << "Open GL Version: " << glGetString(GL_VERSION) << "\n";

		return true;
	}

	bool Window::init_vulkan(bool resizeable)
	{

		glClearColor(0.02f, 0.55f, 1.0f, 1.0f);
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW!\n";
			return false;
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		if (!resizeable)
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		m_Window = glfwCreateWindow(m_Width, m_Height, "VULKAN-TESTING", NULL, NULL);

		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		std::cout << extensionCount << " extensions supported" << std::endl;

		if (!m_Window)
		{
			glfwTerminate();
			std::cout << "Failed to create: " << m_Title << "\n";
			return false;
		}

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowSizeCallback(m_Window, Engine::Core::Input::Input::getInstance()->window_resize_callback_handle);
		glfwSetKeyCallback(m_Window, Engine::Core::Input::Input::getInstance()->key_callback_handle);
		glfwSetMouseButtonCallback(m_Window, Engine::Core::Input::Input::getInstance()->mouse_button_callback_handle);
		glfwSetCursorPosCallback(m_Window, Engine::Core::Input::Input::getInstance()->cursor_position_callback_handle);

		glfwSetWindowUserPointer(m_Window, this);
		glfwSwapInterval(0);

		return true;
	}

	void Window::clear() const
	{
		#if ENGINE_RENDERER_OPENGL
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		#endif

		#if ENGINE_RENDERER_VULKAN
		//ADD VULKAN

		#endif
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