#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../graphics/window.h"

#define MAX_KEYS 1024
#define MAX_BUTTONS 32


namespace Engine { namespace Core { namespace Input {
	class Input
	{
	private:
		static Input* m_Input;	

		bool m_Keys[MAX_KEYS];
		bool m_MouseButtons[MAX_BUTTONS];
		double m_MouseX, m_MouseY = 0;

	public:
		Input();
		~Input();
		static Input* getInputInstance();

		//GLFW Callbacks
		static void window_resize_callback_handle(GLFWwindow *window, int width, int height);
		static void key_callback_handle(GLFWwindow *window, int key, int scancode, int action, int mods);
		static void mouse_button_callback_handle(GLFWwindow *window, int button, int action, int mods);
		static void cursor_position_callback_handle(GLFWwindow *window, double xpos, double ypos);

		//Callback Implementations
		void window_resize_callback(GLFWwindow *window, int width, int height);
		void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
		void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
		void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
	};
}	}	}