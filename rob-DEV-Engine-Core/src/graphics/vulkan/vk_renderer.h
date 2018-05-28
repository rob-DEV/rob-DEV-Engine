#pragma once
#include "vk_include.h"
#include "../common/i_renderer.h"

#if(_ENGINE_RENDERER_VULKAN)
#include "vk_instance.h"
#include "../window.h"

namespace Engine { namespace Core { namespace Graphics { namespace Vulkan {

	//TODO: refactor ALL vulkan objects to the header to ensure deletion!!
	//TODO: class abstraction for VK objects
	class VKRenderer : public IRenderer
	{
	private:

	private:
		void init() override;
		void submit(Engine::Core::Graphics::Mesh* mesh, glm::vec3 position, glm::quat rotation) override;
	public:

		VKRenderer(const Window& rendererWindow);
		~VKRenderer();

		void begin() override;

		void submit(Engine::Core::Graphics::Mesh* mesh) override;
		void submit(Engine::Core::Entities::Entity* renderableEntity) override;
		void submit_triangle_test();

		void draw() override;
		void end() override;

		void dispose() override;

	};

} } } }

#endif