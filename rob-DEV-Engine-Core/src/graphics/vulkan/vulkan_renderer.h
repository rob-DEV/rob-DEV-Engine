#pragma once
#include "../common/i_renderer.h"

namespace Engine { namespace Core { namespace Graphics { 

	class VulkanRenderer : public IRenderer
	{
	private:
		//renderer error handle debug callback
		static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanRenderer::debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, uint32_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData);
	private:
		VkInstance m_Instance;
		VkResult m_InstanceResult;

		std::vector<const char*> m_VKRequiredExtensions;
		std::vector<VkExtensionProperties> m_VKSupportedExtensionsInfo;
		std::vector<VkLayerProperties> m_VKAvailableValidationLayers;


		#if(DEBUG)
		//using VKAPI standard validation layers
		std::vector<const char*> m_ValidationLayers = { "VK_LAYER_LUNARG_standard_validation" };
		const bool m_EnableValidationLayers = true;
		#else
		const bool m_EnableValidationLayers = false;
		#endif

	private:
		void init() override;
		bool checkValidationLayersSupport();
		void setupRequiredExtensions();
		void setupDebugErrorCallback();
		void createVulkanInstance();

		void submit(Engine::Core::Graphics::Mesh* mesh, glm::vec3 position, glm::quat rotation) override;
	public:

		Shader* Shaders = NULL;

		VulkanRenderer();
		~VulkanRenderer();

		void begin() override;

		void submit(Engine::Core::Graphics::Mesh* mesh) override;
		void submit(Engine::Core::Entities::Entity* renderableEntity) override;
		void submit_triangle_test();

		void draw() override;
		void end() override;

		void dispose() override;

	};

} } }