#include "vulkan_renderer.h"
#include <iostream>
#include <glm/gtx/norm.hpp>

namespace Engine { namespace Core { namespace Graphics {

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

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		createInfo.enabledLayerCount = 0;

		m_InstanceResult = vkCreateInstance(&createInfo, nullptr, &m_Instance);
		if (m_InstanceResult != VK_SUCCESS)
			std::cout << "Failed to create Vulkan Instance!\n";
		
		//extension info TODO: remove in release
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);
		m_ExtensionsInfo.resize(extensionCount);
		//fill the info
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, m_ExtensionsInfo.data());

		std::cout << "Vulkan Extensions\n";
		for (const auto extension : m_ExtensionsInfo)
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