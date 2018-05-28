#include "vk_swapchain.h"

#if(_ENGINE_RENDERER_VULKAN)
namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	VKSwapchain::VKSwapchain()
	{

	}

	VKSwapchain::~VKSwapchain()
	{

	}

	void VKSwapchain::querySwapChainDetails(const VkPhysicalDevice& device, const VKSurface& vkSurface)
	{
		if (!m_IsSetup)
		{
			SwapChainSupportDetails details;

			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, vkSurface.VkSurfaceHandle, &details.capabilities);

			uint32_t formatCount;
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, vkSurface.VkSurfaceHandle, &formatCount, NULL);
			if (formatCount != 0) {
				details.formats.resize(formatCount);
				vkGetPhysicalDeviceSurfaceFormatsKHR(device, vkSurface.VkSurfaceHandle, &formatCount, details.formats.data());
			}

			uint32_t presentModeCount;
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, vkSurface.VkSurfaceHandle, &presentModeCount, nullptr);
			if (presentModeCount != 0) {
				details.presentModes.resize(presentModeCount);
				vkGetPhysicalDeviceSurfacePresentModesKHR(device, vkSurface.VkSurfaceHandle, &presentModeCount, details.presentModes.data());
			}

			Details = details;
		}
	}

} } } }

#endif

