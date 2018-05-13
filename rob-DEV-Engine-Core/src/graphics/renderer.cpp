#include "renderer.h"
#include <iostream>

namespace Engine { namespace Core { namespace Graphics {

Renderer::Renderer()
{
	init();
}


Renderer::~Renderer()
{

}

void Renderer::init()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Shaders = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shaders->enable();

	
	glGenBuffers(1, &m_VBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, RENDERER_MAX_BUFFER_SIZE, NULL, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
	glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);

	glEnableVertexAttribArray(SHADER_FRAGMENT_INDEX);
	glVertexAttribPointer(SHADER_FRAGMENT_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));



}

void Renderer::begin()
{
	//mapping to be added
	m_VertexBufferCount = 0;
	m_VertexBuffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void Renderer::submit(const Engine::Core::Graphics::Mesh& mesh)
{
	if (&mesh == NULL)
		return;

	for (size_t i = 0; i < mesh.vertices.size(); i++)
	{
		m_VertexBuffer->position = mesh.vertices[i];

		int r = mesh.colors[i].x * 255.0f;
		int g = mesh.colors[i].y * 255.0f;
		int b = mesh.colors[i].z * 255.0f;
		int a = 255;

		unsigned int c = a << 24 | b << 16 | g << 8 | r;


		m_VertexBuffer->color = c;
		m_VertexBuffer++;


	}

	glBufferSubData(GL_ARRAY_BUFFER, m_VertexBufferCount * RENDERER_VERTEX_SIZE, mesh.vertices.size() * RENDERER_VERTEX_SIZE, m_VertexBuffer);

	m_VertexBufferCount += mesh.vertices.size();

}
void Renderer::submit(const Engine::Core::Entities::GameObject* gameObject)
{
	if (gameObject == NULL)
		return;
}

void Renderer::end()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
}

void Renderer::draw()
{
	std::cout << "VERTEX DRAW COUNT: " << m_VertexBufferCount << "\n";
	glDrawArrays(GL_TRIANGLES, 0, m_VertexBufferCount);
}

void Renderer::dispose()
{
	//assuming buffers are created in init()
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
}

} } }