#pragma once
#include "vk_include.h"

#if(_ENGINE_RENDERER_VULKAN)

namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	class VKSwapchain
	{
	private:
		void init();
	public:
		VKSwapchain();
		~VKSwapchain();
		void destroy();
	};

} } } }

#endif
