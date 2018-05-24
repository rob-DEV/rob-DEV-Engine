#include "input.h"
#include <iostream>

namespace Engine {	namespace Core {
	
	static Input* m_Instance = NULL;

	Input* Input::getInstance()
	{
		if (m_Instance == NULL)
			m_Instance = new Input();

		return m_Instance;

	}

	Input::Input()
	{
		for (size_t i = 0; i < MAX_KEYS; i++)
			m_Keys[i] = false;
	}

	Input::~Input()
	{
	}

	//Callback Static Handles - needed for C binding
	void Input::window_resize_callback_handle(GLFWwindow *window, int width, int height)
	{
		getInstance()->window_resize_callback(window, width, height);
	}
	void Input::key_callback_handle(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		getInstance()->key_callback(window, key, scancode, action, mods);
	}
	void Input::mouse_button_callback_handle(GLFWwindow *window, int button, int action, int mods)
	{
		getInstance()->mouse_button_callback(window, button, action, mods);
	}
	void Input::cursor_position_callback_handle(GLFWwindow *window, double xpos, double ypos)
	{
		getInstance()->cursor_position_callback(window, xpos, ypos);
	}


	//Callback implementations
	void Input::window_resize_callback(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
	void Input::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		//set key bool true when key press (not released)
		m_Keys[key] = action != GLFW_RELEASE;
	}
	void Input::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
	{
		m_MouseButtons[button] = action != GLFW_RELEASE;
	}
	void Input::cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
	{
		RawMouseX = xpos;
		RawMouseY = ypos;

		if (RawMouseX < 320)
			NormalisedMouseX = -320 + RawMouseX;
		if (RawMouseX > 320)
			NormalisedMouseX = RawMouseX - 320;

		if (RawMouseY < 240)
			NormalisedMouseY = 240 - RawMouseY;
		if (RawMouseY > 240)
			NormalisedMouseY = -(RawMouseY - 240);

		if (RawMouseX == 320)
			NormalisedMouseX = 0;

		#if (DEBUG)
		//std::cout << "X:" << NormalisedMouseX << " Y:" << NormalisedMouseY << "\n";
		#endif
	}
	bool Input::getKeyDown(uint32_t keyCode)
	{
		//TODO: log this
		if (keyCode >= MAX_KEYS)
			return false;
		
		return getInstance()->m_Keys[keyCode];
	}


}	}