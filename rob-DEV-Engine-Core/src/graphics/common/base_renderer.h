#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vulkan.h>

#include "../shader.h"
#include "../common/base_renderer.h"
#include "../../entity/game_object.h"
#include "../buffer/vertex_buffer.h"
#include "../buffer/index_buffer.h"
#include "../buffer/vertex_array.h"

namespace Engine { namespace Core { namespace Graphics {
	//set the max amounts which the renderer can handle
	#define RENDERER_MAX_BUFFER_SIZE 5000000
	#define RENDERER_VERTEX_SIZE sizeof(Engine::Core::Graphics::VertexData)

	#define SHADER_VERTEX_INDEX 0
	#define SHADER_FRAGMENT_INDEX 1

	//describes an individual vertex pushed from a model into the renderer::submit()
	typedef struct VertexData
	{
		glm::vec3 position;
		uint32_t color;
	} vertex_data_t;

	typedef struct IndiceData
	{
		uint32_t indice;
	} indice_data_t;

	class IRenderer
	{

	private:
		virtual void init() = 0;
		virtual void submit(Engine::Core::Graphics::Mesh* mesh, glm::vec3 position, glm::quat rotation) = 0;
	public:

		IRenderer() {};
		virtual ~IRenderer() {};

		virtual void begin() = 0;

		virtual void submit(Engine::Core::Graphics::Mesh* mesh) = 0;
		virtual void submit(Engine::Core::Entities::Entity* renderableEntity) = 0;

		virtual void draw() = 0;
		virtual void end() = 0;

		virtual void dispose() = 0;

	};

} } }