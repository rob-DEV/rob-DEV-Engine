#pragma once
#include "../common/base_renderer.h"

namespace Engine { namespace Core { namespace Graphics { 

	class VulkanRenderer : public IRenderer
	{
	private:
		VkInstance m_Instance;
		VkResult m_InstanceResult;
		std::vector<VkExtensionProperties> m_ExtensionsInfo;
		
		std::vector<const char*> m_ValidationLayers = { "VK_LAYER_LUNARG_standard_validation" };
		std::vector<VkLayerProperties> m_AvailableValidationLayers;

		#if(DEBUG)
		const bool m_EnableValidationLayers = true;
		#else
		const bool m_EnableValidationLayers = false;
		#endif

	private:
		void init() override;
		bool checkValidationLayers();
		void submit(Engine::Core::Graphics::Mesh* mesh, glm::vec3 position, glm::quat rotation) override;
	public:

		Shader* Shaders = NULL;

		VulkanRenderer();
		~VulkanRenderer();

		void begin() override;

		void submit(Engine::Core::Graphics::Mesh* mesh) override;
		void submit(Engine::Core::Entities::Entity* renderableEntity) override;

		void draw() override;
		void end() override;

		void dispose() override;

	};

} } }