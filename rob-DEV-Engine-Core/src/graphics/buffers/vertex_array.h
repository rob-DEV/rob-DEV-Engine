#pragma once
#include <GL/glew.h>

namespace Engine { namespace Core { namespace Graphics { namespace Buffers {

	class VertexArray
	{
	private:
		GLuint m_VAO;

	public:
		VertexArray();
		~VertexArray();

		void bind();
		void unbind();
		void del();
	};

} } } }