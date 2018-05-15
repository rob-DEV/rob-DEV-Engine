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
	
	//glGenVertexArrays(1, &m_VAO);


	m_VBO.bind();

	glBindVertexArray(m_VAO);


	glBufferData(GL_ARRAY_BUFFER, RENDERER_MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
	
	glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
	glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);

	glEnableVertexAttribArray(SHADER_FRAGMENT_INDEX);
	glVertexAttribPointer(SHADER_FRAGMENT_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
	
	m_VBO.unbind();


	m_IBO.bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, RENDERER_MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
	m_IBO.unbind();
}

void Renderer::begin()
{
	m_IndiceCount = 0;

	m_VBO.bind();
	m_VertexBuffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	m_IBO.bind();
	m_IndiceBuffer = (IndiceData*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
	
}

void Renderer::submit(const Engine::Core::Graphics::Mesh& mesh, glm::vec3 position)
{
	
	for (size_t i = 0; i < mesh.indices.size(); i++)
	{
		m_IndiceBuffer->indice = mesh.indices[i];
		m_IndiceBuffer++;

		if (i < mesh.vertices.size())
		{
			glm::vec3 temp_vert_to_pos = mesh.vertices[i];
			temp_vert_to_pos.x += position.x;
			temp_vert_to_pos.y += position.y;
			temp_vert_to_pos.z += position.z;

			m_VertexBuffer->position = temp_vert_to_pos;

			m_VertexBuffer->color = mesh.rgb_colors[i];
			m_VertexBuffer++;
		}
	}
	
	m_IndiceCount += mesh.indices.size();
}

void Renderer::submit(const Engine::Core::Graphics::Mesh& mesh)
{
	if (&mesh == NULL)
		return;
	submit(mesh, glm::vec3(0, 0, 0));
}
void Renderer::submit(const Engine::Core::Entities::GameObject& gameObject)
{
	if (&gameObject == NULL)
		return;

	//render at a given position
	submit(*gameObject.mesh, gameObject.transform.position);
}

void Renderer::end()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	
}

void Renderer::draw()
{
	//glDrawArrays(GL_TRIANGLES, 0, m_VertexBufferCount);

	m_IBO.bind();

	glDrawElements(
		GL_TRIANGLES,      // mode
		m_IndiceCount,    // count
		GL_UNSIGNED_INT,   // type
		(void*)0           // element array buffer offset
	);

	

}

void Renderer::dispose()
{
	//assuming buffers are created in init()
	m_VBO.del();
	m_IBO.del();
}

} } }