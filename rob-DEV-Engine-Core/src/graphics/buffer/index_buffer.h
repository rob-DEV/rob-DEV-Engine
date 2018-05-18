#pragma once
#include <GL/glew.h>

namespace Engine { namespace Core { namespace Graphics { namespace Buffers {
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
} } } }
