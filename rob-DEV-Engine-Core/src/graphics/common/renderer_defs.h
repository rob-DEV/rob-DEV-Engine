#pragma once
namespace Engine { namespace Core { namespace Graphics {
	//set the max amounts which the renderer can handle
	#define RENDERER_MAX_BUFFER_SIZE 5000000
	#define RENDERER_VERTEX_SIZE sizeof(Engine::Core::Graphics::VertexData)

	#define SHADER_VERTEX_INDEX 0
	#define SHADER_FRAGMENT_INDEX 1

	//describes an individual vertex pushed from a model into the renderer::submit()
	struct VertexData
	{
		glm::vec3 position;
		unsigned int color;
	};

	struct IndiceData
	{
		unsigned int indice;
	};
} } }