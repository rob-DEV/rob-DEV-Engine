#include "index_buffer.h"

#if(_ENGINE_RENDERER_OPENGL)


namespace Engine { namespace Core { namespace Graphics { namespace OpenGL { namespace Buffers {

	IndexBufferObject::IndexBufferObject()
	{
		glGenBuffers(1, &m_IBO);
	}


	IndexBufferObject::~IndexBufferObject()
	{
		glDeleteBuffers(1, &m_IBO);
	}
	void IndexBufferObject::bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	}

	void IndexBufferObject::unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBufferObject::del()
	{
		glDeleteBuffers(1, &m_IBO);
	}

} } } } }

#endif