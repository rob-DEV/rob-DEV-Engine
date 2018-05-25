#pragma once
#include "vk_include.h"
#include "vk_instance.h"
#include "../window.h"

#if(_ENGINE_RENDERER_VULKAN)
namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	class VKSurface 
	{
	private:
		bool m_IsSetup = false;
	public:
		VkSurfaceKHR VkSurfaceHandle;
		
		//default ctor has no other setup purpose
		VKSurface();
		~VKSurface();

		void setupNativeWindowHandle(const Window& renderWindow, const VKInstance& vkInstance);
		void dispose(const VKInstance& vkInstance);
	};

} } } }
#endif