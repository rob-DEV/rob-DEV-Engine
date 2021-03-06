#pragma once
#include "gl_include.h"
#include "../common/i_renderer.h"


#if(_ENGINE_RENDERER_OPENGL)
#include "shader.h"
#include "buffer/index_buffer.h"
#include "buffer/vertex_array.h"
#include "buffer/vertex_buffer.h"


namespace Engine { namespace Core { namespace Graphics { namespace OpenGL { 

	class OpenGLRenderer : public IRenderer
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
		void init() override;
		void submit(Engine::Core::Graphics::Mesh* mesh, glm::vec3 position, glm::quat rotation) override;
	public:

		Shader* Shaders = NULL;

		OpenGLRenderer();
		~OpenGLRenderer();

		void begin() override;

		void submit(Engine::Core::Graphics::Mesh* mesh) override;
		void submit(Engine::Core::Entities::Entity* renderableEntity) override;

		void draw() override;
		void end() override;

		void dispose() override;

	};

} } } }
#endif