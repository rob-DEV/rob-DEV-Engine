#include "vk_physical_device.h"
#include <iostream>

#if(ENGINE_RENDERER_VULKAN)
namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	VK_GPU::VK_GPU()
	{
		init();
	}

	VK_GPU::~VK_GPU()
	{
		vkDestroyDevice(VkLogicalDeviceHandle, NULL);
	}

	bool VK_GPU::isSupportedDevice(VkPhysicalDevice device)
	{
		//check the details of the GPU
		VkPhysicalDeviceProperties deviceProperties;
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

		//check supported indices
		QueueFamilyIndices indices = findQueueFamilies(device);

		//TODO: make a more complex checking system taking other PD details into account
		return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
			deviceFeatures.geometryShader && indices.isComplete();
	}

	QueueFamilyIndices VK_GPU::findQueueFamilies(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
		//check against needed queues
		//TODO: add more check
		int i = 0;
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				indices.graphicsFamily = i;
			}
			if (indices.isComplete()) {
				break;
			}
			i++;
		}

		return indices;
	}

	void VK_GPU::init()
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
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = indices.graphicsFamily;
		queueCreateInfo.queueCount = 1;

		//set priority to 1.0f as there is only one queue in existence atm
		float queuePriority = 1.0f;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		//TODO: check docs on this VK_FALSE??
		VkPhysicalDeviceFeatures deviceFeatures = {};

		//create the logical device
		VkDeviceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = &queueCreateInfo;
		createInfo.queueCreateInfoCount = 1;
		createInfo.pEnabledFeatures = &deviceFeatures;
		
		createInfo.enabledExtensionCount = 0;
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

		vkGetDeviceQueue(VkLogicalDeviceHandle , indices.graphicsFamily, 0, &VkGraphicsQueueHandle);
	}


} } } }

#endif