#pragma once
#include <GL/glew.h>
#include "buffers/vertex_buffer.h"
#include "buffers/index_buffer.h"
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

struct IndiceData
{
	unsigned int indice;
};

class Renderer
{
private:
	
	Buffers::VertexBufferObject m_VBO;
	Buffers::IndexBufferObject m_IBO;

	GLuint m_VAO;

	VertexData* m_VertexBuffer;
	IndiceData* m_IndiceBuffer;

	GLsizei m_IndiceCount;

	GLsizei m_VertexCount;

	#if(_DEBUG)
	std::vector<unsigned int> indiceRAW;
	#endif


private:
	void init();
	void submit(const Engine::Core::Graphics::Mesh& mesh, glm::vec3 position);
public:

	Shader* Shaders = NULL;

	Renderer();
	~Renderer();

	void begin();

	void submit(const Engine::Core::Graphics::Mesh& mesh);
	void submit(const Engine::Core::Entities::GameObject& gameObject);

	void draw();
	void end();

	void dispose();

};

} } }