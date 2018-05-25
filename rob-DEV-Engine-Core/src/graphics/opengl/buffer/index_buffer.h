#pragma once
#include "../gl_include.h"

#if(_ENGINE_RENDERER_OPENGL)

namespace Engine { namespace Core { namespace Graphics { namespace OpenGL { namespace Buffers {
	class IndexBufferObject
	{
	private:
		GLuint m_IBO;

	public:
		IndexBufferObject();
		~IndexBufferObject();

		void bind();
		void unbind();
		void del();
	};
} } } } }

#endif