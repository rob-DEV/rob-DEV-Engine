#pragma once
#include "../include/EngineConfig.h"

#if(_ENGINE_RENDERER_OPENGL)
#include "opengl/gl_include.h"
#endif
#if(_ENGINE_RENDERER_VULKAN)
#include "vulkan/vk_include.h"
#endif

#include "../input/input.h"

namespace Engine { namespace Core {  namespace Graphics { 

	class Window
	{
	private:
		const char* m_Title; 
		uint32_t m_Width, m_Height = 0;
		GLFWwindow* m_Window;
	private:
		#if(_ENGINE_RENDERER_OPENGL)
		bool init_opengl(bool resizeable);
		#endif
		#if(_ENGINE_RENDERER_VULKAN)
		bool init_vulkan(bool resizeable);
		#endif
	public:
		void clear() const;
		void update();
		bool closed() const;
		void dispose();
		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; };
		inline GLFWwindow* getGLFWNativeWindow() const { return m_Window; }

		Window(const char* title,int width, int height);
		~Window();

	};	
}	}	}

