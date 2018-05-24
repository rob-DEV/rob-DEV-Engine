#include "vk_logical_device.h"
#include <iostream>

namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	VKLogicalDevice::VKLogicalDevice()
	{
		init();
	}

	VKLogicalDevice::~VKLogicalDevice()
	{

	}

	bool VKLogicalDevice::isSupportedDevice(VkPhysicalDevice device)
	{
		return true;
	}

	void VKLogicalDevice::init()
	{

	}

} } } }