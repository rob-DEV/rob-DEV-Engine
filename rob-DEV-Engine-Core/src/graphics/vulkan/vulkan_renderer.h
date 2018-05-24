#pragma once
#include "../common/i_renderer.h"
#include "vk_instance.h"
#include "vk_physical_device.h"

namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	//TODO: refactor ALL vulkan objects to the header to ensure deletion!!
	//TODO: class abstraction for VK objects
	class VulkanRenderer : public IRenderer
	{
	private:
		VK_GPU m_VK_GPU_Device;

	private:
		void init() override;
		void submit(Engine::Core::Graphics::Mesh* mesh, glm::vec3 position, glm::quat rotation) override;
	public:

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

} } } }