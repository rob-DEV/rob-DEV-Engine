#include "renderer.h"
#include <iostream>
#include <glm/gtx/norm.hpp>

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
	
		m_VAO.bind();
		m_VBO.bind();

		glBufferData(GL_ARRAY_BUFFER, RENDERER_MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
	
		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);

		glEnableVertexAttribArray(SHADER_FRAGMENT_INDEX);
		glVertexAttribPointer(SHADER_FRAGMENT_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));

		m_IBO.bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, RENDERER_MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
		m_IBO.unbind();

		m_VAO.unbind();
	
	}

	void Renderer::begin()
	{
		m_VAO.bind();

		m_VBO.bind();
		m_VertexBuffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

		m_IBO.bind();
		m_IndiceBuffer = (IndiceData*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
	
	}

	void Renderer::submit(Engine::Core::Graphics::Mesh* mesh, glm::vec3 position, glm::quat rotation)
	{
		

		glm::mat4 rotation_mat = glm::toMat4(rotation);


		for (size_t i = 0; i < mesh->indices.size(); i++)
		{
			//need to add indice offset
			m_IndiceBuffer->indice = mesh->indices[i] + m_VertexCount;
			m_IndiceBuffer++;

			if (i < mesh->vertices.size())
			{
				//modify the vertex for the rotation (this does work)
				glm::vec3 rotate_corrected_vertex((rotation_mat * glm::vec4(mesh->vertices[i], 1.0)).x, (rotation_mat * glm::vec4(mesh->vertices[i], 1.0)).y, (rotation_mat * glm::vec4(mesh->vertices[i], 1.0)).z);

				rotate_corrected_vertex += position;

				m_VertexBuffer->position = rotate_corrected_vertex;
				m_VertexBuffer->color = mesh->rgb_colors[i];
				m_VertexBuffer++;

			}
		}

		m_VertexCount += mesh->vertices.size();
		m_IndiceCount += mesh->indices.size();

	}

	void Renderer::submit(Engine::Core::Graphics::Mesh* mesh)
	{
		if (mesh == NULL)
			return;
		submit(mesh, glm::vec3(0, 0, 0), glm::quat());
	}

	void Renderer::submit(Engine::Core::Entities::GameObject* gameObject)
	{
		if (gameObject == NULL)
			return;
		if (gameObject->mesh == NULL)
			return;

		if (gameObject->mesh->vertices.size() < 1)
			return;

		//render at a given position
		submit(gameObject->mesh, gameObject->transform.position, gameObject->transform.rotation);
	}

	void Renderer::end()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	}

	void Renderer::draw()
	{
		glDrawElements(
			GL_TRIANGLES,      // mode
			m_IndiceCount,    // count
			GL_UNSIGNED_INT,   // type
			(void*)0           // element array buffer offset
		);

		//reset counters for the next frame
		m_IndiceCount = 0;
		m_VertexCount = 0;
	}

	void Renderer::dispose()
	{
		//assuming buffers are created in init()
		m_VAO.bind();

		m_VBO.del();
		m_IBO.del();
		m_VAO.del();

	}

} } }