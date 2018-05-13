#pragma once
#include <GL/glew.h>

#include "../entity/game_object.h"
#include "shader.h"

//set the max amounts which the renderer can handle
#define RENDERER_MAX_BUFFER_SIZE 5000000
#define RENDERER_VERTEX_SIZE sizeof(Engine::Core::Graphics::VertexData)

#define SHADER_VERTEX_INDEX 0
#define SHADER_FRAGMENT_INDEX 1


namespace Engine { namespace Core { namespace Graphics { 

	//describes an individual vertex pushed from a model into the renderer::submit()
	struct VertexData
	{
		glm::vec3 position;
		unsigned int color;
	};

class Renderer
{
private:
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_IBO;

	VertexData* m_VertexBuffer;

	GLsizei m_VertexBufferCount = 0;
	GLsizei m_IndiceCount;

private:
	void init();
public:

	Shader* Shaders = NULL;

	Renderer();
	~Renderer();

	void begin();

	void submit(const Engine::Core::Graphics::Mesh& mesh);
	void submit(const Engine::Core::Entities::GameObject* gameObject);

	void draw();
	void end();

	void dispose();

};

} } }