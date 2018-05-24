#include "vulkan_renderer.h"
#include <iostream>
#include <glm/gtx/norm.hpp>

namespace Engine { namespace Core { namespace Graphics {

	//debug error calback handler
	VKAPI_ATTR VkBool32 VKAPI_CALL VuldebugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, uint32_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData)
	{
		std::cout << "Vulkan Validation Layer ERROR: " << msg << "\n";

		return VK_FALSE;
	}

	VulkanRenderer::VulkanRenderer()
	{
		init();
	}


	VulkanRenderer::~VulkanRenderer()
	{
		//cleanup instances
		vkDestroyInstance(m_Instance, NULL);
	}

	void VulkanRenderer::init()
	{
		setupRequiredExtensions();
		createVulkanInstance();
	}

	bool VulkanRenderer::checkValidationLayersSupport()
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, NULL);
		m_VKAvailableValidationLayers.resize(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, m_VKAvailableValidationLayers.data());


		for (const char* layerName : m_ValidationLayers) {
			bool layerFound = false;
			for (const auto& layerProperties : m_VKAvailableValidationLayers) {
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
	
	void VulkanRenderer::setupRequiredExtensions()
	{
		//get GLFW extensions and add the validation extension depending on build configuration
		unsigned int glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		for (unsigned int i = 0; i < glfwExtensionCount; i++) {
			m_VKRequiredExtensions.push_back(glfwExtensions[i]);
		}
		if (m_EnableValidationLayers) {
			m_VKRequiredExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		}
	}

	void VulkanRenderer::createVulkanInstance()
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

		if (m_EnableValidationLayers && checkValidationLayersSupport())
		{
			std::cout << "Validation layers exist and are active!\n";
			createInfo.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayers.size());
			createInfo.ppEnabledLayerNames = m_ValidationLayers.data();
		}
		else
		{
			createInfo.enabledLayerCount = 0;
		}

		m_InstanceResult = vkCreateInstance(&createInfo, nullptr, &m_Instance);
		if (m_InstanceResult != VK_SUCCESS)
			std::cout << "Failed to create Vulkan Instance!\n";

		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);
		m_VKSupportedExtensionsInfo.resize(extensionCount);
		//fill the info
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, m_VKSupportedExtensionsInfo.data());

		std::cout << "Vulkan Supported Extensions\n";
		for (const auto extension : m_VKSupportedExtensionsInfo)
			std::cout << "\t" << extension.extensionName << std::endl;



	}
	
	void VulkanRenderer::begin()
	{

	}

	void VulkanRenderer::submit(Engine::Core::Graphics::Mesh* mesh, glm::vec3 position, glm::quat rotation)
	{

	}

	void VulkanRenderer::submit(Engine::Core::Graphics::Mesh* mesh)
	{
	
	}

	void VulkanRenderer::submit_triangle_test()
	{
		//used for testing vulkan
	}

	void VulkanRenderer::submit(Engine::Core::Entities::Entity* renderableEntity)
	{

	}

	void VulkanRenderer::end()
	{
		
	}

	void VulkanRenderer::draw()
	{
			
	}

	void VulkanRenderer::dispose()
	{

	}

} } }