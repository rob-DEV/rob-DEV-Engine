#pragma once
#include "../gl_include.h"

#if(ENGINE_RENDERER_OPENGL)

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
#endif