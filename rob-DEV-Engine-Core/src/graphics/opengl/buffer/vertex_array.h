#pragma once
#include "../gl_include.h"

#if(ENGINE_RENDERER_OPENGL)

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

#endif