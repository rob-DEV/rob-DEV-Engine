#include "vk_physical_device.h"
#include <iostream>

namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	VKPhysicalDevice::VKPhysicalDevice()
	{
		init();
	}

	VKPhysicalDevice::~VKPhysicalDevice()
	{

	}

	bool VKPhysicalDevice::isSupportedDevice(VkPhysicalDevice device)
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

	QueueFamilyIndices VKPhysicalDevice::findQueueFamilies(VkPhysicalDevice device)
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

	void VKPhysicalDevice::init()
	{
		//list all graphics cards
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_VKInstance.Instance_Handle, &deviceCount, NULL);

		if (deviceCount == 0)
			std::cout << "Failed to find physical devices!\n";

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(m_VKInstance.Instance_Handle, &deviceCount, devices.data());

		for (const VkPhysicalDevice& device : devices)
			//use the first supported GPU (I'm using a GTX 760 fopr this)
			if (isSupportedDevice(device))
			{
				m_PhysicalDevice = device;
				break;
			}

		//print physical device information
		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(m_PhysicalDevice, &deviceProperties);
		
		std::cout << "GPU Physical Device Information:\n";
		std::cout << "\t Device ID:" << deviceProperties.deviceID << "\n";
		std::cout << "\t Device Name:" << deviceProperties.deviceName << "\n";
		std::cout << "\t Device Vendor:" << deviceProperties.vendorID << "\n";
		std::cout << "\t Device API Version:" << deviceProperties.apiVersion << "\n";

		//check supported family queues




	}

} } } }