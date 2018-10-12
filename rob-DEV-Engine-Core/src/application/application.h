#pragma once

namespace Engine { namespace Core {
	
	class Application
	{
	private:
		bool m_IsRunning = false;
		void Init();
	public:
		Application();
		~Application();
	};

} }