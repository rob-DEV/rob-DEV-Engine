#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../input/input.h"



namespace Engine { namespace Core {  namespace Graphics { 
	class Window
	{
	private:
		const char* m_Title; 
		unsigned int m_Width, m_Height = 0;
		GLFWwindow* m_Window;
	private:
		bool init();
		static void window_resize(GLFWwindow  *window, int width, int height);
	public:
		void clear() const;
		void update();
		bool closed() const;
		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; };

		Window(const char* title,int width, int height);
		~Window();

	};	
}	}	}

