#pragma once
#include "vk_instance.h"
#include "vk_surface.h"
#include "vk_swapchain.h"

#if(_ENGINE_RENDERER_VULKAN)
namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	struct QueueFamilyIndices {
		int graphicsFamily = -1;
		int presentFamily = -1;
		bool isComplete() {
			return graphicsFamily >= 0 && presentFamily >= 0;
		}
	};

	class VKGPU 
	{
	private:
		void init();
		bool isSupportedDevice(const VkPhysicalDevice& device);

		QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice& device);

		//checking swap chain support
		std::vector<const char*> m_DeviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
		bool checkDeviceExtensionSupport(const VkPhysicalDevice& device);

	public:
		//physical
		VkPhysicalDevice VkPhysicalDeviceHandle = VK_NULL_HANDLE;
		VkDevice VkLogicalDeviceHandle = VK_NULL_HANDLE;
		VkQueue VkGraphicsQueueHandle = VK_NULL_HANDLE;
		VkQueue VkPresentQueueHandle = VK_NULL_HANDLE;

		//vulkan instance will be initalized for each renderer at instantiation automatically
		VKInstance m_VKInstance;
		VKSurface m_VKSurface;
		VKSwapchain m_SwapChain;
		VKGPU();
		~VKGPU();

		void setupGPU(const Window& renderingWindow);
		void dispose();
	};

} } } }
#endif