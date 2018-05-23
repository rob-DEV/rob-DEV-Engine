#pragma once
#include <GL/glew.h>
#include <vulkan.h>

#include "../shader.h"
#include "../common/renderer_defs.h"
#include "../../entity/game_object.h"
#include "../buffer/vertex_buffer.h"
#include "../buffer/index_buffer.h"
#include "../buffer/vertex_array.h"

namespace Engine { namespace Core { namespace Graphics { 

	class OpenGLRenderer
	{
	private:
	
		Buffers::VertexArray m_VAO;
		Buffers::VertexBufferObject m_VBO;
		Buffers::IndexBufferObject m_IBO;

		VertexData* m_VertexBuffer;
		IndiceData* m_IndiceBuffer;

		//counters needed for vertex indice mapping in submit()
		//TODO: refactor
		GLsizei m_IndiceCount;
		GLsizei m_VertexCount;


	private:
		void init();
		void submit(Engine::Core::Graphics::Mesh* mesh, glm::vec3 position, glm::quat rotation);
	public:

		Shader* Shaders = NULL;

		OpenGLRenderer();
		~OpenGLRenderer();

		void begin();

		void submit(Engine::Core::Graphics::Mesh* mesh);
		void submit(Engine::Core::Entities::Entity* renderableEntity);

		void draw();
		void end();

		void dispose();

	};

} } }