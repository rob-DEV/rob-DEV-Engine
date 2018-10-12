#include "application.h"

namespace Engine { namespace Core {

	Application::Application()
	{
		Init();
	}

	void Application::Init()
	{
		//set up window, renderer, level, scripts
		//seriously need fixed time updating to ensure 60ups with unlimited fps

	}

	Application::~Application()
	{
	}

} }