#pragma once
#include "vk_include.h"

#if(_ENGINE_RENDERER_VULKAN)
#include <vector>
namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	class VKInstance
	{
	private:
		void init();
	public:
		VKInstance();
		~VKInstance();
		void destroy();
	};

} } } }

#endif
