#include "vk_instance.h"
#include "vk_ext_utils.h"
#include <iostream>

#if(_ENGINE_RENDERER_VULKAN)
namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	VKInstance::VKInstance()
	{
		init();
	}

	void VKInstance::init()
	{
		setupRequiredExtensions();
		createVulkanInstance();
		setupDebugErrorCallback();
	}

	VKInstance::~VKInstance()
	{
	}

	//debug error calback handler
	VKAPI_ATTR VkBool32 VKAPI_CALL VKInstance::vkDebugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, uint32_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData)
	{
		std::cout << "Vulkan ERROR: " << msg << "\n";
		return VK_FALSE;
	}

	bool VKInstance::checkValidationLayersSupport()
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, NULL);
		VkAvailableValidationLayers.resize(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, VkAvailableValidationLayers.data());


		for (const char* layerName : ValidationLayers) {
			bool layerFound = false;
			for (const auto& layerProperties : VkAvailableValidationLayers) {
				if (strcmp(layerName, layerProperties.layerName) == 0) {
					layerFound = true;
					break;
				}
			}
			if (!layerFound) {
				return false;
			}
		}

		return true;
	}

	void VKInstance::setupRequiredExtensions()
	{
		//get GLFW extensions and add the validation extension depending on build configuration
		unsigned int glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		for (unsigned int i = 0; i < glfwExtensionCount; i++)
			m_VKRequiredExtensions.push_back(glfwExtensions[i]);
		if (isValidationLayersEnable)
			m_VKRequiredExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	}

	void VKInstance::createVulkanInstance()
	{
		//setup the vulkan instance
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "MAIN ENGINE RENDERER";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "rob-DEV-Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		//TODO: check this out!
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		//provide the instance info with the currently in use vulkan extensions
		createInfo.enabledExtensionCount = m_VKRequiredExtensions.size();
		createInfo.ppEnabledExtensionNames = m_VKRequiredExtensions.data();
		createInfo.enabledLayerCount = 0;

		if (isValidationLayersEnable && checkValidationLayersSupport())
		{
			std::cout << "Validation layers exist and are active!\n";
			createInfo.enabledLayerCount = static_cast<uint32_t>(ValidationLayers.size());
			createInfo.ppEnabledLayerNames = ValidationLayers.data();
		}
		else
		{
			createInfo.enabledLayerCount = 0;
		}

		VkInstanceResult = vkCreateInstance(&createInfo, nullptr, &VkInstanceHandle);
		if (VkInstanceResult != VK_SUCCESS)
			std::cout << "Failed to create Vulkan Instance!\n";

		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);
		VkSupportedExtensionsInfo.resize(extensionCount);
		//fill the info
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, VkSupportedExtensionsInfo.data());

		std::cout << "Vulkan Supported Extensions\n";
		for (const auto extension : VkSupportedExtensionsInfo)
			std::cout << "\t" << extension.extensionName << std::endl;



	}


	void VKInstance::setupDebugErrorCallback()
	{
		if (!isValidationLayersEnable) return;

		VkDebugReportCallbackCreateInfoEXT createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
		createInfo.pfnCallback = vkDebugCallback;

		//register callback information and callback function ptr
		if (CreateDebugReportCallbackEXT(VkInstanceHandle, &createInfo, NULL, &m_DebuggingCallBack) != VK_SUCCESS)
			std::cout << "Error registering debug error handle callback in setupDebugErrorCallback()";

	}

	void VKInstance::destroy()
	{
		DestroyDebugReportCallbackEXT(VkInstanceHandle, m_DebuggingCallBack, NULL);
		vkDestroyInstance(VkInstanceHandle, NULL);
	}

} } } }

#endif