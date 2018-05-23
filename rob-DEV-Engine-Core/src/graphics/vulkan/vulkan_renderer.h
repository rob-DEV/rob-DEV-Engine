#pragma once
#include "../common/base_renderer.h"

namespace Engine { namespace Core { namespace Graphics { 

	class VulkanRenderer : public IRenderer
	{
	private:
		VkInstance m_Instance;
		VkResult m_InstanceResult;
		std::vector<VkExtensionProperties> m_ExtensionsInfo;
	private:
		void init() override;
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