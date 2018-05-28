#pragma once
#include "vk_include.h"

#if(_ENGINE_RENDERER_VULKAN)
#include "../window.h"

namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	//TODO: refactor ALL vulkan objects to the header to ensure deletion!!
	//TODO: class abstraction for VK objects
	class VKInstance
	{
	public:

		VKInstance();
		~VKInstance();

	};

} } } }

#endif