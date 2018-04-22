#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Engine { namespace Graphics { 
	class Window
	{
	private:
	
		const char* m_Title; 
		unsigned int m_Width, m_Height = 0;
		GLFWwindow* m_Window;
	private:
		bool init();

	public:
		void clear() const;
		void update();
		bool closed() const;
		
	public:
		Window(const char* title,int width, int height);
		~Window();
	};
}  }

