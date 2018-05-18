#pragma once
#include <GL/glew.h>

namespace Engine { namespace Core { namespace Graphics { namespace Buffers {

	class VertexBufferObject
	{
	private:
		GLuint m_VBO;

	public:
		VertexBufferObject();
		~VertexBufferObject();

		void bind();
		void unbind();
		void del();
	};

} } } }