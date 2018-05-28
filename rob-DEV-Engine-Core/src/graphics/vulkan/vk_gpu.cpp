#include "vk_gpu.h"
#include <iostream>
#include <set>

#if(_ENGINE_RENDERER_VULKAN)
namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	VKGPU::VKGPU()
	{

	}

	VKGPU::~VKGPU()
	{

	}

	void VKGPU::setupGPU(const Window& rendererWindow)
	{
		m_VKSurface.setupNativeWindowHandle(rendererWindow, m_VKInstance);
		init();
		
	}

	bool VKGPU::isSupportedDevice(const VkPhysicalDevice& device)
	{
		//check the details of the GPU
		VkPhysicalDeviceProperties deviceProperties;
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

		
		//check supported indices
		QueueFamilyIndices indices = findQueueFamilies(device);

		//TODO: make a more complex checking system taking other PhyDev details into account
		bool extensionsSupported = checkDeviceExtensionSupport(device);
		bool swapChainAdequate = false;

		if (extensionsSupported)
		{
			//get swapchain info (using a seperate class) probably will refactor this as it doesn't need to be modular
			m_SwapChain.querySwapChainDetails(device, m_VKSurface);
			SwapChainSupportDetails swapChainSupport = m_SwapChain.Details;
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}

		return indices.isComplete() && extensionsSupported && swapChainAdequate;
	}

	QueueFamilyIndices VKGPU::findQueueFamilies(const VkPhysicalDevice& device)
	{
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
		//check against needed queues
		//TODO: add more checks
		int i = 0;
		for (const auto& queueFamily : queueFamilies) {
			
			if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				indices.graphicsFamily = i;

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_VKSurface.VkSurfaceHandle, &presentSupport);

			if (queueFamily.queueCount > 0 && presentSupport)
				indices.presentFamily = i;


			if (indices.isComplete())
				break;
			i++;
		}
		return indices;
	}

	bool VKGPU::checkDeviceExtensionSupport(const VkPhysicalDevice& device)
	{
		uint32_t extensionCount = 0;
		vkEnumerateDeviceExtensionProperties(device, NULL, &extensionCount, NULL);
		
		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, NULL, &extensionCount, availableExtensions.data());

		std::set<std::string> requiredExtensions(m_DeviceExtensions.begin(), m_DeviceExtensions.end());

		for (const auto& extension : availableExtensions)
			requiredExtensions.erase(extension.extensionName);

		return requiredExtensions.empty();
	}

	void VKGPU::init()
	{
		//list all graphics cards
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_VKInstance.VkInstanceHandle, &deviceCount, NULL);

		if (deviceCount == 0)
			std::cout << "Failed to find physical devices!\n";

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(m_VKInstance.VkInstanceHandle, &deviceCount, devices.data());

		for (const VkPhysicalDevice& device : devices)
			//use the first supported GPU (I'm using a GTX 760 fopr this)
			if (isSupportedDevice(device))
			{
				VkPhysicalDeviceHandle = device;
				break;
			}

		//print physical device information
		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(VkPhysicalDeviceHandle, &deviceProperties);
		
		std::cout << "GPU Physical Device Information:\n";
		std::cout << "\t Device ID:" << deviceProperties.deviceID << "\n";
		std::cout << "\t Device Name:" << deviceProperties.deviceName << "\n";
		std::cout << "\t Device Vendor:" << deviceProperties.vendorID << "\n";
		std::cout << "\t Device API Version:" << deviceProperties.apiVersion << "\n";

		//create the logical GPU based on the physical
		QueueFamilyIndices indices = findQueueFamilies(VkPhysicalDeviceHandle);

		//create a set of queueionfos for all the required queues
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<int> uniqueQueueFamilies = { indices.graphicsFamily, indices.presentFamily };

		//set priority to 1.0f as there is only two queues in existence atm
		float queuePriority = 1.0f;
		for (int queueFamily : uniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo queueCreateInfo = {};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		//TODO: check docs on this VK_FALSE??
		VkPhysicalDeviceFeatures deviceFeatures = {};

		//create the logical device
		VkDeviceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.queueCreateInfoCount = queueCreateInfos.size();
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = 0;
		createInfo.enabledExtensionCount = m_DeviceExtensions.size();
		createInfo.ppEnabledExtensionNames = m_DeviceExtensions.data();
		

		if (m_VKInstance.isValidationLayersEnable)
		{
			createInfo.enabledLayerCount = m_VKInstance.ValidationLayers.size();
			createInfo.ppEnabledLayerNames = m_VKInstance.ValidationLayers.data();
		}
		else
		{
			createInfo.enabledLayerCount = 0;
		}

		if (vkCreateDevice(VkPhysicalDeviceHandle, &createInfo, nullptr, &VkLogicalDeviceHandle) != VK_SUCCESS)
			std::cout << "Vulkan Error: Failed to create logical device!\n";

		//assign the actual vk device handles
		vkGetDeviceQueue(VkLogicalDeviceHandle, indices.presentFamily, 0, &VkPresentQueueHandle);
		vkGetDeviceQueue(VkLogicalDeviceHandle , indices.graphicsFamily, 0, &VkGraphicsQueueHandle);
	}

	void VKGPU::dispose()
	{
		vkDestroyDevice(VkLogicalDeviceHandle, NULL);
		vkDestroyInstance(m_VKInstance.VkInstanceHandle, NULL);
	}


} } } }

#endif