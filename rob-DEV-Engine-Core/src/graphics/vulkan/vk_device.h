#pragma once
#include "vk_include.h"

#if(_ENGINE_RENDERER_VULKAN)
#include "vk_swapchain.h"

#include <vector>
namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	class VKDevice
	{
	private:
		void init();
	public:
		VKDevice();
		~VKDevice();
		void destroy();
	};

} } } }

#endif
