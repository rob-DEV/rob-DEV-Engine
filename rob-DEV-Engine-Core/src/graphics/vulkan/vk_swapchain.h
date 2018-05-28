#pragma once
#include "vk_include.h"
#include "vk_surface.h"
#include <vector>

#if(_ENGINE_RENDERER_VULKAN)

namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	class VKSwapchain
	{
	private:
		bool m_IsSetup = false;
	public:
		VKSwapchain();
		~VKSwapchain();
		SwapChainSupportDetails Details;
		void querySwapChainDetails(const VkPhysicalDevice& device, const VKSurface& windowing_surface);
	};

} } } }

#endif