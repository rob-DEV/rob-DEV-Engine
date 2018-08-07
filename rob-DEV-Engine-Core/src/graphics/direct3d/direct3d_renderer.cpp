#include "direct3d_renderer.h"

#if(_ENGINE_RENDERER_DIRECT3D)
#include <iostream>
#include <glm/gtx/norm.hpp>

namespace Engine { namespace Core { namespace Graphics { namespace Direct3D {

	Direct3DRenderer::Direct3DRenderer()
	{
		init();
	}


	Direct3DRenderer::~Direct3DRenderer()
	{

	}

	void Direct3DRenderer::init()
	{
	
	}

	void Direct3DRenderer::begin()
	{
		
	}

	void Direct3DRenderer::submit(Engine::Core::Graphics::Mesh* mesh, glm::vec3 position, glm::quat rotation)
	{
		/*

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
		*/
	}

	void Direct3DRenderer::submit(Engine::Core::Graphics::Mesh* mesh)
	{
		if (mesh == NULL)
			return;
		submit(mesh, glm::vec3(0, 0, 0), glm::quat());
	}

	void Direct3DRenderer::submit(Engine::Core::Entities::Entity* renderableEntity)
	{
		if (((Engine::Core::Entities::GameObject*)renderableEntity) == NULL)
			return;
		if (((Engine::Core::Entities::GameObject*)renderableEntity)->mesh == NULL)
			return;

		if (((Engine::Core::Entities::GameObject*)renderableEntity)->mesh->vertices.size() < 1)
			return;

		//render at a given position
		submit(((Engine::Core::Entities::GameObject*)renderableEntity)->mesh, ((Engine::Core::Entities::GameObject*)renderableEntity)->transform.position, ((Engine::Core::Entities::GameObject*)renderableEntity)->transform.rotation);
	}

	void Direct3DRenderer::end()
	{
	}

	void Direct3DRenderer::draw()
	{
	}

	void Direct3DRenderer::dispose()
	{

	}

} } } }

#endif