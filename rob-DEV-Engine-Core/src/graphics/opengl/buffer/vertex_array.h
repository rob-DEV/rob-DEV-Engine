#pragma once
#include "../gl_include.h"

#if(_ENGINE_RENDERER_OPENGL)

namespace Engine { namespace Core { namespace Graphics { namespace OpenGL { namespace Buffers {

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

} } } } }

#endif