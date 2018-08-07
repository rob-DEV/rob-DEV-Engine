#pragma once
#include "direct3d_include.h"
#include "../common/i_renderer.h"


#if(_ENGINE_RENDERER_DIRECT3D)


namespace Engine { namespace Core { namespace Graphics { namespace Direct3D { 

	class Direct3DRenderer : public IRenderer
	{

	private:
		void init() override;
		void submit(Engine::Core::Graphics::Mesh* mesh, glm::vec3 position, glm::quat rotation) override;
	public:

		Direct3DRenderer();
		~Direct3DRenderer();

		void begin() override;

		void submit(Engine::Core::Graphics::Mesh* mesh) override;
		void submit(Engine::Core::Entities::Entity* renderableEntity) override;

		void draw() override;
		void end() override;

		void dispose() override;

	};

} } } }
#endif